#pragma once
//
#define FUNCXTRA_GRAPHICS
//
//anytime this is used, will look for definitions in the Main header
#ifdef FUNCXTRA_GRAPHICS
//produces a vertex shader
void vertexShadR(int *input_frag_shader, const char *vertexShaderSource);
//produces fragment shader
void fragmentShadR(int *fragmentShaderplz, const char *fragmentShaderSource);
//combines shaders into shaderprogram
void ProgramShadR(GLuint *shaderProgram, int vertexShader, int fragmentShader);
//checks if it loaded successfully
void isSucessful_Load(int *Success, int *shader, char *infolog, char TYPE_OF_SHADER);
/*Draw to screen (simple version)
all types of GLenum mode types for glDrawArrays & GLDrawElements: GL_TRIANGLE_FAN, GL_TRIANGLE_STRIP, GL_TRIANGLES, GL_POINTS, GL_LINES, GL_LINE_STRIP, GL_LINE_LOOP*/
int Drawarray(int program, int VAO, int amountofvertices, int typeofarray);
//texture objects a lot easier (simple version)
void Texture(int *width, int *height, int *nrChannels, char Image[125]);
void ShaderSources(char * Input_Shader_Tag, int chosen);
#endif