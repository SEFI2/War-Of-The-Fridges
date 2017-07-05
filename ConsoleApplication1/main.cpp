#include <stdlib.h>
#include <math.h>

#include <GL\glew.h>

#include <GL/glut.h>
#include "glm\glm\gtx\transform.hpp"

#include "Camera.h"
#include "Object.h"
#include "ShaderLoader.h"
#include "GestureHandler.h"
#include "Leap.h"
#include <cmath>
#include <iomanip>
#include "MineCraft.h"
#include <iostream>
#define pb push_back
#define mp make_pair
#define fi first
#define se second

#include <cstring>
using namespace std;
#include <cstdio>
const int N = 200009;
#include <vector>
#include <deque>
vector < pair<int , int> > g[N];
bool used[N];

vector <int> steps[N];
int u[N] , v[N];
deque < int > q;
int ind [N];

bool usedTo[N];
using namespace glm;
#include "bmploader.cpp"


mat4 projectionMatrix = mat4(1.0);
mat4 modelViewMatrix = mat4(1.0);
vec4 LightSourceAmbient = vec4(0.4, 0.5, 0.5, 1.0);
vec4 LightSourceDiffuse = vec4(0.6, 0.2, 0.2, 1.0);
vec4 LightSourceSpecular = vec4(0.6, 1.0, 0.3, 1.0);
vec4 FrontMaterialAmbient = vec4(0.3, 0.0, 0.3, 1.0);
vec4 FrontMaterialDiffuse = vec4(0.5, 0.4, 0.2, 1.0);
vec4 FrontMaterialSpecular = vec4(0.6, 0.8, 0.0, 1.0);

Object ak47;
Object knife;

float alpha = 10;

GLuint programID;


//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;
int width, height;
Minecraft steve;


void changeSize(int w, int h) {
	if (h == 0) h = 1;

	glViewport(0, 0, w, h);
	width = w, height = h;
	projectionMatrix = glm::perspective(90.0f, (float)w /h, 0.1f, 100.0f);
}



Object bunny;
Object dragon;
Object tree;

Object disk;
Object square;
Object gun[30];
Object bulletFigure;
GLuint textureID;

int bullet = 0;
GLuint color_tex;
GestureHandler gesture;

Camera camera;
Controller controller;
float total_angle = 0.0f;

GLuint red_robot, white_robot, other_tex , grey_robot , simple_robot , mason_robot, robot_tex;
vec3 random_pos[100];
vec3 random_dir[100];
mat4 robot_pos[100];
float random_angle[100];

bool disable[100];


vec3 red_robot_pos = vec3(rand() % 200 - 100 , 3 , rand() % 200 - 100);
vec3 white_robot_pos = vec3(rand() % 200 - 100, 3, rand() % 200 - 100);
vec3 other_tex_pos = vec3(rand() % 200 - 100, 3, rand() % 200 - 100);
vec3 grey_robot_pos = vec3(rand() % 200 - 100, 3, rand() % 200 - 100);
vec3 simple_robot_pos = vec3(rand() % 200 - 100, 3, rand() % 200 - 100);
vec3 mason_robot_pos = vec3(rand() % 200 - 100, 3, rand() % 200 - 100);
vec3 robot_tex_pos = vec3(rand() % 200 - 100, 3, rand() % 200 - 100);
GLuint robotIDS[6];
double radius_of_grass = 30;

std::string equations[] = {
	"25 * X = 75",
	"X + 80 = 86",
	"X ^ 2 = 49",
	"100 - X = 1",
	"66 - 2 * X = 0",
	"Even number which is divisibly by 44",
	"Biggest prime number in the range [1 , 100]",
	"The biggest number among [3 , 5 , 20]"
};

int ansEq[] = {
	3,
	6,
	7,
	99,
	33,
	88,
	97,
	20
};
int currentEquation = 0;
int equationChanger = 0;



