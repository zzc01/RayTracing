#pragma once

#include "hittable.h"

#include <memory>
#include <vector>

//using std::shared_ptr; 
//using std::make_shared; 

class hittable_list : public hittable {
public: 
	hittable_list() = default; 
	hittable_list(std::shared_ptr<hittable> object) { add(object); }

	void clear() { objects.clear(); }
	void add(std::shared_ptr<hittable> object) { objects.push_back(object); }

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override; 

public: 
	// hittable* shared_ptr
	// std::vector< hittable* > 
	std::vector<std::shared_ptr<hittable>> objects;
};

//==============================================================================================
// 
// A project to learn and practice ray tracing. 
// Reference: “Ray Tracing in One Weekend.” raytracing.github.io/books/RayTracingInOneWeekend.html
// 
//==============================================================================================

// a ray v.s. multipl objects 
bool hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
	hit_record temp_rec; 
	bool hit_anything = false; 
	double closest_so_far = t_max; 

	for (const std::shared_ptr<hittable>& object : objects)
	{
		if (object->hit(r, t_min, closest_so_far, temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec; 
		}
	}
	return hit_anything; 
}