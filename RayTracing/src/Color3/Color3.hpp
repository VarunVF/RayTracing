#pragma once

#include <vector>

#include "../Vec3/Vec3.hpp"



// Color3 is simply an alias for Vec3.
using Color3 = Vec3;

// Translate color components from [0, 1] to the byte range [0, 255],
// and insert them into an output stream.
void writeColor(std::ostream& stream, const Color3& pixelColor);


// Translate color components from [0, 1] to the byte range [0, 255],
// and write them to a vector.
void writeColor(std::vector<uint8_t>& list, const Color3& pixelColor);


inline Color3 operator+=(const Color3& first, const Color3& second)
{
	return Color3(
		first[0] + second[0],
		first[1] + second[1],
		first[2] + second[2]
	);
}
