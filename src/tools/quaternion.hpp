#pragma once
#include "vector.hpp"



class CQuaternion : public vec3
{
public:
	float w;

	CQuaternion() { x = 0; y = 0; z = 0; w = 0; }
	CQuaternion(float x, float y, float z, float w) : vec3(x, y, z), w(w) {};
	~CQuaternion() {};

	float length(void);
	CQuaternion normalize(void);
	CQuaternion conjugate(void);


	//operators
	//void operator = (const CQuaternion&);
	//friend bool operator == (const CQuaternion&, const CQuaternion&);
	//void operator += (const CQuaternion&);
	//void operator -= (const CQuaternion&);
	//void operator *= (const CQuaternion&);
	//void operator /= (const CQuaternion&);

	//friend CQuaternion operator + (CQuaternion&, CQuaternion&);
	//friend CQuaternion operator - (CQuaternion&, CQuaternion&);
	friend CQuaternion operator * (CQuaternion&, CQuaternion&);
	//friend CQuaternion operator / (CQuaternion&, CQuaternion&);

};









