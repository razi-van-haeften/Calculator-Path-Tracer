#include <stdio.h>
#include <string.h>
#include "utils.h"

#define TEST_FILE "test.ppm"



int WIDTH = 256;
int HEIGHT = 256;

Sphere sphere = {
	(Vec3){0.0f, 0.0f, 6.0f},
	2.0f
};

int main(){
	printf("P6\n%d %d\n255\n", WIDTH, HEIGHT);
	// path tracing
	unsigned char buffer[WIDTH * HEIGHT * 3] = {};
	int screen_x, screen_y;
	for (screen_y = 0; screen_y < HEIGHT; screen_y += 1){
		for (screen_x = 0; screen_x < WIDTH; screen_x += 1){
			Vec3 final_color = {0.0f, 0.0f, 0.0f};
			Vec2 uv = {
				((float)screen_x / ((float)WIDTH - 1.0f)) * 2.0f - 1.0f,
				(1 - (float)screen_y / ((float)HEIGHT - 1.0f)) * 2.0f - 1.f
			};
			// Z+ FORWARD
			Ray ray = {
				(Vec3){0.0f, 0.0f, 0.0f},
				normalize((Vec3){uv.x, uv.y, 1.0f})
			};
			Hit hit;
			bool hit_sphere = Check_Sphere(&sphere, &ray, &hit);

			if(hit_sphere) 
			{
				final_color = hit.color;
			}

			unsigned char pixel[3] = {
				(unsigned char)(255.0f * final_color.x),
				(unsigned char)(255.0f * final_color.y),
				(unsigned char)(255.0f * final_color.z),
			};
			//printf("%d	%d	%d	\n", screen_x, screen_y, (screen_x + (screen_y * WIDTH)) * 3);
			memcpy(buffer + (screen_x + screen_y * WIDTH) * 3, pixel, 3);
		}
	}
	// Pipe cout to ppm file for testing
	fwrite(buffer, 1, sizeof(buffer), stdout);
}
