#include "Vec3.h"

#include "Vec2.h"
#include "Vec4.h"

yami::Vec3 yami::Vec3::VEC3_X = Vec3(1.0f, 0.0f, 0.0f);
yami::Vec3 yami::Vec3::VEC3_Y = Vec3(0.0f, 1.0f, 0.0f);
yami::Vec3 yami::Vec3::VEC3_Z = Vec3(0.0f, 0.0f, 1.0f);
yami::Vec3 yami::Vec3::VEC3_ONES = Vec3(1.0f, 1.0f, 1.0f);
yami::Vec3 yami::Vec3::VEC3_ZEROS = Vec3(0.0f, 0.0f, 0.0f);

const yami::Vec3::vec yami::Vec3::v = { &yami::Vec3::x, &yami::Vec3::y, &yami::Vec3::z };

yami::Vec3::Vec3() : x(0.0f), y(0.0f), z(0.0f)
{
}

yami::Vec3::Vec3(float value) : x(value), y(value), z(value)
{
}

yami::Vec3::Vec3(float x, float y) : x(x), y(y), z(0.0f)
{

}

yami::Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z)
{

}

yami::Vec3::Vec3(const Vec3 & v) : x(v.x), y(v.y), z(v.z)
{
}

yami::Vec3::Vec3(const Vec2 & v, float z) : x(v.x), y(v.y), z(z)
{
}

yami::Vec3::Vec3(const Vec4 & v) : x(v.x), y(v.y), z(v.z)
{
}

float & yami::Vec3::operator[](size_t i)
{
	return this->*v[i];
}

const float & yami::Vec3::operator[](size_t i) const
{
	return this->*v[i];
}

bool yami::Vec3::operator==(const Vec3 & v)
{
	return this->x == v.x && this->y == v.y && this->z == v.z;
}

bool yami::Vec3::operator!=(const Vec3 & v)
{
	return !(*this == v);
}

yami::Vec3 & yami::Vec3::operator=(const Vec3 & v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	return *this;
}

yami::Vec3 & yami::Vec3::operator+=(const Vec3 & v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	return *this;
}

yami::Vec3 & yami::Vec3::operator-=(const Vec3 & v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	return *this;
}

yami::Vec3 & yami::Vec3::operator+=(float scalar)
{
	this->x += scalar;
	this->y += scalar;
	this->z += scalar;
	return *this;
}

yami::Vec3 & yami::Vec3::operator-=(float scalar)
{
	this->x -= scalar;
	this->y -= scalar;
	this->z -= scalar;
	return *this;
}

yami::Vec3 & yami::Vec3::operator*=(float scalar)
{
	this->x *= scalar;
	this->y *= scalar;
	this->z *= scalar;
	return *this;
}

yami::Vec3 & yami::Vec3::operator/=(float scalar)
{
	this->x /= scalar;
	this->y /= scalar;
	this->z /= scalar;
	return *this;
}

yami::Vec3 yami::Vec3::operator+(const Vec3 & v) const
{
	return Vec3(this->x + v.x, this->y + v.y, this->z + v.z);
}

yami::Vec3 yami::Vec3::operator-(const Vec3 & v) const
{
	return Vec3(this->x - v.x, this->y - v.y, this->z - v.z);
}

yami::Vec3 yami::Vec3::operator+(float scalar) const
{
	return Vec3(this->x + scalar, this->y + scalar, this->z + scalar);
}

yami::Vec3 yami::Vec3::operator-(float scalar) const
{
	return Vec3(this->x - scalar, this->y - scalar, this->z - scalar);
}

yami::Vec3 yami::Vec3::operator*(float scalar) const
{
	return Vec3(this->x * scalar, this->y * scalar, this->z * scalar);
}

yami::Vec3 yami::Vec3::operator/(float scalar) const
{
	return Vec3(this->x / scalar, this->y / scalar, this->z / scalar);
}

yami::Vec3 & yami::Vec3::operator++()
{
	this->x++;
	this->y++;
	this->z++;
	return *this;
}

yami::Vec3 & yami::Vec3::operator--()
{
	this->x--;
	this->y--;
	this->z--;
	return *this;
}

yami::Vec3 yami::Vec3::operator++(int a) const
{
	return Vec3(this->x + a, this->y + a, this->z + a);
}

yami::Vec3 yami::Vec3::operator--(int a) const
{
	return Vec3(this->x - a, this->y - a, this->z - a);
}

yami::Vec3 yami::Vec3::operator-() const
{
	return Vec3(-this->x, -this->y, -this->z);
}

int yami::Vec3::length() const
{
	return 3;
}

yami::Vec2 yami::Vec3::toVec2() const
{
	return Vec2(*this);
}

yami::Vec4 yami::Vec3::toVec4() const
{
	return Vec4(*this);
}
