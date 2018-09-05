#ifndef OCTOON_SCRIPT_COMPONENT_H_
#define OCTOON_SCRIPT_COMPONENT_H_

#include <octoon/game_component.h>

namespace octoon
{
	class OCTOON_EXPORT ScriptComponent final : public GameComponent
	{
		OctoonDeclareSubClass(ScriptComponent, GameComponent)
	public:
		ScriptComponent() noexcept;
		ScriptComponent(const GameObjectPtr& camera) noexcept;

		void setScript(const std::string& camera) noexcept;
		const std::string& getScript() const noexcept;

		octoon::GameComponentPtr clone() const noexcept override;

	private:
		void onActivate() noexcept override;
		void onDeactivate() noexcept override;

		void onFrameBegin() noexcept override;
		void onFrame() noexcept override;
		void onFrameEnd() noexcept override;

	private:
		ScriptComponent(const ScriptComponent&) = delete;
		ScriptComponent& operator=(const ScriptComponent&) = delete;

	private:
		std::string script_;
	};
}

#endif