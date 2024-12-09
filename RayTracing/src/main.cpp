#include <iostream>

#include "Camera/Camera.hpp"
#include "Hittable/Plane.hpp"
#include "Hittable/Sphere.hpp"
#include "HittableList/HittableList.hpp"
#include "Timer/Timer.hpp"


int main(void)
{
	Camera camera;
	camera.aspect_ratio      = 16.0 / 9.0;
	camera.image_width       = 400;
	camera.samples_per_pixel = 50;
	camera.max_depth         = 50;

	HittableList world;
	world.add(std::make_shared<Sphere>(Point3(0, 0, -1.0), 0.5));
	world.add(std::make_shared<Sphere>(Point3(0, -100.5, -1.0), 100));	// Ground
	
	{
		Timer timer;
		camera.renderPNG(world, "lambertian_diffuse_gamma_corrected.png");
	}

	std::clog << "Renders finished (press [Enter])...";
	std::cin.get();
}
