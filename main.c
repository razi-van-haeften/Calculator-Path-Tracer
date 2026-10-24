#include <string.h>
#include "path_trace.h"
#include "utils.h"

#define TEST_FILE "test.ppm"

int WIDTH = 512;
int HEIGHT = 384;
uint seed = 67;
int max_samples = 20;
float GAMMA = 1.1f;
//RADIANS
float FOV = 3.1415f / 2.3f;

Sphere sphere = {
	(Vec3){0.0f, 0.0f, -6.0f},
	1.0f,
	(Material){
		(Vec3){0.0f, 0.0f, 0.0f},
		(Vec3){0.5f, 0.5f, 0.5f}
	}
};
Sphere sphere2 = {
	(Vec3){3.0f, 0.0f, -5.0f},
	1.5f,
	(Material){
		(Vec3){0.0f, 0.0f, 0.0f},
		(Vec3){1.0f, 0.7f, 0.5f}
	}
};
Sphere sphere3 = {
	(Vec3){-1.0f, -5.0f, -5.0f},
	4.0f,
	(Material){
		(Vec3){0.0f, 0.0f, 0.0f},
		(Vec3){0.6f, 0.9f, 0.5f}
	}
};

int main(){

	printf("P6\n%d %d\n255\n", WIDTH, HEIGHT);

	// PATH TRACING
	float aspect_ratio = (float)WIDTH / (float)HEIGHT;
	float camera_distance = 1.0f / tan(FOV * 0.5f);

	Object scene[3];
	scene[0].type = OBJECT_SPHERE;
	scene[0].data.sphere = sphere;
	scene[1].type = OBJECT_SPHERE;
	scene[1].data.sphere = sphere3;
	scene[2].type = OBJECT_SPHERE;
	scene[2].data.sphere = sphere2;

	unsigned char buffer[WIDTH * HEIGHT * 3] = {};
	int screen_x, screen_y;
	for (screen_y = 0; screen_y < HEIGHT; screen_y += 1){
		for (screen_x = 0; screen_x < WIDTH; screen_x += 1){
			Vec3 total_color = {0.0f, 0.0f, 0.0f};
			for(int sample = 0; sample < max_samples; sample += 1)
			{
				Vec3 final_color = {0.0f, 0.0f, 0.0f};
				Vec3 throughput = {1.0f, 1.0f, 1.0f};
				Vec2 uv = {
					((float)screen_x / ((float)WIDTH - 1.0f)) * 2.0f - 1.0f + (random_unit_float(&seed) - 0.5f) / 500.0f,
					(1.0f - (float)screen_y / ((float)HEIGHT - 1.0f)) * 2.0f - 1.0f + (random_unit_float(&seed) - 0.5f) / 500.0f
				};
				// Z+ FORWARD
				Ray ray = {
					(Vec3){0.0f, 0.0f, 0.0f},
					(Vec3){uv.x, uv.y / aspect_ratio, -camera_distance}
				};

				Trace(&ray, scene, 3, 6, &throughput, &final_color, &seed);

				total_color = add(total_color, final_color);
			}

			float R = powf(total_color.x / (float)max_samples, 1.0f/GAMMA);
			float G = powf(total_color.y / (float)max_samples, 1.0f/GAMMA);
			float B = powf(total_color.z / (float)max_samples, 1.0f/GAMMA);

			
			unsigned char pixel[3] = {
				(unsigned char)(255.0f * R),
				(unsigned char)(255.0f * G),
				(unsigned char)(255.0f * B),
			};

			memcpy(buffer + (screen_x + screen_y * WIDTH) * 3, pixel, 3);
		}
	}
	// PIPE STDOUT TO PPM FILE FOR TESTING
	fwrite(buffer, 1, sizeof(buffer), stdout);

	return 0;
}
