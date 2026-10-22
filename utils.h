#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <float.h>

static const float NEAR = 0.00001f;
static const float FAR = 50.0f;

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
	Vec3 albedo;
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
