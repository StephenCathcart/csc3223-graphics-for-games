/*
Here's your first vertex shader! It is described in the OpenGL tutorial series,
but I'll comment what it's doing here, too.
*/

//This tells the compiler what functionality should be allowed in the shader
#version 150 core


/*
Uniforms are special variables that are sent to the shader via your C++
program, using special OpenGL function calls. Shaders can't write to them,
but can read from them. These define mat4s, which is GLSL-speak for a 4*4
matrix.

*/
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

/*
'in' variables are attached to OpenGL generic attributes, either
in your C++ program (I do it like this), or by setting 'layout qualifiers'
in your vertex shader (google it!)
*/
in  vec3 position; //vertex positions always have a w of 1, so why send it?
in  vec2 texCoord;
in  vec4 colour;

/*
outs are sent to the rasteriser, which determines which fragments the shape 
covers, and which interpolates our variables for us. This looks like a struct,
but is really an 'interface block', of which there is only 1, with the variable
name 'OUT' (or whatever you want to call this - I should have picked a better
name for this, it is a bit confusing...)
*/
out Vertex	{
	vec2 texCoord;
	vec4 colour;
} OUT;

/*
All shaders must have a main function, with this signature.
*/
void main(void)	{
//gl_Position is a special inbuilt variable, which should have the clip-space
//position of the vertex written to it. Note we automatically create a w of 1,
//by simply casting our position to a vec4.
	gl_Position		= (projMatrix * viewMatrix * modelMatrix) * vec4(position, 1.0);
	
//These must be manually set - as shaders are programmable,
//the value you take in does not necessarily have to be the
//value you write!
	OUT.texCoord	= texCoord;
	OUT.colour		= colour;
}