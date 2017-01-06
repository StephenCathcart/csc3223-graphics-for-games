#version 400 core

layout ( vertices =3) out ; // num vertices in patch output

uniform float tessLevelInner ;
uniform float tessLevelOuter ;

in Vertex {
	vec4 colour ;
} IN [];

out Vertex {
	vec4 colour ;
} OUT [];

patch out Vector4 subColour ;

void main () {
	gl_TessLevelInner [0] = tessLevelInner ;
	// gl_TessLevelInner [1] = tessLevelInner ; // quads only !

	gl_TessLevelOuter [0] = tessLevelOuter ;
	gl_TessLevelOuter [1] = tessLevelOuter ;
	gl_TessLevelOuter [2] = tessLevelOuter ;
	// gl_TessLevelOuter [3] = tessLevelOuter ; // Quads only !

	barrier (); // Not actually necessary in this particular shader !
	gl_out [ gl_InvocationID ]. gl_Position =
	gl_in [ gl_InvocationID ]. gl_Position ;
}