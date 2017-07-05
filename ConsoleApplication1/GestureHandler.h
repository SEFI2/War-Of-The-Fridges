#pragma once
#include "Leap.h"
#include "glm\glm\glm.hpp"

using namespace Leap;


class GestureHandler : public Listener
{
	
public:
	GestureHandler();
	~GestureHandler();
	virtual void onConnect(const Controller& controller);
	virtual void onFrame(const Controller& controller);
	glm::mat4 fromLeapToGLM(Matrix matrix);
	float fingerX;
	float fingerY;
	float fingerZ;
	float lastX;
	float lastY;
	float lastZ;
	bool shoot;
	bool changeWeapon;




};

