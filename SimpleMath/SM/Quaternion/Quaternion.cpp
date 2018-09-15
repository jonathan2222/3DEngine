#include "Quaternion.h"

#include "../Maths.h"

sm::Quaternion::Quaternion()
{
	init(0.0f, 0.0f, 0.0f, 0.0f);
}

sm::Quaternion::Quaternion(const Quaternion & q)
{
	init(q.s, q.x, q.y, q.z);
}

sm::Quaternion::Quaternion(float s)
{
	init(s, 0.0f, 0.0f, 0.0f);
}

sm::Quaternion::Quaternion(float pitch, float roll, float yaw)
{
	setYawPitchRoll(pitch, roll, yaw);
}

sm::Quaternion::Quaternion(float s, float x, float y, float z)
{
	init(s, x, y, z);
}

sm::Quaternion::Quaternion(const Vec3 & v)
{
	init(0.0f, v.x, v.y, v.z);
}

sm::Quaternion::Quaternion(const Vec3 & from, const Vec3 & to)
{
	setRotation(from, to);
}

sm::Quaternion::Quaternion(float angle, const Vec3 & axis)
{
	init(cos(angle / 2.f), sin(angle / 2.f)*axis.x, sin(angle / 2.f)*axis.y, sin(angle / 2.f)*axis.z);
}

void sm::Quaternion::setAngleAxis(float angle, const Vec3 & axis)
{
	init(cos(angle/2.f), sin(angle/2.f)*axis.x, sin(angle / 2.f)*axis.y, sin(angle / 2.f)*axis.z);
}

void sm::Quaternion::setYawPitchRoll(float pitch, float roll, float yaw)
{
	float cy = cosf(yaw * 0.5f);
	float sy = sinf(yaw * 0.5f);
	float cr = cosf(roll * 0.5f);
	float sr = sinf(roll * 0.5f);
	float cp = cosf(pitch * 0.5f);
	float sp = sinf(pitch * 0.5f);
	init(cy * cr * cp + sy * sr * sp, 
		cy * sr * cp - sy * cr * sp,
		cy * cr * sp + sy * sr * cp, 
		sy * cr * cp - cy * sr * sp);
}

void sm::Quaternion::setRotation(const Vec3 & from, const Vec3 & to)
{
	Quaternion q;
	float d = Maths::dot(from, to);
	if (d > 1.0f- MathsConstatns::EPSILON) // Same direction.
	{
		init(1.0f, 0.0f, 0.0f, 0.0f);
		return;
	}
	if (d < -1.0f + MathsConstatns::EPSILON) // 'to' is inverse from 'from' => rotate 180 deg.
	{
		Vec3 axis = Maths::cross(Vec3::VEC3_X, from);
		if (Maths::isZeroLength(axis))
			axis = Maths::cross(Vec3::VEC3_Y, from);
		axis = Maths::normalize<Vec3>(axis);
		q.setAngleAxis(MathsConstatns::PI, axis);
		init(q.s, q.x, q.y, q.z);
	}
	else
	{
		Vec3 v = Maths::cross(from, to);
		q.v = v;
		float lenF = Maths::length(from);
		float lenT = Maths::length(to);
		q.s = 1.0f + d;// sqrt(lenF*lenF * lenT*lenT) + Maths::dot(from, to);
		q.normalize();
		init(q.s, q.x, q.y, q.z);
	}
}

sm::Vec3 sm::Quaternion::rotate(const Vec3 & v) const
{
	return this->matrix*v;
}

sm::Vec3 sm::Quaternion::operator*(const Vec3 & v)
{
	return rotate(v);
}

sm::Vec3 sm::Quaternion::toVec3() const
{
	return rotate(Vec3(1.0f, 0.0f, 0.0f));
}

void sm::Quaternion::addAngle(float angle)
{
	float preAngle = getAngle();
	setAngleAxis(preAngle + angle, getAxis());
}

void sm::Quaternion::addRotation(float angle, const Vec3 & axis)
{
	Quaternion q;
	q.setAngleAxis(angle, axis);
	addRotation(q);
}

void sm::Quaternion::addRotation(float pitch, float roll, float yaw)
{
	Quaternion q;
	q.setYawPitchRoll(pitch, roll, yaw);
	addRotation(q);
}

