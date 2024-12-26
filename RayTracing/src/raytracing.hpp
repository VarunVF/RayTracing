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

inline uint32_t pcg_hash(uint32_t input)
{
    uint32_t state = input * 747796405u + 2891336453u;
    uint32_t word = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
    return (word >> 22u) ^ word;
}

// Random real in [0, 1) using PCG hash.
inline double random_double(uint32_t& seed)
{
    seed = pcg_hash(seed);
    constexpr double max_plus_one
        = static_cast<double>(std::numeric_limits<uint32_t>::max()) + 1.0;
    return static_cast<double>(seed) / max_plus_one;
}

// Random real in [min, max) using PCG hash.
inline double random_double(double min, double max, uint32_t& seed)
{
    return min + (max - min) * random_double(seed);
}

// Random real in [0, 1) using std::rand().
inline double slow_random_double()
{
    return std::rand() / (RAND_MAX + 1.0);
}
