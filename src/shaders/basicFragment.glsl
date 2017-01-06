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
	float mod = sin(time);
	
	vec3 incident = normalize ( lightPos - IN.worldPos );
	vec3 viewDir = normalize ( cameraPos - IN.worldPos );
	vec3 halfDir = normalize ( incident + viewDir );

	float dist = length ( lightPos - IN.worldPos );
	float atten = 1.0 - clamp ( dist / lightRadius , 0.0 , 1.0);

	float lambert = max (0.0 , dot ( incident , IN.normal ));

	float rFactor = max (0.0 , dot ( halfDir , IN.normal ));
	float sFactor = pow ( rFactor , 50.0 );

	vec4 texCol;
	if(advancedtexture){
		texCol = mix(texture(diffuseTex, IN.texCoord), texture(diffuseTex2, IN.texCoord), (texture(diffuseTex3, IN.texCoord)) );
	}else{
		texCol = mix(texture(diffuseTex, IN.texCoord), texture(diffuseTex2, IN.texCoord), mod);
	}
	//vec4 texCol = mix(texture(diffuseTex, IN.texCoord), texture(diffuseTex3, IN.texCoord), mod);
	//vec4 texCol = mix(texture(diffuseTex, IN.texCoord), texture(diffuseTex2, IN.texCoord), (texture(diffuseTex3, IN.texCoord)) );
	 
	vec3 ambient = texCol.rgb * lightColour.xyz * 0.1;
	vec3 diffuse = texCol.rgb * lightColour.xyz * lambert * atten ;
	vec3 specular = lightColour.xyz * sFactor * atten ;
	
	
	if(!shownormal){
		gl_FragColor = vec4 ( ambient + diffuse + specular , texCol.a * alpha);
	}else
	{
		gl_FragColor = vec4 ( IN.normal, 1.0f);
	}
}