#include <octoon/animation_transform_component.h>

#include <octoon/game_app.h>
#include <octoon/transform_component.h>
#include <octoon/camera_component.h>
#include <octoon/timer_feature.h>

namespace octoon
{
	OctoonImplementSubClass(AnimationTransformComponent, GameComponent, "AnimTransformComponent")

	AnimationTransformComponent::AnimationTransformComponent() noexcept
	{
	}

	AnimationTransformComponent::~AnimationTransformComponent() noexcept
	{
	}

	void
	AnimationTransformComponent::setScale(model::Keyframes<math::float3>&& frames) noexcept
	{
		scale_.frames = std::move(frames);
	}

	void
	AnimationTransformComponent::setAnchorPoint(model::Keyframes<math::float3>&& frames) noexcept
	{
		anchor_.frames = std::move(frames);
	}

	void
	AnimationTransformComponent::setTranslate(model::Keyframes<math::float3>&& frames) noexcept
	{
		pos_.frames = std::move(frames);
	}

	void
	AnimationTransformComponent::setOrientation(model::Keyframes<math::float3>&& frames) noexcept
	{
		orientation_.frames = std::move(frames);
	}

	void
	AnimationTransformComponent::setRotationX(model::Keyframes<math::float1>&& frames) noexcept
	{
		rx_.frames = std::move(frames);
	}

	void
	AnimationTransformComponent::setRotationY(model::Keyframes<math::float1>&& frames) noexcept
	{
		ry_.frames = std::move(frames);
	}

	void
	AnimationTransformComponent::setRotationZ(model::Keyframes<math::float1>&& frames) noexcept
	{
		rz_.frames = std::move(frames);
	}

	void
	AnimationTransformComponent::setScale(const model::Keyframes<math::float3>& frames) noexcept
	{
		scale_.frames = frames;
	}

	void
	AnimationTransformComponent::setAnchorPoint(const model::Keyframes<math::float3>& frames) noexcept
	{
		anchor_.frames = frames;
	}

	void
	AnimationTransformComponent::setTranslate(const model::Keyframes<math::float3>& frames) noexcept
	{
		pos_.frames = frames;
	}

	void
	AnimationTransformComponent::setOrientation(const model::Keyframes<math::float3>& frames) noexcept
	{
		orientation_.frames = frames;
	}

	void
	AnimationTransformComponent::setRotationX(const model::Keyframes<math::float1>& frames) noexcept
	{
		rx_.frames = frames;
	}

	void
	AnimationTransformComponent::setRotationY(const model::Keyframes<math::float1>& frames) noexcept
	{
		ry_.frames = frames;
	}

	void
	AnimationTransformComponent::setRotationZ(const model::Keyframes<math::float1>& frames) noexcept
	{
		rz_.frames = frames;
	}

	void
	AnimationTransformComponent::setScale(model::AnimationCurve<math::float3>&& frames) noexcept
	{
		scale_ = std::move(frames);
	}

	void
	AnimationTransformComponent::setAnchorPoint(model::AnimationCurve<math::float3>&& frames) noexcept
	{
		anchor_ = std::move(frames);
	}

	void
	AnimationTransformComponent::setTranslate(model::AnimationCurve<math::float3>&& frames) noexcept
	{
		pos_ = std::move(frames);
	}

	void
	AnimationTransformComponent::setOrientation(model::AnimationCurve<math::float3>&& frames) noexcept
	{
		orientation_ = std::move(frames);
	}

	void
	AnimationTransformComponent::setRotationX(model::AnimationCurve<math::float1>&& frames) noexcept
	{
		rx_ = std::move(frames);
	}

	void
	AnimationTransformComponent::setRotationY(model::AnimationCurve<math::float1>&& frames) noexcept
	{
		ry_ = std::move(frames);
	}

	void
	AnimationTransformComponent::setRotationZ(model::AnimationCurve<math::float1>&& frames) noexcept
	{
		rz_ = std::move(frames);
	}

