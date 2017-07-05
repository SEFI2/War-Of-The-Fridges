#pragma once

class ShaderLoader
{
public:
	char *textFileRead(char *fn);
	int textFileWrite(char *fn, char *s);
	GLuint loadShader(GLenum shadertype, char *c);
	GLuint createGLSLProgram(char *vs, char *gs, char *fs);


	ShaderLoader()
	{
	}

	~ShaderLoader()
	{
	}
};

