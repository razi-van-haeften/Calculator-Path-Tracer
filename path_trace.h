#ifndef PATH_TRACE_H
#define PATH_TRACE_H

#include "utils.h"

Ray Get_Ray(int screen_x, int screen_y, int width, int height, float aspect_ratio, const Camera *camera, uint *seed);

bool Check_Sphere(const Sphere *sphere, const Ray *ray, Hit *hit);

void Trace(Ray *ray, const Object *scene, size_t scene_size, int depth, Vec3 *throughput, Vec3 *final_color, uint *seed);
#endif
