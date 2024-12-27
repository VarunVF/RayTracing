#pragma once

#include <ostream>


class Vec3
{
public:
	Vec3();
	Vec3(double x, double y, double z);

	double x() const;
	double y() const;
	double z() const;

	double length_squared() const;
	double length() const;
	Vec3 unit_vector() const;
	bool near_zero() const;

	static Vec3 random(uint32_t& seed);
	static Vec3 random(double min, double max, uint32_t& seed);

	double operator[](int i) const;
	double& operator[](int i);

	Vec3 operator-() const;

	Vec3& operator+=(const Vec3& other);
	Vec3& operator-=(const Vec3& other);
	Vec3& operator*=(double scalar);
	Vec3& operator/=(double scalar);

public:
	double elements[3];
};



// Point3 is simply an alias for Vec3.
// Perhaps it should be an actual class.
using Point3 = Vec3;



// Vector Utility Functions

inline std::ostream& operator<<(std::ostream& stream, Vec3 vector)
{
	return stream << "[" << vector.x() << ", " << vector.y() << ", " << vector.z() << "]";
}


inline double dot(const Vec3& u, const Vec3& v)
{
	return u[0] * v[0]
		+ u[1] * v[1]
		+ u[2] * v[2];
}

inline Vec3 cross(const Vec3& u, const Vec3& v)
{
	return Vec3(
		u[1] * v[2] - u[2] * v[1],
		-(u[0] * v[2] - u[2] * v[0]),
		u[0] * v[1] - u[1] * v[0]
	);
}


inline Vec3 operator+(const Vec3& u, const Vec3& v)
{
	return Vec3(
		u.elements[0] + v.elements[0],
		u.elements[1] + v.elements[1],
		u.elements[2] + v.elements[2]
	);
}

inline Vec3 operator-(const Vec3& u, const Vec3& v)
{
	return Vec3(
		u.elements[0] - v.elements[0],
		u.elements[1] - v.elements[1],
		u.elements[2] - v.elements[2]
	);
}

inline Vec3 operator*(const Vec3& u, const Vec3& v)
{
	return Vec3(
		u.elements[0] * v.elements[0],
		u.elements[1] * v.elements[1],
		u.elements[2] * v.elements[2]
	);
}

inline Vec3 operator*(const Vec3& vector, double scalar)
{
	return Vec3(
		vector[0] * scalar,
		vector[1] * scalar,
		vector[2] * scalar
	);
}

inline Vec3 operator*(double scalar, const Vec3& vector)
{
	return vector * scalar;
}

inline Vec3 operator/(const Vec3& vector, double k)
{
	return Vec3(
		vector[0] / k,
		vector[1] / k,
		vector[2] / k
	);
}

inline Vec3 random_unit_vector(uint32_t& seed)
{
	while (true)
	{
		auto point = Vec3::random(seed);
		auto lensq = point.length_squared();
		if (1e-160 < lensq && lensq <= 1)
			return point / std::sqrt(lensq);
	}
}

inline Vec3 random_on_hemisphere(const Vec3& normal, uint32_t& seed)
{
	Vec3 on_unit_sphere = random_unit_vector(seed);
	if (dot(on_unit_sphere, normal) > 0.0)
		return on_unit_sphere;
	else
		return -on_unit_sphere;
}

inline Vec3 reflect(const Vec3& v, const Vec3& normal)
{
	return v - 2*dot(v, normal)*normal;
}


void testVec3();
