#version 140


out vec2 UV;

uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;

void main(){
	gl_Position = ProjectionMatrix * ModelViewMatrix * gl_Vertex;	
    UV = gl_TexCoord[0].xy;
}