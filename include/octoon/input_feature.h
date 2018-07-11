#ifndef OCTOON_INPUT_FEATURE_H_
#define OCTOON_INPUT_FEATURE_H_

#include <octoon/game_feature.h>
#include <octoon/input/iinput.h>

namespace octoon
{
	class OCTOON_EXPORT InputFeature final : public GameFeature
	{
		OctoonDeclareSubClass(InputFeature, GameFeature)
	public:
		InputFeature() noexcept;
		InputFeature(input::WindHandle hwnd) noexcept;
		virtual ~InputFeature() noexcept;

		const input::IInputPtr& getInput() const noexcept;

	private:
		virtual void onActivate() except override;
		virtual void onDeactivate() noexcept override;

		virtual void onInputEvent(const runtime::any& data) noexcept;

		virtual void onReset() noexcept override;

		virtual void onFrameBegin() noexcept override;
		virtual void onFrameEnd() noexcept override;

	private:
		InputFeature(const InputFeature&) = delete;
		InputFeature& operator=(const InputFeature&) = delete;

	private:
		input::IInputPtr input_;
		input::WindHandle window_;
	};
}

#endif