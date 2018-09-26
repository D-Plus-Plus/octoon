#include "camera_controller.h"

#include <octoon/octoon.h>
#include <octoon/editor_camera_component.h>

namespace octoon
{
	namespace editor
	{
		OctoonImplementSubClass(CameraController, GameComponent, "CameraController")

		CameraController::CameraController() noexcept
		{
		}

		CameraController::~CameraController() noexcept
		{
		}

		void
		CameraController::onActivate() noexcept
		{
			camera_ = GameObject::create("MainCamera");
			camera_->getComponent<TransformComponent>()->setTranslate(math::float3(0, 0, -20));
			camera_->addComponent<EditorCameraComponent>();

			auto camera = camera_->addComponent<PerspectiveCameraComponent>(45.0f);
			camera->setCameraType(video::CameraType::Custom);
			camera->setClearColor(octoon::math::float4(0.1f, 0.1f, 0.1f, 1.0f));

			this->sendMessage("editor:camera:set", camera_.get());
			this->addMessageListener("editor:camera:get", std::bind(&CameraController::onGetCamera, this));
		}

		void
		CameraController::onDeactivate() noexcept
		{
			camera_.reset();

			this->sendMessage("editor:camera:set", nullptr);
			this->removeMessageListener("editor:camera:get", std::bind(&CameraController::onGetCamera, this));
		}

		void 
		CameraController::onGetCamera() noexcept
		{
			this->sendMessage("editor:camera:set", camera_.get());
		}

		GameComponentPtr 
		CameraController::clone() const noexcept
		{
			return std::make_shared<CameraController>();
		}
	}
}