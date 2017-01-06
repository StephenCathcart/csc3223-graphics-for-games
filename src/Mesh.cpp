#include "Mesh.h"

Mesh::Mesh(void)	{
	for( int i = 0; i < MAX_BUFFER ; ++i) {
		bufferObject[i] = 0;
	}
	glGenVertexArrays(1, &arrayObject);

	numVertices		= NULL;
	texture			= NULL;
	texture2		= NULL;
	texture3		= NULL;
	numIndices		= NULL;
	indices			= NULL;
	textureCoords	= NULL;
	vertices		= NULL;
	colours			= NULL;
	normals			= NULL;
	type			= GL_TRIANGLES;
}

Mesh::~Mesh(void) {
	glDeleteVertexArrays(1, &arrayObject);
	glDeleteBuffers(MAX_BUFFER ,bufferObject);
	glDeleteTextures(1 ,& texture);
	delete[]vertices;
	delete[]textureCoords;
	delete[]colours;
	delete[]normals;
	delete[]indices ;
}

void Mesh::Draw()	{
	//How you implement this function is up to you, but it
	//should in some way enable the VBOs required for rendering,
	//and call the appropriate OpenGL draw function
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D , texture);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D , texture2);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D , texture3);

	glBindVertexArray(arrayObject);

	if( bufferObject[INDEX_BUFFER]) {
		glDrawElements (type ,numIndices ,GL_UNSIGNED_INT ,0);
	}
	else {
		glDrawArrays(type , 0,numVertices);
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D , 0);
}

Mesh* Mesh::GenerateTriangle()	{
	/*
	Here should go your code to create a triangle... it should
	be pretty similar to the code from the software rasteriser!
	*/
	Mesh*m = new Mesh();
	m-> numVertices = 3;

	m-> vertices = new Vector3[m-> numVertices];
	m-> vertices[0] = Vector3(0.0f, 0.5f, 0.0f);
	m-> vertices[1] = Vector3(0.5f, -0.5f, 0.0f);
	m-> vertices[2] = Vector3(-0.5f, -0.5f, 0.0f);

	m-> textureCoords = new Vector2[m-> numVertices];
	m-> textureCoords[0] = Vector2(0.5f, 0.0f);
	m-> textureCoords[1] = Vector2(1.0f, 1.0f);
	m-> textureCoords[2] = Vector2(0.0f, 1.0f);

	m-> colours = new Vector4[m-> numVertices];
	m-> colours[0] = Vector4(1.0f, 0.0f, 0.0f ,1.0f);
	m-> colours[1] = Vector4(0.0f, 1.0f, 0.0f ,1.0f);
	m-> colours[2] = Vector4(0.0f, 0.0f, 1.0f ,1.0f);

	m->GenerateNormals();
	m->BufferData();	//Send our new data to the GPU
	return m;
}

Mesh * Mesh::GenerateQuadPatch() {
	Mesh * m = new Mesh ();
	m-> numVertices = 4; // Number of vertices
	m-> type = GL_PATCHES ; // The OpenGL render type

	m-> vertices = new Vector3 [m-> numVertices ];
	m-> textureCoords = new Vector2 [m-> numVertices ];

	m-> vertices [0] = Vector3 ( -1.0f, -1.0f, 0.0f);
	m-> vertices [1] = Vector3 ( -1.0f, 1.0f, 0.0f);
	m-> vertices [2] = Vector3 (1.0f, -1.0f, 0.0f);
	m-> vertices [3] = Vector3 (1.0f, 1.0f, 0.0f);

	m-> textureCoords [0] = Vector2 (0.0f, 1.0f);
	m-> textureCoords [1] = Vector2 (0.0f, 0.0f);
	m-> textureCoords [2] = Vector2 (1.0f, 1.0f);
	m-> textureCoords [3] = Vector2 (1.0f, 0.0f);

	m-> BufferData (); // Function containing all of the VAO and VBO setup

	return m;
}

