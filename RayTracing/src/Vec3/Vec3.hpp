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
		// Get a random vector with components in [-1, 1)
		auto point = Vec3::random(-1, 1, seed);
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

// Requires incident and normal vectors to have unit length.
// NOTE: does not check for TIR condition, check before using.
// i = incident ray
// n = normal to interface
// refractionRatio = initial refractive index / final refractive index
inline Vec3 refract(const Vec3& incident, const Vec3& normal, double refractionRatio)
{
	// Transmitted ray = T
	// Incident ray = I
	// T = refractionRatio * (incident + normal*(cosI - sqrt(1 - sinSquaredT));
	
	const double cosI = -dot(incident, normal);
	const double sinSquaredT = refractionRatio * refractionRatio * (1.0 - cosI * cosI);
	const double cosT = std::sqrt(1.0 - sinSquaredT);
	return refractionRatio * incident + (refractionRatio * cosI - cosT) * normal;
}


void testVec3();
