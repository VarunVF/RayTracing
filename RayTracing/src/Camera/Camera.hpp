#pragma once

#include <cstdint>

#include "../Color3/Color3.hpp"
#include "../HittableList/HittableList.hpp"
#include "../Ray3/Ray3.hpp"


class Camera
{
public:
	double aspect_ratio      = 1.0;		// Ratio of image width to height
	int    image_width       = 100;		// Width of rendered image in pixels
	int    samples_per_pixel = 10;		// Antialiasing sample count


	void render(const HittableList& world, const char* filename);
	void renderPNG(const HittableList& world, const char* filename);

private:
	int    image_height;				// Rendered image height
	double pixel_samples_scale;			// Color scale factor
	Point3 center;						// Camera center
	Point3 pixel00_loc;					// Location of pixel (0, 0)
	Vec3   pixel_delta_u;				// Offset to pixel to the right
	Vec3   pixel_delta_v;				// Offset to pixel below

	std::vector<uint8_t> image_buffer;


	void initialise();
	Ray3 getRay(int i, int j) const;
	Vec3 sampleSquare() const;
	Color3 rayColor(const Ray3& ray, const HittableList& world) const;

	// Write a png file in RGB format.
	int writePNG(const char* filename, unsigned char* image,
		unsigned int width, unsigned int height, unsigned int bytes_per_pixel = 3);
};