void DrawCircle(float cx, float cy, float r, int num_segments)
{
	glBegin(GL_POLYGON);
	for (int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

		float x = r * cosf(theta);//calculate the x component
		float y = r * sinf(theta);//calculate the y component

		glVertex3f(x + cx, 0.001 , y + cy);//output vertex

	}
	glEnd();
}
void renderBitmapString(
	float x,
	float y,
	float z,
	void *font,
	char *string) {

	char *c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void renderStrokeFontString(
	float x,
	float y,
	float z,
	void *font,
	char *string) {

	char *c;
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(0.002f, 0.002f, 0.002f);
	for (c = string; *c != '\0'; c++) {
		glutStrokeCharacter(font, *c);
	}
	glPopMatrix();
}




void gameOver() {
	for (;;) {	
	}
}

void initTexture() {
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	// make synthetic cubemap data
	//makeSyntheticImages();

	//
	// Creating a 2D texture from image
	// 

	int width, height;
	uchar4 *dst1;
	LoadBMPFile(&dst1, &width, &height, "grey.bmp"); // this is how to load image
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); glGenTextures(1, &grey_robot); glBindTexture(GL_TEXTURE_2D, grey_robot);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dst1);

	uchar4 *dst2;
	LoadBMPFile(&dst2, &width, &height, "white.bmp"); // this is how to load image
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); glGenTextures(1, &white_robot); glBindTexture(GL_TEXTURE_2D, white_robot);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dst2);


	uchar4 *dst3;
	LoadBMPFile(&dst3, &width, &height, "hah.bmp"); // this is how to load image
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); glGenTextures(1, &robot_tex); glBindTexture(GL_TEXTURE_2D, robot_tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dst3);


	uchar4 *dst4;
	LoadBMPFile(&dst4, &width, &height, "yellow.bmp"); // this is how to load image
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); glGenTextures(1, &red_robot); glBindTexture(GL_TEXTURE_2D, red_robot);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dst4);

	uchar4 *dst5;
	LoadBMPFile(&dst5, &width, &height, "yes.bmp"); // this is how to load image
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); glGenTextures(1, &simple_robot); glBindTexture(GL_TEXTURE_2D, simple_robot);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dst5);

	uchar4 *dst6;
	LoadBMPFile(&dst6, &width, &height, "mason.bmp"); // this is how to load image
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); glGenTextures(1, &mason_robot); glBindTexture(GL_TEXTURE_2D, mason_robot);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dst6);

}
float dir_const = 0.0;

float rotation_angle[100];
float how_much[100];
bool down[100];

Object home;
float angleTest = 0;
std::string toStr(int a) {
	std::string first = "";
	
	while (a > 0) {
		first = first + char(a % 10 + '0');
		a /= 10;		
	}
	return first;
}




void *font = GLUT_BITMAP_TIMES_ROMAN_24;
void *fontStroke = GLUT_STROKE_ROMAN;

