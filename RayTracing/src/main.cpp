#include <iostream>

#include "Camera/Camera.hpp"
#include "Hittable/Sphere.hpp"
#include "Hittable/Triangle.hpp"
#include "HittableList/HittableList.hpp"
#include "Material/Lambertian.hpp"
#include "Material/Metal.hpp"
#include "Material/Dielectric.hpp"
#include "Material/DiffuseLight.hpp"
#include "Timer/Timer.hpp"

#include "raytracing.hpp"


void cornell_box(const char* filename)
{
	Camera camera;
	HittableList world;

	// actual render
	camera.aspect_ratio = 1.0;
	camera.image_width = 600;
	camera.samples_per_pixel = 200;
	camera.max_depth = 50;

	// for devt speed
	//camera.aspect_ratio = 1.0;
	//camera.image_width = 400;
	//camera.samples_per_pixel = 15;
	//camera.max_depth = 15;

	auto red = std::make_shared<Lambertian>(Color3(.65, .05, .05));
	auto white = std::make_shared<Lambertian>(Color3(.73, .73, .73));
	auto green = std::make_shared<Lambertian>(Color3(.12, .45, .15));
	auto light = std::make_shared<DiffuseLight>(Color3(2, 2, 2));


	double maxZ = 1;

	// white face at front
	world.add(std::make_shared<Triangle>(
		Point3(-1, -1, -2), Point3(1, -1, -2), Point3(1, 1, -2), white
	));
	world.add(std::make_shared<Triangle>(
		Point3(-1, 1, -2), Point3(-1, -1, -2), Point3(1, 1, -2), white
	));

	// green face at left
	world.add(std::make_shared<Triangle>(
		Point3(-1, 1, maxZ), Point3(-1, 1, -2), Point3(-1, -1, maxZ), green
	));
	world.add(std::make_shared<Triangle>(
		Point3(-1, -1, -2), Point3(-1, 1, -2), Point3(-1, -1, maxZ), green
	));

	// red face at right
	world.add(std::make_shared<Triangle>(
		Point3(1, 1, -2), Point3(1, -1, -2), Point3(1, 1, maxZ), red
	));
	world.add(std::make_shared<Triangle>(
		Point3(1, -1, maxZ), Point3(1, -1, -2), Point3(1, 1, maxZ), red
	));

	// white face at top
	world.add(std::make_shared<Triangle>(
		Point3(-1, 1, -2), Point3(1, 1, -2), Point3(1, 1, maxZ), white
	));
	world.add(std::make_shared<Triangle>(
		Point3(-1, 1, -2), Point3(-1, 1, maxZ), Point3(1, 1, maxZ), white
	));

	// white face at bottom
	world.add(std::make_shared<Triangle>(
		Point3(-1, -1, -2), Point3(1, -1, -2), Point3(1, -1, maxZ), white
	));
	world.add(std::make_shared<Triangle>(
		Point3(-1, -1, -2), Point3(-1, -1, maxZ), Point3(1, -1, maxZ), white
	));

	// light source
	world.add(std::make_shared<Triangle>(
		Point3(-0.5, 0.99, -2), Point3(0.5, 0.99, -2), Point3(0.5, 0.99, -1), light
	));
	world.add(std::make_shared<Triangle>(
		Point3(-0.5, 0.99, -2), Point3(-0.5, 0.99, -1), Point3(0.5, 0.99, -1), light
	));

	// spheres
	auto metal = std::make_shared<Metal>(Color3(0.14, 0.42, 0.48));
	world.add(std::make_shared<Sphere>(
		Point3(-0.3, -0.7, -1.5), .3, metal
	));

	auto glass = std::make_shared<Dielectric>(1.5);
	world.add(std::make_shared<Sphere>(
		Point3(0.33, -0.7, -1.4), .3, glass
	));

	{
		Timer timer;
		camera.renderPNGParallel(world, filename);
	}
}

void total_internal_reflection(const char* filename)
{
	HittableList world;

	// Materials
	auto material_ground = std::make_shared<Lambertian>(Color3(0.8, 0.8, 0.0));
	auto material_center = std::make_shared<Lambertian>(Color3(0.1, 0.2, 0.5));
	auto material_left   = std::make_shared<Dielectric>(1.00 / 1.33);
	auto material_right  = std::make_shared<Metal>(Color3(0.8, 0.6, 0.2), 1.0);

	// Spheres
	world.add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
	world.add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.2), 0.5, material_center));
	world.add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, material_left));
	world.add(std::make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, material_right));

	Camera camera;

	camera.aspect_ratio = 16.0 / 9.0;
	camera.image_width = 800;
	camera.samples_per_pixel = 100;
	camera.max_depth = 50;

	{
		Timer timer;
		camera.renderPNGParallel(world, filename);
	}
}

