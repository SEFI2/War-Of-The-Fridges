#include "GestureHandler.h"
#include <iostream>
#include "glm\glm\gtx\transform.hpp"
#include "Object.h"

Object arrow;

GestureHandler::GestureHandler()
{
	Listener::Listener();
	shoot = false;
	lastX = -0.2;
	lastY = 0;
	lastZ = -0.2;
}


GestureHandler::~GestureHandler()
{
}


glm::mat4 GestureHandler::fromLeapToGLM(Matrix matrix) {
	double arr[16];
	matrix.toArray4x4(arr);
	glm::mat4 ret = glm::mat4(1.0f);
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			ret[i][j] = arr[i * 4 + j];
		}
	}
	return ret;
}

void GestureHandler::onConnect(const Controller& controller) {
	std::cout << "Leap motion is connected" << "\n";
	//arrow.InitCube();

}
int counter = 0;
int changer = 0;
int shooter = 0;



void GestureHandler::onFrame(const Controller& controller) {
	const Frame frame = controller.frame();
	if (frame.hands().count() <= 0)return;
	Hand hand = frame.hands().rightmost();
	Hand leftHand = frame.hands().leftmost();
	changer++;

	if (hand.isRight())
	{
		fingerX = hand.palmPosition().x - 130.0f;
		fingerY = 0.0f;
		fingerZ = hand.palmPosition().z / 200.0f;

		Leap::FingerList fingers = hand.fingers();
		   
		bool fingersAllExtended = true;

		for (Leap::FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); fl++)
		{
			//if ((*fl).type() == Leap::Finger::Type::TYPE_THUMB) 
			//	fingersAllExtended &= (*fl).isExtended();
			//else
				fingersAllExtended &= (!(*fl).isExtended());
		}


		if (fingersAllExtended && changer > 30)
		{
			if (changeWeapon)
				changeWeapon = false;
			else
				changeWeapon = true;
			changer = 0;
		}
		

	}
	else {
		leftHand = hand;
	}

	if (leftHand.isLeft()) {
		lastX = leftHand.palmPosition().x / 200.0f;
		lastY = leftHand.palmPosition().y / 200.0f;
		lastZ = leftHand.palmPosition().z / 200.0f;
	}
	else {
		lastX = -0.3;
		lastY = 0;
		lastZ = -0.3;
	}
	
	{
		Leap::FingerList fingers = hand.fingers();

		bool fingersAllExtended = true;

		for (Leap::FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); fl++)
		{
			if ((*fl).type() == Leap::Finger::Type::TYPE_INDEX || (*fl).type() == Leap::Finger::Type::TYPE_THUMB || (*fl).type() == Leap::Finger::Type::TYPE_MIDDLE)
				fingersAllExtended &= (*fl).isExtended();
			else
				fingersAllExtended &= (!(*fl).isExtended());
		}


		if (fingersAllExtended && shooter > 25)
		{
			shoot = true;
			shooter = 0;
		}
		shooter++;
	}
	return;
	for (int i = 0; i < frame.gestures().count(); i++) {
		Gesture g = frame.gestures()[i];
		if (g.type() == Gesture::TYPE_KEY_TAP) {
			shoot = true;
			break;
		}
	}

}
