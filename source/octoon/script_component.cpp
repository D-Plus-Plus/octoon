#include <octoon/script_component.h>

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
		onUpdateBegin_();
	}

	void
	ScriptComponent::onFrame() noexcept
	{
		onUpdate_();
	}

	void
	ScriptComponent::onFrameEnd() noexcept
	{
		onUpdateEnd_();
	}

	void
	ScriptComponent::onGui() noexcept
	{
		onGui_();
	}

	void
	ScriptComponent::updateScript() noexcept
	{
		if (script_.empty() || !this->getGameObject())
			return;

		scriptEnv_ = std::make_shared<script::ScriptEnv>();
		scriptEnv_->doString(script_.c_str());
		scriptEnv_->get("OnUpdateBegin", onUpdateBegin_);
		scriptEnv_->get("OnUpdate", onUpdate_);
		scriptEnv_->get("OnUpdateEnd", onUpdateEnd_);
		scriptEnv_->get("OnGui", onGui_);

		if (onUpdateBegin_)
			this->addComponentDispatch(GameDispatchType::FrameBegin);

		if (onUpdate_)
			this->addComponentDispatch(GameDispatchType::Frame);

		if (onUpdateEnd_)
			this->addComponentDispatch(GameDispatchType::FrameEnd);

		if (onGui_)
			this->addComponentDispatch(GameDispatchType::Gui);
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