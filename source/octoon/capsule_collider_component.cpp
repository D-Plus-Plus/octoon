#include <octoon/capsule_collider_component.h>
#include <octoon/rigidbody_component.h>
#include <octoon/runtime/except.h>
#include <PxPhysicsAPI.h>

namespace octoon
{
    OctoonImplementSubClass(CapsuleCollider, Collider, "CapsuleCollider")

    CapsuleCollider::CapsuleCollider() noexcept
		: radius(0.5f), halfHeight(1.0f)
    {
    }

	CapsuleCollider::CapsuleCollider(float r, float half_h) noexcept
		: radius(r), halfHeight(half_h)
	{
	}

    CapsuleCollider::~CapsuleCollider()
    {
    }

    GameComponentPtr CapsuleCollider::clone() const noexcept
    {
        return std::make_shared<CapsuleCollider>();
    }

	void CapsuleCollider::setRadius(float r) except
	{
		radius = r;
		if (shape)
		{
			physx::PxCapsuleGeometry geometry(radius, halfHeight);
			shape->setGeometry(geometry);
		}
	}

	float CapsuleCollider::getRadius() const except
	{
		return radius;
	}

	void CapsuleCollider::setHalfHeight(float h) except
	{
		halfHeight = h;
		if (shape)
		{
			physx::PxCapsuleGeometry geometry(radius, halfHeight);
			shape->setGeometry(geometry);
		}
	}

	float CapsuleCollider::getHalfHeight() const except
	{
		return halfHeight;
	}

    void CapsuleCollider::onAttach() except
    {
		buildCollider();
    }

    void CapsuleCollider::onDetach() noexcept
    {
		releaseCollider();
    }

    void CapsuleCollider::onAttachComponent(const GameComponentPtr& component) except
    {
    }

    void CapsuleCollider::onDetachComponent(const GameComponentPtr& component) noexcept
    {
    }

	void CapsuleCollider::buildCollider() except
	{
		auto physics_feature = GameApp::instance()->getFeature<PhysicsFeature>();
		physx::PxCapsuleGeometry geometry(radius, halfHeight);
		shape = physics_feature->getSDK()->createShape(geometry, *this->shared_material->getMaterial()); // reference count is 1
		if (!shape)
			runtime::runtime_error::create("create shape failed!");
	}

	void CapsuleCollider::releaseCollider() except
	{
		shape->release();
		shape = nullptr;
	}
}