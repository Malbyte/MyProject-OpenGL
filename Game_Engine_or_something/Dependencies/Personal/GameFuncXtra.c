#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "GameFuncXtra.h"
//
#define FUNCXTRA_GRAPHICS
//
#ifdef FUNCXTRA_GRAPHICS

void vertexShadR(int *input_frag_shader, const char *vertexShaderSource) {
	*input_frag_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(*input_frag_shader, 1, &vertexShaderSource, NULL);
	glCompileShader(*input_frag_shader);
}

void fragmentShadR(int *fragmentShaderplz, const char *fragmentShaderSource) {
	*fragmentShaderplz = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(*fragmentShaderplz, 1, &fragmentShaderSource, NULL);
	glCompileShader(*fragmentShaderplz);
}
void ProgramShadR(GLuint *shaderProgram, int vertexShader, int fragmentShader) {
	*shaderProgram = glCreateProgram();
	glAttachShader(*shaderProgram, vertexShader);
	glAttachShader(*shaderProgram, fragmentShader);
	glLinkProgram(*shaderProgram);

}

#endif