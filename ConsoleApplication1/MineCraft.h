#pragma once
#include "BodyPart.h"
#include "GL\freeglut.h"
#include "GL\glew.h"

#include "glm\glm\glm.hpp"
#include "glm\glm\gtx\transform.hpp"
using namespace glm;

int vert[] = {
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,

	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f
};


class Minecraft
{
public:

	 
	Minecraft() {
		buildCharacter();
	}
	BodyPart hand[2];
	BodyPart head;
	BodyPart body;
	BodyPart foot[2];
	const int LEFT_HAND = 0;
	const int RIGHT_HAND = 1;
	const int LEFT_FOOT = 0;
	const int RIGHT_FOOT = 1;


	void initHand(float a[]) {
		for (int i = 0; i < 48; ++i) hand[LEFT_HAND].vertices[i] = a[i];
		for (int i = 0; i < 48; ++i) hand[RIGHT_HAND].vertices[i] = a[i];
	}
	void initFoot(float a[]) {
		for (int i = 0; i < 48; ++i) foot[LEFT_HAND].vertices[i] = a[i];
		for (int i = 0; i < 48; ++i) foot[RIGHT_HAND].vertices[i] = a[i];
	}
	void initHead(float a[]) { for (int i = 0; i < 48; ++i) { head.vertices[i] = a[i]; } }
	void initBody(float a[]) { for (int i = 0; i < 48; ++i) { body.vertices[i] = a[i]; } }

	float matrix[16];


	void showCharacter() {

		glMatrixMode(GL_MODELVIEW);
		glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
		glPushMatrix();

		//head
		glLoadIdentity();	head.bodyMatrix = glm::translate(glm::vec3(0.0f, 0.0f, 0.0f)) * glm::scale(mat4(1.0f), vec3(0.5, 0.5, 0.5));
		glMultMatrixf(&head.bodyMatrix[0][0]);
		glMultMatrixf(matrix);
		glBegin(GL_QUADS); for (int i = 0; i < 24; i++) {
			glTexCoord2f(head.vertices[i * 2], head.vertices[i * 2 + 1]); glVertex3f(vert[i * 3 + 0], vert[i * 3 + 1], vert[i * 3 + 2]);
		}
		glEnd();

		//body
		glLoadIdentity(); body.bodyMatrix = glm::translate(glm::vec3(0.0f, -1.0f, 0.0f)) * glm::scale(mat4(1.0f), vec3(0.5, 0.5, 0.5));
		glMultMatrixf(&body.bodyMatrix[0][0]); glMultMatrixf(matrix);
		glBegin(GL_QUADS); for (int i = 0; i < 24; i++) {
			glTexCoord2f(body.vertices[i * 2], body.vertices[i * 2 + 1]); glVertex3f(vert[i * 3 + 0], vert[i * 3 + 1], vert[i * 3 + 2]);
		}
		glEnd();

		glPopMatrix();
		return;




		//left foot
		glLoadIdentity(); foot[LEFT_FOOT].bodyMatrix = 
			glm::translate(glm::vec3(-0.5f, -3.5f, 0.0f))* glm::scale(mat4(1.0f), vec3(0.2, 1, 0.2)) * glm::rotate(glm::radians(90.0f), vec3(1, 0, 0));
		glMultMatrixf(&foot[LEFT_FOOT].bodyMatrix[0][0]); glMultMatrixf(matrix);
		glBegin(GL_QUADS); for (int i = 0; i < 24; i++) {
			glTexCoord2f(foot[LEFT_FOOT].vertices[i * 2], foot[LEFT_FOOT].vertices[i * 2 + 1]); glVertex3f(vert[i * 3 + 0], vert[i * 3 + 1], vert[i * 3 + 2]);
		}
		glEnd();

		//right foot
		glLoadIdentity(); foot[RIGHT_FOOT].bodyMatrix = glm::translate(glm::vec3(+0.5f, -3.5f, 0.0f))* glm::scale(mat4(1.0f), vec3(0.2, 1, 0.2)) * glm::rotate(glm::radians(90.0f), vec3(1, 0, 0));
		glMultMatrixf(&foot[RIGHT_FOOT].bodyMatrix[0][0]); glMultMatrixf(matrix);
		glBegin(GL_QUADS); for (int i = 0; i < 24; i++) {
			glTexCoord2f(foot[RIGHT_FOOT].vertices[i * 2], foot[RIGHT_FOOT].vertices[i * 2 + 1]); glVertex3f(vert[i * 3 + 0], vert[i * 3 + 1], vert[i * 3 + 2]);
		}
		glEnd();

		//left hand
		glLoadIdentity(); hand[LEFT_HAND].bodyMatrix = glm::translate(glm::vec3(-1.2f, -2.0f, 0.0f))* glm::scale(mat4(1.0f), vec3(0.2, 1.0, 0.2))  * glm::rotate(glm::radians(90.0f), vec3(1, 0, 0));
		glMultMatrixf(&hand[LEFT_HAND].bodyMatrix[0][0]); glMultMatrixf(matrix);
		glBegin(GL_QUADS); for (int i = 0; i < 24; i++) {
			glTexCoord2f(hand[LEFT_HAND].vertices[i * 2], hand[LEFT_HAND].vertices[i * 2 + 1]); glVertex3f(vert[i * 3 + 0], vert[i * 3 + 1], vert[i * 3 + 2]);
		}
		glEnd();

		//right hand
		glLoadIdentity();
		hand[RIGHT_HAND].bodyMatrix = glm::translate(glm::vec3(+1.2f, -2.0f, 0.0f))* glm::scale(mat4(1.0f), vec3(0.2, 1.0, 0.2)) * glm::rotate(glm::radians(90.0f), vec3(1, 0, 0));
		glMultMatrixf(&hand[RIGHT_HAND].bodyMatrix[0][0]); glMultMatrixf(matrix);
		glBegin(GL_QUADS); for (int i = 0; i < 24; i++) {
			glTexCoord2f(hand[RIGHT_HAND].vertices[i * 2], hand[RIGHT_HAND].vertices[i * 2 + 1]); glVertex3f(vert[i * 3 + 0], vert[i * 3 + 1], vert[i * 3 + 2]);
		}
		glEnd();

		glPopMatrix();
	}



