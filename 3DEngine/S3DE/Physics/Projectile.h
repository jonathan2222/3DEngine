#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "SM/Maths.h"
#include "../Game/Node/Node.h"

namespace s3de
{
	struct Geometry
	{
		enum Type { Sphere, Cuboid } type;
		Geometry(Type type) : type(type) {}
	};

	struct Sphere : public Geometry
	{
		Sphere() : Geometry(Type::Sphere) { this->radius = 0.25f; }
		Sphere(float radius) : Geometry(Type::Sphere) { this->radius = radius; }
		float radius;
	};

	struct Cuboid : public Geometry
	{
		Cuboid(const sm::Vec3& dim) : Geometry(Type::Cuboid) { this->dim = dim; }
		sm::Vec3 dim;
	};

	struct Bow
	{
		float mass;
		float c;
		float F;
		float e;
	};

	struct Projectile : public Node
	{
		sm::Vec3 vel;
		sm::Vec3 pos;
		sm::Vec3 angVel;
		float area = 1.0f;
		float mass = 1.0f;
		float cd = 0.4f;
		Geometry* geometry;

		void singleUpdate(float dt) override
		{
			getTransform().setPosition(this->pos);
		};
	};
}

#endif