#pragma once
#include "RenderObject.h"

class Cube : public RenderObject {
public:
	Cube(void);
	Cube(Mesh*m, Shader*s, GLuint t = 0);
	~Cube(void);

	void Update(float msec);
};

