#version 150 core

/*
Another interface block - this should match the output interface block
defined by the vertex shader. Note however, that this block will receive
INTERPOLATED attribute data, so we can automatically create our 'rainbow' 
triangle without having to manually calculate any interpolations.
*/
in Vertex	{
	vec2 texCoord;
	vec4 colour;
} IN;

//Value written to the back buffer
out vec4 gl_FragColor;

void main(void)	{	
	gl_FragColor= IN.colour;
//When shaders don't appear to be working, the first thing I usually
//do is to make them just output white, so that weird issues with alpha,
//or empty registers can be discounted quickly
//gl_FragColor = vec4(1,1,1,1);
}