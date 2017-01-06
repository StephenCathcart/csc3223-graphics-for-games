#include "Renderer.h"
#include "RenderObject.h"

/*
This tells the C++ compiler to pull in some function definitions from elsewhere.
In this case, all of the math / input / window functions are kept in a separate library,
derived from the one I use to teach OpenGL on the Games Engineering MSc
*/
#pragma comment(lib, "nclgl.lib")

/*
This time around, it'll mostly be the custom Renderer class, rather than main, which contains
all of the creation of objects etc.

This allows you to have multiple classes derived from OGLRenderer with different functionality,
with the only changes in main being which one to initialise and attach to the window.

So you could have a TriRenderer class which simply renders a coloured triangle on screen,
or a CubeRenderer class to render a cube on screen in a perspective view, and so on

*/

bool isWireframe = false;
const float ALPHA_STRENGTH = 0.01f;
const float LIGHT_STRENGTH = 0.05f;

void main(void) {
	Window w("133t Spinning Cube", 1280, 720, false);
	Renderer r(w);
	w.LockMouseToWindow(true);
	w.ShowOSPointer(false);
	

	while(w.UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE )) {
		if(Window::GetKeyboard()->KeyTriggered(KEYBOARD_L)) {
			if(isWireframe){
				glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ); 
				isWireframe = false;
			}else{
				glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
				isWireframe = true;
			}
		}
		if(Window::GetKeyboard()->KeyTriggered(KEYBOARD_N)) {
			if(r.getShowNormals()){
				r.setShowNormals(false);
			}else{
				r.setShowNormals(true);
			}
		}
		if(Window::GetKeyboard()->KeyTriggered(KEYBOARD_T)) {
			if(r.getIsAdvancedTexture()){
				r.setIsAdvancedTexture(false);
			}else{
				r.setIsAdvancedTexture(true);
			}
		}
		if(Window::GetKeyboard()->KeyTriggered(KEYBOARD_1)) {
			if(r.getHasShaderSwapped()){
				r.setHasShaderSwapped(false);
				r.setCubeShader(new Shader("Tut1Shaders/basicVertex.glsl",
					"Tut1Shaders/basicFragment.glsl",
					"Tut1Shaders/basicGeom.glsl"));
			}else{
				r.setHasShaderSwapped(true);
				r.setCubeShader(new Shader("Tut1Shaders/rotVertex.glsl",
					"Tut1Shaders/colourFragment.glsl",
					"Tut1Shaders/basicGeom.glsl"));
			}
		}
		if(Window::GetKeyboard()->KeyHeld(KEYBOARD_HOME)){
			float red = r.getLight()->GetColour().x + LIGHT_STRENGTH;
			float green = r.getLight()->GetColour().y + LIGHT_STRENGTH;
			float blue = r.getLight()->GetColour().z + LIGHT_STRENGTH;

			red = min(red, 255);
			green = min(red, 255);
			blue = min(red, 255);

			Vector4 newColour(red, green, blue, 1);
			r.getLight()->SetColour(newColour);
		}else if(Window::GetKeyboard()->KeyHeld(KEYBOARD_END)) {
			float red = r.getLight()->GetColour().x - LIGHT_STRENGTH;
			float green = r.getLight()->GetColour().y - LIGHT_STRENGTH;
			float blue = r.getLight()->GetColour().z - LIGHT_STRENGTH;

			red = max(red, 0);
			green = max(red, 0);
			blue = max(red, 0);

			Vector4 newColour(red, green, blue, 1);
			r.getLight()->SetColour(newColour);
		}
		if(Window::GetKeyboard()->KeyHeld(KEYBOARD_INSERT)){
			float a = r.getAlpha() + ALPHA_STRENGTH;
			a = min(a, 1.0f);
			r.setAlpha( a );
		}else if(Window::GetKeyboard()->KeyHeld(KEYBOARD_DELETE)) {
			float a = r.getAlpha() - ALPHA_STRENGTH;
			a = max(a, 0.0f);
			r.setAlpha( a );
		}

		float msec = w.GetTimer()->GetTimedMS();
		r.UpdateScene(msec);
		r.RenderScene();
	}
}