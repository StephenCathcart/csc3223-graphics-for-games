# version 150 core

 layout(triangles )in;
 layout(triangle_strip , max_vertices = 81) out;
 
uniform float time;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;

 in Vertex {
	vec4 colour;
	vec2 texCoord;
	vec3 normal;
	vec3 worldPos ;
 } IN[];

 out Vertex {
	vec4 colour;
	vec2 texCoord;
	vec3 normal;
	vec3 worldPos ;
 } OUT;

 void main() {
	float mod = sin(time);
	float distance = 300;
	distance += mod * 100;
	
	for (int c = 0; c < 3; ++c) {
		for (int a = 0; a < 3; ++a) {
			for (int b = 0; b < 3; ++b) {
				for (int i = 0; i < gl_in.length(); ++i) {
				
					vec3 pos = vec3((distance * a), (distance * b), (distance * c));
					gl_Position = gl_in[i].gl_Position + vec4(pos, pos.z);
					
					OUT.colour = IN[i].colour;
					OUT.texCoord = IN[i].texCoord;
					OUT.normal = IN[i].normal;
					OUT.worldPos = IN[i].worldPos;
					EmitVertex();
				}
				EndPrimitive();
			}
		}
	}
 }