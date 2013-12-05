#include "stdafx.hpp"
#include "quaternion.hpp"




float CQuaternion::length(void)
{
	return sqrt(this->x*this->x + this->y*this->y + this->z*this->z + this->w*this->w);
}

CQuaternion CQuaternion::normalize(void)
{
	CQuaternion temp;
	float len = this->length();
	temp.x = this->x / len;
	temp.y = this->y / len;
	temp.z = this->z / len;
	temp.w = this->w / len;
	return temp;
}

CQuaternion CQuaternion::conjugate(void)
{
	CQuaternion temp;
	temp.x = -this->x;
	temp.y = -this->y;
	temp.z = -this->z;
	return temp;
}




CQuaternion operator * (CQuaternion &a, CQuaternion &b)
{
	CQuaternion tmp;

	tmp.x = a.w*b.x + a.x*b.w + a.y*b.z - a.z*b.y;
	tmp.y = a.w*b.y - a.x*b.z + a.y*b.w + a.z*b.x;
	tmp.z = a.w*b.z + a.x*b.y - a.y*b.x + a.z*b.w;
	tmp.w = a.w*b.w - a.x*b.x - a.y*b.y - a.z*b.z;

	return tmp;
}








