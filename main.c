#include <string.h>
#include "path_trace.h"
#include "utils.h"

#define TEST_FILE "test.ppm"

int WIDTH = 512;
int HEIGHT = 384;
//RADIANS
float FOV = 1.571f;

Sphere sphere = {
	(Vec3){0.0f, 0.0f, 6.0f},
	2.0f
};

int main(){

	printf("P6\n%d %d\n255\n", WIDTH, HEIGHT);

	// PATH TRACING
	float aspect_ratio = (float)WIDTH / (float)HEIGHT;
	float camera_distance = 1.0f / tan(FOV * 0.5f);

	Object scene[1];
	scene[0].type = OBJECT_SPHERE;
	scene[0].data.sphere = sphere;

	unsigned char buffer[WIDTH * HEIGHT * 3] = {};
	int screen_x, screen_y;
	for (screen_y = 0; screen_y < HEIGHT; screen_y += 1){
		for (screen_x = 0; screen_x < WIDTH; screen_x += 1){
			Vec3 final_color = {0.0f, 0.0f, 0.0f};
			Vec3 throughput = {1.0f, 1.0f, 1.0f};
			Vec2 uv = {
				((float)screen_x / ((float)WIDTH - 1.0f)) * 2.0f - 1.0f,
				(1 - (float)screen_y / ((float)HEIGHT - 1.0f)) * 2.0f - 1.f
			};
			// Z+ FORWARD
			Ray ray = {
				(Vec3){0.0f, 0.0f, 0.0f},
				normalized((Vec3){uv.x, uv.y / aspect_ratio, camera_distance})
			};

			Trace(&ray, scene, sizeof(scene) / sizeof(Object), 1, &throughput, &final_color);
			
			unsigned char pixel[3] = {
				(unsigned char)(255.0f * final_color.x),
				(unsigned char)(255.0f * final_color.y),
				(unsigned char)(255.0f * final_color.z),
			};

			memcpy(buffer + (screen_x + screen_y * WIDTH) * 3, pixel, 3);
		}
	}
	// PIPE STDOUT TO PPM FILE FOR TESTING
	fwrite(buffer, 1, sizeof(buffer), stdout);

	return 0;
}
