#ifdef _WIN64
#include "Dependencies/glew-2.1.0-win32/glew-2.1.0/include/GL/glew.h"
#include "Dependencies/glfw-3.3.bin.WIN64/glfw-3.3.bin.WIN64/include/GLFW/glfw3.h"
#include <stdio.h>
#include <Windows.h>
#include "GameFuncXtra.h"
#include "main.h"
GLuint VAO123, shaderProgrammap1;
bool firstRun = true;
int Menu_map(GLFWwindow* window, int menu, int *level_selected) {
	glClearColor(0.7f, 0.3f, 0.3f, 1.0f);
	while (menu == 1) {
		glfwPollEvents();
		glfwSwapBuffers(window);
		GLuint vertexShader, fragmentShader;
		if (firstRun == true) {
			//printf("1");
			GLuint VBO123;
			ShaderSource *vertexShaderSource = "#version 330 core\n"
				"layout ( location = 0 ) in vec3 position;\n"
				"void main()\n"
				"{\n"
				"gl_Position = vec4( position.x, position.y, position.z, 1.0);\n"
				"}";

			ShaderSource *fragmentShaderSource = "#version 330 core\n"
				"out vec4 color;\n"
				"void main()\n"
				"{\n"
				"color = vec4( 1.0f, 0.5f, 0.2f, 1.0f );\n"
				"}\n";
			vertexShadR(&vertexShader, vertexShaderSource);

			fragmentShadR(&fragmentShader, fragmentShaderSource);

			ProgramShadR(&shaderProgrammap1, vertexShader, fragmentShader);


			//WALLS
			GLfloat vertices1[] =
			{
			-0.81f, 0.81f, 0.0f,
			0.81f, 0.81f, 0.0f,
			0.81f, 0.86f, 0.0f,
			-0.81f, 0.86f, 0.0f,
			};
			//GL_Triangle_Fan has one central vertex and other vertices branch off and kinda snake back


			glGenVertexArrays(1, &VAO123);
			glGenBuffers(1, &VBO123);



			glBindVertexArray(VAO123);
			glBindBuffer(GL_ARRAY_BUFFER, VBO123);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_DYNAMIC_DRAW);



			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
			glEnableVertexAttribArray(0);



			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glBindVertexArray(0);
			Drawarray(shaderProgrammap1, VAO123, 4, GL_TRIANGLE_FAN);
			firstRun = false;
			continue;
		}

		else if (firstRun == false) {
			//do main map functions such as inputs in here
			glClear(GL_COLOR_BUFFER_BIT);
			Drawarray(shaderProgrammap1, VAO123, 4, GL_TRIANGLE_FAN);
			SHORT ENTERKEY = GetAsyncKeyState(VK_RETURN);
			if (100000 & ENTERKEY) {
				menu = 0;
			}
			//printf("2");
			continue;
		}
		return 0;
	}
	return 1;
}
#else
#error OS NOT SUPPORTED
#endif