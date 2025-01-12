#include <fstream>
#include <thread>
#include <vector>

#include <zlib.h>
#include <png.h>

#include "Camera.hpp"
#include "Material/Material.hpp"
#include "Color3/Color3.hpp"
#include "raytracing.hpp"



void Camera::renderPPM(const HittableList& world, const char* filename)
{
	initialise();
	uint32_t seed;

	std::ofstream imageFile(filename, std::ios_base::out);
	if (!imageFile.is_open())
	{
		std::cerr << "Error: could not open file.\n";
		return;
	}

	imageFile << "P3\n"
		<< image_width << " " << image_height << "\n"
		<< "255" << "\n";

	for (int j = 0; j < image_height; j++)
	{
		std::clog << "Scanlines remaining: " << image_height - j << "\n";

		for (int i = 0; i < image_width; i++)
		{
			seed = i * j;
			Color3 pixel_color(0.0, 0.0, 0.0);
			for (int sample = 0; sample < samples_per_pixel; sample++)
			{
				Ray3 random_ray = getRay(i, j, seed);
				pixel_color += rayColor(random_ray, max_depth, world, seed);
			}
			pixel_color *= pixel_samples_scale;
			writeColor(imageFile, pixel_color);
		}
	}

	std::clog << "Render finished and saved to " << filename << "\n";
}

void Camera::renderPNG(const HittableList& world, const char* filename)
{
	initialise();
	uint32_t seed;

	std::cout << "Render started (single-threaded).\n";

	// Write colors to the buffer
	for (int j = 0; j < image_height; j++)
	{
		// std::cout << "Scanlines remaining: " << image_height - j << "\n";

		for (int i = 0; i < image_width; i++)
		{
			seed = i * j;
			Color3 pixel_color(0.0, 0.0, 0.0);
			for (int sample = 0; sample < samples_per_pixel; sample++)
			{
				Ray3 random_ray = getRay(i, j, seed);
				pixel_color += rayColor(random_ray, max_depth, world, seed);
			}
			pixel_color *= pixel_samples_scale;
			writeColor(image_buffer, pixel_color);
		}
	}
	
	// Write PNG using the buffer
	writePNG(filename, image_buffer.data(), image_width, image_height);

	std::cout << "Render finished and saved to " << filename << "\n";
}

void Camera::renderRows(int startRow, int endRow, const HittableList& world)
{
	uint32_t seed;

	for (int j = startRow; j < endRow; j++)
		for (int i = 0; i < image_width; i++)
		{
			seed = i * j;
			Color3 pixel_color(0.0, 0.0, 0.0);
			for (int sample = 0; sample < samples_per_pixel; sample++)
			{
				Ray3 random_ray = getRay(i, j, seed);
				pixel_color += rayColor(random_ray, max_depth, world, seed);
			}
			pixel_color *= pixel_samples_scale;
			int offset = (j * image_width + i) * 3;
			writeColorAtPos(image_buffer.data() + offset, pixel_color);
		}
}

void Camera::renderPNGParallel(const HittableList& world, const char* filename)
{
	initialise();

	// default construct (all 0)
	image_buffer.resize(3 * image_width * image_height);

	const int maxThreadCount = std::thread::hardware_concurrency();
	const int rowsPerThread  = image_height / maxThreadCount;
	std::vector<std::thread> workers;
	workers.reserve(maxThreadCount);
	
	std::cout << "Render started with " << maxThreadCount << " threads, "
		<< rowsPerThread << " rows per thread.\n";

	// Start and run threads
	for (int t = 0; t < maxThreadCount; t++)
	{
		int startRow = t * rowsPerThread;
		int endRow = (t == maxThreadCount - 1) ?
			image_height : startRow + rowsPerThread;
		workers.emplace_back(&Camera::renderRows, this, startRow, endRow, world);
	}

	// Wait for threads to complete
	for (auto& worker : workers)
		worker.join();

	// Write PNG file using the buffer
	writePNG(filename, image_buffer.data(), image_width, image_height);

	std::cout << "Render finished and saved to " << filename << "\n";
}

