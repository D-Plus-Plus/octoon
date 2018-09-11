#ifndef OCTOON_SCRIPT_FEATURE_H_
#define OCTOON_SCRIPT_FEATURE_H_

#include <octoon/game_feature.h>

namespace octoon
{
	class OCTOON_EXPORT ScriptFeature final : public GameFeature
	{
		OctoonDeclareSubClass(ScriptFeature, GameFeature)
	public:
		ScriptFeature() noexcept;
		~ScriptFeature() noexcept;

	private:
		void onActivate() except override;
		void onDeactivate() noexcept override;

		void onFrameBegin() noexcept override;
		void onFrame() noexcept override;
		void onFrameEnd() noexcept override;
	};
}

#endif