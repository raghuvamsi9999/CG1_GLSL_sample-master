#pragma once

#include <math.h> 
#include <string>    // Math library (Higher math functions )
#include<vector>
#include "glew.h"
#include <GL/freeglut.h>
#include<iostream>
#include"Vector2.h"
#include"Vector3.h"
#include "VSMathlib.h"
#include "VSShaderlib.h"
using namespace std;
class sCad
{
public:
	sCad();
	~sCad();
	
	enum Menu {
		EXTRUDE, TRANSFORM, ERASE, EXIT 
	}MenuOption;
	enum DrawOptions {
		LINES
	};
	void initOpenGL();
	void processNormalKeys(unsigned char key, int x, int y);
	void pressSpecialKey(int key, int xx, int yy);
	void drawHprimid1();
	void drawHprimid();
	void init(void);
	void reshape_1(int w, int h) ;
	void drawpolygon_1();
	void display_1(void);

	void drawTest_2();
	void point2();
	void drawpolygon_2();
	bool selectedOldPoint_2(int x, int y);
	void mouse_2(int btn, int state, int x, int y);
	void reshape_2(int w, int h) ;
	void display_2(void);

	void drawTest_3();
	void point3();
	void drawpolygon_3();
	bool selectedOldPoint_3(int x, int y);
	void mouse_3(int btn, int state, int x, int y);
	void reshape_3(int w, int h) ;
	void display_3(void);

	void drawTest_4();
	void point4();
	void drawpolygon_4();
	bool selectedOldPoint_4(int x, int y);
	void mouse_4(int btn, int state, int x, int y);
	void reshape_4(int w, int h) ;
	void display_4(void);

// 5th window functions
	void draw_s(int vao);
	int tPoints = 0;
	GLsizei MOUSEx = 0, MOUSEy = 0;
	GLfloat BLUE[3] = { 0,0,1 };
	GLfloat GREEN[3] = { 0, 1, 0 };
	GLfloat point = 5;
	vector<Vector2> mousePoints[4];

	void processMenuEvents(int option);
	void createGLUTMenus();
	/*  //lighting
	GLfloat LightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat LightDiffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat LightPosition[] = { 5.0f, 5.0f, -10.0f, 1.0f };
	GLfloat mat_specular[] = { 0.2, 0.2, 0.2, 1.0 };*/
	//Vector2 startPoint(0, 0);
	//Vector2 endPoint(0, 0);
	Vector2 MousepointClick;
	Vector2 *CurrentVertex = nullptr;
	bool Edit = false;
	bool AlreadyClicked = false;
	bool putCurrrentVerctor = false;
	bool polystart = false;
	unsigned int count = 0;
	
	//coordinates for HALF PRISM
	GLfloat points[5][3] = { { 1,0,0 },{ 0,3,0 },{ -1,0,0 },{ 0,0,1 },{ 0,0,0 } };
	int window_1, window_2, window_3, window_4;
	//static int view_state = 0, light_state = 0;
	GLfloat xRotated, yRotated, zRotated;
	int shape, ch;
	GLfloat obSize = 1.0;
	GLint xyz[3] = { 0, 0, 0 };
	GLint window_size[2] = { 350, 350 };
	GLint window_center[2] = { 175, 175 };
	vector<vector<Vector3>> polygons;
	unsigned int polygoncount = 0;
	float angle = 0.0f;
	// actual vector representing the camera's direction
	float lx = 0.0f, lz = -1.0f;
	// XZ position of the camera
	float x = 10.0f, z = 20.0f;// the key states. These variables will be zero
							   //when no key is being presses
	float deltaAngle = 0.0f;
	float deltaMove = 0;
	float radious = 10;
	int w1, h1;
	float ratio;
	GLuint buffers[4];

};

