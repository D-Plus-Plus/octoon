// +----------------------------------------------------------------------
// | Project : ray.
// | All rights reserved.
// +----------------------------------------------------------------------
// | Copyright (c) 2013-2016.
// +----------------------------------------------------------------------
// | * Redistribution and use of this software in source and binary forms,
// |   with or without modification, are permitted provided that the following
// |   conditions are met:
// |
// | * Redistributions of source code must retain the above
// |   copyright notice, this list of conditions and the
// |   following disclaimer.
// |
// | * Redistributions in binary form must reproduce the above
// |   copyright notice, this list of conditions and the
// |   following disclaimer in the documentation and/or other
// |   materials provided with the distribution.
// |
// | * Neither the name of the ray team, nor the names of its
// |   contributors may be used to endorse or promote products
// |   derived from this software without specific prior
// |   written permission of the ray team.
// |
// | THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// | "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// | LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// | A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// | OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// | SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// | LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// | DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// | THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// | (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// | OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// +----------------------------------------------------------------------
#if defined(_BUILD_PLATFORM_APPLE)
#include "nsgl_swapchain.h"

#include <Cocoa/Cocoa.h>

_NAME_BEGIN

__ImplementSubClass(NSGLSwapchain, GraphicsSwapchain, "NSGLSwapchain")

NSGLSwapchain* NSGLSwapchain::_swapchain = nullptr;

NSGLSwapchain::NSGLSwapchain() noexcept
	: _isActive(false)
	, _major(3)
	, _minor(3)
	, _context(0)
	, _pixelFormat(0)
{
}

NSGLSwapchain::NSGLSwapchain(GLuint major, GLuint minor) noexcept
	: _isActive(false)
	, _major(major)
	, _minor(minor)
	, _context(0)
	, _pixelFormat(0)
{
}

NSGLSwapchain::~NSGLSwapchain() noexcept
{
	this->close();
}

bool
NSGLSwapchain::setup(const GraphicsSwapchainDesc& swapchainDesc) noexcept
{
	assert(swapchainDesc.getWindHandle());

	if (!initSurface(swapchainDesc))
		return false;

	if (!initPixelFormat(swapchainDesc))
		return false;

	if (!initSwapchain(swapchainDesc))
		return false;

	_swapchainDesc = swapchainDesc;
	return true;
}

void
NSGLSwapchain::close() noexcept
{
	this->setActive(false);

	if (this->_pixelFormat != nil)
	{
		NSOpenGLPixelFormat* pfd = (NSOpenGLPixelFormat*)this->_pixelFormat;
		[pfd release];
		this->_pixelFormat = nil;
	}

	if (this->_context != nil)
	{
		NSOpenGLContext* context = (NSOpenGLContext*)this->_context;
		[context release];
		this->_context = nil;
	}
}

void
NSGLSwapchain::setActive(bool active) noexcept
{
	if (_isActive != active)
	{
		if (active)
		{
			if (_swapchain)
				_swapchain->setActive(false);

			NSOpenGLContext* context = (NSOpenGLContext*)this->_context;
			[context makeCurrentContext];

			_swapchain = this;
		}
		else
		{
			[NSOpenGLContext clearCurrentContext];

			if (_swapchain == this)
				_swapchain = nullptr;
		}

		_isActive = active;
	}
}

bool
NSGLSwapchain::getActive() const noexcept
{
	return _isActive;
}

void
NSGLSwapchain::setWindowResolution(std::uint32_t w, std::uint32_t h) noexcept
{
	_swapchainDesc.setWidth(w);
	_swapchainDesc.setHeight(h);
}

void
NSGLSwapchain::getWindowResolution(std::uint32_t& w, std::uint32_t& h) const noexcept
{
	w = _swapchainDesc.getWidth();
	h = _swapchainDesc.getHeight();
}

void
NSGLSwapchain::setSwapInterval(GraphicsSwapInterval interval) noexcept
{
	assert(interval >= GraphicsSwapInterval::GraphicsSwapIntervalBeginRange && interval <= GraphicsSwapIntervalEndRange);

	GLint sync = interval;
	NSOpenGLContext* context = (NSOpenGLContext*)this->_context;
	[context setValues:&sync forParameter:NSOpenGLCPSwapInterval];

	_swapchainDesc.setSwapInterval(interval);
}

GraphicsSwapInterval
NSGLSwapchain::getSwapInterval() const noexcept
{
	return _swapchainDesc.getSwapInterval();
}

void
NSGLSwapchain::present() noexcept
{
	NSOpenGLContext* context = (NSOpenGLContext*)this->_context;
	[context flushBuffer];
}

bool
NSGLSwapchain::initSurface(const GraphicsSwapchainDesc& swapchainDesc)
{
	return true;
}

