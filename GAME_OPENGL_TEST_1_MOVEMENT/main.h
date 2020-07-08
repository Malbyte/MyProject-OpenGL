#ifndef MAIN_H
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

float a, b, c, d, e, f, g, h, i, z, bv1, bv2, bv3, bv4, bv5, bv6;
float vert_velocity, gravity;
int inbattle, escprsd, bullet1onscreen;
char song[32];
move(int *error);
const GLint WIDTH, HEIGHT;

void MoveWKEY();
void MoveSKEY();
void MoveAKEY();
void MoveDKEY();
void map_audio();
void deleteVAO();
void createprograms();
void jump();
void Texture(int *width, int *height, int *nrChannels, char Image[125]);