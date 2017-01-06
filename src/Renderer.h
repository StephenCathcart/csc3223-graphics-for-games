/******************************************************************************
Class:Renderer
Implements:OGLRenderer
Author:Rich Davison	<richard.davison4@newcastle.ac.uk>
Description: Subclass containing the actual objects, meshes, and shaders 
required to draw a scene using OpenGL.

While only one can be active per program execution, there's no reason not to
have multiple subclasses of OGLRenderer defined, each describing a different
scene.


-_-_-_-_-_-_-_,------,   
_-_-_-_-_-_-_-|   /\_/\   NYANYANYAN
-_-_-_-_-_-_-~|__( ^ .^) /
_-_-_-_-_-_-_-""  ""   

*//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "../nclgl/OGLRenderer.h"
#include "Camera.h"
#include "Light.h"
#include "RenderObject.h"
#include "Cube.h"
#include <vector>

using std::vector;

class Renderer : public OGLRenderer	{

public:

	Renderer(Window &parent);
	~Renderer(void);

	virtual void	RenderScene();
	virtual void	UpdateScene(float msec);

	void UpdateTextureMatrix (float rotation);
	void ToggleRepeating ();
	void ToggleFiltering ();

	Light* getLight(){ return light; };
	float getTime(){ return time / 1000.0f; };

	float getAlpha(){ return alpha; };
	void setAlpha(float a){ alpha = a; };

	bool getIsMeshTransparent(){ return isMeshTransparent; };
	void setIsMeshTransparent(bool t){ isMeshTransparent = t; };

	bool getShowNormals(){ return showNormals; };
	void setShowNormals(bool s){ showNormals = s; };

	bool getIsAdvancedTexture(){ return isAdvancedTexture; };
	void setIsAdvancedTexture(bool t){ isAdvancedTexture = t; };

	bool getHasShaderSwapped(){ return hasShaderSwapped; };
	void setHasShaderSwapped(bool s){ hasShaderSwapped = s; };

	void setCubeShader(Shader* s);
protected:
	/*
	In the tutorial text, I had a 'LoadTexture' function here...it's never
	referred to again! It's function definition was incorrect anyway - the
	idea was to have a function that took in a filename as a string, and 
	returned an OpenGL name for it - having probably been read in using
	an image loader library like SOIL. You might want to create some sort
	of function that does this, but it doesn't have to be in here - it might
	be better off as a static function of the RenderObject class, maybe, or
	a 'Texture' class, if you want to be very OO.
	*/
	void SetShaderLight(const Light &l);

	Cube* cube;
	Mesh* cubeMesh;
	Light* light;
	Camera* camera;
	Shader* currentShader;
	float time;
	float alpha;
	bool isMeshTransparent;
	bool showNormals;
	bool isAdvancedTexture;
	bool hasShaderSwapped;

	bool filtering ;
	bool repeating ;
};

