#include "Dependencies/glew-2.1.0-win32/glew-2.1.0/include/GL/glew.h"
#include <Windows.h>
#include <stdio.h>
#include <stdbool.h>
#include "Dependencies/glfw-3.3.bin.WIN64/glfw-3.3.bin.WIN64/include/GLFW/glfw3.h"
#include "Structs.h"
#include "Definitions.h"
#include "Non_Defined_Functions.h"
#include "Dependencies/Personal/GameFuncXtra.h"
//#include "Dependencies/cglm/cglm.h"
typedef int bool_;
typedef const char ShaderSource;
#ifndef _DEBUGGING_GRAPHIC_SUBROUTINE
#define _DEBUGGING_GRAPHIC_SUBROUTINE 0
#endif // !_DEBUGGING_GRAPHIC_SUBROUTINE

#define INIT_GRAPHIC DWORD GraphicThread_ID;HANDLE Graphic_Thread = CreateThread(0, 0, GRFCTHRD, &GRAPHIC_INFO, 0, &GraphicThread_ID);

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

/*DWORD WINAPI Graphic_WORKER_THREAD0(struct GRAPHIC_WORKER_THREADS *input) {

}

DWORD WINAPI Graphic_WORKER_THREAD1(struct GRAPHIC_WORKER_THREADS *input) {

}*/
int Drawarray(int program, int VAO, int amountofvertices, int typeofarray) {
	glUseProgram(program);
	glBindVertexArray(VAO);
	glDrawArrays(typeofarray, 0, amountofvertices);
	glBindVertexArray(0);
	return 1;
}

int Graphic_IO(struct graphic* input, int action, GLFWwindow* window_name, float(*vertices[]), int tag);

