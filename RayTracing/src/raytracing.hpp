#pragma once

// General header file.


// STL headers

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>


// Common headers

#include "Color3/Color3.hpp"
#include "Ray3/Ray3.hpp"
#include "Vec3/Vec3.hpp"


// Mathematical constants

constexpr double infinity = std::numeric_limits<double>::infinity();
constexpr double pi       = 3.1415926535897932385;


// Utility functions

inline double degrees_to_radians(double degrees)
{
    return degrees * pi / 180.0;
}

// Random real in [0, 1)
inline double random_double()
{
    return std::rand() / (RAND_MAX + 1.0);
}

// Random real in [min, max)
inline double random_double(double min, double max)
{
    return min + (max - min) * random_double();
}