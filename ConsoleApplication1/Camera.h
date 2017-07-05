#pragma once
#include "glm\glm\glm.hpp"
#include "glm\glm\gtx\transform.hpp"

class Camera
{
public:
	glm::vec3 position;
	glm::vec3 rot;
	float angle;
	public:
		Camera();
		~Camera();
		void rotation(float deltaAgnle);
		void translation(float deltaMove);
		glm::mat4 getView();



};

