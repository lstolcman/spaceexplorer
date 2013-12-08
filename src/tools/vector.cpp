#include "stdafx.hpp"
#include "vector.hpp"





float vec3::length() const
{
	return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

void vec3::normalize(void)
{
	float len = this->length();
	this->x /= len;
	this->y /= len;
	this->z /= len;
}




void vec3::operator =(const vec3 &a)
{
	this->x = a.x;
	this->y = a.y;
	this->z = a.z;
}

bool operator ==(const vec3 &a, const vec3 &b)
{
	if (a.x == b.x && a.y == b.y && a.z == b.z)
	{
		return true;
	}
	return false;
}

void vec3::operator +=(const vec3 &a)
{
	this->x += a.x;
	this->y += a.y;
	this->z += a.z;
}

void vec3::operator -=(const vec3 &a)
{
	this->x -= a.x;
	this->y -= a.y;
	this->z -= a.z;
}

void vec3::operator *=(const vec3 &a)
{
	this->x *= a.x;
	this->y *= a.y;
	this->z *= a.z;
}

void vec3::operator /=(const vec3 &a)
{
	this->x /= a.x;
	this->y /= a.y;
	this->z /= a.z;
}



vec3 operator +(vec3 &a, vec3 &b)
{
	vec3 tmp;

	tmp.x = a.x + b.x;
	tmp.y = a.y + b.y;
	tmp.z = a.z + b.z;

	return tmp;
}

vec3 operator -(vec3 &a, vec3 &b)
{
	vec3 tmp;

	tmp.x = a.x - b.x;
	tmp.y = a.y - b.y;
	tmp.z = a.z - b.z;

	return tmp;
}


vec3 operator *(vec3 &a, vec3 &b)
{
	vec3 tmp;

	tmp.x = a.x * b.x;
	tmp.y = a.y * b.y;
	tmp.z = a.z * b.z;

	return tmp;
}



vec3 operator /(vec3 &a, vec3 &b)
{
	vec3 tmp;

	tmp.x = a.x / b.x;
	tmp.y = a.y / b.y;
	tmp.z = a.z / b.z;

	return tmp;
}





vec3 crossProduct(vec3 &a, vec3 &b)
{
	vec3 tmp;

	tmp.x = a.y * b.z - a.z * b.y;
	tmp.y = a.z * b.x - a.x * b.z;
	tmp.z = a.x * b.y - a.y * b.x;

	return tmp;
}