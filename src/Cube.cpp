#include "Cube.h"


Cube::Cube(void) 
	: RenderObject() {
}

Cube::Cube(Mesh*m, Shader*s, GLuint t) 
	: RenderObject(m, s, t) {
}


Cube::~Cube(void) {
}

void Cube::Update(float msec) {
	mesh->Draw();
}
