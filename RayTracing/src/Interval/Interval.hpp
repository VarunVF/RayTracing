#pragma once


class Interval
{
public:
	Interval();
	Interval(double min_value, double max_value);

	double size() const;
	double clamp(double value) const;
	bool contains(double value) const;
	bool surrounds(double value) const;

public:
	double min, max;
	static const Interval empty;
	static const Interval universe;
};
