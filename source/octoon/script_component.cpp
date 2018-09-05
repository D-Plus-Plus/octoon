#include <octoon/script_component.h>
#include "script_context.h"

namespace octoon
{
	OctoonImplementSubClass(ScriptComponent, GameComponent, "ScriptComponent")

	ScriptComponent::ScriptComponent() noexcept
	{
		classname_ = this->type_name();
		classname_init_ = "var " + classname_ + "= new main()";
		classname_onFrameBegin_ = classname_ + ".OnUpdateBegin()";
		classname_onFrame_ = classname_ + ".OnUpdate()";
		classname_onFrameEnd_ = classname_ + ".OnUpdateEnd()";
		classname_onGui_ = classname_ + ".OnGui()";
	}

	ScriptComponent::ScriptComponent(std::string&& script) noexcept
		: ScriptComponent()
	{
		this->setScript(std::move(script));
	}

	ScriptComponent::ScriptComponent(const std::string& script) noexcept
		: ScriptComponent()
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
			js_dostring(j, classname_onFrameBegin_.c_str());
		}
	}

	void
	ScriptComponent::onFrame() noexcept
	{
		auto j = js_getstate();
		if (j)
		{
			js_dostring(j, classname_onFrame_.c_str());
		}
	}

	void
	ScriptComponent::onFrameEnd() noexcept
	{
		auto j = js_getstate();
		if (j)
		{
			js_dostring(j, classname_onFrameEnd_.c_str());
		}
	}

	void
	ScriptComponent::onGui() noexcept
	{
		auto j = js_getstate();
		if (j)
		{
			js_dostring(j, classname_onGui_.c_str());
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
			js_dostring(j, classname_init_.c_str());

			js_getglobal(j, classname_.c_str());
			if (js_isobject(j, -1))
			{
				if (js_hasproperty(j, -1, "OnUpdateBegin"))
				{
					this->addComponentDispatch(GameDispatchType::FrameBegin);
					js_pop(j, 1);
				}

				if (js_hasproperty(j, -1, "OnUpdate"))
				{
					this->addComponentDispatch(GameDispatchType::Frame);
					js_pop(j, 1);
				}

				if (js_hasproperty(j, -1, "OnUpdateEnd"))
				{
					this->addComponentDispatch(GameDispatchType::FrameEnd);
					js_pop(j, 1);
				}

				if (js_hasproperty(j, -1, "OnGui"))
				{
					this->addComponentDispatch(GameDispatchType::Gui);
					js_pop(j, 1);
				}
			}
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