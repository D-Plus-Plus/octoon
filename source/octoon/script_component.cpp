#include <octoon/script_component.h>
#include "script_context.h"

extern "C" {
	#include <jsi.h>
	#include <jsparse.h>
	#include <jscompile.h>
}

namespace octoon
{
	OctoonImplementSubClass(ScriptComponent, GameComponent, "ScriptComponent")

	ScriptComponent::ScriptComponent() noexcept
	{
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
			js_newscript(j, js_onUpdateBegin_, j->GE);

			js_pushundefined(j);
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
			js_newscript(j, js_onUpdate_, j->GE);

			js_pushundefined(j);
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
			js_newscript(j, js_onUpdateEnd_, j->GE);

			js_pushundefined(j);
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
			js_newscript(j, js_onGui_, j->GE);

			js_pushundefined(j);
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
			std::string classname_ = this->type_name() + std::to_string((std::uintptr_t)this);
			std::string classname_init_ = "var " + classname_ + "= new main()";
			
			js_dostring(j, script_.c_str());
			js_dostring(j, classname_init_.c_str());

			js_getglobal(j, classname_.c_str());
			if (js_isobject(j, -1))
			{
				if (js_hasproperty(j, -1, "OnUpdateBegin"))
				{
					this->addComponentDispatch(GameDispatchType::FrameBegin);

					std::string method = classname_ + ".OnUpdateBegin()";
					js_onUpdateBegin_ = jsC_compile(j, jsP_parse(j, "[string]", method.c_str()));
					jsP_freeparse(j);
					js_pop(j, 1);
				}

				if (js_hasproperty(j, -1, "OnUpdate"))
				{
					this->addComponentDispatch(GameDispatchType::Frame);

					std::string method = classname_ + ".OnUpdate()";
					js_onUpdate_ = jsC_compile(j, jsP_parse(j, "[string]", method.c_str()));
					jsP_freeparse(j);
					js_pop(j, 1);
				}

				if (js_hasproperty(j, -1, "OnUpdateEnd"))
				{
					this->addComponentDispatch(GameDispatchType::FrameEnd);

					std::string method = classname_ + ".OnUpdateEnd()";
					js_onUpdateEnd_ = jsC_compile(j, jsP_parse(j, "[string]", method.c_str()));
					jsP_freeparse(j);
					js_pop(j, 1);
				}

				if (js_hasproperty(j, -1, "OnGui"))
				{
					this->addComponentDispatch(GameDispatchType::Gui);

					std::string method = classname_ + ".OnGui()";
					js_onGui_ = jsC_compile(j, jsP_parse(j, "[string]", method.c_str()));
					jsP_freeparse(j);
					js_pop(j, 1);
				}
			}

			js_pop(j, 1);
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