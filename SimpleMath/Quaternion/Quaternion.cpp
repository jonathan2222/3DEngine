#include "Quaternion.h"

#include "../Maths.h"

yami::Quaternion::Quaternion()
{
	init(0.0f, 0.0f, 0.0f, 0.0f);
}

yami::Quaternion::Quaternion(const Quaternion & q)
{
	init(q.s, q.x, q.y, q.z);
}

yami::Quaternion::Quaternion(float s)
{
	init(s, 0.0f, 0.0f, 0.0f);
}

yami::Quaternion::Quaternion(float pitch, float roll, float yaw)
{
	setYawPitchRoll(pitch, roll, yaw);
}

yami::Quaternion::Quaternion(float s, float x, float y, float z)
{
	init(s, x, y, z);
}

yami::Quaternion::Quaternion(const Vec3 & v)
{
	init(0.0f, v.x, v.y, v.z);
}

yami::Quaternion::Quaternion(const Vec3 & from, const Vec3 & to)
{
	setRotation(from, to);
}

yami::Quaternion::Quaternion(float angle, const Vec3 & axis)
{
	init(cos(angle / 2.f), sin(angle / 2.f)*axis.x, sin(angle / 2.f)*axis.y, sin(angle / 2.f)*axis.z);
}

void yami::Quaternion::setAngleAxis(float angle, const Vec3 & axis)
{
	init(cos(angle/2.f), sin(angle/2.f)*axis.x, sin(angle / 2.f)*axis.y, sin(angle / 2.f)*axis.z);
}

void yami::Quaternion::setYawPitchRoll(float pitch, float roll, float yaw)
{
	double cy = cos(yaw * 0.5);
	double sy = sin(yaw * 0.5);
	double cr = cos(roll * 0.5);
	double sr = sin(roll * 0.5);
	double cp = cos(pitch * 0.5);
	double sp = sin(pitch * 0.5);
	init(cy * cr * cp + sy * sr * sp, 
		cy * sr * cp - sy * cr * sp,
		cy * cr * sp + sy * sr * cp, 
		sy * cr * cp - cy * sr * sp);
}

void yami::Quaternion::setRotation(const Vec3 & from, const Vec3 & to)
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

yami::Vec3 yami::Quaternion::rotate(const Vec3 & v) const
{
	return this->matrix*v;
}

yami::Vec3 yami::Quaternion::operator*(const Vec3 & v)
{
	return rotate(v);
}

yami::Vec3 yami::Quaternion::toVec3() const
{
	return rotate(Vec3(1.0f, 0.0f, 0.0f));
}

void yami::Quaternion::addAngle(float angle)
{
	float preAngle = getAngle();
	setAngleAxis(preAngle + angle, getAxis());
}

void yami::Quaternion::addRotation(float angle, const Vec3 & axis)
{
	Quaternion q;
	q.setAngleAxis(angle, axis);
	addRotation(q);
}

void yami::Quaternion::addRotation(float pitch, float roll, float yaw)
{
	Quaternion q;
	q.setYawPitchRoll(pitch, roll, yaw);
	addRotation(q);
}

void yami::Quaternion::addRotation(const Quaternion & q)
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

yami::Quaternion yami::Quaternion::operator*(const Quaternion & q)
{
	float a = s * q.s - x * q.x - y * q.y - z * q.z;
	float b = s * q.x + x * q.s + y * q.z - z * q.y;
	float c = s * q.y - x * q.z + y * q.s + z * q.x;
	float d = s * q.z + x * q.y - y * q.x + z * q.s;
	return Quaternion(a, b, c, d);
}

yami::Quaternion & yami::Quaternion::operator*=(const Quaternion & q)
{
	addRotation(q);
	calculateMatrix();
	return *this;
}

yami::Mat3 yami::Quaternion::operator*(const Mat3 & m)
{
	return this->matrix * m;
}

yami::Mat4 yami::Quaternion::operator*(const Mat4 & m)
{
	return getMatrix4() * m;
}

yami::Quaternion yami::Quaternion::operator*(float a)
{
	return Quaternion(s*a, x*a, y*a, z*a);
}

yami::Quaternion yami::Quaternion::operator/(float a)
{
	return Quaternion(s/a, x/a, y/a, z/a);
}

yami::Quaternion & yami::Quaternion::operator*=(float a)
{
	this->s *= a;
	this->v *= a;
	calculateMatrix();
	return *this;
}

yami::Quaternion & yami::Quaternion::operator/=(float a)
{
	this->s /= a;
	this->v /= a;
	calculateMatrix();
	return *this;
}

yami::Vec3 yami::Quaternion::getAxis() const
{
	const Vec3 axis(this->x, this->y, this->z);
	const float len = Maths::length(axis);
	return axis / len;
}

float yami::Quaternion::getAngle() const
{
	const Vec3 axis(this->x, this->y, this->z);
	const float len = Maths::length(axis);
	return 2.0f * std::atan2f(len, this->s);
}

yami::Quaternion yami::Quaternion::getConjugate() const
{
	return Quaternion(s, -x, -y, -z);
}

yami::Quaternion yami::Quaternion::getInverse() const
{
	Quaternion inverse(getConjugate());
	return inverse/length2();
}

yami::Quaternion & yami::Quaternion::conjugate()
{
	this->v *= -1;
	calculateMatrix();
	return *this;
}

yami::Quaternion & yami::Quaternion::inverse()
{
	Quaternion conjugate(getConjugate());
	(*this) /= length2();
	calculateMatrix();
	return *this;
}

yami::Quaternion& yami::Quaternion::normalize()
{
	(*this) /= length();
	calculateMatrix();
	return *this;
}

float yami::Quaternion::length() const
{
	return sqrt(length2());
}

float yami::Quaternion::length2() const
{
	return s * s + x * x + y * y + z * z;
}

void yami::Quaternion::init(float s, float x, float y, float z)
{
	this->s = s;
	this->x = x;
	this->y = y;
	this->z = z;
	calculateMatrix();
}

void yami::Quaternion::calculateMatrix()
{
	const float len = length();
	const float a = 1.0f / (len*len);
	this->matrix[0][0] = 1 - 2*a*(y*y + z*z);	this->matrix[1][0] = 2*a*(x*y - z*s);		this->matrix[2][0] = 2*a*(x*z + y*s);
	this->matrix[0][1] = 2*a*(x*y + z*s);		this->matrix[1][1] = 1 - 2*a*(x*x + z*z);	this->matrix[2][1] = 2*a*(y*z - x*s);
	this->matrix[0][2] = 2*a*(x*z - y*s);		this->matrix[1][2] = 2*a*(y*z + x*s);		this->matrix[2][2] = 1 - 2*a*(x*x + y*y);
}

yami::Mat3 yami::Quaternion::getMatrix3() const
{
	return this->matrix;
}

yami::Mat4 yami::Quaternion::getMatrix4() const
{
	return Mat4(this->matrix);
}
