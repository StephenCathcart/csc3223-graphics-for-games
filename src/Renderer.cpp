#include "Renderer.h"

Renderer::Renderer(Window &parent) : OGLRenderer(parent)	{
	//Create some Shaders, Meshes, and RenderObjects here!
	camera = new Camera();
	camera->SetPosition(Vector3(2000, 400, 2000.0f));

	//triangle = Mesh::GenerateTriangle ();
	cubeMesh = Mesh::LoadMeshFile("cube.asciimesh");

	cubeMesh->SetTextureA(SOIL_load_OGL_texture("wood.jpg",
		SOIL_LOAD_AUTO , SOIL_CREATE_NEW_ID , 0));

	if (!cubeMesh->GetTextureA()) {
		return;
	}

	cubeMesh->SetTextureB(SOIL_load_OGL_texture("wall.jpg",
		SOIL_LOAD_AUTO , SOIL_CREATE_NEW_ID , 0));

	if (!cubeMesh->GetTextureB()) {
		return;
	}

	cubeMesh->SetTextureC(SOIL_load_OGL_texture("board.jpg",
		SOIL_LOAD_AUTO , SOIL_CREATE_NEW_ID , 0));

	if (!cubeMesh->GetTextureC()) {
		return;
	}

	currentShader = new Shader("Tut1Shaders/basicVertex.glsl",
							   "Tut1Shaders/basicFragment.glsl",
							   "Tut1Shaders/basicGeom.glsl");

	light = new Light(Vector3(1000.0f, 1000.0f, -2000.0f),
					  Vector4(1 ,1 ,1 ,0), 
					  4000.0f);

	SetProjectionMatrix(Matrix4::Perspective(1.0f ,15000.0f,(float)width / (float)height ,45.0f));

	cube = new Cube(cubeMesh, currentShader, 0);
	cube-> SetModelMatrix ( Matrix4 :: Scale ( Vector3 (100 ,100 ,-100)));

	if (!currentShader->LinkProgram()) {
		return;
	}

	init = true;
	time = 0.0f;
	alpha = 1.0f;
	isMeshTransparent = false;
	isAdvancedTexture = false;
	showNormals = false;
	hasShaderSwapped = false;
	filtering = true ;
	repeating = false ;
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Renderer::~Renderer(void)	{
	//We should probably delete anythin g we create, here...
	delete cubeMesh;
	delete currentShader;
	delete cube;
	delete camera;
	delete light;
}

void Renderer::setCubeShader(Shader* s) {
	currentShader = s;

	if (!currentShader->LinkProgram()) {
		return;
	}
}

/*
The purpose of this function is to render everything in the scene.

How you do so is up to you, but iterating over an array of RenderObjects,
and calling some sort of generic Draw function on them seems like a good
idea.
*/
void Renderer::RenderScene() {
	glClearColor(0.2f ,0.2f ,0.2f ,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Rotate cube
	Matrix4 m = cube->GetModelMatrix();
	m = m * Matrix4::Rotation(time / 20, Vector3(0 ,1 ,0)); // Comment out to edit vertex shader
	modelMatrix = m;
	
	GLuint program = currentShader->GetShaderProgram();
	glUseProgram (program);

	UpdateShaderMatrices(program);
	SetShaderLight(*light);

	glUniform1i(glGetUniformLocation(program, "diffuseTex"), cube->GetMesh()->GetTextureA()-1);
	glUniform1i(glGetUniformLocation(program, "diffuseTex2"), cube->GetMesh()->GetTextureB()-1); 
	glUniform1i(glGetUniformLocation(program, "diffuseTex3"), cube->GetMesh()->GetTextureC()-1); 
	glUniform1f(glGetUniformLocation(program, "time"), getTime());
	glUniform1f(glGetUniformLocation(program, "alpha"), getAlpha());

	glUniform3fv(glGetUniformLocation(program,"cameraPos"), 1, (float*)&camera->GetPosition());
	glUniform1i(glGetUniformLocation(program, "shownormal"), getShowNormals());
	glUniform1i(glGetUniformLocation(program, "advancedtexture"), getIsAdvancedTexture());

	cube->Update(time);

	glUseProgram(0);
	SwapBuffers();
}

/*
This function takes in a time delta from the main file - that is, how
much time has passed since the last time the scene was rendered. This
value could be used to modify variables over time, or keep movements
consistent by integrating any movement changes with the time delta.

*/
void Renderer::UpdateScene(float msec) {
	camera->UpdateCamera(msec);
	viewMatrix = camera->BuildViewMatrix(); 
	time += msec;
}

void Renderer::UpdateTextureMatrix(float value) {
	Matrix4 pushPos = Matrix4::Translation(Vector3(0.5f ,0.5f ,0));
	Matrix4 popPos = Matrix4::Translation(Vector3(-0.5f , -0.5f ,0));
	Matrix4 rotation = Matrix4::Rotation(value ,Vector3(0 ,0 ,1));
	textureMatrix = pushPos * rotation * popPos;
}

void Renderer::SetShaderLight(const Light &l) {
	glUniform3fv(glGetUniformLocation(currentShader->GetShaderProgram(),
		"lightPos") ,1,(float*)&l.GetPosition());

	glUniform4fv(glGetUniformLocation(currentShader->GetShaderProgram(),
		"lightColour"),1,(float*)&l.GetColour());

	glUniform1f(glGetUniformLocation(currentShader->GetShaderProgram(),
		"lightRadius"),l.GetRadius());
}