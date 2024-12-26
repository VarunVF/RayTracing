#pragma once

#include "../Color3/Color3.hpp"
#include "../HittableList/HittableList.hpp"
#include "../Ray3/Ray3.hpp"


class Camera
{
public:
	double aspect_ratio      = 1.0;		// Ratio of image width to height
	int    image_width       = 100;		// Width of rendered image in pixels
	int    samples_per_pixel = 10;		// Antialiasing sample count
	int    max_depth         = 10;		// Maximum number of child rays


	// Render scene to a PPM file
	void renderPPM(const HittableList& world, const char* filename);

	// Render scene to a PNG file
	void renderPNG(const HittableList& world, const char* filename);

	// Render scene to a PNG file (multithreaded)
 	void renderPNGParallel(const HittableList& world, const char* filename);

private:
	void renderRows(int startRow, int endRow, const HittableList& world);

private:
	int    image_height        = 0;		// Rendered image height
	double pixel_samples_scale = 0.0;	// Color scale factor
	Point3 center;						// Camera center
	Point3 pixel00_loc;					// Location of pixel (0, 0)
	Vec3   pixel_delta_u;				// Offset to pixel to the right
	Vec3   pixel_delta_v;				// Offset to pixel below

	std::vector<uint8_t> image_buffer;


	void initialise();
	
	// Construct a ray from the camera towards a randomly sampled point around pixel (i, j).
	Ray3 getRay(int i, int j, uint32_t& seed) const;
	
	// Construct a vector to a random point in a pixel's square bounds.
	// Range: x in [-0.5, 0.5), y in [-0.5, 0.5), z = 0
	Vec3 sampleSquare(uint32_t& seed) const;
	
	// Get the color for a given scene ray.
	Color3 rayColor(const Ray3& ray, const int depth,
		const HittableList& world, uint32_t& seed) const;

	// Write to a PNG file from a buffer
	int writePNG(const char* filename, unsigned char* image,
		unsigned int width, unsigned int height, unsigned int bytes_per_pixel = 3);
};
