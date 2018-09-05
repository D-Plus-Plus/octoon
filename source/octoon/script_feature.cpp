#if defined(OCTOON_FEATURE_SCRIPT_ENABLE)
#include <octoon/script_feature.h>
#include <octoon/runtime/except.h>
#include "script_context.h"
#include "script_binder_console.h"
#include "script_binder_io.h"

namespace octoon
{
	OctoonImplementSubClass(ScriptFeature, GameFeature, "ScriptFeature")

	ScriptFeature::ScriptFeature() noexcept
		: state_(nullptr)
	{
	}

	ScriptFeature::~ScriptFeature() noexcept
	{
	}

	void
	ScriptFeature::onActivate() except
	{
		assert(state_ == nullptr);

		state_ = js_newstate(0, 0, JS_STRICT);
		if (!state_)
			throw runtime::runtime_error::create("js_newstate() failed");

		binders.push_back(std::make_unique<ScriptBinderIo>());
		binders.push_back(std::make_unique<ScriptBinderConsole>());

		for (auto& it : binders)
			it->bind(state_);
	}

	void
	ScriptFeature::onDeactivate() noexcept
	{
		if (state_)
		{
			js_freestate(state_);
			state_ = nullptr;
		}

		binders.clear();
	}

	void
	ScriptFeature::onFrameBegin() noexcept
	{
		js_setstate(state_);
	}

	void
	ScriptFeature::onFrame() noexcept
	{
	}

	void
	ScriptFeature::onFrameEnd() noexcept
	{
	}
}
#endif