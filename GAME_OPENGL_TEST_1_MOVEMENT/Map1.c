#include "Dependencies/glew-2.1.0-win32/glew-2.1.0/include/GL/glew.h"
#include "Dependencies/glfw-3.3.bin.WIN64/glfw-3.3.bin.WIN64/include/GLFW/glfw3.h"
#include <Windows.h>
#include <stdio.h>
#include <time.h>
#include "main.h"
#include "GameFuncXtra.h"
#include "Dependencies/stb-master/stb_image.h"
#define move_w 119

//ignore what i said underneath this, I'll fix this soon!

//im dearly sorry if you are trying to read my spagetti code, i tried having the global floats enter and exit through *int and &int inside the move function parenthesis but int* cannot be compared with normal ints... one day it may be revisited and redone to make it "cleaner"
float a, b, c, d, e, f, g, h, i, y, z, bv1, bv2, bv3, bv4, bv5, bv6, bv7, bv8;
int loo = 0, audio = 1, audst1 = 0, facing = 1, bullet1onscreen = 0, inbattle = 0, escprsd = 0, devmde = 0, load;
const GLint WIDTH = 800, HEIGHT = 600;
GLuint vertexShader, fragmentShader, shaderProgrammap1, shaderProgrammap2, vertexShaderBOSS, shaderProgramBOSS, fragmentShaderBOSS;
GLuint VBOmap1, VAOmap1;
GLuint VBOmap2, VAOmap2;
GLuint VBOBOSS, VAOBOSS;


float vert_velocity, gravity;


const GLchar *vertexShaderSourcemap1 = "#version 330 core\n"
"layout ( location = 0 ) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4( position.x, position.y, position.z, 1.0);\n"
"}";

const GLchar *fragmentShaderSourcemap1 = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4( 1.0f, 0.5f, 0.2f, 1.0f );\n"
"}\n";
Solids_Hitboxes(char Type_Of_Direction);
void deleteVAO() {
	glDeleteVertexArrays(3, &VAOBOSS, &VAOmap1, &VAOmap2);
	glBindVertexArray(0);
	glDeleteProgram(shaderProgramBOSS);
	glDeleteProgram(shaderProgrammap2);
	glDeleteProgram(shaderProgrammap1);
}

void createprograms() {
	vertexShadR(&vertexShader, vertexShaderSourcemap1);

	fragmentShadR(&fragmentShader, fragmentShaderSourcemap1);

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


	glGenVertexArrays(1, &VAOmap1);
	glGenBuffers(1, &VBOmap1);



	glBindVertexArray(VAOmap1);
	glBindBuffer(GL_ARRAY_BUFFER, VBOmap1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_DYNAMIC_DRAW);



	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);



	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	ProgramShadR(&shaderProgrammap2, vertexShader, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



	GLfloat vertices2[] =
	{
	-0.81f, -0.81f, 0.0f,
	0.81f, -0.81f, 0.0f,
	0.81f, -0.86f, 0.0f,
	-0.81f, -0.86f, 0.0f,
	};
	//GL_Triangle_Fan has one central vertex and other vertices branch off and kinda snake back


	glGenVertexArrays(1, &VAOmap2);
	glGenBuffers(1, &VBOmap2);



	glBindVertexArray(VAOmap2);
	glBindBuffer(GL_ARRAY_BUFFER, VBOmap2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);



	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);



	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);







	//load boss
	vertexShadR(&vertexShaderBOSS, vertexShaderSourcemap1);


	fragmentShadR(&fragmentShaderBOSS, fragmentShaderSourcemap1);



	shaderProgramBOSS = glCreateProgram();
	glAttachShader(shaderProgramBOSS, vertexShaderBOSS);
	glAttachShader(shaderProgramBOSS, fragmentShaderBOSS);
	glLinkProgram(shaderProgramBOSS);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	GLfloat verticesBOSS[] =
	{
	bv1, bv2, 0.0f,
	bv3, bv4, 0.0f,
	bv5, bv6, 0.0f,
	bv7, bv8, 0.0f
	};
	//GL_Triangle_Fan has one central vertex and other vertices branch off and kinda snake back

	glGenVertexArrays(1, &VAOBOSS);
	glGenBuffers(1, &VBOBOSS);



	glBindVertexArray(VAOBOSS);
	glBindBuffer(GL_ARRAY_BUFFER, VBOBOSS);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesBOSS), verticesBOSS, GL_STATIC_DRAW);



	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);



	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	glDeleteBuffers(3, &VBOBOSS, &VBOmap1, &VBOmap2);
}
void map_audio() {
	clock_t uptime = clock() / (CLOCKS_PER_SEC / 1000);
	if (loo == 0) {
		if (inbattle == 1) {
			mciSendString("open audio//fight_song_game_2d_beginning.mp3 type mpegvideo alias boss_battle", NULL, 0, 0);
			mciSendString("play boss_battle repeat", NULL, 0, NULL);
			//setup audio beginning and play till the end of (& four measures) of the main melodies singing in harmony then play that specific harmony(and 4 measures after) over and over until a change in music may happen and have it end (or just switch over)
			audst1 = uptime + 82200;
			loo = 1;
			//printf(" what ");
		}
	}
	//mciSendString("close boss_battle", NULL, 0, 0);

}