DWORD WINAPI GRFCTHRD(struct graphic *input) {
	//printf("%d\n\n\n\n\n\n\n", __LINE__);
	int amountOfObjects = 0;
	 struct GRAPHIC_OBJECT* object = calloc(_STARTING_GRAPHIC_ALLOCATIONS, sizeof(struct graphic));
	 bool* LoadedObject;
	 for (int i = 0; i < _STARTING_GRAPHIC_ALLOCATIONS; i++) {
		 //increasing amountOfObjects number by 1 (each time this cycles is one object allocated therefore if it also adds one each time to amountOfObjects then it can keep track of how many is initially allocated)
		 ++amountOfObjects;
		 //init all base objects
		 object[i].AmountOfVerticesPerline = malloc(sizeof(int));
		 object[i].VAO = malloc(sizeof(unsigned int));
		 object[i].TYPEOFARRAY = malloc(25*sizeof(char));
		 object[i].vertices = calloc(80, sizeof(float));
		 object[i].Program = malloc(sizeof(unsigned int));
		 object[i].AmountOfVertices = malloc(sizeof(int));
	 }
	 LoadedObject = malloc(amountOfObjects * sizeof(bool));

	 for (int i = 0; i < _STARTING_GRAPHIC_ALLOCATIONS; i++) {
		 //for init all to NULL
		 object[i].AmountOfVerticesPerline = NULL;
		 //object[i].VAO = NULL;
		 strcpy(object[i].TYPEOFARRAY, "NULL");
		 object[i].Program = NULL;
		 object[i].AmountOfVertices = NULL;
		 if (i < 3) {
			 LoadedObject[i] = false;
		 }
	 }
	
	 if (_DEBUGGING_GRAPHIC_SUBROUTINE == 1) {
		 for (int i = 0; i < 2; i++)
		 {
			 //checking objects
			 printf("\n\n%s, %f", object[i].TYPEOFARRAY, object[i].vertices[i]);
		 }
	 }









	int mntvrtprln;
	int VertexShader;
	int FragmentShader;
	unsigned int VBO;
	FILE *Error = fopen("APPLICATION_CRASH_REPORT.txt", "w+");



	

	//main     graphic thread
	while (!glfwWindowShouldClose(input->Window_Data.window)) {
		switch (input->function) {
			case NULL:
				continue;
			case 0x01:
				glfwMakeContextCurrent(input->Window_Data.window);
				//add ability to set this clear color later
				if (/*input->Window_Data.ClearColor[3] != 0.0*/1) {
					glClearColor(input->Window_Data.ClearColor[0], input->Window_Data.ClearColor[1], input->Window_Data.ClearColor[2], input->Window_Data.ClearColor[3]);
				}
				else {
					glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
				}

				input->function = NULL;
				input->return_value = 1;
				//make window context current here
				break;
			case 0x02:
				//put Graphical Data into memory

				object->TYPEOFARRAY = input->Object_Data.TYPEOFARRAY;

				//Data_Worker.Objects[input->Tag][0] = input->strngarg;
				if(_DEBUGGING_GRAPHIC_SUBROUTINE)
				printf("R");
				vertexShadR(&VertexShader, vertexShaderSourcebul);
				if (_DEBUGGING_GRAPHIC_SUBROUTINE)
				printf("L");
				fragmentShadR(&FragmentShader, fragmentShaderSourcebul);
				if (_DEBUGGING_GRAPHIC_SUBROUTINE)
				printf("E");
				ProgramShadR(&object[input->Tag].Program, VertexShader, FragmentShader);
				if (_DEBUGGING_GRAPHIC_SUBROUTINE)
				printf("\nH\n");
				//do not delete shaders if input specifies so (helps speed up process if user decides to reuse shaders)
				glDeleteShader(VertexShader);
				glDeleteShader(FragmentShader);



				glGenVertexArrays(1, &object->VAO);

				glGenBuffers(1, &VBO);
				glBindVertexArray(object->VAO);
				glBindBuffer(GL_ARRAY_BUFFER, VBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(object[input->Tag].vertices), object[input->Tag].vertices, GL_STATIC_DRAW);
				mntvrtprln = object[input->Tag].AmountOfVerticesPerline;




				//remove this later, unnecessary calculations

				if (_DEBUGGING_GRAPHIC_SUBROUTINE) {
					printf("%d", mntvrtprln);
				}





				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * mntvrtprln, (void*)0);
				glEnableVertexAttribArray(0);

				if(input->Object_Data.hascolorInput == true){
					glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * mntvrtprln, (void*)0);
					glEnableVertexAttribArray(1);
					if (_DEBUGGING_GRAPHIC_SUBROUTINE == 1) {
						printf("HasColorInput Activated\n");
					}
				}
				
				/*if(input->textureinput == 1){
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * mntvrtprln, (void*)0);
				glEnableVertexAttribArray(2);
				}
				*/

				glBindVertexArray(0);
				/*if(input->textureinput == 1){
				Texture(&width, &height, &nrChannels, input->TextureName);
				}
				*/


				LoadedObject[input->Tag] = true;

				input->strngarg = NULL;
				input->Tag = NULL;
				input->return_value = 0;
				input->function = NULL;
				break;
			case 0x03:


				//all_slots_is_load = false;
				//should_draw[input->Tag] = false;
				//free Graphical Data from memory
				break;
			case 0x04:
				//testing, delete this asap
				
				glClear(GL_COLOR_BUFFER_BIT);


				for (int i = 0; i < amountOfObjects; i++) {
					if (LoadedObject[i] == true) {
						printf("A");
						Drawarray(object[i].Program, object[i].VAO, 4, object[i].TYPEOFARRAY);
					}
					else {
						printf("B");
					}
				}
				printf("\n\n\n\n\n");
				glfwSwapBuffers(input->Window_Data.window);
				break;
			case 0x05:
				//allocate more object data
				break;
			case 0x06:
				//move object data from one tag to another
			case 0x07:
				//deallocate extranious object data
			default:
				fputs("ERROR: NOT A VALID GRAPHICAL FUNCTION", Error);
				printf("ERROR: NOT A VALID GRAPHICAL FUNCTION");
				glfwSetWindowShouldClose(input->Window_Data.window, GLFW_TRUE);
				//no corrosponding function so it defaults here
		}
		



			
			//fprintf(Error, "No function is correlated with set value");

			//glfwSetWindowShouldClose(input->window, GLFW_TRUE);
	}
	glfwSetWindowShouldClose(input->Window_Data.window, GLFW_TRUE);
	for (int i = 0; i < amountOfObjects; i++) {
		glfwPollEvents();
		glDeleteVertexArrays(1, &object[i].VAO);
		object[i].VAO = 0;
		object[i].TYPEOFARRAY = 0;
		printf("%d", i);
		glDeleteProgram(object[i].Program);
		LoadedObject[i] = false;
		free(LoadedObject[i]);
	}
	
	free(object->AmountOfVerticesPerline);
	
	free(object->Program);
	free(object->TYPEOFARRAY);
	free(object->vertices);
	//freeing VAO causes crashing if you do not delete the VAO first, need to delete all data before freeing allocation (delete the vertex array then assign the pointer to 0 to do so)
	
	free(object->VAO);
	
	free(object);
	
	//CloseHandle(GRAPHIC_WORKER_THREAD0);
	return 0;
}
 int INIT_GRAPHIC_SUBROUTINE() {
	 int error = 0;
	 


	 //check for errors when actually initializing everything, if anything does not occur succesfully then return the corrosponding error code via return
	 return error;
}



/*
DWORD WINAPI PRCSCLCTHRD(struct process *input) {
	//main     processing and calculating thread
	while (!glfwWindowShouldClose(input->)) {

	}
	return 0;
}
*/




