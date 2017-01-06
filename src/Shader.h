/******************************************************************************
Class:Shader
Implements:
Author:Rich Davison	<richard.davison4@newcastle.ac.uk>
Description: Class to encapsulate OpenGL GLSL shader functionality, treating
all of the shader stages as a single coherent program.

This shouldn't be too tricky a class to implement, just look at the example
in the tutorial of how to attach shader stages to a shader object.

-_-_-_-_-_-_-_,------,   
_-_-_-_-_-_-_-|   /\_/\   NYANYANYAN
-_-_-_-_-_-_-~|__( ^ .^) /
_-_-_-_-_-_-_-""  ""   

*//////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include "GL/glew.h"

#define SHADER_VERTEX 0
#define SHADER_FRAGMENT 1
#define SHADER_GEOMETRY 2

using namespace std;
class Shader	{
public:
	Shader(const string &vertex,const string &fragment ,const string &geometry = "",const string &tcs = "",const string &tes = "");
	~Shader(void);

	//Might as well give you this one ;)
	//It's a good example of how OpenGL treats everything as a named object,
	//using unsigned int 'names' rather than pointers, or a specific struct type.
	//Note the use of the typedef 'GLuint' rather than 'unsigned int' - I did the same
	//in the software rasteriser, typedeffing 'unsigned int' as uint, so it took up
	//less space in the tutorial text...noone seemed to notice!
	GLuint  GetShaderProgram() { return program;}
	bool LinkProgram();

protected:
	void SetDefaultAttributes();
	bool LoadShaderFile(string from ,string &into);
	GLuint GenerateShader(string from ,GLenum type);

	GLuint objects[3];
	GLuint program;

	bool loadFailed ;
};

