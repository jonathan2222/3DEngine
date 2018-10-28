#include "Physics.h"

#define GLM_ENABLE_EXPERIMENTAL

#include "SM/Maths.h"

s3de::Physics::Physics()
{
	this->grav = 9.82;
}

s3de::Physics::~Physics()
{
}

void s3de::Physics::update(float dt)
{
	static float time = 0.0f;
	time += dt;
	if (time > 1.f/UPDATE_FREQUENCY)
	{
		for (unsigned int i = 0; i < this->projectiles.size(); i++)
			updateProjectile(1.f / UPDATE_FREQUENCY * TIME_FACTOR, this->projectiles[i]);
		
		Projectile* p1 = this->projectiles[0];
		Projectile* p2 = this->projectiles[1];
		sm::Vec3 loa;
		if(SphereSphereCollision(*p1, *p2, loa))
		//if (SphereCuboidCollision(*p1, *p2, loa))
		{
			printf("Collision!\n");
			collisionResponse(*p1, *p2, 1.0f, loa);
		}

		time = 0.0f;
	}
}

void s3de::Physics::addProjectile(Projectile * projectile)
{
	this->projectiles.push_back(projectile);
}

void s3de::Physics::applyBowForce(Projectile * projectile, const Bow* bow, const sm::Vec3 dir, const float& x)
{
	projectile->vel = sqrt((bow->F * x * bow->e) / (projectile->mass + bow->mass * bow->c)) * sm::Maths::normalize(dir);
}

void s3de::Physics::updateProjectile(float dt, Projectile* projectile)
{
	float fd = calcAirResistence(projectile->cd, projectile->area, projectile->vel);
	sm::Vec3 ev(0.0f);
	if (sm::Maths::length2(projectile->vel) > EPSILON)
		ev = sm::Maths::normalize(projectile->vel);
	sm::Vec3 fdv = -fd * ev;
	sm::Vec3 fgv = sm::Vec3(0.0f, -this->grav * projectile->mass, 0.0f);

	sm::Vec3 acc = (fdv + fgv) / projectile->mass;
	
	projectile->vel += acc * dt;
	projectile->pos += projectile->vel * dt;
	static float t = 0.0f;
	t += dt/ TIME_FACTOR;
	if (t > 1.f) 
	{ 
		printf("fd: %f, v: %f\n", fd, sm::Maths::length(projectile->vel));
		t = 0.0f;
	}
}

float s3de::Physics::calcAirResistence(float cd, float area, const sm::Vec3 & vel)
{
	return 0.5f * AIR_DENSITY * area * cd * sm::Maths::length2(vel);
}

sm::Vec3 s3de::Physics::getClosestPointOBB(const sm::Vec3 & p, const sm::Vec3 & c, const sm::Vec3 & size)
{
	// TODO: Put this in Cuboid!!!
	sm::Vec3 normals[3] = { sm::Vec3::VEC3_X, sm::Vec3::VEC3_Y, sm::Vec3::VEC3_Z };

	sm::Vec3 d = p - c;
	sm::Vec3 q = c;
	for (unsigned int i = 0; i < 3; i++)
	{
		sm::Vec3 extension = normals[i] * size[i];

		float dist = sm::Maths::dot(d, normals[i]);
		if (dist > sm::Maths::length(extension))
			dist = sm::Maths::length(extension);

		if (dist < -sm::Maths::length(extension))
			dist = -sm::Maths::length(extension);
	
		q += dist * normals[i];
	}
	return q;
}

bool s3de::Physics::SphereSphereCollision(Projectile& p1, Projectile& p2, sm::Vec3& loa)
{
	sm::Vec3 p1p2 = p2.pos - p1.pos;
	const float d = ((Sphere*)p1.geometry)->radius + ((Sphere*)p2.geometry)->radius;
	float l = sm::Maths::length(p1p2);
	if (l <= d)
	{
		sm::Vec3 u = p2.vel - p1.vel;
		float x = d - l;
		float t = x / sm::Maths::length(u);
		p1.pos -= t * p1.vel;
		p2.pos -= t * p2.vel;
		loa = sm::Maths::normalize(p2.pos - p1.pos);
		return true;
	}
	return false;
}

bool s3de::Physics::SphereCuboidCollision(Projectile & sphere, Projectile & cuboid, sm::Vec3 & loa)
{
	
	sm::Vec3 normals[3] = { sm::Vec3::VEC3_X, sm::Vec3::VEC3_Y, sm::Vec3::VEC3_Z };

	sm::Vec3 size = ((Cuboid*)cuboid.geometry)->dim;
	float radius = ((Sphere*)sphere.geometry)->radius;

	int collidedWith = 0;
	int lastIndex = -1;
	float minL = 100000.f;
	for (unsigned int i = 0; i < 6; i++)
	{
		sm::Vec3 normal = (i > 2 ? -1.f : 1.f) * normals[i%3];
		sm::Vec3 pointOnPlane = cuboid.pos + size[i%3]*normal;
		sm::Vec3 v = sphere.pos - pointOnPlane;
		float l = sm::Maths::dot(normal, v);
		if (l > 0.0)
		{
			v = l * normal;
			if (sm::Maths::length(v) <= radius)
			{
				collidedWith++;
				if (abs(l) < minL)
				{
					minL = abs(l);
					lastIndex = i;
				}
			}
		}
		else
		{
			collidedWith++;
			// ?
			if (abs(l) < minL)
			{
				minL = abs(l);
				lastIndex = i;
			}
		}
	}
	if (collidedWith == 6)
	{
		sm::Vec3 point = getClosestPointOBB(sphere.pos, cuboid.pos, size);
		loa = sm::Maths::normalize(point- sphere.pos);
		return true;
	}
	return false;
}
// TODO: Not working if mc not align with loa.
void s3de::Physics::collisionResponse(Projectile & p1, Projectile & p2, float e, const sm::Vec3 & loa)
{
	float v1rho = sm::Maths::dot(loa, p1.vel);
	float v2rho = sm::Maths::dot(loa, p2.vel);
	float totalMass = p1.mass + p2.mass;
	
	float A = (p1.mass - e * p2.mass) / totalMass;
	float B = (1.f + e)*p2.mass / totalMass;
	float u1rho = A * v1rho + B * v2rho;

	A = (p2.mass - e * p1.mass) / totalMass;
	B = (1.f + e)*p1.mass / totalMass;
	float u2rho = A * v2rho + B * v1rho;

	// TODO: Add friction and angular velocity.
	p1.vel += (u1rho - v1rho)*loa;
	p2.vel += (u2rho - v2rho)*loa;

	// Avoid unecessary collision.
	p1.pos += sm::Maths::normalize(p1.vel)*0.1f;
	p2.pos += sm::Maths::normalize(p2.vel)*0.1f;

	// Angular velocity
	/*float friction = 0.03;
	float radius = 2;
	A = (p1.mass * radius * friction * (u1rho - v1rho)) / 0.4*p1.mass*radius*radius;
	glm::vec3 en = glm::cross(loa, )
	p1.angVel = 
	*/
}