	void
	AnimationTransformComponent::setScale(const model::AnimationCurve<math::float3>& frames) noexcept
	{
		scale_ = frames;
	}

	void
	AnimationTransformComponent::setAnchorPoint(const model::AnimationCurve<math::float3>& frames) noexcept
	{
		anchor_ = frames;
	}

	void
	AnimationTransformComponent::setTranslate(const model::AnimationCurve<math::float3>& frames) noexcept
	{
		pos_ = frames;
	}

	void
	AnimationTransformComponent::setOrientation(const model::AnimationCurve<math::float3>& frames) noexcept
	{
		orientation_ = frames;
	}

	void
	AnimationTransformComponent::setRotationX(const model::AnimationCurve<math::float1>& frames) noexcept
	{
		rx_ = frames;
	}

	void
	AnimationTransformComponent::setRotationY(const model::AnimationCurve<math::float1>& frames) noexcept
	{
		ry_ = frames;
	}

	void
	AnimationTransformComponent::setRotationZ(const model::AnimationCurve<math::float1>& frames) noexcept
	{
		rz_ = frames;
	}
	
	GameComponentPtr
	AnimationTransformComponent::clone() const noexcept
	{
		auto instance = std::make_shared<AnimationTransformComponent>();
		instance->setName(instance->getName());
		instance->setScale(this->pos_);
		instance->setOrientation(this->scale_);
		instance->setTranslate(this->orientation_);
		instance->setAnchorPoint(this->anchor_);
		instance->setRotationX(this->rx_);
		instance->setRotationY(this->ry_);
		instance->setRotationZ(this->rz_);

		return instance;
	}

	void
	AnimationTransformComponent::onActivate()
	{
		this->addComponentDispatch(GameDispatchType::Frame);
	}

	void
	AnimationTransformComponent::onDeactivate() noexcept
	{
		this->removeComponentDispatchs();
	}

	void 
	AnimationTransformComponent::onFrame() except
	{
		auto transform = this->getGameObject()->getComponent<TransformComponent>();
		if (transform)
		{
			float step = 1.0f / 60.0f;
			step = GameApp::instance()->getFeature<TimerFeature>()->delta() * 23.9f;

			if (!pos_.empty())
				transform->setTranslate(pos_.evaluate(step));

			if (!scale_.empty())
				transform->setScale(scale_.evaluate(step));

			math::float3 rotation = math::float3::Zero;
			if (!rx_.empty()) rotation.x += rx_.evaluate(step);
			if (!ry_.empty()) rotation.y += ry_.evaluate(step);
			if (!rz_.empty()) rotation.z += rz_.evaluate(step);
			if (!orientation_.empty()) rotation += orientation_.evaluate(step);

			math::Quaternion quat = math::Quaternion::Zero;
			if (rotation.x != 0.0f) quat = math::cross(quat, math::Quaternion(math::float3::UnitX, rotation.x));
			if (rotation.y != 0.0f) quat = math::cross(quat, math::Quaternion(math::float3::UnitY, rotation.y));
			if (rotation.z != 0.0f) quat = math::cross(quat, math::Quaternion(math::float3::UnitZ, rotation.z));

			if (!anchor_.empty())
			{
				auto hasCamera = this->getGameObject()->getComponent<CameraComponent>();
				if (hasCamera)
				{
					auto target = anchor_.evaluate(step);
					auto camera = transform->getTranslate();
					auto angle = math::normalize(target - camera);

					quat = math::cross(quat, math::Quaternion(math::float3(angle.y, angle.x, 0.0f)));
				}
				else
				{
					if (pos_.empty())
						transform->setTranslate(math::rotate(quat, -anchor_.evaluate(step)) * transform->getScale());
					else
						transform->setTranslateAccum(math::rotate(quat, -anchor_.evaluate(step)) * transform->getScale());
				}
			}

			transform->setQuaternion(quat);
		}
	}
}