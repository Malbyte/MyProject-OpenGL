#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include "GameFuncXtra.h"
#include "main.h"

//#pragma comment (lib , "winmm.lib")
//^for playsound it requires winmm.lib and that apparently is not included so go to linker, input, additional dependecies and add as a new lib winmm.lib and you will not need #pragma comment and get the errors


//Draw to screen (simple version)


//make all Global variables local! 
int x = 0, error;
float a = -0.04f, b = -0.04f, c = 0.04f, d = -0.04f, e = 0.04f, f = 0.00f, g = 0.98f, h = -0.98f, i = -0.97f, z = 0.0097f, bv1 = 0.7f, bv2 = 0.8f, bv3 = 0.8f, bv4 = 0.8f, bv5 = 0.8f, bv6 = 0.7f, bv7 = 0.9f, bv8 = 0.8f;
float b1a = 0.0f, b1b = 0.0f, b1c = 0.0f, b1d = 0.0f, b1e = 0.0f, b1f = 0.0f, b1g = 0.0f, b1h = 0.0f;//this is the fallback/normal speed/size/borders/bullets
const GLint WIDTH, HEIGHT;
const GLchar *vertexShaderSource = "#version 330 core\n"
"layout ( location = 0 ) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4( position.x, position.y, position.z, 1.0);\n"
"}";

const GLchar *fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4( 1.0f, 0.5f, 0.2f, 1.0f );\n"
"}\n";