void Camera::initialise()
{
	image_height = (int)(image_width / aspect_ratio);
	image_height = image_height < 1 ? 1 : image_height;	// Must be at least 1
	pixel_samples_scale = 1.0 / samples_per_pixel;

	int buffer_size = 3 * image_width * image_height;
	image_buffer.reserve(buffer_size);					// Set capacity (RGB = 3 channels)

	// Viewport dimensions
	double focal_length = 1.0;							// Camera to viewport distance
	double theta = degrees_to_radians(vfov);
	double h = std::tan(theta/2);
	double viewport_height = 2.0 * h * focal_length;
	double viewport_width = viewport_height * ((double)image_width / image_height);
	center = Point3(0, 0, 0);

	// Vectors across viewport edges
	Vec3 viewport_u(viewport_width, 0, 0);				// horizontal
	Vec3 viewport_v(0, -viewport_height, 0);			// vertical

	// Delta vectors (step size)
	pixel_delta_u = viewport_u / image_width;
	pixel_delta_v = viewport_v / image_height;

	// Upper left pixel
	Vec3 viewport_upper_left = center
		- Vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;

	// Viewport is inset by half of pixel separation
	pixel00_loc = viewport_upper_left
		- 0.5 * (pixel_delta_u + pixel_delta_v);
}

Ray3 Camera::getRay(int i, int j, uint32_t& seed) const
{
	Point3 offset = sampleSquare(seed);
	Point3 sample_pixel = pixel00_loc
		+ ((i + offset.x()) * pixel_delta_u)
		+ ((j + offset.y()) * pixel_delta_v);

	Point3 ray_origin = center;
	Vec3 ray_direction = sample_pixel - center;
	return Ray3(ray_origin, ray_direction);
}

Vec3 Camera::sampleSquare(uint32_t& seed) const
{
	return Vec3(
		random_double(seed) - 0.5,
		random_double(seed) - 0.5,
		0.0
	);
}

Color3 Camera::rayColor(const Ray3& ray, const int depth,
	const HittableList& world, uint32_t& seed) const
{
	if (depth <= 0)
		return Color3(0, 0, 0);

	HitRecord rec;
	if (world.hit(ray, Interval(0.001, infinity), rec))
	{
		Color3 attenuation;
		Ray3 scattered;

		Color3 emissionColor = rec.material->emitted(ray, seed);
		Color3 scatteredColor;
		if (rec.material->scatter(ray, rec, attenuation, scattered, seed))
			scatteredColor = attenuation * rayColor(scattered, depth - 1, world, seed);
		
		return emissionColor + scatteredColor;
	}

	Vec3 unit_direction = ray.direction().unit_vector();
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return do_draw_sky * lerp(Color3(1.0, 1.0, 1.0), Color3(0.5, 0.7, 1.0), t);
}

int Camera::writePNG(const char* filename, unsigned char* image, unsigned int width, unsigned int height, unsigned int bytes_per_pixel)
{
	FILE* fp;
	png_structp png_ptr;
	png_infop info_ptr;
	// png_colorp palette;

	/* Open the file */
	fp = fopen(filename, "wb");
	if (fp == NULL)
		return 1;

	/* Create and initialize the png_struct with the desired error handler
	 * functions.  If you want to use the default stderr and longjump method,
	 * you can supply NULL for the last three parameters.  We also check that
	 * the library version is compatible with the one used at compile time,
	 * in case we are using dynamically linked libraries.  REQUIRED.
	 */
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,
		NULL, NULL, NULL);
	if (png_ptr == NULL)
	{
		fclose(fp);
		return 2;
	}

	/* Allocate/initialize the image information data.  REQUIRED. */
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL)
	{
		fclose(fp);
		png_destroy_write_struct(&png_ptr, NULL);
		return 3;
	}

	/* Set up error handling.  REQUIRED if you aren't supplying your own
	 * error handling functions in the png_create_write_struct() call.
	 */
	if (setjmp(png_jmpbuf(png_ptr)))
	{
		/* If we get here, we had a problem writing the file. */
		fclose(fp);
		png_destroy_write_struct(&png_ptr, &info_ptr);
		return 4;
	}

	/* One of the following I/O initialization functions is REQUIRED. */

   /* I/O initialization method 1 */
   /* Set up the output control if you are using standard C streams. */
	png_init_io(png_ptr, fp);


	/* This is the hard way. */

