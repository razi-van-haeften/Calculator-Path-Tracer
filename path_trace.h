#ifndef PATH_TRACE_H
#define PATH_TRACE_H

#include "utils.h"

bool Check_Sphere(const Sphere *sphere, const Ray *ray, Hit *hit);

void Trace(Ray *ray, const Object *scene, size_t scene_size, int depth, Vec3 *throughput, Vec3 *final_color);
#endif