//How you implement this function is up to you, but it
//should create some VBOs (and perhaps a VAO?), and upload
//some data into it, so that it can be used by the Draw function
void Mesh :: BufferData () {
#define normalIndex 3

	glBindVertexArray(arrayObject );
	glGenBuffers(1, &bufferObject[VERTEX_BUFFER]);
	glBindBuffer(GL_ARRAY_BUFFER , bufferObject[VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER , numVertices * sizeof(Vector3),
		vertices ,GL_STATIC_DRAW );
	glVertexAttribPointer(VERTEX_BUFFER ,3, GL_FLOAT ,GL_FALSE ,0, 0);
	glEnableVertexAttribArray(VERTEX_BUFFER);

	if(textureCoords) { 
		glGenBuffers(1, & bufferObject[ TEXTURE_BUFFER ]);
		glBindBuffer(GL_ARRAY_BUFFER , bufferObject[ TEXTURE_BUFFER ]);
		glBufferData(GL_ARRAY_BUFFER , numVertices * sizeof(Vector2),
			textureCoords , GL_STATIC_DRAW);
		glVertexAttribPointer(TEXTURE_BUFFER , 2, GL_FLOAT , GL_FALSE ,0 ,0);
		glEnableVertexAttribArray(TEXTURE_BUFFER);
	}

	if(colours) {
		glGenBuffers(1, &bufferObject[COLOUR_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER , bufferObject[COLOUR_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER , numVertices * sizeof(Vector4),
			colours ,GL_STATIC_DRAW);
		glVertexAttribPointer(COLOUR_BUFFER ,4 ,GL_FLOAT ,GL_FALSE ,0 ,0);
		glEnableVertexAttribArray(COLOUR_BUFFER);
	}

	if(normals) {
		glGenBuffers(1, & bufferObject [NORMAL_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER ,bufferObject[NORMAL_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER ,numVertices * sizeof(Vector3),
			normals, GL_STATIC_DRAW);
		glVertexAttribPointer(NORMAL_BUFFER ,3, GL_FLOAT ,GL_FALSE ,0 ,0);
		glEnableVertexAttribArray(NORMAL_BUFFER);
	}

	if(indices) {
		glGenBuffers(1, &bufferObject[INDEX_BUFFER]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
			bufferObject[INDEX_BUFFER]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER ,numIndices * sizeof(GLuint),
			indices, GL_STATIC_DRAW );
	}

	glBindVertexArray (0);
}

Mesh*	Mesh::LoadMeshFile(const string &filename) {
	Mesh *m = new Mesh ();

	std::ifstream f(filename);

	if (!f) {
		return NULL ;
	}

	//m->type = GL_TRIANGLES;
	f >> m-> numVertices;

	int hasTex = 0;
	int hasColour = 0;

	f >> hasTex ; // Oooh ! Sneak preview of later tutorial ...
	f >> hasColour;

	m-> vertices = new Vector3 [m->numVertices];
	m-> textureCoords = new Vector2 [m->numVertices ];
	m-> colours = new Vector4[m->numVertices ];

	for (int i = 0; i < m-> numVertices ; ++i) {
		f >> m-> vertices [i].x;
		f >> m-> vertices [i].y;
		f >> m-> vertices [i].z;
	}
	if( hasColour ) {
		for (int i = 0; i < m-> numVertices ; ++i) {
			f >> m-> colours [i].x; 
			f >> m-> colours [i].y;
			f >> m-> colours [i].z; 
			f >> m-> colours [i].w;
		}
	}
	if( hasTex ) { // new bit !!
		for ( unsigned int i = 0; i < m -> numVertices ; ++ i ) {
			f >> m -> textureCoords [ i ]. x ;
			f >> m -> textureCoords [ i ]. y ;
		}
	} // end of new bit :)


	for(int i = 0; i < m->numVertices; i++){
		if(i < 6){
			m->colours [i].x = 100.1f;
			m->colours [i].y = 0.0f;
			m->colours [i].z = 0.0f;
			m->colours [i].w = 1.0f;
		}else if(i >= 6 && i < 12) {
			m->colours [i].x = 0.0f;
			m->colours [i].y = 100.0f;
			m->colours [i].z = 0.0f;
			m->colours [i].w = 1.0f;
		}else if(i >= 6 && i < 12) {
			m->colours [i].x = 0.0f;
			m->colours [i].y = 0.0f;
			m->colours [i].z = 100.0f;
			m->colours [i].w = 1.0f;
		}else if(i >= 12 && i < 18) {
			m->colours [i].x = 100.0f;
			m->colours [i].y = 100.0f;
			m->colours [i].z = 0.0f;
			m->colours [i].w = 1.0f;
		}else if(i >= 18 && i < 24) {
			m->colours [i].x = 100.0f;
			m->colours [i].y = 0.0f;
			m->colours [i].z = 100.0f;
			m->colours [i].w = 0.0f;
		}else if(i >= 24 && i < 30) {
			m->colours [i].x = 0.0f;
			m->colours [i].y = 100.0f;
			m->colours [i].z = 100.0f;
			m->colours [i].w = 1.0f;
		}else if(i >= 30) {
			m->colours [i].x = 100.0f;
			m->colours [i].y = 100.0f;
			m->colours [i].z = 100.0f;
			m->colours [i].w = 1.0f;
		}
	}

	m->GenerateNormals();
	m->BufferData();	//Send our new data to the GPU
	return m;
}

void Mesh::GenerateNormals () {
	if (!normals) {
		normals = new Vector3[numVertices];
	}
	for ( GLuint i = 0; i < numVertices ; ++i){
		normals[i] = Vector3();
	}
	if( indices ) { // Generate per - vertex normals
		for ( GLuint i = 0; i < numIndices ; i +=3){
			unsigned int a = indices [i];
			unsigned int b = indices [i +1];
			unsigned int c = indices [i +2];

			Vector3 normal = Vector3 :: Cross (
				( vertices [b]- vertices [a]) ,( vertices [c]- vertices [a ]));

			normals [a] += normal ;
			normals [b] += normal ;
			normals [c] += normal ;
		}
	}
	else { // It 's just a list of triangles , so generate face normals
		for ( GLuint i = 0; i < numVertices ; i +=3){
			Vector3 &a = vertices [i];
			Vector3 &b = vertices [i +1];
			Vector3 &c = vertices [i +2];

			Vector3 normal = Vector3 :: Cross (b-a,c-a);

			normals [i] = normal;
			normals [i+1] = normal;
			normals [i+2] = normal;
		}
	}
	for ( GLuint i = 0; i < numVertices; ++i){
		normals [i]. Normalise ();
	}
}
