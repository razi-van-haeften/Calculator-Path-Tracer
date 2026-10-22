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
