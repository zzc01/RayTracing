//==============================================================================================
// 
// A project to learn and practice ray tracing. 
// Reference: “Ray Tracing in One Weekend.” raytracing.github.io/books/RayTracingInOneWeekend.html
// 
//==============================================================================================

#pragma once
#include "ray.h"

struct hit_record
{
	point3 p;
	vec3 normal;
	double t;
	bool front_face; 
	
	inline void set_face_nromal(const ray& r, const vec3& outward_normal)
	{
		front_face = dot(r.direction(), outward_normal) < 0; 
		// when front_face > 0: outside normal 
		// when front_face < 0: inside normal 
		normal = front_face ? outward_normal : -outward_normal; 
	}
};

// virtual means will be and can be override later 
// = 0; means the children class need to implement or else will get compile error 
class hittable
{
public:
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

