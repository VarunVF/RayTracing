#include <ostream>

#include "Color3.hpp"
#include "../Interval/Interval.hpp"


// Translate color components from [0, 1] to the byte range [0, 255],
// and insert them into an output stream.
void writeColor(std::ostream& stream, const Color3& pixelColor)
{
	Interval intensity(0.0, 0.999);
	auto r = pixelColor.x();
	auto g = pixelColor.y();
	auto b = pixelColor.z();

	int translatedRed   = (int)(256 * intensity.clamp(r));
	int translatedGreen = (int)(256 * intensity.clamp(g));
	int translatedBlue  = (int)(256 * intensity.clamp(b));

	stream << translatedRed << " " << translatedGreen << " " << translatedBlue << "\n";
}


// Translate color components from [0, 1] to the byte range [0, 255],
// and write them to a vector.
void writeColor(std::vector<uint8_t>& list, const Color3& pixelColor)
{
	Interval intensity(0.0, 0.999);
	auto r = pixelColor.x();
	auto g = pixelColor.y();
	auto b = pixelColor.z();

	uint8_t translatedRed   = (uint8_t)(256 * intensity.clamp(r));
	uint8_t translatedGreen = (uint8_t)(256 * intensity.clamp(g));
	uint8_t translatedBlue  = (uint8_t)(256 * intensity.clamp(b));

	list.push_back(translatedRed);
	list.push_back(translatedGreen);
	list.push_back(translatedBlue);
}