bool
NSGLSwapchain::initPixelFormat(const GraphicsSwapchainDesc& swapchainDesc) noexcept
{
	std::size_t index = 0;
	NSOpenGLPixelFormatAttribute attributes[40];

	if (swapchainDesc.getImageNums() != 1 && swapchainDesc.getImageNums() != 2)
	{
		GL_PLATFORM_LOG("Invalid image number");
		return false;
	}

	attributes[index++] = NSOpenGLPFAAccelerated;
	attributes[index++] = (NSOpenGLPixelFormatAttribute)true;

	attributes[index++] = NSOpenGLPFAClosestPolicy;

	if (swapchainDesc.getImageNums() == 2)
	{
		attributes[index++] = NSOpenGLPFADoubleBuffer;
		attributes[index++] = (NSOpenGLPixelFormatAttribute)true;
	}

	auto deviceType = this->getDevice()->getGraphicsDeviceDesc().getDeviceType();
	if (deviceType == GraphicsDeviceType::GraphicsDeviceTypeOpenGLCore)
	{
		attributes[index++] = NSOpenGLPFAOpenGLProfile;
		attributes[index++] = NSOpenGLProfileVersion4_1Core;
	}
	else
	{
		attributes[index++] = NSOpenGLPFAOpenGLProfile;
		attributes[index++] = NSOpenGLProfileVersion3_2Core;
	}

	auto colorFormat = swapchainDesc.getColorFormat();
	if (colorFormat == GraphicsFormat::GraphicsFormatB8G8R8A8UNorm)
	{
		attributes[index++] = NSOpenGLPFAColorSize;
		attributes[index++] = (NSOpenGLPixelFormatAttribute)32;
	}
	else
	{
		GL_PLATFORM_LOG("Cannot support color format");
		return false;
	}

	auto depthStencilFormat = swapchainDesc.getDepthStencilFormat();
	if (depthStencilFormat == GraphicsFormat::GraphicsFormatD16UNorm)
	{
		attributes[index++] = NSOpenGLPFADepthSize;
		attributes[index++] = (NSOpenGLPixelFormatAttribute)16;
		attributes[index++] = NSOpenGLPFAStencilSize;
		attributes[index++] = (NSOpenGLPixelFormatAttribute)0;
	}
	else if (depthStencilFormat == GraphicsFormat::GraphicsFormatX8_D24UNormPack32)
	{
		attributes[index++] = NSOpenGLPFADepthSize;
		attributes[index++] = (NSOpenGLPixelFormatAttribute)24;
		attributes[index++] = NSOpenGLPFAStencilSize;
		attributes[index++] = (NSOpenGLPixelFormatAttribute)0;
	}
	else if (depthStencilFormat == GraphicsFormat::GraphicsFormatD32_SFLOAT)
	{
		attributes[index++] = NSOpenGLPFADepthSize;
		attributes[index++] = (NSOpenGLPixelFormatAttribute)32;
		attributes[index++] = NSOpenGLPFAStencilSize;
		attributes[index++] = (NSOpenGLPixelFormatAttribute)0;
	}
	else if (depthStencilFormat == GraphicsFormat::GraphicsFormatD16UNorm_S8UInt)
	{
		attributes[index++] = NSOpenGLPFADepthSize;
		attributes[index++] = (NSOpenGLPixelFormatAttribute)16;
		attributes[index++] = NSOpenGLPFAStencilSize;
		attributes[index++] = (NSOpenGLPixelFormatAttribute)8;
	}
	else if (depthStencilFormat == GraphicsFormat::GraphicsFormatD24UNorm_S8UInt)
	{
		attributes[index++] = NSOpenGLPFADepthSize;
		attributes[index++] = (NSOpenGLPixelFormatAttribute)24;
		attributes[index++] = NSOpenGLPFAStencilSize;
		attributes[index++] = (NSOpenGLPixelFormatAttribute)8;
	}
	else if (depthStencilFormat == GraphicsFormat::GraphicsFormatD32_SFLOAT_S8UInt)
	{
		attributes[index++] = NSOpenGLPFADepthSize;
		attributes[index++] = (NSOpenGLPixelFormatAttribute)32;
		attributes[index++] = NSOpenGLPFAStencilSize;
		attributes[index++] = (NSOpenGLPixelFormatAttribute)8;
	}
	else
	{
		GL_PLATFORM_LOG("Cannot support depth stencil format");
		return false;
	}

    this->_pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attributes];
	if (this->_pixelFormat == nil)
    {
        GL_PLATFORM_LOG("NSGL: Failed to find a suitable pixel format");
        return false;
    }

	return true;
}

bool
NSGLSwapchain::initSwapchain(const GraphicsSwapchainDesc& swapchainDesc) noexcept
{
	NSWindow* window = (NSWindow*)swapchainDesc.getWindHandle();
	if (window == nil)
	{
        GL_PLATFORM_LOG("NSGL: Empty window handle.");
        return false;
	}

	NSOpenGLPixelFormat* pfd = (NSOpenGLPixelFormat*)this->_pixelFormat;
	if (pfd == nil)
	{
        GL_PLATFORM_LOG("NSGL: Failed to initialize GL PixelFormat.");
        return false;
	}

    NSOpenGLContext* share = NULL;
    NSOpenGLContext* context = [[NSOpenGLContext alloc] initWithFormat:pfd shareContext:share];
	if (context == nil)
	{
        GL_PLATFORM_LOG("NSGL: Failed to initialize GL context.");
        return false;
	}

	[context setView:[window contentView]];

	this->_context = context;

	this->setActive(true);
	this->setSwapInterval(swapchainDesc.getSwapInterval());
	this->setActive(false);

	return true;
}

const GraphicsSwapchainDesc&
NSGLSwapchain::getGraphicsSwapchainDesc() const noexcept
{
	return _swapchainDesc;
}

void
NSGLSwapchain::setDevice(GraphicsDevicePtr device) noexcept
{
	_device = device;
}

GraphicsDevicePtr
NSGLSwapchain::getDevice() noexcept
{
	return _device.lock();
}

_NAME_END

#endif