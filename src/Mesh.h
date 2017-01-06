/******************************************************************************
Class:Mesh
Implements:
Author:Rich Davison	<richard.davison4@newcastle.ac.uk>
Description:Wrapper around OpenGL primitives, geometry and related 
OGL functions.

This class should contain all of the functionality required to send some
geometric data to the graphics card, including the creation of the arrays
of position / texture coordinate / etc data


The empty function definitions are or purpose - you should be able to figure
out what sort of OGL functions to use by reading the first two OpenGL-specific
tutorials.

-_-_-_-_-_-_-_,------,   
_-_-_-_-_-_-_-|   /\_/\   NYANYANYAN
-_-_-_-_-_-_-~|__( ^ .^) /
_-_-_-_-_-_-_-""  ""   

*//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../nclgl/OGLRenderer.h"
#include <vector>
#include <string>

using std::string;

enum MeshBuffer {
	VERTEX_BUFFER , COLOUR_BUFFER , TEXTURE_BUFFER , NORMAL_BUFFER , INDEX_BUFFER, MAX_BUFFER
};

class Mesh	{
public:
	Mesh(void);
	virtual ~Mesh(void);

	virtual void Draw();

	//Generates a single triangle, with RGB colours
	static Mesh* GenerateTriangle();
	static Mesh* GenerateQuadPatch();
	static Mesh* LoadMeshFile(const string &filename);

	void SetTextureA(GLuint tex) { texture = tex ;}
	GLuint GetTextureA() { return texture ;}

	void SetTextureB(GLuint tex) { texture2 = tex ;}
	GLuint GetTextureB() { return texture2 ;}

	void SetTextureC(GLuint tex) { texture3 = tex ;}
	GLuint GetTextureC() { return texture3 ;}

	void GenerateNormals();

	/*
	The tutorial mentions that the GenerateCube function should use the same vertices as before...
	This is wrong! I changed my mind, and instead changed the tutorials to load in mesh data from a file,
	so instead implement this function - the loading should be pretty much identical to the Software part
	of the module, with an additional call to your function to upload it all to the GPU.
	*/

	GLuint	type; //GL_TRIANGLES etc

protected:
	//Buffers all VBO data into graphics memory. Required before drawing!
	void	BufferData();

	GLuint arrayObject;
	GLuint bufferObject[MAX_BUFFER];
	GLuint numVertices;
	GLuint texture;
	GLuint texture2;
	GLuint texture3;

	Vector3* normals;

	/*
	Using the following is optional, just remember you need to store
	vertex data somewhere!

	Feel free to give 'interleaved' vertices a go rather than this method,
	perhaps by creating a struct, and having a pointer to an array of that
	struct?
	*/

	//Pointer to vertex position attribute data (badly named...?)
	Vector3*		vertices;
	//Pointer to vertex colour attribute data
	Vector4*		colours;
	//Pointer to vertex texture coordinate attribute data
	Vector2*		textureCoords;

	//Optional, but using indices is more efficient
	GLuint numIndices;
	unsigned int* indices;
};

