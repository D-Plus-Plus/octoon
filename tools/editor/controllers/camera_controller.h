#ifndef OCTOON_EDITOR_CAMERA_CONTROLLER_H_
#define OCTOON_EDITOR_CAMERA_CONTROLLER_H_

#include <octoon/game_component.h>

namespace octoon
{
	namespace editor
	{
		class CameraController : public GameComponent
		{
			OctoonDeclareSubClass(CameraController, GameComponent)
		public:
			CameraController() noexcept;
			~CameraController() noexcept;

			virtual GameComponentPtr clone() const noexcept override;

		private:
			void onActivate() noexcept override;
			void onDeactivate() noexcept override;

			void onGetCamera() noexcept;

		private:
			GameObjectPtr camera_;
		};
	}
}

#endif