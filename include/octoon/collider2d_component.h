#ifndef OCTOON_COLLIDER2D_COMPONENT_H_
#define OCTOON_COLLIDER2D_COMPONENT_H_

#include <memory>
#include <octoon/game_component.h>
#include <octoon/math/math.h>
#include <octoon/physics_material2d.h>


class b2Body;
class b2Fixture;

namespace octoon
{
    class OCTOON_EXPORT Collider2D : public GameComponent
	{
        OctoonDeclareSubInterface(Collider2D, GameComponent)
        public:
            Collider2D() noexcept;
            ~Collider2D();

            void setBounciness(float b) noexcept;
            float getBounciness() const noexcept;

            void setDensity(float d) noexcept;
            float getDensity() const noexcept;

            void setFriction(float f) noexcept;
            float getFriction() const noexcept;

        protected:
            virtual void onCollisionChange() = 0;
            virtual void onCollisionEnter() = 0;
            virtual void onCollisionExit() = 0;
            virtual void onCollisionStay() = 0;
        
        protected:
            b2Fixture *collider;

        private:
            float bounciness; // Get the bounciness used by the collider.
            float density; // The density of the collider used to calculate its mass (when auto mass is enabled).
            float friction; // Get the friction used by the collider.
            std::shared_ptr<PhysicsMaterial2D> shared_material; // The PhysicsMaterial2D that is applied to this collider.
            friend class Rigidbody2D;
    };
}


#endif // OCTOON_COLLIDER2D_COMPONENT_H_