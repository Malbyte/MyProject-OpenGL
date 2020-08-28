#include "Dependencies/glew-2.1.0-win32/glew-2.1.0/include/GL/glew.h"
//something to help replace glew maybe? https://www.rastertek.com/gl40tut03.html
#include "Dependencies/glfw-3.3.bin.WIN64/glfw-3.3.bin.WIN64/include/GLFW/glfw3.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "GameFuncXtra.h"
#include "main.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Dependencies/stb-master/stb_image.h"
#include <process.h>
//#pragma comment (lib , "winmm.lib")
//^for playsound it requires winmm.lib and that apparently is not included so go to linker, input, additional dependecies and add as a new lib winmm.lib and you will not need #pragma comment and get the errors

//make all Global variables local! 
int x = 0, error, LastCallTime;
float g = 0.98f, h = -0.98f, i = -0.97f, z = 0.0097f, bv1 = 0.7f, bv2 = 0.8f, bv3 = 0.8f, bv4 = 0.8f, bv5 = 0.8f, bv6 = 0.7f, bv7 = 0.9f, bv8 = 0.8f, Health = 3.0f;
Xcoord /*player*/d = -0.04f, e = 0.04f, f = 0.00f/*player*/;
Ycoord /*player*/a = -0.04f, b = -0.04f, c = 0.04f/*player*/;
//this is the fallback/normal speed/size/borders/bullets
float vert_velocity = 0.00128f, gravity = 0.00000281f;

const int WIDTH, HEIGHT;

bool stop = false;


ShaderSource *vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"layout(location = 1) in vec3 aColor;\n"
"layout(location = 2) in vec2 aTexCoord;\n"

"out vec3 ourColor;\n"
"out vec2 TexCoord;\n"

"void main()\n"
"{\n"
"	gl_Position = vec4( aPos, 1.0);\n"
"	ourColor = aColor;\n"
"	TexCoord = aTexCoord;\n"
"}\n";
ShaderSource *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"

"in vec3 ourColor;\n"
"in vec2 TexCoord;\n"

"uniform sampler2D ourTexture;\n"

"void main()\n"
"{\n"
"	FragColor = texture(ourTexture, TexCoord);\n"
//"FragColor = vec4(ourColor, 1.0);\n"
"}\n";






ShaderSource *vertexShaderSource2 = "#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"layout(location = 1) in vec3 aColor;\n"
"layout(location = 2) in vec2 aTexCoord;\n"

"out vec3 ourColor;\n"
"out vec2 TexCoord;\n"

"void main()\n"
"{\n"
"	gl_Position = vec4( aPos, 1.0);\n"
"	ourColor = aColor;\n"
"	TexCoord = aTexCoord;\n"
"}\n";
ShaderSource *fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"

"in vec3 ourColor;\n"
"in vec2 TexCoord;\n"

"uniform sampler2D ourTexture;\n"

"void main()\n"
"{\n"
"	FragColor = texture(ourTexture, TexCoord);\n"
//"FragColor = vec4(ourColor, 1.0);\n"
"}\n";




ShaderSource *vertexShaderSourcebul = "#version 330 core\n"
"layout ( location = 0 ) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4( position.x, position.y, position.z, 1.0);\n"
"}";

ShaderSource *fragmentShaderSourcebul = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4( 1.0f, 0.5f, 0.2f, 1.0f );\n"
"}\n";


#ifdef _WIN64
#include <Windows.h>

