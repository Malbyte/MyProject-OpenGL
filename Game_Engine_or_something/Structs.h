#pragma once
#include "Definitions.h"
typedef char string;
#define _STARTING_GRAPHIC_ALLOCATIONS 5
/*{
	GLFWwindow* window;
	int function;
	int Tag;
	string vertexShaderSource;
	string fragmentShaderSource;
	string strngarg;
	float (*VerticeData)[];
	int return_value;
};*/
struct texture {
	char texturename;
};
struct window_Data {
	GLFWwindow* window;
	float ClearColor[4];
};
struct Object_Data {
	float(*VerticeData)[];
	char vertexShaderSource;
	char fragmentShaderSource;
	bool hasTextureInput;
	bool hascolorInput;
	char TYPEOFARRAY;
};
struct graphic {
	int function;
	int Tag;
	string strngarg;
	int return_value;
	struct texture Texturing_Settings;
	struct Object_Data Object_Data;
	struct window_Data Window_Data;
	int _LINE_;
};
/*
	GLFWwindow* window;
*/
struct timing {
	GLFWwindow* window;
};
/*
	GLFWwindow* window;
	int Curr_portion0;
	int Curr_portion1;
	string Objects[AMOUNT_OF_AVAILABLE_SLOTS_GRAPHIC][20];
*/
struct GRAPHIC_WORKER_THREADS {
	GLFWwindow* window;
	int Curr_portion0;
	int Curr_portion1;
	string Objects[AMOUNT_OF_AVAILABLE_SLOTS_GRAPHIC][20];
};

struct GRAPHIC_OBJECT {
	int* AmountOfVertices;
	int *AmountOfVerticesPerline;
	char *TYPEOFARRAY;
	float *vertices;
	unsigned int *VAO;
	unsigned int *Program;
};