/* Set the image information here.  Width and height are up to 2^31,
 * bit_depth is one of 1, 2, 4, 8 or 16, but valid values also depend on
 * the color_type selected.  color_type is one of PNG_COLOR_TYPE_GRAY,
 * PNG_COLOR_TYPE_GRAY_ALPHA, PNG_COLOR_TYPE_PALETTE, PNG_COLOR_TYPE_RGB,
 * or PNG_COLOR_TYPE_RGB_ALPHA.  interlace is either PNG_INTERLACE_NONE or
 * PNG_INTERLACE_ADAM7, and the compression_type and filter_type MUST
 * currently be PNG_COMPRESSION_TYPE_BASE and PNG_FILTER_TYPE_BASE.
 * REQUIRED.
 */
	png_set_IHDR(png_ptr, info_ptr, width, height, 8,
		PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

	/* Set the palette if there is one.  REQUIRED for indexed-color images. */
	//palette = (png_colorp)png_malloc(png_ptr,
	//	PNG_MAX_PALETTE_LENGTH * (sizeof(png_color)));
	/* ... Set palette colors ... */
	//png_set_PLTE(png_ptr, info_ptr, palette, PNG_MAX_PALETTE_LENGTH);
	/* You must not free palette here, because png_set_PLTE only makes a link
	 * to the palette that you allocated.  Wait until you are about to destroy
	 * the png structure.
	 */

	 /* Optional significant bit (sBIT) chunk. */
	png_color_8 sig_bit;

	/* Otherwise, if we are dealing with a color image then */
	sig_bit.red = 8;
	sig_bit.green = 8;
	sig_bit.blue = 8;

	png_set_sBIT(png_ptr, info_ptr, &sig_bit);

	/* Optional gamma chunk is strongly suggested if you have any guess
	 * as to the correct gamma of the image. */
	//const double gamma = 1 / 0.5;
	//png_set_gAMA(png_ptr, info_ptr, gamma);

	/* Other optional chunks like cHRM, bKGD, tRNS, tIME, oFFs, pHYs. */

	/* Note that if sRGB is present, the gAMA and cHRM chunks must be ignored
	 * on read and, if your application chooses to write them, they must
	 * be written in accordance with the sRGB profile.
	 */

	 /* Write the file header information.  REQUIRED. */
	png_write_info(png_ptr, info_ptr);

	/* If you want, you can write the info in two steps, in case you need to
	 * write your private chunk ahead of PLTE:
	 *
	 *   png_write_info_before_PLTE(write_ptr, write_info_ptr);
	 *   write_my_chunk();
	 *   png_write_info(png_ptr, info_ptr);
	 *
	 * However, given the level of known- and unknown-chunk support in 1.2.0
	 * and up, this should no longer be necessary.
	 */

	 /* Once we write out the header, the compression type on the text
	  * chunk gets changed to PNG_TEXT_COMPRESSION_NONE_WR or
	  * PNG_TEXT_COMPRESSION_zTXt_WR, so it doesn't get written out again
	  * at the end.
	  */

	  /* Set up the transformations you want.  Note that these are
	   * all optional.  Only call them if you want them.
	   */

	   /* Invert monochrome pixels. */
	//png_set_invert_mono(png_ptr);

	/* Shift the pixels up to a legal bit depth and fill in
	 * as appropriate to correctly scale the image.
	 */
	 //png_set_shift(png_ptr, &sig_bit);

	 /* Pack pixels into bytes. */
	 //png_set_packing(png_ptr);

	 /* Swap location of alpha bytes from ARGB to RGBA. */
	 //png_set_swap_alpha(png_ptr);

	 /* Get rid of filler (OR ALPHA) bytes, pack XRGB/RGBX/ARGB/RGBA into
	  * RGB (4 channels -> 3 channels).  The second parameter is not used.
	  */
	  //png_set_filler(png_ptr, 0, PNG_FILLER_BEFORE);

	  /* Flip BGR pixels to RGB. */
	  //png_set_bgr(png_ptr);

	  /* Swap bytes of 16-bit files to most significant byte first. */
	  //png_set_swap(png_ptr);

	  /* Swap bits of 1-bit, 2-bit, 4-bit packed pixel formats. */
	  //png_set_packswap(png_ptr);

	  /* The easiest way to write the image (you may have a different memory
	   * layout, however, so choose what fits your needs best).  You need to
	   * use the first method if you aren't handling interlacing yourself.
	   */

	   /* In this example, "image" is a one-dimensional array of bytes. */

	   /* Guard against integer overflow. */
	if (height > PNG_SIZE_MAX / (width * bytes_per_pixel))
		png_error(png_ptr, "Image data buffer would be too large");

	// png_byte image[height * width * bytes_per_pixel];
	png_bytepp row_pointers = new png_bytep[height];
	// png_bytep row_pointers[height];

	if (height > PNG_UINT_32_MAX / (sizeof(png_bytep)))
		png_error(png_ptr, "Image is too tall to process in memory");

	/* Set up pointers into your "image" byte array. */
	png_uint_32 k;
	for (k = 0; k < height; k++)
		row_pointers[k] = image + k * width * bytes_per_pixel;

	/* One of the following output methods is REQUIRED. */

	/* Write out the entire image data in one call */
	png_write_image(png_ptr, row_pointers);

	/* It is REQUIRED to call this to finish writing the rest of the file. */
	png_write_end(png_ptr, info_ptr);

	/* Clean up after the write, and free any allocated memory. */
	png_destroy_write_struct(&png_ptr, &info_ptr);

	/* Close the file. */
	fclose(fp);

	/* That's it! */
	return 0;
}
