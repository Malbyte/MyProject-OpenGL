#include "Dependencies/glew-2.1.0-win32/glew-2.1.0/include/GL/glew.h"
#include "Dependencies/glfw-3.3.bin.WIN64/glfw-3.3.bin.WIN64/include/GLFW/glfw3.h"
#include "GameFuncXtra.h"


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
