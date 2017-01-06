#include "RenderObject.h"


RenderObject::RenderObject(void)	{
	mesh	= NULL;
	shader	= NULL;
	texture = NULL;
}

/*
Some later tutorials use this constructor as shorthand, so it should
probably be implemented...so here it is!
*/
RenderObject::RenderObject(Mesh*m, Shader*s, GLuint t) {
	mesh	= m;
	shader	= s;
	texture = t;
}

RenderObject::~RenderObject(void)
{
}

/*
Your Renderer class should probably call this update function for every
object you create (the Renderer::UpdateScene function is designed for this
purpose). The default RenderObject class probably won't do much with it,
but any subclasses that do more interesting things, should implement
whatever those interesting things are, here (perhaps an object modifies
its model matrix over time, scaling up and down according to a sine wave?)
*/
void RenderObject::Update(float msec) {
	mesh->Draw();
}