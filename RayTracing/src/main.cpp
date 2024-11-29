#include <cstdint>
#include <cstdio>
#include <chrono>
#include <fstream>

#include "Camera/Camera.hpp"
#include "Hittable/Hittable.hpp"
#include "HittableList/HittableList.hpp"
#include "Hittable/Sphere.hpp"
#include "raytracing.hpp"

#include "Timer/Timer.hpp"


int main(void)
{
	Camera camera;
	camera.aspect_ratio = 16.0 / 9.0;
	camera.image_width = 400;
	camera.samples_per_pixel = 50;

	HittableList world;

	for (double i = 0; i < 3; i++)
	{
		Vec3 center(-0.5 + 1.1 * i, -0.3 * i, -1.0 - i / 2);
		auto radius = 0.5;
		auto sphere = std::make_shared<Sphere>(center, radius);
		world.add(sphere);
	}
	world.add(std::make_shared<Sphere>(Point3( 1.5,  0.9,   -1.0), 0.5));
	world.add(std::make_shared<Sphere>(Point3(-0.5, -1.7,   -2.0), 0.2));
	world.add(std::make_shared<Sphere>(Point3( 0.0, -100.5, -1.0), 100));	// Ground

	// camera.render(world, "new_world.ppm");
	{
		Timer timer;
		camera.renderPNG(world, "new_world.png");
	}

	std::clog << "Renders finished (press [Enter])...";
	std::cin.get();
}
