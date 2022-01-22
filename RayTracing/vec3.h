//==============================================================================================
// 
// A project to learn and practice ray tracing. 
// Reference: �Ray Tracing in One Weekend.� raytracing.github.io/books/RayTracingInOneWeekend.html
// 
//==============================================================================================

#pragma once
#include <cmath>
#include <iostream>

//using std::sqrt;


class vec3
{
public: 
	vec3() : e{ 0, 0, 0 } 	{}
	vec3(double e0, double e1, double e2) : e{ e0, e1, e2 } {}

	double x() const { return e[0]; }
	double y() const { return e[1]; }
	double z() const { return e[2]; }

	vec3 operator-() const
	{
		return vec3(-e[0], -e[1], -e[2]); 
	}

	// indexing: a const one and returns a copy 
	double operator[](int i) const { return e[i]; }

	// indexing: a none const one that returns a reference (lvalue)
	double& operator[](int i) { return e[i]; }

	vec3& operator+=(const vec3& other) {
		e[0] += other.e[0];
		e[1] += other.e[1];
		e[2] += other.e[2];
		return *this;
	}

	vec3& operator*=(const double t) {
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	vec3& operator/=(const double t) {
		return (*this) *= 1 / t;
	}

	double length() const 
	{
		return std::sqrt(length_squared());
	}

	double length_squared() const
	{
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	inline static vec3 random()
	{
		return vec3(random_double(), random_double(), random_double());
	}

	inline static vec3 random(double min, double max)
	{
		return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
	}

public: 
	double e[3];
};

// Type aliases for vec3 
using point3 = vec3; // 3D point
using color = vec3; // RGB point


// vec3 utility functions 

vec3 random_in_unit_sphere()
{
	while (true)
	{
		auto p = vec3::random(-1, 1);
		if (p.length_squared() >= 1) continue; 
		return p; 
	}
}

inline std::ostream& operator<<(std::ostream& out, const vec3& v)
{	
	// here I don't understand. if the out is reference by address. 
	// why need to return a reference by address 
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2]; 
}

inline vec3 operator+(const vec3& u, const vec3& v)
{
	return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v)
{
	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v)
{
	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3& u)
{
	return vec3(t * u.e[0], t * u.e[1], t * u.e[2]);
}

inline vec3 operator*(const vec3& u, double t)
{
	return t * u;
}

inline vec3 operator/(const vec3& u, double t)
{
	return (1/t) * u;
}

inline double dot(const vec3& v, const vec3& u)
{
	return (u.e[0] * v.e[0]) + (u.e[1] * v.e[1]) + (u.e[2] * v.e[2]);
}

inline vec3 cross(const vec3& u, const vec3& v)
{
	return vec3( u.e[1] * v.e[2] - u.e[2] * v.e[1], 
				 u.e[2] * v.e[0] - u.e[0] * v.e[2],
				 u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(vec3 v)
{
	return v / v.length();
}
