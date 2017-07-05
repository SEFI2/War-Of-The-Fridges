#version 140
#define GL_compatibility_profile 1
#extension GL_ARB_compatibility: enable



uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;

out vec3 normal;
out vec4 p;
out vec4 color;

void main()
{	
	mat4 normalMatrix = transpose(inverse(ModelViewMatrix));
	normal = normalize (vec3(normalMatrix * vec4(gl_Normal , 0.0)));	
	p = ModelViewMatrix * gl_Vertex;
	gl_Position = ProjectionMatrix * ModelViewMatrix * gl_Vertex;	
	color = gl_Color;
}