void sm::Quaternion::addRotation(const Quaternion & q)
{
	if (this->s == 0.0f && this->x == 0.0f && this->y == 0.0f && this->z == 0.0f)
	{
		setAngleAxis(0.0f, Vec3(1.0f, 0.0f, 0.0f));
	}
	
	float a = s * q.s - x * q.x - y * q.y - z * q.z;
	float b = s * q.x + x * q.s + y * q.z - z * q.y;
	float c = s * q.y - x * q.z + y * q.s + z * q.x;
	float d = s * q.z + x * q.y - y * q.x + z * q.s;
	this->s = a;
	this->x = b;
	this->y = c;
	this->z = d;
	normalize();
	calculateMatrix();
}

sm::Quaternion sm::Quaternion::operator*(const Quaternion & q)
{
	float a = s * q.s - x * q.x - y * q.y - z * q.z;
	float b = s * q.x + x * q.s + y * q.z - z * q.y;
	float c = s * q.y - x * q.z + y * q.s + z * q.x;
	float d = s * q.z + x * q.y - y * q.x + z * q.s;
	return Quaternion(a, b, c, d);
}

sm::Quaternion & sm::Quaternion::operator*=(const Quaternion & q)
{
	addRotation(q);
	calculateMatrix();
	return *this;
}

sm::Mat3 sm::Quaternion::operator*(const Mat3 & m)
{
	return this->matrix * m;
}

sm::Mat4 sm::Quaternion::operator*(const Mat4 & m)
{
	return getMatrix4() * m;
}

sm::Quaternion sm::Quaternion::operator*(float a)
{
	return Quaternion(s*a, x*a, y*a, z*a);
}

sm::Quaternion sm::Quaternion::operator/(float a)
{
	return Quaternion(s/a, x/a, y/a, z/a);
}

sm::Quaternion & sm::Quaternion::operator*=(float a)
{
	this->s *= a;
	this->v *= a;
	calculateMatrix();
	return *this;
}

sm::Quaternion & sm::Quaternion::operator/=(float a)
{
	this->s /= a;
	this->v /= a;
	calculateMatrix();
	return *this;
}

sm::Vec3 sm::Quaternion::getAxis() const
{
	const Vec3 axis(this->x, this->y, this->z);
	const float len = Maths::length(axis);
	return axis / len;
}

float sm::Quaternion::getAngle() const
{
	const Vec3 axis(this->x, this->y, this->z);
	const float len = Maths::length(axis);
	return 2.0f * std::atan2f(len, this->s);
}

sm::Quaternion sm::Quaternion::getConjugate() const
{
	return Quaternion(s, -x, -y, -z);
}

sm::Quaternion sm::Quaternion::getInverse() const
{
	Quaternion inverse(getConjugate());
	return inverse/length2();
}

sm::Quaternion & sm::Quaternion::conjugate()
{
	this->v *= -1;
	calculateMatrix();
	return *this;
}

sm::Quaternion & sm::Quaternion::inverse()
{
	Quaternion conjugate(getConjugate());
	(*this) /= length2();
	calculateMatrix();
	return *this;
}

sm::Quaternion& sm::Quaternion::normalize()
{
	(*this) /= length();
	calculateMatrix();
	return *this;
}

float sm::Quaternion::length() const
{
	return sqrt(length2());
}

float sm::Quaternion::length2() const
{
	return s * s + x * x + y * y + z * z;
}

void sm::Quaternion::init(float s, float x, float y, float z)
{
	this->s = s;
	this->x = x;
	this->y = y;
	this->z = z;
	calculateMatrix();
}

void sm::Quaternion::calculateMatrix()
{
	const float len = length();
	const float a = 1.0f / (len*len);
	this->matrix[0][0] = 1 - 2*a*(y*y + z*z);	this->matrix[1][0] = 2*a*(x*y - z*s);		this->matrix[2][0] = 2*a*(x*z + y*s);
	this->matrix[0][1] = 2*a*(x*y + z*s);		this->matrix[1][1] = 1 - 2*a*(x*x + z*z);	this->matrix[2][1] = 2*a*(y*z - x*s);
	this->matrix[0][2] = 2*a*(x*z - y*s);		this->matrix[1][2] = 2*a*(y*z + x*s);		this->matrix[2][2] = 1 - 2*a*(x*x + y*y);
}

sm::Mat3 sm::Quaternion::getMatrix3() const
{
	return this->matrix;
}

sm::Mat4 sm::Quaternion::getMatrix4() const
{
	return Mat4(this->matrix);
}
