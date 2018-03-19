/*
Name : Gyuhyeon, Lee
Assignment Number : 2
Course name : CS250
Term : Spring 2018
*/

#include "Render.h"
#include <iostream>

int CreateShader(const char *shaderCode, GLenum shaderType)
{
	int result = glCreateShader(shaderType);
	glShaderSource(result, 1, (const GLchar **)&shaderCode, NULL);
	glCompileShader(result);

	int success;
	char infoLog[512];
	glGetShaderiv(result, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(result, 512, NULL, infoLog);
		std::cout << "Error compiling shader code!" << infoLog << std::endl;
	}

	return result;
}

int CreateProgram(const char *vertexCode, const char *fragCode)
{
	int vertexShader = CreateShader(vertexCode, GL_VERTEX_SHADER);
	int fragShader = CreateShader(fragCode, GL_FRAGMENT_SHADER);
	
	int result = glCreateProgram();

	// Attack vertex shader to the program
	glAttachShader(result, vertexShader);
	glAttachShader(result, fragShader);
	glLinkProgram(result);

	int success;
	char infoLog[512];
	glGetProgramiv(result, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(result, 512, NULL, infoLog);
		std::cout << "Error linking shader program!" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);

	return result;
}

Render::Render(void)
{
	const char* fragShaderCode =
		R"(#version 330 core
               precision highp float;
               uniform vec3 color;
               out vec4 frag_color;
               void main(void) {
                   frag_color = vec4(color,1);
               })";

	const char* vertexShaderCode =
		R"(#version 330 core
               in vec4 position;
               void main() {
                   gl_Position = position;
               })";

	program = CreateProgram(vertexShaderCode, fragShaderCode);

	// Enable depth buffer
	glEnable(GL_DEPTH_TEST);

	ucolor = glGetUniformLocation(program, "color");
	aposition = glGetAttribLocation(program, "position");
}

Render::~Render(void)
{
	glUseProgram(0);
	glDeleteProgram(program);

	program = 0;
	ucolor = 0;
	aposition = 0;
}

void Render::ClearBuffers(const Vector& c)
{
	glClearColor(c.x, c.y, c.z, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	// Clear depth buffer
	glClearDepth(1);
	glClear(GL_DEPTH_BUFFER_BIT);
}

void Render::SetColor(const Vector& c)
{
	glUseProgram(program);

	glUniform3f(ucolor, c.x, c.y, c.z);

	glUseProgram(0);
}

void Render::DrawLine(const Hcoord& P, const Hcoord& Q)
{
	glUseProgram(program);

	float vertices[] = {P.x, P.y, P.z, P.w,
						Q.x, Q.y, Q.z, Q.w};

	unsigned int vao = 0;
	unsigned int vbo = 0;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	int stride = sizeof(float) * 4;
	
	unsigned int verticesTotalSize = stride * 2;
	glBufferData(GL_ARRAY_BUFFER, verticesTotalSize, (void *)vertices, GL_STATIC_DRAW);

	// Now, tell the VAO how to interpret the currently binded VBO

	glVertexAttribPointer(aposition, 4, GL_FLOAT, GL_FALSE, stride, 0);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_LINES, 0, 2);

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

	glUseProgram(0);
}

void Render::FillTriangle(const Hcoord& P, const Hcoord& Q, const Hcoord& R)
{
	glUseProgram(program);

	float vertices[] = { P.x, P.y, P.z, P.w,
						Q.x, Q.y, Q.z, Q.w,
						R.x, R.y, R.z, R.w};

	unsigned int vao = 0;
	unsigned int vbo = 0;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	int stride = sizeof(float) * 4;

	unsigned int verticesTotalSize = stride * 3;
	glBufferData(GL_ARRAY_BUFFER, verticesTotalSize, (void *)vertices, GL_STATIC_DRAW);

	// Now, tell the VAO how to interpret the currently binded VBO

	glVertexAttribPointer(aposition, 4, GL_FLOAT, GL_FALSE, stride, 0);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

	glUseProgram(0);
}