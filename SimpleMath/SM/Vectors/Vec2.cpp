#include "Vec2.h"

#include "Vec3.h"
#include "Vec4.h"

sm::Vec2 sm::Vec2::VEC2_X = Vec2(1.0f, 0.0f);
sm::Vec2 sm::Vec2::VEC2_Y = Vec2(0.0f, 1.0f);
sm::Vec2 sm::Vec2::VEC2_ONES = Vec2(1.0f, 1.0f);
sm::Vec2 sm::Vec2::VEC2_ZEROS = Vec2(0.0f, 0.0f);

const sm::Vec2::vec sm::Vec2::v = { &sm::Vec2::x, &sm::Vec2::y };

sm::Vec2::Vec2() : x(0.0f), y(0.0f)
{
}

sm::Vec2::Vec2(float value) : x(value), y(value)
{
}

sm::Vec2::Vec2(float x, float y) : x(x), y(y)
{
}

sm::Vec2::Vec2(const Vec2 & v) : x(v.x), y(v.y)
{
}

sm::Vec2::Vec2(const Vec3 & v) : x(v.x), y(v.y)
{
}

sm::Vec2::Vec2(const Vec4 & v) : x(v.x), y(v.y)
{
}

float & sm::Vec2::operator[](size_t i)
{
	return this->*v[i];
}

const float & sm::Vec2::operator[](size_t i) const
{
	return this->*v[i];
}

bool sm::Vec2::operator==(const Vec2 & v)
{
	return this->x == v.x && this->y == v.y;
}

bool sm::Vec2::operator!=(const Vec2 & v)
{
	return !(*this == v);
}

sm::Vec2 & sm::Vec2::operator=(const Vec2 & v)
{
	this->x = v.x;
	this->y = v.y;
	return *this;
}

sm::Vec2 & sm::Vec2::operator+=(const Vec2 & v)
{
	this->x += v.x;
	this->y += v.y;
	return *this;
}

sm::Vec2 & sm::Vec2::operator-=(const Vec2 & v)
{
	this->x -= v.x;
	this->y -= v.y;
	return *this;
}

sm::Vec2 & sm::Vec2::operator+=(float scalar)
{
	this->x += scalar;
	this->y += scalar;
	return *this;
}

sm::Vec2 & sm::Vec2::operator-=(float scalar)
{
	this->x -= scalar;
	this->y -= scalar;
	return *this;
}

sm::Vec2 & sm::Vec2::operator*=(float scalar)
{
	this->x *= scalar;
	this->y *= scalar;
	return *this;
}

sm::Vec2 & sm::Vec2::operator/=(float scalar)
{
	this->x /= scalar;
	this->y /= scalar;
	return *this;
}

sm::Vec2 sm::Vec2::operator+(const Vec2 & v) const
{
	return Vec2(this->x + v.x, this->y + v.y);
}

sm::Vec2 sm::Vec2::operator-(const Vec2 & v) const
{
	return Vec2(this->x - v.x, this->y - v.y);
}

sm::Vec2 sm::Vec2::operator+(float scalar) const
{
	return Vec2(this->x + scalar, this->y + scalar);
}

sm::Vec2 sm::Vec2::operator-(float scalar) const
{
	return Vec2(this->x - scalar, this->y - scalar);
}

sm::Vec2 sm::Vec2::operator*(float scalar) const
{
	return Vec2(this->x * scalar, this->y * scalar);
}

sm::Vec2 sm::Vec2::operator/(float scalar) const
{
	return Vec2(this->x / scalar, this->y / scalar);
}

sm::Vec2 & sm::Vec2::operator++()
{
	this->x++;
	this->y++;
	return *this;
}

sm::Vec2 & sm::Vec2::operator--()
{
	this->x--;
	this->y--;
	return *this;
}

sm::Vec2 sm::Vec2::operator++(int a) const
{
	return Vec2(this->x + a, this->y +a);
}

sm::Vec2 sm::Vec2::operator--(int a) const
{
	return Vec2(this->x - a, this->y - a);
}

sm::Vec2 sm::Vec2::operator-() const
{
	return Vec2(-this->x, -this->y);
}

int sm::Vec2::length() const
{
	return 2;
}

sm::Vec3 sm::Vec2::toVec3() const
{
	return Vec3(*this);
}

sm::Vec4 sm::Vec2::toVec4() const
{
	return Vec4(*this);
}
