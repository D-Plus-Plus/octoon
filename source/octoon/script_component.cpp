#include <octoon/script_component.h>
#include "script_context.h"

namespace octoon
{
	OctoonImplementSubClass(ScriptComponent, GameComponent, "ScriptComponent")

	ScriptComponent::ScriptComponent() noexcept
	{
	}

	ScriptComponent::ScriptComponent(std::string&& script) noexcept
	{
		this->setScript(std::move(script));
	}

	ScriptComponent::ScriptComponent(const std::string& script) noexcept
	{
		this->setScript(script);
	}

	void 
	ScriptComponent::setScript(std::string&& script) noexcept
	{
		script_ = std::move(script);
		this->updateScript();
	}

	void
	ScriptComponent::setScript(const std::string& script) noexcept
	{
		script_ = script;
		this->updateScript();
	}

	const std::string&
	ScriptComponent::getScript() const noexcept
	{
		return script_;
	}

	void
	ScriptComponent::onActivate() noexcept
	{
		this->updateScript();
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
		{
			js_getglobal(j, "OnUpdateBegin");
			js_pushnull(j);
			js_call(j, 0);
			js_pop(j, 1);
		}
	}

	void
	ScriptComponent::onFrame() noexcept
	{
		auto j = js_getstate();
		if (j)
		{
			js_getglobal(j, "OnUpdate");
			js_pushnull(j);
			js_call(j, 0);
			js_pop(j, 1);
		}
	}

	void 
	ScriptComponent::onFrameEnd() noexcept
	{
		auto j = js_getstate();
		if (j)
		{
			js_getglobal(j, "OnUpdateEnd");
			js_pushnull(j);
			js_call(j, 0);
			js_pop(j, 1);
		}
	}

	void 
	ScriptComponent::onGui() noexcept
	{
		auto j = js_getstate();
		if (j)
		{
			js_getglobal(j, "OnGui");
			js_pushnull(j);
			js_call(j, 0);
			js_pop(j, 1);
		}
	}

	void 
	ScriptComponent::updateScript() noexcept
	{
		if (script_.empty() || !this->getGameObject())
			return;

		auto j = js_getstate();
		if (j)
		{
			js_dostring(j, script_.c_str());

			js_getglobal(j, "OnUpdateBegin");
			js_getglobal(j, "OnUpdate");
			js_getglobal(j, "OnUpdateEnd");
			js_getglobal(j, "OnGui");

			if (!js_isundefined(j, -4))
				this->addComponentDispatch(GameDispatchType::FrameBegin);

			if (!js_isundefined(j, -3))
				this->addComponentDispatch(GameDispatchType::Frame);

			if (!js_isundefined(j, -2))
				this->addComponentDispatch(GameDispatchType::FrameEnd);

			if (!js_isundefined(j, -1))
				this->addComponentDispatch(GameDispatchType::Gui);

			js_pop(j, 4);
		}
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