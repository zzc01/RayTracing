//==============================================================================================
// 
// A project to learn and practice ray tracing. 
// Reference: �Ray Tracing in One Weekend.� raytracing.github.io/books/RayTracingInOneWeekend.html
// 
//==============================================================================================

#if 0

#include <iostream>
#include "ConstantsAndUtilities.h"

//bool hit_sphere(const point3& center, double radius, const ray& r)
//{
//	vec3 oc = r.origin() - center; 
//	double a = dot(r.direction(), r.direction()); 
//	double b = 2.0 * dot(oc, r.direction()); 
//	double c = dot(oc, oc) - radius * radius;
//	double discriminant = b * b - 4 * a * c; 
//	return (discriminant > 0); 
//}

double hit_sphere(const point3& center, double radius, const ray& r)
{
	vec3 oc = r.origin() - center; 
	double a = dot(r.direction(), r.direction()); 
	double b = 2.0 * dot(oc, r.direction()); 
	double c = dot(oc, oc) - radius * radius;
	double discriminant = b * b - 4 * a * c; 
	if (discriminant < 0)
	{
		return -1; 
	}
	else
	{
		return (-b - std::sqrt(discriminant)) / (2.0 * a); 
	}
}

//color ray_color(const ray& r)
//{
//	if (hit_sphere(point3(0, 0, -1.0), 0.5, r)) 
//		return color(1, 0, 0);
//	vec3 unit_direction = unit_vector(r.direction());
//	double t = 0.5 * (unit_direction.y() + 1.0);
//	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
//}

color ray_color(const ray& r)
{
	double t = hit_sphere(point3(0, 0, -1.0), 0.5, r); 
	if (t > 0.0)
	{
		vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));
		return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
	}
	vec3 unit_direction = unit_vector(r.direction());
	t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main()
{
	// Image 
	const double aspect_ratio = 16.0 / 9.0; 
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);

	// Camera 
	double viewport_height = 2.0; 
	double viewport_width = aspect_ratio * viewport_height;
	double focal_length = 1.0; 

	point3 origin = point3(0, 0, 0);
	vec3 horizontal = vec3(viewport_width, 0, 0);
	vec3 vertical = vec3(0, viewport_height, 0); 
	point3 lower_left_corner = origin - (horizontal / 2) - (vertical / 2) - vec3(0, 0, focal_length);

	// Render 
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n";
	std::cout << "255\n" ;

	for (int j = image_height - 1; j >= 0; j--)	// 0 ~ 255, from bottom to top  
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < image_width; i++) // from left to right 
		{
			double u = double(i) / (image_width - 1);
			double v = double(j) / (image_height - 1);
			ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
			color pixel_color = ray_color(r); 

			write_color(std::cout, pixel_color);
		}
	}
	std::cerr << "\nDone.\n";
}

#endif 
