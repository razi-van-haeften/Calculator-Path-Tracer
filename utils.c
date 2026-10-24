#include "utils.h"

void normalize(Vec3* a)
{
	float length = sqrt(a->x*a->x + a->y*a->y + a->z*a->z);
	if(length > 0.0f)
	{
		a->x /= length;
		a->y /= length;
		a->z /= length;
	}
}

uint wang_hash(uint *seed)
{
	*seed = (uint)(*seed ^ (uint)(61)) ^ (uint)(*seed >> (uint)(16));
	*seed *= (uint)(9);
	*seed = *seed ^ (*seed >> 4);
	*seed *= (uint)(0x27d4eb2d);
	*seed = *seed ^ (*seed >> 15);
	return *seed;
}

float random_unit_float(uint *seed)
{
	return (float)wang_hash(seed) / 4294967295.0f;
}

Vec3 random_unit_Vec3(uint *seed)
{
	float z = random_unit_float(seed) * 2.0f - 1.0f;
	float a = random_unit_float(seed) * 2.0f * PI;
	float r = sqrt(1.0f - z * z);
	float x = r * cos(a);
	float y = r * sin(a);
	return (Vec3){x, y, z};
}
