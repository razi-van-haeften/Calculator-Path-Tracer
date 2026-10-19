#include "utils.h"

Vec3 normalize(Vec3 a)
{
	float length = sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
	return multiply(a, 1.0f/length);
}

bool Check_Sphere(const Sphere *sphere, const Ray *ray, Hit *hit)
{
	Vec3 J = subtract(ray->position, sphere->position);

	float A = dot(ray->direction, ray->direction);
	float B = 2.0f * dot(J, ray->direction);
	float C = dot(J, J) - sphere->radius * sphere->radius;
	float D = B * B - 4.0f * A * C;

	if (D < 0.0f)
	{
		return false;
	}

	float t = (-B - sqrt(D)) / (2.0f * A);

	if (t < 0.0f)
	{
		return false;
	}

	Vec3 L = normalize((Vec3){1.0f, 0.0f, 0.0f});

	hit->distance = t;
	hit->position = add(ray->position, multiply(ray->direction, t));
	hit->normal = normalize(subtract(hit->position, sphere->position));

	float k = dot(multiply(L, -1.0f), hit->normal);
	hit->color = (Vec3){k, k, k};

	return true;
}
