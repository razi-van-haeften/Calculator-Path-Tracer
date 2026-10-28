#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <float.h>

static const float PI = 3.1415;
static const float NEAR = 0.00001f;
static const float FAR = 50.0f;

typedef unsigned int uint;

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
	Vec3 emissive;
	Vec3 albedo;//0 - 1
	float specular_probability;//0 - 1
	float smoothness;//0 - 1
	Vec3 specular_color;
} Material;

typedef struct {
	Vec3 position;
	Vec3 normal;
	Material material;
	float distance;
} Hit;

typedef struct {
	Vec3 position;
	Vec3 direction;
} Ray;

typedef struct {
	Vec3 position;
	Vec3 direction;
	float FOV;
	float FOV_distance;
	float defocus;
} Camera;

typedef struct {
	Vec3 position;
	float radius;
	Material material;
} Sphere;

typedef enum {
	OBJECT_SPHERE,
	OBJECT_QUAD
} Object_Type;

typedef struct {
	Object_Type type;
	union {
		Sphere sphere;
	} data;
} Object;

uint wang_hash(uint *seed);
float random_unit_float(uint *seed);
Vec3 random_unit_Vec3(uint *seed);

static inline float dot(Vec3 a, Vec3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

static inline Vec3 cross(Vec3 a, Vec3 b)
{
	return (Vec3){
		a.y*b.z - a.z*b.y,
		a.z*b.x - a.x*b.z,
		a.x*b.y - a.y*b.x
	};
}

static inline Vec3 add(Vec3 a, Vec3 b)
{
	return (Vec3){
		a.x + b.x,
		a.y + b.y,
		a.z + b.z
	};
}

static inline Vec3 blend(Vec3 a, Vec3 b, float t)
{
	return (Vec3){
		a.x+(b.x-a.x) * t,
		a.y+(b.y-a.y) * t,
		a.z+(b.z-a.z) * t
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

static inline Vec3 extrapolate(Vec3 a, float t)
{
	return (Vec3){
		a.x * t,
		a.y * t,
		a.z * t
	};
}

static inline Vec3 multiply(Vec3 a, Vec3 b)
{
	return (Vec3){
		a.x * b.x,
		a.y * b.y,
		a.z * b.z
	};
}

static inline Vec3 clamp(Vec3 a, float min, float max)
{
    float r = a.x < min ? min : a.x;
    float g = a.y < min ? min : a.y;
    float b = a.z < min ? min : a.z;

    r = r > max ? max : r;
    g = g > max ? max : g;
    b = b > max ? max : b;

    return (Vec3){r, g, b};
}

void normalize(Vec3* a);
static inline Vec3 normalized(Vec3 a)
{
	float length = sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
	if (length > 0.0f) {
		return (Vec3){
			a.x / length,
			a.y / length,
			a.z / length
		};
	};
	return (Vec3){
		0.0f,
		0.0f,
		0.0f
	};
}

#endif
