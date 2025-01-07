#pragma once

#include <vector>

#include "../Vec3/Vec3.hpp"



// Color3 is simply an alias for Vec3.
using Color3 = Vec3;


// Convert from linear space to gamma space.
inline double linearToGamma(double linear_component)
{
	if (linear_component > 0.0)
		return std::sqrt(linear_component);
	return 0;
}

// Translate color components from [0, 1] to the byte range [0, 255],
// and insert them into an output stream.
void writeColor(std::ostream& stream, const Color3& pixelColor);


// Translate color components from [0, 1] to the byte range [0, 255],
// and write them to a vector.
void writeColor(std::vector<uint8_t>& list, const Color3& pixelColor);

// Translate color components from [0, 1] to the byte range [0, 255],
// and write them at the specified address.
void writeColorAtPos(uint8_t* position, const Color3& pixelColor);