	void buildCharacter() {
		float head[] = {
			(float)816 / 1480, (float)588 / 1169,
			(float)1118 / 1480, (float)588 / 1169,
			(float)1118 / 1480, (float)794 / 1169,
			(float)816 / 1480, (float)794 / 1169,
			(float)512 / 1480, (float)588 / 1169,
			(float)512 / 1480, (float)794 / 1169,
			(float)214 / 1480, (float)794 / 1169,
			(float)214 / 1480, (float)588 / 1169,
			(float)816 / 1480, (float)1098 / 1169,
			(float)816 / 1480, (float)794 / 1169,
			(float)1118 / 1480, (float)794 / 1169,
			(float)1118 / 1480, (float)1098 / 1169,
			(float)1118 / 1480, (float)588 / 1169,
			(float)816 / 1480, (float)588 / 1169,
			(float)816 / 1480, (float)286 / 1169,
			(float)1118 / 1480, (float)286 / 1169,
			(float)1424 / 1480, (float)588 / 1169,
			(float)1424 / 1480, (float)794 / 1169,
			(float)1118 / 1480, (float)794 / 1169,
			(float)1118 / 1480, (float)588 / 1169,
			(float)512 / 1480, (float)588 / 1169,
			(float)816 / 1480, (float)588 / 1169,
			(float)816 / 1480, (float)794 / 1169,
			(float)512 / 1480, (float)794 / 1169
		};
		initHead(head);
		float body[] = {
			(float)450 / 1480, (float)246 / 1169,
			(float)258 / 1480, (float)246 / 1169,
			(float)258 / 1480, (float)60 / 1169,
			(float)450 / 1480, (float)60 / 1169,
			(float)640 / 1480, (float)246 / 1169,
			(float)640 / 1480, (float)60 / 1169,
			(float)838 / 1480, (float)60 / 1169,
			(float)838 / 1480, (float)246 / 1169,
			(float)816 / 1480, (float)1098 / 1169,
			(float)816 / 1480, (float)794 / 1169,
			(float)1118 / 1480, (float)794 / 1169,
			(float)1118 / 1480, (float)1098 / 1169,
			(float)258 / 1480, (float)246 / 1169,
			(float)450 / 1480, (float)246 / 1169,
			(float)450 / 1480, (float)442 / 1169,
			(float)258 / 1480, (float)442 / 1169,
			(float)66 / 1480, (float)246 / 1169,
			(float)66 / 1480, (float)60 / 1169,
			(float)258 / 1480, (float)60 / 1169,
			(float)258 / 1480, (float)246 / 1169,
			(float)640 / 1480, (float)246 / 1169,
			(float)450 / 1480, (float)246 / 1169,
			(float)450 / 1480, (float)60 / 1169,
			(float)640 / 1480, (float)60 / 1169,
		};
		initBody(body);
		float hand[] = {
			(float)240 / 1480, (float)918 / 1169,
			(float)170 / 1480, (float)918 / 1169,
			(float)170 / 1480, (float)850 / 1169,
			(float)240 / 1480, (float)850 / 1169,
			(float)312 / 1480, (float)1060 / 1169,
			(float)312 / 1480, (float)1132 / 1169,
			(float)240 / 1480, (float)1132 / 1169,
			(float)240 / 1480, (float)1060 / 1169,
			(float)240 / 1480, (float)1060 / 1169,
			(float)240 / 1480, (float)918 / 1169,
			(float)312 / 1480, (float)918 / 1169,
			(float)312 / 1480, (float)1060 / 1169,
			(float)170 / 1480, (float)1060 / 1169,
			(float)96 / 1480, (float)1060 / 1169,
			(float)96 / 1480, (float)918 / 1169,
			(float)170 / 1480, (float)918 / 1169,
			(float)240 / 1480, (float)1060 / 1169,
			(float)170 / 1480, (float)1060 / 1169,
			(float)240 / 1480, (float)918 / 1169,
			(float)170 / 1480, (float)918 / 1169,
			(float)170 / 1480, (float)1060 / 1169,
			(float)170 / 1480, (float)918 / 1169,
			(float)240 / 1480, (float)918 / 1169,
			(float)240 / 1480, (float)1060 / 1169
		};
		initHand(hand);
		float foot[] = {
			(float)240 / 1480, (float)918 / 1169		,
			(float)170 / 1480, (float)918 / 1169		,
			(float)170 / 1480, (float)850 / 1169		,
			(float)240 / 1480, (float)850 / 1169		,

			(float)312 / 1480, (float)1060 / 1169		,
			(float)312 / 1480, (float)1132 / 1169		,
			(float)240 / 1480, (float)1132 / 1169		,
			(float)240 / 1480, (float)1060 / 1169		,

			(float)240 / 1480, (float)1060 / 1169		,
			(float)240 / 1480, (float)918 / 1169		,
			(float)312 / 1480, (float)918 / 1169		,
			(float)312 / 1480, (float)1060 / 1169		,

			(float)170 / 1480, (float)1060 / 1169		,
			(float)96 / 1480, (float)1060 / 1169		,
			(float)96 / 1480, (float)918 / 1169			,
			(float)170 / 1480, (float)918 / 1169		,

			(float)240 / 1480, (float)1060 / 1169		,
			(float)170 / 1480, (float)1060 / 1169		,
			(float)240 / 1480, (float)918 / 1169		,
			(float)170 / 1480, (float)918 / 1169		,

			(float)170 / 1480, (float)1060 / 1169		,
			(float)170 / 1480, (float)918 / 1169		,
			(float)240 / 1480, (float)918 / 1169		,
			(float)240 / 1480, (float)1060 / 1169
		};
		initFoot(foot);

	}

};