struct Bullet Bullet1;
void lelelelel() {
	printf("Lel\n");
}
DWORD WINAPI Mythread(bool *x) {
	while (stop == false) {
		if (*x == 1){
			printf("Damn");
		}
		printf("E");
	}
	lelelelel();
	return 0;
}
main() {
	printf("E");
	DWORD mythreadid;
	bool DX = 0;
	//to pass multiple variables to a thread you need to use a structure
	HANDLE myhandle = CreateThread(0, 0, Mythread, &DX, 0, &mythreadid);
	bool main_menu = true;
	int vertexShader, fragmentShader;
	bool graphic_load = false;
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
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//sets window to not be able to be resized, just set to true if want to be able to do that

	GLFWwindow * window = glfwCreateWindow(WIDTH, HEIGHT, "LEARNING OPENGL!", NULL, NULL);
	glfwMakeContextCurrent(window);
	//VSYNC

	glfwSwapInterval(1);

	int screenwidth, screenheight;
	glfwGetFramebufferSize(window, &screenwidth, &screenheight);
	printf("%d", screenheight);
	//getting the actual width of the window relative to the whole screen

	if (NULL == window) {
		printf("failed to create GLFW window");
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glewExperimental = GL_TRUE;
	//so it knows to use a modern approach to retrieve function pointers & extensions/// basically saying use newer version of glew

	if (GLEW_OK != glewInit()) {
		printf("Failed to initialise GLEW");

		return EXIT_FAILURE;
	}
	stbi_set_flip_vertically_on_load(true);
	//sets images to load non upside down since 0.0 is usually set to the top of the y axis in images so this flips the y-axis
	glViewport(0, 0, screenwidth, screenheight);





	//vertex shaders

	vertexShadR(&vertexShader, vertexShaderSource);
	//fragment shaders

	fragmentShadR(&fragmentShader, fragmentShaderSource);


	//attachment of shaders to glCreateProgram function
	GLuint shaderProgram;
	ProgramShadR(&shaderProgram, vertexShader, fragmentShader);

	//^attachment of shaders to glCreateProgram function^
	//setting of vertices for object
	VerticeData vertices[] =
	{	//positions	       //colors	          //texture coords
		d, a, 0.0f,  1.0f, 0.5f, 0.2f,  1.0f, 1.0f,
		e, b, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
		f, c, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f
	};
	///REMEMBER TO ADD SECOND VERTEXATTRIBPOINTER!!!!
	//^setting of vertices for object^
	//setting of vertex Arrays object & vertex Buffers object
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);



	//the Attrib pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	//glBindTexture(GL_TEXTURE_2D, 0);
	//^vertex buffer object & vertex array object^



	//texture loading
	//quick reminder that unsigned means to instead start from the lowest value in the negatives to the highest value in positives, it instead shifts all over so there is only positives (instead of starting from -x all the way to x, it is instead from 0 to 2x)
	int width = 0, height = 0, nrChannels = 0;
	Texture(&width, &height, &nrChannels, "temporary-texture.jpg");




	//bullets on screen
	//vertex shaders

	vertexShadR(&vertexShader, vertexShaderSourcebul);
	//fragment shaders

	fragmentShadR(&fragmentShader, fragmentShaderSourcebul);

	GLuint shaderProgrambullet1 = glCreateProgram();
	glAttachShader(shaderProgrambullet1, vertexShader);
	glAttachShader(shaderProgrambullet1, fragmentShader);
	glLinkProgram(shaderProgrambullet1);





	VerticeData verticesbullet1[] =
	{
	Bullet1.v1, Bullet1.v2, 0.0f,
	Bullet1.v3, Bullet1.v4, 0.0f,
	Bullet1.v5, Bullet1.v6, 0.0f,
	Bullet1.v7, Bullet1.v8, 0.0f
	};
	//GL_Triangle_Fan has one central vertex and other vertices branch off and kinda snake back


	GLuint VBObullet1, VAObullet1;
	glGenVertexArrays(1, &VAObullet1);
	glGenBuffers(1, &VBObullet1);


	glBindVertexArray(VAObullet1);
	glBindBuffer(GL_ARRAY_BUFFER, VBObullet1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesbullet1), verticesbullet1, GL_STATIC_DRAW);



	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);



	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);








	//vertex shaders

	vertexShadR(&vertexShader, vertexShaderSource);
	//fragment shaders

	fragmentShadR(&fragmentShader, fragmentShaderSource);

	GLuint shaderProgramMenu = glCreateProgram();
	glAttachShader(shaderProgramMenu, vertexShader);
	glAttachShader(shaderProgramMenu, fragmentShader);
	glLinkProgram(shaderProgramMenu);





	VerticeData verticesMenu[] =
	{	//positions	       //colors	          //texture coords
		1.0f, 1.0f, 0.0f,  1.0f, 0.5f, 0.2f,  1.0f, 1.0f,
		-1.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
		1.0f, -1.0f, 0.0f,   0.2f, 0.3f, 0.4f,  1.0f, 0.0f
	};


	GLuint VBOMenu, VAOMenu;
	glGenVertexArrays(1, &VAOMenu);
	glGenBuffers(1, &VBOMenu);

	glBindVertexArray(VAOMenu);
	glBindBuffer(GL_ARRAY_BUFFER, VBOMenu);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesMenu), verticesMenu, GL_DYNAMIC_DRAW);



	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(0);



	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	Texture(&width, &height, &nrChannels, "temporary-texture.jpg");
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);




	////
	inbattle = 0;
	////
	createprograms();
	while (!glfwWindowShouldClose(window)) {



		if (menu == 1) {
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			//home menu
			while (menu == 1) {
				//main_menu = false;
				glfwPollEvents();
				if (glfwWindowShouldClose(window)) {
					break;
				}
				SHORT ENTERCURR = GetAsyncKeyState(VK_RETURN);
				if (/*enter into map*/ ENTERCURR & 100000) {
					if (Menu_map(window, menu, 0) == 1) {
						menu = 0;
						break;
						Sleep(250);
						//printf("Successful");
					}
					else {
						printf("'Menu_map' function has run into an unexpected error.");
					}
				}
				//
				//
				glClear(GL_COLOR_BUFFER_BIT);
				Drawarray(shaderProgramMenu, VAOMenu, 4, GL_TRIANGLE_FAN);
				glfwSwapBuffers(window);
			}
		}
		if (glfwWindowShouldClose(window)) {
			break;
		}
		int pausbgn = 0;


		DX = 1;
		if (menu == 4) {
			while (menu == 4) {
				stop = true;
				//pause
				glfwPollEvents();
				//printf("%d, %d, %d\n", width, height, nrChannels);
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
					menu = 0;
				}
				pausbgn = 1;
				if (glfwWindowShouldClose(window)) {
					break;
				}
			}
			pausbgn = 0;
			Sleep(250);
			mciSendString("resume boss_battle", NULL, 0, 0);
			mciSendString("resume level_audio", NULL, 0, 0);
		}
		//this is a basic pause menu^

		//checking for events, clearing, rendering OpenGL, etc
		glfwPollEvents();
		//is to show window is responding ^
		
		//gravity i guess
		if (inbattle == 0) {
			//have a check to see how long since the last time this was called, if it was more than 1/4 second (like 2/4 seconds) then the person is having low framerate and we want to have this happen once per quarter second so have it do it twice maybe?
			if (a >= i) {
				//a, b, and c
				a = a + vert_velocity;
				b = b + vert_velocity;
				c = c + vert_velocity;
				if (vert_velocity > -0.0058f) {
					vert_velocity = vert_velocity - gravity;
					//Right now this is frame dependent, this needs to be time dependent!
				}
			}
			else {
				vert_velocity = 0;
			}
		}
		//this next part is in case it gains too much speed and goes underneath the map a smidge.  this puts the character back on top (when the math subtracts beneath 1.0)
		if (b <= -1.01f) {
			printf("T");
			c = c - (b - 1.0f);
			b = b - (b - 1.0f);
			a = a - (a - 1.0f);
		}



		//map_audio();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//this is here to not have a blank/black background ^
		glClear(GL_COLOR_BUFFER_BIT);
		//this is to clear window for next draw ^
		move(&error, &Bullet1);
		if (error == 1) {
			printf("Move_Function_Error");
			break;
		}

		//here do math to check if any rules are being activated such as: being killed by enemy


		VerticeData vertices[] =
		{	//positions	 //colors	        //texture coords
			d, a, 0.0f,  1.0f, 0.5f, 0.2f,  1.0f, 1.0f,
			e, b, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
			f, c, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f
		};
		//draw opengl stuff
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		Drawarray(shaderProgram, VAO, 3, GL_TRIANGLES);

		//drawing bullets on screen
		VerticeData verticesbullet1[] =
		{
		Bullet1.v1, Bullet1.v2, 0.0f,
		Bullet1.v3, Bullet1.v4, 0.0f,
		Bullet1.v5, Bullet1.v6, 0.0f,
		Bullet1.v7, Bullet1.v8, 0.0f
		};
		glBindBuffer(GL_ARRAY_BUFFER, VBObullet1);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticesbullet1), verticesbullet1, GL_STATIC_DRAW);


		Drawarray(shaderProgrambullet1, VAObullet1, 4, GL_TRIANGLE_FAN);

		glfwSwapBuffers(window);
		//printf(" %f ", d);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	////
	deleteVAO();
	////
	glfwTerminate;
	return EXIT_SUCCESS;
}
#else
#error OS NOT SUPPORTED
#endif

