#version 150 core

uniform float time;
uniform float alpha;
uniform bool shownormal;
uniform bool advancedtexture;
uniform sampler2D diffuseTex;
uniform sampler2D diffuseTex2;
uniform sampler2D diffuseTex3;

uniform vec3 cameraPos;
uniform vec4 lightColour;
uniform vec3 lightPos;
uniform float lightRadius;

in Vertex {
	vec4 colour;
	vec2 texCoord;
	vec3 normal;
	vec3 worldPos;
} IN;

out vec4 gl_FragColor;

void main(void) {	
	if( IN.colour.a < 0.1) {
		discard ;
	}
	
	vec4 c = vec4(IN.colour.x, IN.colour.y, IN.colour.z, IN.colour.w);
	gl_FragColor = c;
	
}