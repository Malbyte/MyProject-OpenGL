#include <stdbool.h>
#define FUNCXTRA_GRAPHICS
#define BULLET 0x01
#ifdef _WIN64

#endif // 

typedef float Xcoord;
typedef float Ycoord;
typedef const char ShaderSource;
typedef float VerticeData;
#ifndef MAIN_H
#define MAIN_H
struct Bullet {
	float v1;
	float v2;
	float v3;
	float v4;
	float v5;
	float v6;
	float v7;
	float v8;
};
#endif // !
GLFWwindow *window;
float a, b, c, d, e, f, g, h, i, z, bv1, bv2, bv3, bv4, bv5, bv6;
float vert_velocity, gravity;
int inbattle, menu, bullet1onscreen, devmde;
char song[32];
move(int *error);
const int WIDTH, HEIGHT;

void MoveWKEY();
void MoveSKEY();
void MoveAKEY();
void MoveDKEY();
void map_audio();
void deleteVAO();
void createprograms();
void jump();
void physics();
int Menu_map(GLFWwindow* window, int menu, int *level_selected);
int tpslc(int *x);


int VAOmap1, shaderProgrammap2;