#include "path_trace.h"
#include "utils.h"
#include <float.h>

Ray Get_Ray(int screen_x, int screen_y, int width, int height, float aspect_ratio, const Camera *camera, uint *seed)
{
	float dx = screen_x + (random_unit_float(seed) - 0.5f) * 2.0f * camera->defocus;
	float dy = screen_y + (random_unit_float(seed) - 0.5f) * 2.0f * camera->defocus;

	Vec2 uv = {
		dx / (float)(width - 1) * 2.0f - 1.0f,
		(1.0f - dy / (float)(height - 1)) * 2.0f -1.0f
	};

	// uv.y /= aspect_ratio;
	//
	Vec3 Z = normalized(camera->direction);
	Vec3 up = (Vec3){0.0f, 1.0f, 0.0f};
	Vec3 X = normalized(cross(up, Z));
	Vec3 Y = cross(Z, X);	
	X = extrapolate(X, -1.0f);

	Vec3 z = extrapolate(Z, camera->FOV_distance);
	Vec3 direction = add(add(z, extrapolate(Y, uv.y / aspect_ratio)), extrapolate(X, uv.x));

	return (Ray){
		camera->position,
		direction
	};
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

	hit->distance = t;
	hit->position = add(ray->position, extrapolate(ray->direction, t));
	hit->normal = normalized(subtract(hit->position, sphere->position));
	hit->material = sphere->material;

	return true;
}

void Trace(Ray *ray, const Object *scene, size_t scene_size, int depth, Vec3 *throughput, Vec3 *final_color, uint *seed)
{	
	if(depth <= 0) return;
	Hit closest_hit;
	closest_hit.distance = FLT_MAX;
	Hit tmp_hit;
	for(int i=0; i < scene_size; i += 1)
	{
		if(Check_Sphere(&scene[i].data.sphere, ray, &tmp_hit))
		{
			if(tmp_hit.distance < closest_hit.distance && tmp_hit.distance > NEAR)
			{
				closest_hit = tmp_hit;
			}
		}
	}
	if(closest_hit.distance == FLT_MAX)
	{
		float d = (normalized(ray->direction).y + 1.0f) * 0.5f;
		Vec3 sky = add(extrapolate((Vec3){1.0f, 1.0f, 1.0f}, 1.0f-d), extrapolate((Vec3){0.5f, 0.7f, 1.0f}, d));
		sky = extrapolate(sky, 0.7f);
		*final_color = add(*final_color, multiply(*throughput, sky));	
		return;
	}

	ray->position = closest_hit.position;

	Vec3 diffuse_direction = normalized(add(closest_hit.normal, random_unit_Vec3(seed)));
	Vec3 specular_direction;
	bool is_specular_bounce = closest_hit.material.specular_probability > random_unit_float(seed);
	if(is_specular_bounce)
	{
		specular_direction = subtract(ray->direction, extrapolate(closest_hit.normal, 2.0f * dot(ray->direction, closest_hit.normal)));
	}
	ray->direction = blend(diffuse_direction, specular_direction, closest_hit.material.smoothness * is_specular_bounce);


	*final_color = add(*final_color, multiply(closest_hit.material.emissive, *throughput));
	*throughput = multiply(*throughput, blend(closest_hit.material.albedo, closest_hit.material.specular_color, is_specular_bounce));	

	//here we go again
	Trace(ray, scene, scene_size, depth - 1, throughput, final_color, seed);
	return;
}
