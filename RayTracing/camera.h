#pragma once

#include "ConstantsAndUtilities.h"

class camera {
public:
	camera(
		point3 lookfrom,
		point3 lookat,
		vec3 vup,
		double vfov,
		double aspect_ratio,
		double aperature,
		double focus_dist)
	{
		double theta = degrees_to_radians(vfov);
		double h = tan(theta / 2);
		//const double aspect_ratio = 16.0 / 9.0;
		double viewport_height = 2.0 * h;
		double viewport_width = aspect_ratio * viewport_height;
		double focal_length = 1.0;

		w = unit_vector(lookfrom - lookat);
		u = unit_vector(cross(vup, w));
		v = unit_vector(cross(w, u));

		origin = lookfrom;
		horizontal = focus_dist * viewport_width * u;
		vertical = focus_dist * viewport_height * v;
		lower_left_corner = origin - (horizontal / 2) - (vertical / 2) - focus_dist * w;

		lens_radius = aperature / 2;
	}

	ray get_ray(double s, double t) const
	{
		vec3 rd = lens_radius * random_in_unit_disk();
		vec3 offset = u * rd.x() + v * rd.y();
		return ray(
			origin + offset, 
			lower_left_corner + s * horizontal + t * vertical - origin - offset
		);
	}

private:
	point3 origin;
	point3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	vec3 u, v, w;
	double lens_radius;
};