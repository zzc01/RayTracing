//==============================================================================================
// 
// A project to learn and practice ray tracing. 
// Reference: “Ray Tracing in One Weekend.” raytracing.github.io/books/RayTracingInOneWeekend.html
// 
//==============================================================================================

#if 0


#include <iostream>
#include "vec3.h"
#include "ray.h"

void write_color(std::ostream& out, color pixel_color)
{
	out << static_cast<int>(255.999 * pixel_color.x()) << ' '
		<< static_cast<int>(255.999 * pixel_color.y()) << ' '
		<< static_cast<int>(255.999 * pixel_color.z()) << '\n';
}

color ray_color(const ray& r)
{
	// only affected by the y? 
	// but different point has different ray (0,0,0), (x, y, z=-1)
	vec3 unit_direction = unit_vector(r.direction());
	double t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
	//return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.0, 0.0, 0.0);
}


int main()
{
	// Image 
	const double aspect_ratio = 16.0 / 9.0;
	//const int image_width = 256; 
	const int image_width = 400;
	//const int image_height = 256;
	const int image_height = static_cast<int>(image_width / aspect_ratio);

	// Camera 
	double viewport_height = 2.0;
	double viewport_width = aspect_ratio * viewport_height;
	double focal_length = 1.0;

	point3 origin = point3(0, 0, 0);
	vec3 horizontal = vec3(viewport_width, 0, 0);
	vec3 vertical = vec3(0, viewport_height, 0);
	point3 lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

	// Render 
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n";
	std::cout << "255\n";

	for (int j = image_height - 1; j >= 0; j--)	// 0 ~ 255, from bottom to top  
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < image_width; i++) // from left to right 
		{
			double u = double(i) / (image_width - 1);
			double v = double(j) / (image_height - 1);
			ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
			color pixel_color = ray_color(r);

			//color pixel_color(double(i) / (image_width - 1), double(j) / (image_width - 1), 0.25);
			write_color(std::cout, pixel_color);
			/*
			auto r = double(i) / (image_width - 1);
			auto g = double(j) / (image_height - 1);
			auto b = 0.25;

			int ir = static_cast<int>(255.999 * r);
			int ig = static_cast<int>(255.999 * g);
			int ib = static_cast<int>(255.999 * b);
			std::cout << ir << ' ' << ig << ' ' << ib << "\n";
			*/
		}
	}
	std::cerr << "\nDone.\n";
}

#endif 