move(int *error, struct Bullet Bullet1) {
	clock_t uptime = clock() / (CLOCKS_PER_SEC / 1000);

	//keypress recording
	SHORT WKEYCURR = GetAsyncKeyState(0x57);
	SHORT SKEYCURR = GetAsyncKeyState(0x53);
	SHORT AKEYCURR = GetAsyncKeyState(0x41);
	SHORT DKEYCURR = GetAsyncKeyState(0x44);
	SHORT ESCKEYCURR = GetAsyncKeyState(VK_ESCAPE);
	SHORT SPCEKEYCURR = GetAsyncKeyState(VK_SPACE);
	SHORT BCKLEYCURR = GetAsyncKeyState(VK_BACK);
	SHORT ALTKEYCURR = GetAsyncKeyState(VK_MENU);


	if(inbattle == 0){
		Drawarray(shaderProgrammap1, VAOmap1, 4, GL_TRIANGLE_FAN);
		Drawarray(shaderProgrammap2, VAOmap2, 4, GL_TRIANGLE_FAN);
	}

	if (inbattle == 1) {
		Drawarray(shaderProgramBOSS, VAOBOSS, 4, GL_TRIANGLE_STRIP);
	}
	//maybe call flush if there is a lot of draw commands, it might be good to look into for increased performance (search it and get a good understanding beforehand)
	//all types of GLenum mode types for glDrawArrays & GLDrawElements: GL_TRIANGLE_FAN, GL_TRIANGLE_STRIP, GL_TRIANGLES, GL_POINTS, GL_LINES, GL_LINE_STRIP, GL_LINE_LOOP
	///enemy/bullet moves now

	//printf("%.6f", b1b);
	if (Bullet1.v2 >= 1.0f) {
		bullet1onscreen = 0;
	}
	if (inbattle == 1){
		if (Bullet1.v2 >= bv6 + 0.02 && Bullet1.v1 >= bv1) {
			if (Bullet1.v3 < bv7) {
				bullet1onscreen = 0;
				Bullet1.v2 = 1.1f;
				Bullet1.v4 = 1.1f;
				Bullet1.v6 = 1.1f;
				Bullet1.v8 = 1.1f;
				//reads if the bullet is in contact with enemy ship
			}
		}
	}

	if (bullet1onscreen == 1) {
		Bullet1.v2 = Bullet1.v2 + 0.06f;
		Bullet1.v4 = Bullet1.v4 + 0.06f;
		Bullet1.v6 = Bullet1.v6 + 0.06f;
		Bullet1.v8 = Bullet1.v8 + 0.06f;
	}

//-=-=-=-=-=-keypress recording-=-=-=-=-=-

	if (100000 & BCKLEYCURR) {
		if (devmde == 0) {
			devmde = 1;
			printf("\nDevMode on \n");
			Sleep(250);
		}
		else {
			devmde = 0;
			printf("\nDevMode off \n");
			Sleep(250);
		}
	}

	if (devmde == 1) {
		printf("   Ship Front X  %.2f   Ship Front Y  %.2f    time spent open: %dms   \n", f, c, uptime);
	}




	//all of this should be moved to the main file Main.c and there should be a 
	if (inbattle == 1) {
		if (100000 & SPCEKEYCURR) {
			if (bullet1onscreen != 1) {
				Bullet1.v1 = f - 0.005f;
				Bullet1.v2 = c + 0.04f;
				Bullet1.v3 = f - -0.005f;
				Bullet1.v4 = c + 0.04f;
				Bullet1.v5 = f - -0.005f;
				Bullet1.v6 = c + 0.06f;
				Bullet1.v7 = f - 0.005f;
				Bullet1.v8 = c + 0.06f;
				bullet1onscreen = 1;
			}
		}
	}



	if (devmde == 1) {
			//allows testing of different parts of level at will... Remove in production!
		if (100000 & ALTKEYCURR) {
			Sleep(125);
			if (inbattle == 1) {
				inbattle = 0;
			}
			else {
				inbattle = 1;
			}
		}
	}



	if (100000 & ESCKEYCURR) {
		//pause the game
		escprsd = 1;
	}


	
	if (100000 & WKEYCURR) {
		facing = 1;
		if (c <= g) {
			if(inbattle == 0){
				vert_velocity = 0.000128f;
				a = a + 0.1f;
				b = b + 0.1f;
				c = c + 0.1f;
			}
			if (inbattle == 1) {
				for (int x = 0; x <= 0; x++) {
					MoveWKEY();
				}
			}
		}
	}



	//collision detection of walls
	if (100000 & SKEYCURR) {
		facing = 2;
		if (a >= i) {
			if(inbattle == 0){
				//this is harder to read and is very non efficient.  maybe there is some way to use a lookup table?
				if (a > 0.8621f || e < -0.799f || d > 0.799f || a < 0.81f) {
					if (a > -0.8f || e < -0.799f || d > 0.799f || a < -0.849f) {
						for (int x = 0; x <= 0; x++) {
							MoveSKEY();
							//change player's movement/position
						}
					}
				}
			}
			if (inbattle == 1) {
				for (int x = 0; x <= 0; x++) {
					MoveSKEY();
				}
			}
		}
	}
	if (100000 & AKEYCURR) {
		facing = 3;
		if (d >= h) {
			for (int x = 0; x <= 0; x++) {
				MoveAKEY();
				//change player's movement/position
				//do a second time so it still goes double but it looks smoother
			}
		}
	}
	if (100000 & DKEYCURR) {
		facing = 4;
		if (e <= g) {
			for (int x = 0; x <= 0; x++) {
				MoveDKEY();
				//change player's movement/position
				//do a second time so it still goes double but it looks smoother
			}
		}
	}


	Solids_Hitboxes(move_w);
	error = 0;
	return 1;
}

Solids_Hitboxes(char Type_Of_Direction) {
	if (Type_Of_Direction == 119) {
		if (c < 0.8f || e < -0.8f || /*c > 0.849f ||*/ d > 0.8f) {//wall one
			if (c < -0.86f || e < -0.8f || c > -0.849f || d > 0.8f) {
				return 0;
			}
			else
			{
				return 1;
			}
		}
		else
		{
			return 1;
		}
	}
}