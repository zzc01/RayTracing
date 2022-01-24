//========================================================================================
// 
// A project to learn and practice ray tracing. 
// Reference: “Ray Tracing in One Weekend.” 
// raytracing.github.io/books/RayTracingInOneWeekend.html
// 
//========================================================================================

#include <iostream>
#include "camera.h"
#include "ConstantsAndUtilities.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "material.h"

hittable_list random_scene()
{
	hittable_list world; 
	// the ground
	std::shared_ptr<lambertian> ground_material = std::make_shared<lambertian>(color(0.5, 0.5, 0.5));
	world.add(std::make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

	// the random objects
	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			double choose_mat = random_double();
			// random the x and z. but fix the y 
			point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

			// what is this for? 
			if ((center - point3(4, 0.2, 0)).length() > 0.9)
			{
				std::shared_ptr<material> sphere_material; 
				if (choose_mat < 0.8)
				{
					// diffuse 
					// why this kind of random? 
					color albedo = color::random() * color::random();
					sphere_material = std::make_shared<lambertian>(albedo);
					world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
				}
				else if (choose_mat < 0.95)
				{
					// metal 
					// why this kind of random? 
					color albedo = color::random(0.5, 1);
					double fuzz = random_double(0.0, 0.5);
					sphere_material = std::make_shared<metal>(albedo, fuzz);
					world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
				}
				else 
				{
					// glass 
					sphere_material = std::make_shared<dielectric>(1.5);
					world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
				}

			}
		}
	}

	std::shared_ptr<dielectric> material1 = std::make_shared<dielectric>(1.5);
	world.add(std::make_shared<sphere>(point3(0, 1, 0), 1.0, material1));	

	std::shared_ptr<lambertian> material2 = std::make_shared<lambertian>(color(0.4, 0.2, 0.1));
	world.add(std::make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

	std::shared_ptr<metal> material3 = std::make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
	world.add(std::make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

	return world; 
}

color ray_color(const ray& r, const hittable& world, int depth)
{
	hit_record rec; 

	// If exceed the ray bounce limit, no more light is gathered 
	if (depth <= 0) 
		return color(0.0, 0.0, 0.0);

	if (world.hit(r, 1e-5, infinity, rec))
	{
		ray scattered; 
		color attenuation; 
		//point3 target = rec.p + random_in_hemisphere(rec.normal);
		//return 0.5 * ray_color(ray(rec.p, target - rec.p), world, depth - 1);
		if(rec.mat_ptr->scatter(r, rec, attenuation, scattered))
			return attenuation * ray_color(scattered, world, depth - 1);
		return color(0, 0, 0);
	}
	vec3 unit_direction = unit_vector(r.direction());
	double t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

#include <chrono>

struct Timer {
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
	//std::chrono::duration<float> duration;
public:
	Timer() {
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}
	~Timer() {
		stop();
	}
	void stop() {
		auto m_endTimepoint = std::chrono::high_resolution_clock::now();
		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(m_endTimepoint).time_since_epoch().count();
		auto duration = (end - start) * 0.001;

		double sec = duration * 0.001;
		// output data input a tracker that measures things 
		std::cerr << "Timer took " << duration << "ms (" << sec << "sec)\n";
		//std::cout << "Timer took " << duration << "ms (" << sec << "sec)\n";
	}
};

int main()
{
	Timer timer;

	// Image 
	const double aspect_ratio = 3.0 / 2.0;
	const int image_width = 1200;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int samples_per_pixel = 500; 
	const int max_depth = 50; 

	// World
	hittable_list world = random_scene();

	// Camera 
	point3 lookfrom(13, 2, 3);
	point3 lookat(0, 0, 0);
	vec3 vup(0, 1, 0);
	// why hard code this to 10.0? (lookfrom - lookat).length();
	double dist_to_focus = 10;
	double aperature = 0.1; 
	camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperature, dist_to_focus);

	// Render 
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; j--)	// 0 ~ 255, from bottom to top  
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < image_width; i++) // from left to right 
		{
			color pixel_color(0, 0, 0);
			for (int s = 0; s < samples_per_pixel; s++)
			{
				double u = (i + random_double()) / (image_width - 1);
				double v = (j + random_double()) / (image_height - 1);
				ray r = cam.get_ray(u, v);
				pixel_color += ray_color(r, world, max_depth);
			}
			write_color(std::cout, pixel_color, samples_per_pixel);
		}
	}
	std::cerr << "\nDone.\n";
}
