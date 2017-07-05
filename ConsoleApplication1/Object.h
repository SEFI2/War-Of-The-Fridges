#pragma once
#include <string>
#include "GL/glew.h"
#include "glm\glm\glm.hpp"

class Object
{
public:
	Object();
	~Object();
	void Init(std::string file_name);
	void InitObj(std::string file_name);

	void draw();
	
	void InitCube();
	void InitTriangle();
	void InitSphere();
	void drawCircle();
	glm::vec3 position;
	float currentAngle;
	glm::mat4 objectMatrix;


private:
	float *vertex;
	int *indices;
	void normalize(int a);
	void calcNormals(int a, int b, int c);
	int  numVertex, numIndicies;
	void Mesh_Init();
	GLuint vertexVBO, indexVBO;
};

