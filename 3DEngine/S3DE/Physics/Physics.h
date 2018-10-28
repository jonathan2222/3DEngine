#ifndef PHYSICS_H
#define PHYSICS_H

#include <vector>
#include "Projectile.h"

#include "SM/Vectors/Vec3.h"

#define AIR_DENSITY 1.225f
#define EPSILON 0.00001f
#define UPDATE_FREQUENCY 60.f
#define TIME_FACTOR 0.5f

namespace s3de
{
	class Physics
	{
	public:
		Physics();
		~Physics();

		void update(float dt);

		void addProjectile(Projectile* projectile);

		void applyBowForce(Projectile* projectile, const Bow* bow, const sm::Vec3 dir, const float& x);

	private:
		void updateProjectile(float dt, Projectile* projectile);
		float calcAirResistence(float cd, float area, const sm::Vec3& vel);

		sm::Vec3 getClosestPointOBB(const sm::Vec3& p, const sm::Vec3& c, const sm::Vec3& size);

		bool SphereSphereCollision(Projectile& p1, Projectile& p2, sm::Vec3& loa);
		bool SphereCuboidCollision(Projectile& sphere, Projectile& cuboid, sm::Vec3& loa);

		void collisionResponse(Projectile& p1, Projectile& p2, float e, const sm::Vec3& loa);

		std::vector<Projectile*> projectiles;
		float grav;
	};
}

#endif