void renderScene(void) {
	if (gesture.lastX < -0.65) {
		deltaAngle = -0.01f;
	}
	else if (gesture.lastX > -0.35){
		deltaAngle = +0.01f;
	}
	else {
		deltaAngle = 0.0f;
	}


	if (gesture.lastZ > 0.5) {
		deltaMove = -1.0f;
	}
	else if (gesture.lastZ < -0.6) {
		deltaMove = 1.0f;
	}
	else {
		deltaMove = 0.0f;
	}
	

	if (deltaMove) {
		camera.translation(deltaMove);
	}
	if (deltaAngle) {	
		camera.rotation(deltaAngle);
	}
	equationChanger++;
	if (equationChanger > 2000) {
		currentEquation = rand() % 8;
		equationChanger = 0;
	}

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	glClearColor(0, 0.7, 0.7, 0.5);
	
	projectionMatrix = glm::perspective(70.0f, (float)width / height, 0.01f, 100.0f) * camera.getView();


	mat4 currentMatrix;
	
	glUseProgram(0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); glMultMatrixf(&projectionMatrix[0][0]);
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);
	int robotCnt = 0;
	

	for (int i = 0; i < 100; ++i) {
		if (disable[i]) 
			continue;
		robotCnt++;

		robot_pos[i] = glm::translate(random_pos[i]) * glm::translate(random_dir[i] * dir_const) * glm::rotate(
			random_angle[i] , vec3(0,1,0)) * glm::rotate(glm::radians(how_much[i]) , vec3(0 , 0 , 1));
		
		if (how_much[i] <= -rotation_angle[i]) {
			down[i] = false;
		}
		else
		if (how_much[i] >= rotation_angle[i]) {
			down[i] = true;
		}
		if (down[i]) {
			how_much[i] -= 0.5;
		}
		else {
			how_much[i] += 0.5;
		}

		
		glLoadIdentity();
		glMultMatrixf(&robot_pos[i][0][0]);
		glBindTexture(GL_TEXTURE_2D, robotIDS[i % 6]);
		steve.showCharacter();
			
		//glColor3f(1, 0, 0);
		glLoadIdentity();				

		mat4 cur = glm::translate(random_pos[i]) * glm::translate(random_dir[i] * dir_const + random_dir[i] * 20.0f) * glm::rotate(
			random_angle[i], vec3(0, 1, 0)) * glm::rotate(glm::radians(how_much[i]), vec3(0, 0, 1)) *  glm::scale(vec3(0.005, 0.005, 0.005));
		
		glMultMatrixf(&cur[0][0]);		
		//glMultMatrixf(&robot_pos[i][0][0]);

		std::string val = toStr(i + 1);
		const char *c = (char *)(val.c_str());
		
		for (; *c != '\0'; c++) 
		{		
			glutStrokeCharacter(fontStroke, *c);
		}
		
		
	}

	
	for (int i = 0; i < 100; ++i) {
		if (!disable[i]) {
			for (int j = 0; j < bullet; ++j) {
				if (gun[j].position.z < -50)continue;

				vec3 bulletPos = vec3(gun[j].objectMatrix[3][0], 0, gun[j].objectMatrix[3][2]);
				vec3 robotPos = vec3(robot_pos[i][3][0], 0, robot_pos[i][3][2]);

				if (length(bulletPos - robotPos) < 4.0f) {
					disable[i] = true;
					break;
				}
			}
			vec3 robotPos = vec3(robot_pos[i][3][0], 0, robot_pos[i][3][2]);
			
			glLoadIdentity();
			


			if (length(robotPos) < 30.0) {
				radius_of_grass -= 0.001;
			}
			if (gesture.changeWeapon && length(robotPos - camera.position) < 1.0) {
				disable[i] = true;
			}
			if (length(robotPos) < 1.0 || radius_of_grass < 1.0) {
				exit(0);
				//gameOver();

			}
		}
	}

	dir_const += 0.02;	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, height, 0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	std::string grassRadius = "Radius of grass: " + std::to_string(radius_of_grass);
	std::string robotsLeft = "Robots left: " + std::to_string(robotCnt);
	std::string currentEQ = "CURRENT THREE EQUATIONS:";
	std::string firstEQ = equations[currentEquation];
	std::string secondEQ = equations[(currentEquation + 1) % 8];
	std::string thirdEQ = equations[(currentEquation + 2) % 8];

	renderBitmapString(60, 35, 0, font, (char *)"WAR OF FRIDGES");
	renderBitmapString(30, 65, 0, font, (char *)grassRadius.c_str());
	renderBitmapString(30, 90, 0, font, (char *)robotsLeft.c_str());
	renderBitmapString(30, 125, 0, font, (char *)currentEQ.c_str());
	renderBitmapString(30, 145, 0, font, (char *)firstEQ.c_str());
	renderBitmapString(30, 165, 0, font, (char *)secondEQ.c_str());
	renderBitmapString(30, 185, 0, font, (char *)thirdEQ.c_str());

	
	
	
	glUseProgram(programID);
	glUniformMatrix4fv(glGetUniformLocation(programID, "ModelViewMatrix"), 1, GL_FALSE, &modelViewMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(programID, "ProjectionMatrix"), 1, GL_FALSE, &projectionMatrix[0][0]);
	glUniform4fv(glGetUniformLocation(programID, "ambientConst"), 1, &((LightSourceAmbient * FrontMaterialAmbient)[0]));
	glUniform4fv(glGetUniformLocation(programID, "diffuseConst"), 1, &((LightSourceDiffuse * FrontMaterialDiffuse)[0]));
	glUniform4fv(glGetUniformLocation(programID, "specularConst"), 1, &((LightSourceSpecular * FrontMaterialSpecular)[0]));
	glUniform1f(glGetUniformLocation(programID, "alpha"), alpha);

	// Draw ground
	glColor3f(0.9f, 0.9f, 0.9f);
					
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f, 100.0f);
		glVertex3f(100.0f, 0.0f, 100.0f);
		glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();

	glColor3f(0.4f, 0.7f, 0.4f);
	DrawCircle(0, 0, radius_of_grass, 50);


	glColor3f(0.0, 0.5,0.0);
	currentMatrix = glm::scale(vec3(0.05,0.05,0.05));
	glUniformMatrix4fv(glGetUniformLocation(programID, "ModelViewMatrix"), 1, GL_FALSE, &currentMatrix[0][0]);
	tree.draw();
							
	glColor3f(0.4, 0.4, 0.35);
	currentMatrix = glm::translate(vec3(0, 0, 3)) *glm::rotate(glm::radians(-90.0f), vec3(1, 0, 0))* glm::scale(vec3(0.005, 0.005, 0.005));
	glUniformMatrix4fv(glGetUniformLocation(programID, "ModelViewMatrix"), 1, GL_FALSE, &currentMatrix[0][0]);
	home.draw();

	
	


	for (int i = -2; i < 2; i++)		
		for (int j = -2; j < 2; j++) {				
			if (i == 0 && j == 0)continue;
			mat4 currentMatrix = modelViewMatrix;

			currentMatrix = currentMatrix * glm::translate(vec3(i*10.0, 0, j * 10.0));

			currentMatrix = currentMatrix *  glm::translate(vec3(i*10.0, 0, j * 10.0));
			glColor3f(1.0f, 1.0f, 1.0f);

			currentMatrix = currentMatrix * glm::translate(vec3(0.0f, 0.75f, 0.0f)) ;
			glUniformMatrix4fv(glGetUniformLocation(programID, "ModelViewMatrix"), 1, GL_FALSE, &currentMatrix[0][0]);
			glutSolidSphere(0.75f, 20, 20);

			currentMatrix = currentMatrix * glm::translate(vec3(0.0f, 1.0f, 0.0f)) ;
			glUniformMatrix4fv(glGetUniformLocation(programID, "ModelViewMatrix"), 1, GL_FALSE, &currentMatrix[0][0]);
			glutSolidSphere(0.25f, 20, 20);

			glm::mat4 forEyes = currentMatrix;
			glColor3f(0.0f, 0.0f, 0.0f);
			forEyes = forEyes * glm::translate(vec3(0.05f, 0.10f, 0.18f)) ;
			glUniformMatrix4fv(glGetUniformLocation(programID, "ModelViewMatrix"), 1, GL_FALSE, &forEyes[0][0]);
			glutSolidSphere(0.05f, 10, 10);

			forEyes = forEyes * glm::translate(vec3(-0.1f, 0.0f, 0.0f)) ;
			glUniformMatrix4fv(glGetUniformLocation(programID, "ModelViewMatrix"), 1, GL_FALSE, &forEyes[0][0]);
			glutSolidSphere(0.05f, 10, 10);
			
			glColor3f(1.0f, 0.5f, 0.5f);
			currentMatrix = currentMatrix * glm::rotate(0.0f, vec3(1.0f, 0.0f, 0.0f)) ;
			glUniformMatrix4fv(glGetUniformLocation(programID, "ModelViewMatrix"), 1, GL_FALSE, &currentMatrix[0][0]);
			glutSolidCone(0.08f, 0.5f, 10, 2);
		}
	

	for (int i = 0; i < bullet; ++i) {
		gun[i].objectMatrix *= glm::translate(vec3(0, 0, -2));
		if (gun[i].position.z < -100)continue;
		gun[i].position.z -= 0.1; 
		currentMatrix = gun[i].objectMatrix *  glm::rotate(90.0f, vec3(1, 0, 0));
		glUniformMatrix4fv(glGetUniformLocation(programID, "ModelViewMatrix"), 1, GL_FALSE, &currentMatrix[0][0]);
		square.draw();
		//std::cout << i << " ";

	}	
	//std::cout << bullet << "\n";


	

	glColor3f(0.3, 0.3, 0.2);
	const float gesturePosX = gesture.fingerX;
	const float gesturePosY = gesture.fingerY;


				
	total_angle += deltaAngle;
	if (gesture.changeWeapon) {
		square.objectMatrix =
			glm::translate(camera.position)
			* glm::rotate(-total_angle, vec3(0, 1, 0))
			* glm::scale(mat4(1), vec3(0.001, 0.001, 0.001))
			* glm::translate(vec3(gesturePosX, gesturePosY - 10, -40)) 
			* glm::rotate(glm::radians(180.0f), vec3(0, 0, 1))
			* glm::rotate(glm::radians(180.0f), vec3(1, 0, 0));
		glUniformMatrix4fv(glGetUniformLocation(programID, "ModelViewMatrix"), 1, GL_FALSE, &square.objectMatrix[0][0]);
		ak47.draw();
	}
	else {
		square.objectMatrix =
			glm::translate(camera.position)
			* glm::rotate(-total_angle, vec3(0, 1, 0))
			* glm::scale(mat4(1), vec3(0.001, 0.001, 0.001))
			* glm::translate(vec3(gesturePosX, gesturePosY - 10, -40))	 
			* glm::rotate(glm::radians(180.0f), vec3(0, 0, 1))
			* glm::rotate(glm::radians(140.0f), vec3(0, 0, 1));
		glUniformMatrix4fv(glGetUniformLocation(programID, "ModelViewMatrix"), 1, GL_FALSE, &square.objectMatrix[0][0]);
		knife.draw();
	}

	glUniformMatrix4fv(glGetUniformLocation(programID, "ModelViewMatrix"), 1, GL_FALSE, &modelViewMatrix[0][0]);
	if (gesture.shoot) {
		gesture.shoot = false;
		if (bullet == 30) {
			bullet = 0;
		}				
		
		gun[bullet].position.z = 0;
		gun[bullet].objectMatrix =  glm::translate(mat4(1), camera.position)
									* glm::rotate(-total_angle, vec3(0, 1, 0))
									* glm::scale(mat4(1), vec3(0.02, 0.02, 0.1)) 
								* glm::translate(vec3(gesturePosX, gesturePosY - 6, -20));
		bullet++;
	}

	glutSwapBuffers();
}








