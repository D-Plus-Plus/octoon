#include "camera_window.h"

#include <octoon/octoon.h>
#include <octoon/ui/imgui.h>

namespace octoon
{
	namespace editor
	{
		OctoonImplementSubClass(CameraWindow, GameComponent, "CameraWindow")

		CameraWindow::CameraWindow() noexcept
			: framebufferSizeW_(0)
			, framebufferSizeH_(0)
			, isShowedCameraWindow_(true)
			, selectedCamera_(nullptr)
		{
		}

		CameraWindow::~CameraWindow() noexcept
		{
		}

		void
		CameraWindow::onActivate() noexcept
		{
			this->addComponentDispatch(GameDispatchType::Gui);
			this->addMessageListener("editor:camera:set", std::bind(&CameraWindow::onCameraSelected, this, std::placeholders::_1));
			this->sendMessage("editor:camera:get", nullptr);
		}

		void
		CameraWindow::onDeactivate() noexcept
		{
			this->removeComponentDispatchs();
			this->removeMessageListener("editor:camera:set", std::bind(&CameraWindow::onCameraSelected, this, std::placeholders::_1));
		}

		void 
		CameraWindow::onGui() noexcept
		{
			if (imgui::beginDock("Camera", &isShowedCameraWindow_, imgui::GuiWindowFlagBits::AlwaysUseWindowPaddingBit | imgui::GuiWindowFlagBits::NoScrollWithMouseBit))
			{
				imgui::setScrollY(imgui::getStyleDefault().WindowPadding.y);

				if (selectedCamera_)
				{
					auto cameraComponent = selectedCamera_->getComponent<CameraComponent>();

					auto size = imgui::getWindowSize();

					if (framebufferSizeW_ != size.x || framebufferSizeH_ != size.y)
					{
#if defined(OCTOON_BUILD_PLATFORM_EMSCRIPTEN)
						selectedCamera_->getComponent<CameraComponent>()->setupFramebuffers((std::uint32_t)size.x, (std::uint32_t)size.y);
#else
						selectedCamera_->getComponent<CameraComponent>()->setupFramebuffers((std::uint32_t)size.x, (std::uint32_t)size.y, 4);
						selectedCamera_->getComponent<CameraComponent>()->setupSwapFramebuffers((std::uint32_t)size.x, (std::uint32_t)size.y);
#endif
						framebufferSizeW_ = (std::uint32_t)size.x;
						framebufferSizeH_ = (std::uint32_t)size.y;
					}

#if defined(OCTOON_BUILD_PLATFORM_EMSCRIPTEN)
					auto framebuffer = cameraComponent->getFramebuffer();
#else
					auto framebuffer = cameraComponent->getSwapFramebuffer();
#endif
					if (framebuffer)
					{
						auto texture = framebuffer->getGraphicsFramebufferDesc().getColorAttachment().getBindingTexture();
						if (texture)
							imgui::image(texture.get(), size, math::float2::UnitY, math::float2::UnitX);
					}
				}

				imgui::endDock();
			}
		}

		GameComponentPtr 
		CameraWindow::clone() const noexcept
		{
			return std::make_shared<CameraWindow>();
		}

		void
		CameraWindow::onCameraSelected(const runtime::any& data) noexcept
		{
			try
			{
				selectedCamera_ = runtime::any_cast<GameObject*>(data);
			}
			catch (...)
			{
				selectedCamera_ = nullptr;
			}				
		}
	}
}