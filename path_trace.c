#include "path_trace.h"

bool Check_Sphere(const Sphere *sphere, const Ray *ray, Hit *hit)
{
	Vec3 J = subtract(ray->position, sphere->position);

	float A = dot(ray->direction, ray->direction);
	float B = 2.0f * dot(J, ray->direction);
	float C = dot(J, J) - sphere->radius * sphere->radius;
	float D = B * B - 4.0f * A * C;

	if (D < 0.0f)
	{
		return false;;
	}

	float t = (-B - sqrt(D)) / (2.0f * A);
	if (t < 0.0f)
	{
		return false;
	}

	hit->distance = t;
	hit->position = add(ray->position, multiply(normalized(ray->direction), t));
	hit->normal = subtract(hit->position, sphere->position);
	hit->material = sphere->material;

	return true;
}

void Trace(Ray *ray, const Object *scene, size_t scene_size, int depth, Vec3 *throughput, Vec3 *final_color)
{
	
	Hit closest_hit;
	closest_hit.distance = FLT_MAX;
	Hit tmp_hit;
	for(int i=0; i < scene_size; i += 1)
	{
		if(Check_Sphere(&scene[i].data.sphere, ray, &tmp_hit))
		{
			if(tmp_hit.distance < closest_hit.distance)
			{
				closest_hit = tmp_hit;
			}
		} else {
			return;
		}
		*final_color = tmp_hit.normal;
	}
}
