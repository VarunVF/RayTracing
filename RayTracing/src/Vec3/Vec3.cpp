#include "Vec3.hpp"
#include "raytracing.hpp"


Vec3::Vec3()
	: elements{ 0.0, 0.0, 0.0 }
{
}

Vec3::Vec3(double x, double y, double z)
	: elements{ x, y, z }
{
}

double Vec3::x() const
{
	return elements[0];
}

double Vec3::y() const
{
	return elements[1];
}

double Vec3::z() const
{
	return elements[2];
}

double Vec3::length_squared() const
{
	return elements[0] * elements[0]
		+ elements[1] * elements[1]
		+ elements[2] * elements[2];
}

double Vec3::length() const
{
	return std::sqrt(length_squared());
}

Vec3 Vec3::unit_vector() const
{
	double magnitude = length();
	return Vec3(
		elements[0] / magnitude,
		elements[1] / magnitude,
		elements[2] / magnitude
	);
}

bool Vec3::near_zero() const
{
	constexpr auto maxDist = 1.0e-8;
	return (std::fabs(elements[0]) < maxDist)
		&& (std::fabs(elements[1]) < maxDist)
		&& (std::fabs(elements[2]) < maxDist);
}

Vec3 Vec3::random(uint32_t& seed)
{
	return Vec3(
		random_double(seed),
		random_double(seed),
		random_double(seed)
	);
}

Vec3 Vec3::random(double min, double max, uint32_t& seed)
{
	return Vec3(
		random_double(min, max, seed),
		random_double(min, max, seed),
		random_double(min, max, seed)
	);
}

double Vec3::operator[](int i) const
{
	return elements[i];
}

double& Vec3::operator[](int i)
{
	return elements[i];
}

Vec3 Vec3::operator-() const
{
	return Vec3(
		-elements[0],
		-elements[1],
		-elements[2]
	);
}

Vec3& Vec3::operator+=(const Vec3& other)
{
	elements[0] += other.elements[0];
	elements[1] += other.elements[1];
	elements[2] += other.elements[2];
	return *this;
}

Vec3& Vec3::operator-=(const Vec3& other)
{
	elements[0] -= other.elements[0];
	elements[1] -= other.elements[1];
	elements[2] -= other.elements[2];
	return *this;
}

Vec3& Vec3::operator*=(double scalar)
{
	elements[0] *= scalar;
	elements[1] *= scalar;
	elements[2] *= scalar;
	return *this;
}

Vec3& Vec3::operator/=(double scalar)
{
	return *this *= 1 / scalar;
}



void testVec3()
{
	Vec3 a;									// Default ctor
	Vec3 b(1.0, 2.0, 2.0);					// Second ctor
	// std::cout << a << "\n" << b << "\n";	// x(), y(), z(), operator<<(std::ostream&, Vec3&)

	auto b_mag = b.length();
	auto b_mag_squared = b.length_squared();
	// std::cout << b.length() << " " << b.length_squared() << "\n";

	Vec3 b_hat = b.unit_vector();
	// std::cout << b.unit_vector() << "\n";

	Vec3 antiparallel_b = -b;
	// std::cout << -b << "\n";				// Vec3 operator- (negation)

	b[0] = -4.3;							// double& operator[](int)
	// std::cout << b[0] << "\n";			// double& operator[](int)

	b += a;									// Vec3& operator+=(Vec3&)
	a -= a;									// Vec3& operator-=(Vec3&)
	b *= 4.0;								// Vec3& operator*=(Vec3&)
	b /= 3.0;								// Vec3& operator/=(Vec3&)

	Vec3 twice_b = b * 2.0;
	Vec3 another_twice_b = 2.0 * b;
	// std::cout << b * 7.2 << "\n";			// Vec3 operator*(Vec3&, double)
	// std::cout << 7.2 * b << "\n";			// Vec3 operator*(double, Vec3&)

	a = Vec3(1, 2, 3);
	b = Vec3(4, 5, 6);
	auto a_dot_b = dot(a, b);
	Vec3 a_x_b = cross(a, b);
	// std::cout << "dot product: " << dot(a, b) << "\n";
	// std::cout << "cross product: " << cross(a, b) << "\n";
}