main() {
	GLuint vertexShader, fragmentShader;
	//mciSendString("open audio//game_intro_1.mp3 type mpegvideo alias mp3", NULL, 0, 0);//MCI can load mp3, avi & wav.  playsound is easier but mci allows for smaller audio files.  playsound is also easier to understand
	//mciSendString("play mp3 repeat", NULL, 0, NULL);//remove repeat from the quotes to get it to play once:  mciSendString("play mp3", NULL, 0, NULL);
	//PlaySound("audio//game_intro_1_placeholder.wav", NULL, SND_ASYNC | SND_LOOP | SND_FILENAME);//SND_ASYNC allows the application to keep running
	//put main loading of graphics here (in opengl graphics loop check for w a s d then enemy & other sprites then finally reload the graphics vbo and vao)
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//mjor sets one value of which opengl using and minor sets the tenth
	//right now it it using opengl 4.5/ usually you should use one of the newest ones, going back one whole digit in the ones place in this situation is going to lose a lot of new and better functions
	//says try to set it to 3.3 otherwise set it to older version
	// youtuber sets it to 3.3, older commands can work on newer versions!
	//youtuber:  https://youtu.be/mGC4T9AG4nc
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//core profile just uses new opengl stuff
	//compatabilty uses old way as well
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//sets to forward compatability for up to newest opengl ^
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	//sets window to not be able to be resized, just set to true if want to be able to do that

	GLFWwindow * window = glfwCreateWindow(WIDTH, HEIGHT, "LEARNING OPENGL!", NULL, NULL);

	int screenwidth, screenheight;
	glfwGetFramebufferSize(window, &screenwidth, &screenheight);
	//getting the actual width of the window relative to the whole screen

	if (NULL == window) {
		printf("failed to create GLFW window");
		glfwTerminate();
		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	//so it knows to use a modern approach to retrieve function pointers & extensions/// basically saying use newer version of glew

	if (GLEW_OK != glewInit()) {
		printf("Failed to initialise GLEW");

		return EXIT_FAILURE;
	}

	glViewport(0, 0, screenwidth, screenheight);


	//vertex shaders

	vertexShadR(&vertexShader, vertexShaderSource);
	//fragment shaders

	fragmentShadR(&fragmentShader, fragmentShaderSource);


	//attachment of shaders to glCreateProgram function
	GLuint shaderProgram;
	ProgramShadR(&shaderProgram, vertexShader, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//^attachment of shaders to glCreateProgram function^
	//setting of vertices for object
	GLfloat vertices[] =
	{
		d, a, 0.0f,	//bottom left
		e, b, 0.0f,	//bottom right
		f, c, 0.0f  //top
	};
	//^setting of vertices for object^
	//setting of vertex Arrays object & vertex Buffers object
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);




	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);
	//^vertex buffer object & vertex array object^
	



	//bullets on screen


	GLuint shaderProgrambullet1 = glCreateProgram();
	glAttachShader(shaderProgrambullet1, vertexShader);
	glAttachShader(shaderProgrambullet1, fragmentShader);
	glLinkProgram(shaderProgrambullet1);





	GLfloat verticesbullet1[] =
	{
	b1a, b1b, 0.0f,
	b1c, b1d, 0.0f,
	b1e, b1f, 0.0f,
	b1g, b1h, 0.0f
	};
	//GL_Triangle_Fan has one central vertex and other vertices branch off and kinda snake back


	GLuint VBObullet1, VAObullet1;
	glGenVertexArrays(1, &VAObullet1);
	glGenBuffers(1, &VBObullet1);


	//glActiveTexture(GL_TEXTURE0);
	//GLbindTexture(GL_TEXTURE_2D, texture);
	//glUniform1i(glGetUniformLocation(ourshader.program, "ourTexture"), 0);


	glBindVertexArray(VAObullet1);
	glBindBuffer(GL_ARRAY_BUFFER, VBObullet1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesbullet1), verticesbullet1, GL_STATIC_DRAW);



	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);



	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);


	////
	inbattle = 1;
	////

	while (!glfwWindowShouldClose(window)) {
		//checking for events, clearing, rendering OpenGL, etc
		glfwPollEvents();
		//is to show window is responding ^
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//this is here to not have a blank/black background ^
		glClear(GL_COLOR_BUFFER_BIT);
		//this is to clear window for next draw ^
		move(&error);
		if (error == 1) {
			printf("Move_Function_Error");
		}
		int pausbgn = 0;
		if (escprsd == 1) {
			while (escprsd == 1){
				//pause
				glfwPollEvents();
				glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT);
				mciSendString("pause boss_battle", NULL, 0, 0);
				mciSendString("pause level_audio", NULL, 0, 0);
				glfwSwapBuffers(window);
				if (pausbgn == 0) {
					Sleep(250);
				}
				SHORT ESCKEY = GetAsyncKeyState(VK_ESCAPE);
				if (100000 & ESCKEY) {
					escprsd = 0;
				}
				pausbgn = 1;
			}
			pausbgn = 0;
			Sleep(250);
			mciSendString("resume boss_battle", NULL, 0, 0);
			mciSendString("resume level_audio", NULL, 0, 0);
		}
		//this is a basic pause menu^



		//^this is to read if you pressed any movement keys

		//here do math to check if any rules are being activated such as: being killed by enemy


		GLfloat vertices[] =
		{
			d, a, 0.0f, //bottom left
			e, b, 0.0f,//bottom right
			f, c, 0.0f,//top
		};

		//draw opengl stuff
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);//3 symbolizes the amount of vertices being added
		glBindVertexArray(0);

		//drawing bullets on screen
		GLfloat verticesbullet1[] =
		{
		b1a, b1b, 0.0f,
		b1c, b1d, 0.0f,
		b1e, b1f, 0.0f,
		b1g, b1h, 0.0f
		};
		glBindBuffer(GL_ARRAY_BUFFER, VBObullet1);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticesbullet1), verticesbullet1, GL_STATIC_DRAW);

		
		Drawarray(shaderProgrambullet1, VAObullet1, 4, GL_TRIANGLE_FAN);

		glfwSwapBuffers(window);
		//printf(" %f ", d);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate;
	return EXIT_SUCCESS;



	/*SHORT y = 1 << 5;
	if (y == 32) {
		printf("howdy");
	}
	printf("%d", y);*/
	while (1) {
		SHORT WKEYCURR = GetAsyncKeyState(0x57);
		if (100000 & WKEYCURR) {
			//it reads it in binary maybe?  100000 is binary version of 32 which is 1<<5
			//<< operator means move the number over a certain amount of place(add number of zeros to end according to the number to the right[1<<5 means move the 1 digit over 5 places so now it is 100,000])
			//& is and sign for and input,

			//learn bitwise functions (>>, <<, >>=, <<=)  and the & sign for an equation
		}
	}
}





void Drawarray(int program, int VAO, int amountofvertices, int typeofarray) {
	glUseProgram(program);
	glBindVertexArray(VAO);
	glDrawArrays(typeofarray, 0, amountofvertices);
	glBindVertexArray(0);
}
void MoveWKEY() {
	a = a + z;
	b = b + z;
	c = c + z;
}
void MoveSKEY() {
	a = a - z;
	b = b - z;
	c = c - z;
}
void MoveAKEY() {
	d = d - z;
	e = e - z;
	f = f - z;
}
void MoveDKEY() {
	d = d + z;
	e = e + z;
	f = f + z;
}