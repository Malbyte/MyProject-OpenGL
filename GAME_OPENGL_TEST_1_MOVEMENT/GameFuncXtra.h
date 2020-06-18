#pragma once
//produces a vertex shader
void vertexShadR(int *input_frag_shader, const char *vertexShaderSource);
//produces fragment shader
void fragmentShadR(int *fragmentShaderplz, const char *fragmentShaderSource);
//combines shaders
void ProgramShadR(GLuint *shaderProgram, int vertexShader, int fragmentShader);
//checks if it loaded successfully
void isSucessful_Load(int *Success, int *shader, GLchar *infolog, GLchar TYPE_OF_SHADER);
/*Draw to screen (simple version)
all types of GLenum mode types for glDrawArrays & GLDrawElements: GL_TRIANGLE_FAN, GL_TRIANGLE_STRIP, GL_TRIANGLES, GL_POINTS, GL_LINES, GL_LINE_STRIP, GL_LINE_LOOP*/
void Drawarray(int program, int VAO, int amountoftriangles, int typeofarray);