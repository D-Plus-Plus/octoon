#if defined(OCTOON_FEATURE_SCRIPT_ENABLE)
#include <octoon/script_feature.h>

namespace octoon
{
	OctoonImplementSubClass(ScriptFeature, GameFeature, "ScriptFeature")

	ScriptFeature::ScriptFeature() noexcept
	{
	}

	ScriptFeature::~ScriptFeature() noexcept
	{
	}

	void
	ScriptFeature::onActivate() except
	{
	}

	void
	ScriptFeature::onDeactivate() noexcept
	{
	}

	void
	ScriptFeature::onFrameBegin() noexcept
	{
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