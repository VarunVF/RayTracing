#include "Interval.hpp"

#include <limits>


constexpr double infinity = std::numeric_limits<double>::infinity();


// Default interval is empty
Interval::Interval()
	: min(+infinity), max(-infinity)
{
}

Interval::Interval(double min_value, double max_value)
	: min(min_value), max(max_value)
{
}

double Interval::size() const
{
	return max - min;
}

double Interval::clamp(double value) const
{
	if (value < min) return min;
	if (value > max) return max;
	return value;
}

// Inclusive bounds check
bool Interval::contains(double value) const
{
	return min <= value && value <= max;
}

// Exclusive bounds check
bool Interval::surrounds(double value) const
{
	return min < value && value < max;
}


const Interval Interval::empty    = Interval(+infinity, -infinity);
const Interval Interval::universe = Interval(-infinity, +infinity);
