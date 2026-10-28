#include <string.h>
#include "path_trace.h"
#include "utils.h"

#define TEST_FILE "test.ppm"
#define min(a,b) (((a) < (b)) ? (a) : (b))

int WIDTH = 1024;
int HEIGHT = 1024;
float ASPECT_RATIO;
uint SEED = 67;
int MAX_SAMPLES = 256;
int MAX_DEPTH = 12;
float GAMMA = 2.2f;

Camera CAMERA = {
	(Vec3){0.0f, 0.0f, 6.0f},
	(Vec3){0.0f, 0.0f, -1.0f},
	3.1415f / 2.0f,
	0.0f,
	10.0f,
	1.2f
};

Sphere sphere = {
	(Vec3){0.0f, 0.0f, -4.0f},
	1.0f,
	(Material){
		(Vec3){0.0f, 0.0f, 0.0f},
		(Vec3){1.0f, 1.0f, 1.0f},
		0.15f,
		0.95f,
		(Vec3){1.0f, 1.0f, 1.0f}
	}
};
Sphere sphere2 = {
	(Vec3){4.0f, 2.0f, -2.0f},
	0.75f,
	(Material){
		(Vec3){6.0f, 2.0f, 2.0f},
		(Vec3){0.0f,0.0f, 0.0f},
		0.0f,
		1.0f,
		(Vec3){1.0f, 1.0f, 1.0f}
	}
};
Sphere sphere3 = {
	(Vec3){-3.0f, 0.0f, 1.0f},
	1.0f,
	(Material){
		(Vec3){0.0f, 0.0f, 0.0f},
		(Vec3){1.0f, 0.95f, 0.2f},
		0.2f,
		1.0f,
		(Vec3){1.0f, 1.0f, 1.0f}
	}
};

int main(){
	printf("P6\n%d %d\n255\n", WIDTH, HEIGHT);

	// PATH tracing
	ASPECT_RATIO = (float)WIDTH / HEIGHT;
	CAMERA.FOV_distance = 1.0f / tan(CAMERA.FOV * 0.5f);

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
			for(int sample = 0; sample < MAX_SAMPLES; sample += 1)
			{
				Vec3 final_color = {0.0f, 0.0f, 0.0f};
				Vec3 throughput = {1.0f, 1.0f, 1.0f};

				Ray ray = Get_Ray(screen_x, screen_y, WIDTH, HEIGHT, ASPECT_RATIO, &CAMERA, &SEED);

				Trace(&ray, scene, 3, MAX_DEPTH, &throughput, &final_color, &SEED);

				total_color = add(total_color, final_color);
			}

			total_color = extrapolate(total_color, 1.0f / (float)MAX_SAMPLES);
			total_color.x = total_color.x / (1.0f + total_color.x);
			total_color.y = total_color.y / (1.0f + total_color.y);
			total_color.z = total_color.z / (1.0f + total_color.z);
			float R = powf(total_color.x, 1.0f/GAMMA);
			float G = powf(total_color.y, 1.0f/GAMMA);
			float B = powf(total_color.z, 1.0f/GAMMA);
			
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
