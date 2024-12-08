#include <iostream>

#include "Camera/Camera.hpp"
#include "HittableList/HittableList.hpp"
#include "Hittable/Sphere.hpp"
#include "Hittable/Plane.hpp"
#include "Timer/Timer.hpp"


int main(void)
{
	Camera camera;
	camera.aspect_ratio = 16.0 / 9.0;
	camera.image_width = 400;
	camera.samples_per_pixel = 50;

	HittableList world;
		
	world.add(std::make_shared<Sphere>(Point3( 0.0, -100.5, -1.0), 100));	// Ground
	
	world.add(std::make_shared<Sphere>(Point3(0, 0, -1.0), 0.5));
	world.add(std::make_shared<Plane>(Point3(0, 0, -1.0), Vec3(-1.0, 1.0, 1.0),
		Interval(-1.0, 1.0), Interval(-1.0, 1.0), Interval(-5.0, 0.0)
	));

	{
		Timer timer;
		camera.renderPNG(world, "new_world.png");
	}

	std::clog << "Renders finished (press [Enter])...";
	std::cin.get();
}