void pressKey(int key, int xx, int yy) {
	switch (key) {
		case GLUT_KEY_LEFT: deltaAngle = -0.01f; break;
		case GLUT_KEY_RIGHT: deltaAngle = 0.01f; break;
		case GLUT_KEY_UP: gesture.shoot = true;   break;
		case GLUT_KEY_DOWN: deltaMove = -0.5f; break;
	}
}

void releaseKey(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_LEFT:
	case GLUT_KEY_RIGHT: deltaAngle = 0.0f; break;
	case GLUT_KEY_UP:
	case GLUT_KEY_DOWN: deltaMove = 0; break;
	}
}
void keyboardDown(unsigned char key, int x, int y) {
	switch (key) {
		case 'a': deltaAngle = -0.01f; break;
		case 'd': deltaAngle = 0.01f; break;
		case 'w': deltaMove = 0.5f; break;
		case 's': deltaMove = -0.5f; break;
	}
}
void keyboardUp(unsigned char key, int x, int y) {
	switch (key) {
		case 'a':
		case 'd': deltaAngle = 0.0f; break;
		case 'w':
		case 's': deltaMove = 0; break;
	}
}


ShaderLoader shaderLoader;
const float  M_PI = 3.14159265359;


struct trie{
        int leaf;
        int next[26];
        trie () {
            leaf = false;
            memset (next , -1 , sizeof next);
        }

};

