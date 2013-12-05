#pragma once




class vec3
{
public:
	float x, y, z;

	vec3() { x = 0; y = 0; z = 0; };
	vec3(float x, float y, float z) : x(x), y(y), z(z) {};
	~vec3() {};

	float length(void) const;
	void normalize(void);
	

	//operators
	void operator = (const vec3&);
	friend bool operator == (const vec3&, const vec3&);
	void operator += (const vec3&);
	void operator -= (const vec3&);
	void operator *= (const vec3&);
	void operator /= (const vec3&);

	friend vec3 operator + (vec3&, vec3&);
	friend vec3 operator - (vec3&, vec3&);
	friend vec3 operator * (vec3&, vec3&);
	friend vec3 operator / (vec3&, vec3&);
};


vec3 crossProduct(vec3&, vec3&);

