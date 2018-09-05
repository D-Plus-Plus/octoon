#include <octoon/script_component.h>
#include "script_context.h"

namespace octoon
{
	OctoonImplementSubClass(ScriptComponent, GameComponent, "ScriptComponent")

	ScriptComponent::ScriptComponent() noexcept
		: script_(R"(console.count("count"))")
	{
	}

	void
	ScriptComponent::setScript(const std::string& script) noexcept
	{
		script_ = script;
	}

	const std::string&
	ScriptComponent::getScript() const noexcept
	{
		return script_;
	}

	void
	ScriptComponent::onActivate() noexcept
	{
		this->addComponentDispatch(GameDispatchType::FrameBegin);
	}

	void
	ScriptComponent::onDeactivate() noexcept
	{
		this->removeComponentDispatchs();
	}

	void
	ScriptComponent::onFrameBegin() noexcept
	{
		auto j = js_getstate();
		if (j)
			js_dostring(j, script_.c_str());
	}

	void
	ScriptComponent::onFrame() noexcept
	{
	}

	void 
	ScriptComponent::onFrameEnd() noexcept
	{
	}

	GameComponentPtr
	ScriptComponent::clone() const noexcept
	{
		auto instance = std::make_shared<ScriptComponent>();
		instance->setName(this->getName());
		instance->setScript(this->getScript());
		return instance;
	}
}