int tpslc(int *x) {
	//time    last call
	int y = 0;
	clock_t uptime = clock() / (CLOCKS_PER_SEC);
	if (LastCallTime < uptime) {
		int y = 1;
		x = LastCallTime - uptime;
	}
	LastCallTime = LastCallTime + uptime;
	return y;
}


void Texture(int *width, int *height, int *nrChannels, char Image[125]) {
	//texture loading
	unsigned int texture;
	//quick reminder that unsigned means to instead start from the lowest value in the negatives to the highest value in positives, it instead shifts all over so there is only positives (instead of starting from -x all the way to x, it is instead from 0 to 2x)
	unsigned char *data = stbi_load(Image, &width, &height, &nrChannels, 0);
	//stbi_load loads image data (selects image in first parameter) then outputs the width, height and nrChannels (and returns values required to load image as texture)
	//setting of currently bound texture of texture wrapping and filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glGenTextures(1, &texture);
	//glGenTextures takes how many textures we want to have generated then stores them inside the integer which is being pointed to
	glBindTexture(GL_TEXTURE_2D, texture);
	//lets you set what type of data will be stored inside, in this case the format for 2d textures will be stored inside of texture


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	//glTexImage2D generates a 2d texture using the 2d texture data loaded from an image.
	//glTexImage2D(texture target(will only generate texture of same target so GL_TEXURE 1D/3D will not be generated as well), mipmap level, what format to sture texture(*for example this current image is RGB therefore we shall tell the function to store it as such*), width of new texture, height of new texture, 0 (legacy command, seems uneeded, maybe check it out sometime?), format of source image(RGB, CMYK, etc), datatype of image, image data)
	//The top of page 60 in LearnOpengl goes into better detail on glTexImage2D!!
	glGenerateMipmap(GL_TEXTURE_2D);
	//
	stbi_image_free(data);
	//freeing image from memory so it is not floating about taking up room.
}


int Drawarray(int program, int VAO, int amountofvertices, int typeofarray) {
	glUseProgram(program);
	glBindVertexArray(VAO);
	glDrawArrays(typeofarray, 0, amountofvertices);
	glBindVertexArray(0);
	return 1;
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
void jump(int position_x, int position_y, int velocity_x, int velocity_y, int gravity) {
	//website of information on some game physics such as jumping (can be used for things bouncing and such, basically goes more in depth on how to use the equation of a parabola in game sense [y = ax^2+bx+c])	
	//https://medium.com/@brazmogu/physics-for-game-dev-a-platformer-physics-cheatsheet-f34b09064558
}
int Damage(char type_of_enemy) {
	switch (type_of_enemy)
	{
	case 0x01:
		Health = Health - 0.5f;
		if (devmde == 1) {
			printf("Hit: Bullet\n");
		}
		return 1;
	case 0x02:
		Health = Health - 0.25f;
		return 1;
	case 0x03:
		Health = Health - 1.0f;
		return 1;
	default:
		return 0;
	}
}