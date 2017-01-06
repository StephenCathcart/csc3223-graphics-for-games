#version 150 core

uniform float time;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;
uniform mat4 textureMatrix ;

in vec4 colour;
in vec2 texCoord;
in vec3 normal; 
in vec3 position;

out Vertex {
	vec4 colour;
	vec2 texCoord;
	vec3 normal; 
	vec3 worldPos ; 
} OUT;

void main(void) {
	float mod = sin(time);
	mat4 scale = mat4(0.4);
	scale[3][3] += (mod / 4);

	OUT.colour = colour ;
	OUT.texCoord = (textureMatrix * vec4(texCoord, 0.0 ,1.0)).xy;
	
	mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
	
	OUT.normal = normalize(normalMatrix * normalize(normal));
	OUT.worldPos = (modelMatrix * vec4(position ,1)).xyz;

	gl_Position = (projMatrix * viewMatrix) * scale * vec4(OUT.worldPos, 1.0);
}

