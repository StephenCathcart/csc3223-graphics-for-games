#include "Shader.h"
#include "Mesh.h"

Shader::Shader(const string &vertex,const string &fragment ,const string &geometry,const string &tcs,const string &tes)	{
	//here's an example of how OpenGL works - object creation functions will either
	//return a uint, or take in a reference to a uint, that it will then modify
	program	= glCreateProgram();

	objects [ SHADER_VERTEX ] = GenerateShader(vertex , GL_VERTEX_SHADER );
	objects [ SHADER_FRAGMENT ]= GenerateShader(fragment , GL_FRAGMENT_SHADER );
	objects [ SHADER_GEOMETRY ]= 0;

	if (!geometry.empty()) {
		objects[SHADER_GEOMETRY] = GenerateShader(geometry,
			GL_GEOMETRY_SHADER);
		glAttachShader(program ,objects[SHADER_GEOMETRY]);
	}

	glAttachShader(program ,objects[SHADER_VERTEX]);
	glAttachShader(program ,objects[SHADER_FRAGMENT]);

	SetDefaultAttributes ();

	/*
	Here we should have a block of code to read in the text from each of the files 
	passed in to the constructor, and generate the shader objects necessary to link
	to the program. There's plenty of ways of doing this, but I usually have a function
	to read the actual text in, and then a function to compile and attach - it should
	all be highly reusable, as only a single uint changes to compile each different
	shader stage.

	*/

	SetDefaultAttributes();
}

Shader::~Shader(void)	{
	/*
	While probably not strictly necessary for the programs you will be making,
	it's nevertheless a good idea to delete any OpenGL objects we create.
	*/
	for (int i = 0; i < 3; ++i) {
		glDetachShader ( program , objects [i]);
		glDeleteShader ( objects [i]);
	}
	glDeleteProgram ( program );
}

/*
This function should set up which generic attribute attaches to which
input variable of the vertex shader. I always make my vertex shaders
use the same basic names (i.e "position" for positions...) so that it
becomes trivial to attach vertex data to shaders, without having to
mess around with layout qualifiers in the shaders themselves etc.

This is up to you, though, you wouldn't be docked any marks for doing
the vertex shader / VBO connection a different way!
*/
void Shader::SetDefaultAttributes () {
	glBindAttribLocation(program , VERTEX_BUFFER , "position");
	glBindAttribLocation(program , COLOUR_BUFFER , "colour");
	glBindAttribLocation(program , NORMAL_BUFFER , "normal"); 
	glBindAttribLocation(program , TEXTURE_BUFFER , "texCoord");
}

GLuint Shader :: GenerateShader ( string from , GLenum type ) {
	cout << " Compiling Shader ... " << endl ;

	string load ;
	if (! LoadShaderFile (from , load )) {
		cout << " Compiling failed !" << endl ;
		loadFailed = true ;
		return 0;
	}
	GLuint shader = glCreateShader ( type );

	const char * chars = load . c_str ();
	glShaderSource (shader , 1, &chars , NULL );
	glCompileShader ( shader );

	GLint status ;
	glGetShaderiv (shader , GL_COMPILE_STATUS , & status );

	if ( status == GL_FALSE ) {
		cout << " Compiling failed !" << endl ;
		char error [512];
		glGetInfoLogARB (shader , sizeof ( error ), NULL , error );
		cout << error ;
		loadFailed = true ;
		return 0;
	}
	cout << " Compiling success !" << endl << endl ;
	loadFailed = false ;
	return shader ;
}

bool Shader :: LoadShaderFile ( string from , string & into ) {
	ifstream file ;
	string temp ;

	cout << " Loading shader text from " << from << endl << endl ;

	file . open ( from . c_str ());
	if (! file . is_open ()){
		cout << " File does not exist !" << endl ;
		return false ;
	}
	while (! file .eof ()){
		getline (file , temp );
		into += temp + "\n";
	}

	file . close ();
	cout << into << endl << endl ;
	cout << " Loaded shader text !" << endl << endl ;
	return true ;
}

bool Shader::LinkProgram() {
	if(loadFailed) {
		return false;
	}
	glLinkProgram(program);

	GLint code;
	glGetProgramiv(program ,GL_LINK_STATUS ,&code );
	return code == GL_TRUE ? true : false;
}