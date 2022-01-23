//========================================================================================
// 
// A project to learn and practice ray tracing. 
// Reference: “Ray Tracing in One Weekend.” 
// raytracing.github.io/books/RayTracingInOneWeekend.html
// 
//========================================================================================

#pragma once
#include "ConstantsAndUtilities.h"
#include "hittable.h"

class sphere : public hittable
{
public: 
	sphere() = default;
	sphere(point3 cen, double r, std::shared_ptr<material> m)
		: center(cen), radius(r), mat_ptr(m) {};

	// you also have to write virtual here in the children class? 
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override; 
	
public: 
	point3 center; 
	double radius;
	std::shared_ptr<material> mat_ptr; 
};



bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
	vec3 oc = r.origin() - center;
	double a = dot(r.direction(), r.direction());
	double half_b = dot(oc, r.direction());
	double c = dot(oc, oc) - radius * radius;
	double discriminant = half_b * half_b - a * c;
	if (discriminant < 0) return false;

	double sqrtd = std::sqrt(discriminant);
	// Find the nearest root that lies in the acceptable range ???
	double root = (-half_b - sqrtd) / a;
	if (root < t_min || t_max < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < t_min || t_max < root)
			return false;
	}
	rec.t = root;
	rec.p = r.at(rec.t);
	vec3 outward_normal = (rec.p - center) / radius;
	rec.set_face_nromal(r, outward_normal);
	rec.mat_ptr = mat_ptr;
	return true;
}

