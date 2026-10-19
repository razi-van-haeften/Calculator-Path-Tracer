#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <math.h>

typedef struct {
	float x;
	float y;
	float z;
} Vec3;

typedef struct {
	float x;
	float y;
} Vec2;

typedef struct {
	Vec3 position;
	Vec3 normal;
	Vec3 color;
	float distance;
} Hit;

typedef struct {
	Vec3 position;
	Vec3 direction;
} Ray;

typedef struct {
	Vec3 position;
	float radius;
} Sphere;

static inline float dot(Vec3 a, Vec3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

static inline Vec3 add(Vec3 a, Vec3 b)
{
	return (Vec3){
		a.x + b.x,
		a.y + b.y,
		a.z + b.z
	};
}

static inline Vec3 subtract(Vec3 a, Vec3 b)
{
	return (Vec3){
		a.x - b.x,
		a.y - b.y,
		a.z - b.z
	};
}

static inline Vec3 multiply(Vec3 a, float t)
{
	return (Vec3){
		a.x * t,
		a.y * t,
		a.z * t
	};
}

static inline Vec3 clamp(Vec3 a)
{
	float r = 0.0f ? a.x < 0.0 : a.x;
	float g = 0.0f ? a.y < 0.0 : a.y;
	float b = 0.0f ? a.z < 0.0 : a.z;

	return (Vec3){r, g, b};
}

Vec3 normalize(Vec3 a);


bool Check_Sphere(const Sphere *sphere, const Ray *ray, Hit *hit);

#endif