DWORD WINAPI CLCKACTVTYTHRD(struct timing *input) {
	int MilliSeconds = 0, Seconds = 0;
	while (!glfwWindowShouldClose(input->window)) {
		//for gravity calculations and such, not going to be interacted with by the user, only used for internal threads
		Sleep(10);
		Clock_10MS();
		if (MilliSeconds == 1000) {
			Clock_S();
			Seconds = Seconds + 1;
			MilliSeconds = 0;
		}
		if (Seconds == 60) {
			Clock_M();
			Seconds = 0;
		}
		MilliSeconds = MilliSeconds + 10;
	}
	return 0;
}






main() {
	struct graphic GRAPHIC_INFO = {
	NULL,
	0x03,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	0
	};

	struct timing CLOCK_INFO = {
		NULL
	};
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

	GLFWwindow * Main_Window = glfwCreateWindow(800, 600, "TEST", NULL, NULL);
	glfwMakeContextCurrent(Main_Window);
	glewExperimental = GL_TRUE;
	glewInit();
	
	glViewport(0, 0, 800, 600);

	//GRAPHIC_INFO.window = Main_Window;
	CLOCK_INFO.window = Main_Window;
	float color[] = {
		0.45f, 0.75f, 0.9f, 1.0f
	};
	memcpy(&GRAPHIC_INFO.Window_Data.ClearColor, &color, sizeof(float)*4);
	//Graphic_IO(&GRAPHIC_INFO, 0x01, Main_Window, NULL, NULL);
	GRAPHIC_INFO.Window_Data.window = Main_Window;
	GRAPHIC_INFO.function = 0x01;
	//int xyzy = cos(15);
	//printf("%f", xyzy);
	glfwMakeContextCurrent(NULL);
	INIT_GRAPHIC
	//DWORD GraphicThread_ID;
	//HANDLE Graphic_Thread = CreateThread(0, 0, GRFCTHRD, &GRAPHIC_INFO, 0, &GraphicThread_ID);
	//DWORD ClockThread_ID;
	//HANDLE Clock_Thread = CreateThread(0, 0, CLCKACTVTYTHRD, &CLOCK_INFO, 0, &ClockThread_ID);
	int VertexShader;
	int FragmentShader;
	Sleep(50);
	if (GRAPHIC_INFO.function == NULL) {
		GRAPHIC_INFO.Window_Data.window = Main_Window;
		GRAPHIC_INFO.Object_Data.hascolorInput = false;
		GRAPHIC_INFO.Tag = 0x03;
		GRAPHIC_INFO._LINE_ = __LINE__;
		float vertices[] = {
			0.4f, 0.5f, 0.0f,
		-0.4f, 0.5f, 0.0f,
		-0.4f, -0.5f, 0.0f
		};
		memcpy(&GRAPHIC_INFO.Object_Data.VerticeData, &vertices, sizeof(vertices)/sizeof(float));
		GRAPHIC_INFO.Object_Data.TYPEOFARRAY = "GL_TRIANGLES";
		GRAPHIC_INFO.function = 0x02;
		//Graphic_IO(&GRAPHIC_INFO, 0x06, Main_Window, NULL, NULL);
	}


	///
	Sleep(150);
	if (GRAPHIC_INFO.function == NULL) {
		GRAPHIC_INFO.function = 0x04;
		//GRAPHIC_IO(&GRAPHIC_INFO, 0x02, Main_Window, NULL, NULL);
	}
	///


	//GRAPHIC_INFO.Tag = 0x01;
	//GRAPHIC_INFO.function = 0x01;

	while (!glfwWindowShouldClose(Main_Window)) {
		glfwPollEvents();
		//process Input (user events)
		/*if (GRAPHIC_INFO.return_value != 0) {
			strcat(Error, GRAPHIC_INFO.Error);
		}*/
		
	}
	WaitForSingleObject(Graphic_Thread, INFINITE);
	CloseHandle(Graphic_Thread);
	//CloseHandle(ClockThread_ID);
}


int Graphic_IO(struct graphic* input, int action, GLFWwindow* window_name, float(*vertices[]), int tag, float ClearColor[4]) {
	//simplifies interaction with the graphics thread as it interacts via a struct
	if (input->function != NULL) {
		return 1;
		//is busy with other activity
	}
	switch (action)
	{
	case(0x01):
		//set curr window
		input->Window_Data.window = window_name;
		input->function = 0x01;
		break;
	case(0x02):
		//load graphics
		input->Tag = tag;
		input->Object_Data.VerticeData = vertices;
		input->function = 0x02;
		break;
	case(0x03):
		//free graphics
		input->Tag = tag;
		input->function = 0x03;
		break;
	case(0x04):
		//stops drawing image
		input->Tag = tag;
		break;
	case(0x05):
		//starts drawing image
		input->Tag = tag;
	case(0x06):
		//testing, delete this asap
		input->function = 0x04;
	default:
		break;
	}
}