void dielectric_reflectance(const char* filename)
{
	HittableList world;

	// Materials
	auto material_ground = std::make_shared<Lambertian>(Color3(0.8, 0.8, 0.0));
	auto material_center = std::make_shared<Lambertian>(Color3(0.1, 0.2, 0.5));
	auto material_left   = std::make_shared<Dielectric>(1.50);
	auto material_bubble = std::make_shared<Dielectric>(1.00 / 1.50);  // Air bubble
	auto material_right  = std::make_shared<Metal>(Color3(0.8, 0.6, 0.2), 1.0);

	// Spheres
	world.add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
	world.add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.2), 0.5, material_center));
	world.add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, material_left));
	world.add(std::make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, material_right));
	world.add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.4, material_bubble));

	Camera camera;

	camera.aspect_ratio = 16.0 / 9.0;
	camera.image_width = 800;
	camera.samples_per_pixel = 100;
	camera.max_depth = 50;

	{
		Timer timer;
		camera.renderPNGParallel(world, filename);
	}

}

void wide_angle(const char* filename)
{
	HittableList world;

	auto R = std::cos(pi / 4);

	// Materials
	auto material_left   = std::make_shared<Lambertian>(Color3(0.8, 0.3, 0.7));
	auto material_right  = std::make_shared<Lambertian>(Color3(0.8, 0.6, 0.2));

	// Spheres
	world.add(std::make_shared<Sphere>(Point3(-R, 0.0, -1.0), R, material_left));
	world.add(std::make_shared<Sphere>(Point3( R, 0.0, -1.0), R, material_right));

	Camera camera;

	camera.aspect_ratio = 16.0 / 9.0;
	camera.image_width = 800;
	camera.samples_per_pixel = 100;
	camera.max_depth = 50;

	camera.vfov = 90;

	{
		Timer timer;
		camera.renderPNGParallel(world, filename);
	}
}

void luminous_no_sky(const char* filename)
{
	HittableList world;

	// Materials
	auto material_ground = std::make_shared<Lambertian>(Color3(0.8, 0.8, 0.0));
	auto material_center = std::make_shared<DiffuseLight>(Color3(0.8, 0.6, 0.2));
	auto material_left = std::make_shared<Dielectric>(1.33);
	auto material_right = std::make_shared<Lambertian>(Color3(0.1, 0.2, 0.5));

	// Spheres
	world.add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
	world.add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.2), 0.5, material_center));
	world.add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, material_left));
	world.add(std::make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, material_right));

	Camera camera;

	camera.aspect_ratio = 16.0 / 9.0;
	camera.image_width = 800;
	camera.samples_per_pixel = 100;
	camera.max_depth = 50;

	camera.do_draw_sky = false;

	{
		Timer timer;
		camera.renderPNGParallel(world, filename);
	}
}

void luminous_sky(const char* filename)
{
	HittableList world;

	// Materials
	auto material_ground = std::make_shared<Lambertian>(Color3(0.8, 0.8, 0.0));
	auto material_center = std::make_shared<DiffuseLight>(Color3(0.9, 0.75, 0.7));
	auto material_left = std::make_shared<Dielectric>(1.33);
	auto material_right = std::make_shared<Lambertian>(Color3(0.1, 0.2, 0.5));

	// Spheres
	world.add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
	world.add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.2), 0.5, material_center));
	world.add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, material_left));
	world.add(std::make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, material_right));

	Camera camera;

	camera.aspect_ratio = 16.0 / 9.0;
	camera.image_width = 800;
	camera.samples_per_pixel = 100;
	camera.max_depth = 50;

	camera.do_draw_sky = true;

	{
		Timer timer;
		camera.renderPNGParallel(world, filename);
	}
}


int main(void)
{
	// cornell_box("cornell-box-spheres.png");
	// total_internal_reflection("underwater-tir.png");
	// dielectric_reflectance("schlick-approx.png");
	// wide_angle("fov90.png");
	// luminous_no_sky("luminous-no-sky.png");
	luminous_sky("luminous-sky.png");

	std::clog << "Renders finished (press [Enter])...";
	std::cin.get();
}
