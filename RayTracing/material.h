//========================================================================================
// 
// A project to learn and practice ray tracing. 
// Reference: �Ray Tracing in One Weekend.� 
// raytracing.github.io/books/RayTracingInOneWeekend.html
// 
//========================================================================================

#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

#include "ConstantsAndUtilities.h"

struct hit_record; 

class material
{
public: 
	virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const = 0; 
};


class lambertian : public material
{
public: 
	lambertian(const color& a) : albedo(a) {}

	virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override
	{
		// why can this sctter_direction be tilted to other direction? 
		vec3 scatter_direction = rec.normal + random_unit_vector();

		// Catch degrenerate scatter direction 
		if (scatter_direction.near_zero())
			scatter_direction = rec.normal; 

		scattered = ray(rec.p, scatter_direction);
		attenuation = albedo;
		return true; 
	}
public: 
	color albedo;
};


class metal : public material
{
public:
	metal(const color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}
public: 
	virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override
	{
		vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
		scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
		attenuation = albedo; 
		return (dot(scattered.direction(), rec.normal) > 0);
	}
public:
	color albedo; 
	double fuzz;
};

#endif 