int cnt = 0;
trie a[1234567];
string str[1234567];
string ans[10009];
int dp[10009];

char c[10009];
char s[1009];

void go (int j) {
    if (j == -1)return;
    go (dp[j]);
    cout << ans[j] << " ";

}

int make () {
   // ios_base :: sync_with_stdio (false);
   //a cin.tie (0);

    int n;
    cin >> n;
    scanf ("\n");
    for (int i = 0 ; i < n ; ++i) {
            scanf ("%c" , &c[i]);
    }

    int m;
    cin >> m;
    for (int i = 0 ; i < m ; ++i) {
            scanf ("\n%s" , &s);
            int st = strlen (s);
            int now = 0;
            for (int j = 0 ; j < st ; ++j) {
                    char ss = s[j];
                    if (isupper(ss)) ss = tolower(ss);
                    if (a[now].next[ss - 'a'] == -1)
                    {
                        a[now].next[ss - 'a'] = cnt ++;
                    }
                    now = a[now].next[ss - 'a'];
            }
            str[now] = s;
            a[now].leaf = i;
    }

    for (int i = 0 ; i < n ; ++i)
        dp[i] = -2;

    for (int i = 0 ; i < n ; ++i) {
                 int now = 0;
                 for (int j = i ; j >= 0 ; --j) {
                            if (a[now].next[c[j] - 'a'] == -1)break;
                            now = a[now].next[c[j]-'a'];
                            if (a[now].leaf && (!j || dp[j - 1] != -2)) {
                                    dp[i] = j - 1;
                                    ans[i] = str[now];
                                    break;
                            }
                 }
    }

    go (n - 1);



    return 0;

}
void putLights();

