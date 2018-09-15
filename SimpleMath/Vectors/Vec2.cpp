#include "Vec2.h"

#include "Vec3.h"
#include "Vec4.h"

yami::Vec2 yami::Vec2::VEC2_X = Vec2(1.0f, 0.0f);
yami::Vec2 yami::Vec2::VEC2_Y = Vec2(0.0f, 1.0f);
yami::Vec2 yami::Vec2::VEC2_ONES = Vec2(1.0f, 1.0f);
yami::Vec2 yami::Vec2::VEC2_ZEROS = Vec2(0.0f, 0.0f);

const yami::Vec2::vec yami::Vec2::v = { &yami::Vec2::x, &yami::Vec2::y };

yami::Vec2::Vec2() : x(0.0f), y(0.0f)
{
}

yami::Vec2::Vec2(float value) : x(value), y(value)
{
}

yami::Vec2::Vec2(float x, float y) : x(x), y(y)
{
}

yami::Vec2::Vec2(const Vec2 & v) : x(v.x), y(v.y)
{
}

yami::Vec2::Vec2(const Vec3 & v) : x(v.x), y(v.y)
{
}

yami::Vec2::Vec2(const Vec4 & v) : x(v.x), y(v.y)
{
}

float & yami::Vec2::operator[](size_t i)
{
	return this->*v[i];
}

const float & yami::Vec2::operator[](size_t i) const
{
	return this->*v[i];
}

bool yami::Vec2::operator==(const Vec2 & v)
{
	return this->x == v.x && this->y == v.y;
}

bool yami::Vec2::operator!=(const Vec2 & v)
{
	return !(*this == v);
}

yami::Vec2 & yami::Vec2::operator=(const Vec2 & v)
{
	this->x = v.x;
	this->y = v.y;
	return *this;
}

yami::Vec2 & yami::Vec2::operator+=(const Vec2 & v)
{
	this->x += v.x;
	this->y += v.y;
	return *this;
}

yami::Vec2 & yami::Vec2::operator-=(const Vec2 & v)
{
	this->x -= v.x;
	this->y -= v.y;
	return *this;
}

yami::Vec2 & yami::Vec2::operator+=(float scalar)
{
	this->x += scalar;
	this->y += scalar;
	return *this;
}

yami::Vec2 & yami::Vec2::operator-=(float scalar)
{
	this->x -= scalar;
	this->y -= scalar;
	return *this;
}

yami::Vec2 & yami::Vec2::operator*=(float scalar)
{
	this->x *= scalar;
	this->y *= scalar;
	return *this;
}

yami::Vec2 & yami::Vec2::operator/=(float scalar)
{
	this->x /= scalar;
	this->y /= scalar;
	return *this;
}

yami::Vec2 yami::Vec2::operator+(const Vec2 & v) const
{
	return Vec2(this->x + v.x, this->y + v.y);
}

yami::Vec2 yami::Vec2::operator-(const Vec2 & v) const
{
	return Vec2(this->x - v.x, this->y - v.y);
}

yami::Vec2 yami::Vec2::operator+(float scalar) const
{
	return Vec2(this->x + scalar, this->y + scalar);
}

yami::Vec2 yami::Vec2::operator-(float scalar) const
{
	return Vec2(this->x - scalar, this->y - scalar);
}

yami::Vec2 yami::Vec2::operator*(float scalar) const
{
	return Vec2(this->x * scalar, this->y * scalar);
}

yami::Vec2 yami::Vec2::operator/(float scalar) const
{
	return Vec2(this->x / scalar, this->y / scalar);
}

yami::Vec2 & yami::Vec2::operator++()
{
	this->x++;
	this->y++;
	return *this;
}

yami::Vec2 & yami::Vec2::operator--()
{
	this->x--;
	this->y--;
	return *this;
}

yami::Vec2 yami::Vec2::operator++(int a) const
{
	return Vec2(this->x + a, this->y +a);
}

yami::Vec2 yami::Vec2::operator--(int a) const
{
	return Vec2(this->x - a, this->y - a);
}

yami::Vec2 yami::Vec2::operator-() const
{
	return Vec2(-this->x, -this->y);
}

int yami::Vec2::length() const
{
	return 2;
}

yami::Vec3 yami::Vec2::toVec3() const
{
	return Vec3(*this);
}

yami::Vec4 yami::Vec2::toVec4() const
{
	return Vec4(*this);
}
