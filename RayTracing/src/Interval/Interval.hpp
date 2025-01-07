#pragma once


// Represents a range of continuous real numbers between two points
class Interval
{
public:
	// Default interval is empty
	Interval();
	Interval(double min_value, double max_value);

	// Size of the interval, max - min.
	double size() const;

	// Clamp a value within the inclusive bounds [min, max] of the Interval.
	double clamp(double value) const;
	
	// Inclusive bounds check
	bool contains(double value) const;

	// Exclusive bounds check
	bool surrounds(double value) const;

public:
	double min, max;
	static const Interval empty;
	static const Interval universe;
};