int main(int argc, char **argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(620, 620);
	glutCreateWindow("Robot Destruction");
	glewInit();
	initTexture();
	steve.buildCharacter();

	for (int i = 0; i < 100; ++i)
	{
		random_pos[i] = vec3((rand() % 50 + 50)  * (rand() % 2 == 0? - 1 : 1), 3, (rand() % 200 + 50)* (rand() % 2 == 0 ? -1 : 1) );
		random_dir[i] = -random_pos[i];
		random_dir[i].y = 0;
		random_dir[i] /= length(random_dir[i]);
		
		random_angle[i] = asinf(random_dir[i].x - 0.001);
		//std::cout << random_angle[i] << " " << random_dir[i].x << "\n";
		rotation_angle[i] = rand() % 4+2;

	}


	robotIDS[0] = red_robot;
	robotIDS[1] = grey_robot;
	robotIDS[2] = robot_tex;
	robotIDS[3] = red_robot;
	robotIDS[4] = mason_robot;
	robotIDS[5] = simple_robot;

	//creating shaders
	programID = shaderLoader.createGLSLProgram("VertexShader.glsl", NULL, "FragmentShader.glsl"); 
	textureID = shaderLoader.createGLSLProgram("textureVertex.glsl", NULL, "textureFragment.glsl");
	putLights();
	bulletFigure.InitObj("model.obj");
	ak47.InitObj("AKM.obj");
	knife.InitObj("kukri_low.obj");
	tree.InitObj("tree.obj");

	//bunny.Init("bunny.off");
	//dragon.Init("dragon-full.off");
	disk.Init("fandisk.off");
	square.InitCube();
	home.InitObj("garden.obj");

	
	controller.addListener(gesture);
	controller.enableGesture(Leap::Gesture::TYPE_KEY_TAP);
	controller.enableGesture(Leap::Gesture::TYPE_CIRCLE);


	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutSpecialFunc(pressKey);

	// here are the new entries
	glutSpecialUpFunc(releaseKey);
	glutKeyboardFunc(keyboardDown);
	glutKeyboardUpFunc(keyboardUp);
	glutIgnoreKeyRepeat(1);

	

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	glutMainLoop();

	controller.removeListener(gesture);
	return 1;
}


void putLights() {

	GLfloat lightPos1[] = { 20, 20, 100, 1 };
	GLfloat diffuse1[] = { 1.0, 0.0, 0.2, 0.0 };
	GLfloat specular1[] = { 1.0, 0.0, 0.3, 0.0 };
	GLfloat ambient1[] = { 0.4, 0.1, 0.5, 0.0 };

	GLfloat lightPos2[] = { 40, 40, -100, 1};
	GLfloat diffuse2[] = { 0.0,0.0,1.0,0.2 };
	GLfloat specular2[] = { 0.0,1.0,1,0.1 };
	GLfloat ambient2[] = { 0,0.1,0.6,0.3 };

	GLfloat lightPos3[] = { 0, 100, 0, 1 };
	GLfloat diffuse3[] = { 1.0,0.0,0.0,0.3 };
	GLfloat specular3[] = { 1.0,0.1,0.1,0.5 };
	GLfloat ambient3[] = { 0.3,0.1,0.6,1.0 };

	GLfloat materialColor[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat materialSpecular[] = { 0.1,0.1,0.0,0.1 };
	GLfloat materialEmission[] = { 0.1f,0.1f,0.1, 0.0f };
	GLfloat shininess = 50;


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	/*glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse1);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient1);
	*/
	//glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);
	
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	
	glEnable(GL_LIGHT2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specular2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, ambient2);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);


	glEnable(GL_LIGHT3);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse3);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specular3);
	glLightfv(GL_LIGHT2, GL_AMBIENT, ambient3);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPos3);

	/*glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, materialColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialSpecular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, materialEmission);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);*/
}






