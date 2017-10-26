#include "sCad.h"

sCad::sCad()
{
}
sCad::~sCad()
{
}

void sCad::initOpenGL()
{
	// some GL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_MULTISAMPLE);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

}
void sCad::processNormalKeys(unsigned char key, int x, int y)
{
	std::cout << "Working" << std::endl;
	if (key == 'q')
		obSize += 0.3f;
	if (key == 'e')
		obSize -= 0.3f;
	if (key == 'a')
		yRotated += 3.0f;
	if (key == 'd')
		yRotated -= 3.0f;
	if (key == 'w')
		xRotated += 3.0f;
	if (key == 's')
		xRotated -= 3.0f;
}
void sCad::pressKey(int key, int xx, int yy)
{
	switch (key) {
	case GLUT_KEY_LEFT: angle += -0.1f; break;
	case GLUT_KEY_RIGHT: angle += 0.1f; break;
	case GLUT_KEY_UP: radious += 1.0f; break;
	case GLUT_KEY_DOWN: radious += -1.0f; break;
	}
	x = radious*sin(angle);
	z = radious*-cos(angle);
	cout << "X:" << x << " Z:" << z << " R:" << radious << endl;
}

//Drawing a half prism for Window1
void sCad::drawHprimid1()
{
	// rotation about X axis
	glRotatef(xRotated, 1.0, 0.0, 0.0);
	// rotation about Y axis
	glRotatef(yRotated, 0.0, 1.0, 0.0);
	// rotation about Z axis
	glRotatef(zRotated, 0.0, 0.0, 1.0);
	// scaling transfomation 
	glScalef(1.0, 1.0, 1.0);

	glBegin(GL_TRIANGLES);
	//face 1
	glColor3f(1.0, 0.0, 0.0);
	glVertex3fv(points[0]);
	glVertex3fv(points[1]);
	glVertex3fv(points[3]);
	//face 2
	glColor3f(0.0, 1.0, 0.0);
	glVertex3fv(points[1]);
	glVertex3fv(points[2]);
	glVertex3fv(points[3]);
	//face 3
	glColor3f(0.0, 0.0, 1.0);
	glVertex3fv(points[0]);
	glVertex3fv(points[2]);
	glVertex3fv(points[3]);
	//face 4
	glColor3f(1.0, 1.0, 0.0);
	glVertex3fv(points[0]);
	glVertex3fv(points[1]);
	glVertex3fv(points[2]);

	glEnd();
	glutPostRedisplay();
}

//Drawing a half prism for 2D windows
void sCad::drawHprimid()
{
	/*glBegin(GL_TRIANGLES);
	//face 1
	glColor3f(1.0, 0.0, 0.0);
	glVertex3fv(points[0]);
	glVertex3fv(points[1]);
	glVertex3fv(points[3]);
	//face 2
	glColor3f(0.0, 1.0, 0.0);
	glVertex3fv(points[1]);
	glVertex3fv(points[2]);
	glVertex3fv(points[3]);
	//face 3
	glColor3f(0.0, 0.0, 1.0);
	glVertex3fv(points[0]);
	glVertex3fv(points[2]);
	glVertex3fv(points[3]);
	//face 4
	glColor3f(1.0, 1.0, 0.0);
	glVertex3fv(points[0]);
	glVertex3fv(points[1]);
	glVertex3fv(points[2]);

	glEnd();*/
	glColor3fv(GREEN);
	glBegin(GL_LINES);
	//vector<Vector2>::iterator po = mousePoints[0].begin();
	unsigned int lPoints = mousePoints[LINES].size() - mousePoints[LINES].size() % 2;
	for (unsigned int i = 0; i < lPoints; i = i + 2)
	{
		Vector2 vec[2];
		//vec[0] = (*std::next(line_mousePoints.begin(),i));
		//vec[1] = (*std::next(line_mousePoints[].begin(), i));
		vec[0] = mousePoints[LINES][i];
		vec[1] = mousePoints[LINES][i + 1];

		glVertex2i(vec[0].getVector2x(), vec[0].getVector2y());
		glVertex2i(vec[1].getVector2x(), vec[1].getVector2y());
	}
	glutPostRedisplay();
}

/*void Sprint(int x, int y, char *st)
{
int l, i;

l = strlen(st); // see how many characters are in text string.
glRasterPos2i(x, y); // location to start printing text
for (i = 0; i < l; i++)  // loop until i is greater then l
{
glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, st[i]); // Print a character on the screen
}
}*/

float angleRot = 0.0f;

void sCad::init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);  // When screen cleared, use black.
	glShadeModel(GL_SMOOTH);  // How the object color will be rendered smooth or flat
	glEnable(GL_DEPTH_TEST);   // Check depth when rendering
							   // Lighting is added to scene
							   /*glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
							   glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
							   glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
							   glEnable(GL_LIGHTING);  // Turn on lighting
							   glEnable(GL_LIGHT1);    // Turn on light 1*/
}
void sCad::reshape_1(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);
	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	ratio = 1.0f * w / h;
	gluPerspective(45, ratio, 0.1, 1000);
	//glOrtho(-8.0, 8.0, -8.0, 8.0, 0.0, 30.0);  // Setup an Ortho view


	//glMatrixMode(GL_MODELVIEW);
}
void sCad::drawpolygon_1()
{
	//	unsigned int lPoints = mousePoints[POLYGON].size() - mousePoints[POLYGON].size() % 2;
	for (unsigned int j = 0; j <polygoncount; j++)
	{
		glColor3f(1.0, 0.0, 1.0);
		glBegin(GL_LINE_LOOP);
		//	unsigned int lPoints = polygons[j].size() - polygons[j].size() % 3;
		for (unsigned int i = 0; i < polygons[j].size(); i++)
		{
			Vector3 vec[1];

			vec[0] = polygons[j][i];
			//vec[1] = mousePoints[POLYGON][i + 1];
			GLfloat point1[3] = { vec[0].getVector3x() / 100.0, vec[0].getVector3y() / 100.0, vec[0].getVector3z() / 100.0 };
			glVertex3fv(point1);
		}
		glEnd();
	}
	glutPostRedisplay();
}
void sCad::display_1(void)
{
	char *p;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //Clear the screen

														 //glMatrixMode(GL_PROJECTION);  // Tell opengl that we are doing project matrix work
														 //glLoadIdentity();  // Clear the matrix
														 //glOrtho(-8.0, 8.0, -8.0, 8.0, 0.0, 300.0);  // Setup an Ortho view

	glMatrixMode(GL_MODELVIEW);  // Tell opengl that we are doing model matrix work. (drawing)
	glLoadIdentity(); // Clear the model matrix
	
	glColor3f(1.0, 1.0, 1.0);


	//gluLookAt(10, 5, 20, 0, 0, 0, 0, 1, 0);
	/*if (deltaMove)
	computePos(deltaMove);
	if (deltaAngle)
	computeDir(deltaAngle);*/

	gluLookAt(x, 0.0f, z,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);
	glRotatef(angleRot, 0, 1.5, 1.0);
	angleRot += 0.1f;
	drawpolygon_1();
	//drawHprimid1();


	glutSwapBuffers();
}

void sCad::drawTest_2()
{
	glColor3fv(BLUE);
	glPointSize(point);
	glBegin(GL_POINTS);

	glVertex2i(xyz[0], xyz[2]);
	glEnd();
	glutPostRedisplay();
}
//Creating a point
void sCad::point2()
{
	glColor3f(0.0, 0.0, 1.0);
	glPointSize(point);
	glBegin(GL_POINTS);

	for (unsigned int j = 0; j <polygoncount; j++)
	{
		for (unsigned int i = 0; i <polygons[j].size(); i++)
		{
			Vector3 vec[2];
			vec[0] = polygons[j][i];
			glVertex2i(vec[0].getVector3x(), vec[0].getVector3z());
		}
	}
	glEnd();
	glutPostRedisplay();
}
void sCad::drawpolygon_2()
{
	//	unsigned int lPoints = mousePoints[POLYGON].size() - mousePoints[POLYGON].size() % 2;
	for (unsigned int j = 0; j <polygoncount; j++)
	{
		glColor3f(1.0, 0.0, 1.0);
		glBegin(GL_LINE_LOOP);
		for (unsigned int i = 0; i <polygons[j].size(); i++)
		{
			Vector3 vec[2];

			vec[0] = polygons[j][i];
			//vec[1] = mousePoints[POLYGON][i + 1];

			glVertex2i(vec[0].getVector3x(), vec[0].getVector3z());
		}
		glEnd();
	}
	glutPostRedisplay();
}
bool sCad::selectedOldPoint_2(int x, int y)
{
	bool oldPoint = false;
	Vector3 *Opoint = NULL;
	for (int z = 0; z < polygons.size(); z++)
	{
		if (!oldPoint)
			for (int a = 0; a < polygons[z].size(); a++)
			{
				int Vertexpointx = polygons[z].at(a).getVector3x();
				int Vertexpointy = polygons[z].at(a).getVector3z();
				int clickpointx = x;
				int clickpointy = y;
				if ((Vertexpointx > clickpointx - 10 && Vertexpointx < clickpointx + 10) &&
					(Vertexpointy > clickpointy - 10 && Vertexpointy < clickpointy + 10))
				{
					Opoint = &polygons[z].at(a);
					(polygons[polygoncount - 1]).push_back(*Opoint);
					(polygons[polygoncount - 1]).push_back(*Opoint);
					oldPoint = true;
					break;
				}
			}
	}
	return oldPoint;
}
void sCad::mouse_2(int btn, int state, int x, int y)
{
	if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_UP)
	{
		//if (chosenOption == POLYGON)
		{
			polygoncount++;
			vector<Vector3> polyPoints;
			polygons.push_back(polyPoints);
			polystart = false;
		}
	}
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		if (polygons.size() > 0)
		{
			(polygons[polygoncount - 1]).pop_back();
		}
	}
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		Vector3 xyz{ x - window_center[0] , 0,  y - window_center[1] };
		//	if (chosenOption == POLYGON)
		{
			if (polygons.size() == 0)
			{
				polygoncount = 1;
				vector<Vector3> polyPoints;
				polygons.push_back(polyPoints);
			}
			if ((polygons[polygoncount - 1]).size() == 0)
			{
				if (!selectedOldPoint_2(xyz.getVector3x(), xyz.getVector3z()))
				{
					(polygons[polygoncount - 1]).push_back(xyz);
					(polygons[polygoncount - 1]).push_back(xyz);
				}
			}
			else
			{
				if (!selectedOldPoint_2(xyz.getVector3x(), xyz.getVector3z()))
				{
					(polygons[polygoncount - 1]).push_back(xyz);
				}
			}
			polystart = true;
		}
	}
	std::cout << "S_X = " << x << " , S_Y = " << y << endl;
	std::cout << "X = " << xyz[0] << " , Y = " << xyz[1] << " , Z = " << xyz[2] << endl;

}
void sCad::reshape_2(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);
	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	gluOrtho2D(-window_center[0], window_center[1], window_center[1], -window_center[0]);

	glMatrixMode(GL_MODELVIEW);
}
void sCad::display_2(void)
{
	char *p;

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //Clear the screen
														 //gluLookAt(0, 10, 0, 0, 0, 0, 0, 0, -2);

														 //glRotatef( 45, 1.0, 1.0, 0.0); // rotate cube
														 //glRotatef(spin++, 1.0, 1.0, 1.0); // spin cube

														 //	if (shape == 0) //glutSolidTeapot(4); // Draw a cube
														 //		drawHprimid();
	drawpolygon_2();
	point2();
	glFlush();
	glutSwapBuffers();
}

void sCad::drawTest_3()
{
	glColor3fv(BLUE);
	glPointSize(point);
	glBegin(GL_POINTS);

	glVertex2i(xyz[0], xyz[1]);
	glEnd();
	glutPostRedisplay();
}
//Creating a point
void sCad::point3()
{
	glColor3f(0.0, 0.0, 1.0);
	glPointSize(point);
	glBegin(GL_POINTS);

	for (unsigned int j = 0; j <polygoncount; j++)
	{
		for (unsigned int i = 0; i <polygons[j].size(); i++)
		{
			Vector3 vec[2];
			vec[0] = polygons[j][i];
			glVertex2i(vec[0].getVector3x(), vec[0].getVector3y());
		}
	}
	glEnd();
	glutPostRedisplay();
}
void sCad::drawpolygon_3()
{
	//	unsigned int lPoints = mousePoints[POLYGON].size() - mousePoints[POLYGON].size() % 2;
	for (unsigned int j = 0; j <polygoncount; j++)
	{
		glColor3f(1.0, 0.0, 1.0);
		glBegin(GL_LINE_LOOP);
		for (unsigned int i = 0; i <polygons[j].size(); i++)
		{
			Vector3 vec[2];

			vec[0] = polygons[j][i];
			//vec[1] = mousePoints[POLYGON][i + 1];

			glVertex2i(vec[0].getVector3x(), vec[0].getVector3y());
		}
		glEnd();
	}
	glutPostRedisplay();
}
bool sCad::selectedOldPoint_3(int x, int y)
{
	bool oldPoint = false;
	Vector3 *Opoint = NULL;
	for (int z = 0; z < polygons.size(); z++)
	{
		if (!oldPoint)
			for (int a = 0; a < polygons[z].size(); a++)
			{
				int Vertexpointx = polygons[z].at(a).getVector3x();
				int Vertexpointy = polygons[z].at(a).getVector3y();
				int clickpointx = x;
				int clickpointy = y;
				if ((Vertexpointx > clickpointx - 10 && Vertexpointx < clickpointx + 10) &&
					(Vertexpointy > clickpointy - 10 && Vertexpointy < clickpointy + 10))
				{
					Opoint = &polygons[z].at(a);
					(polygons[polygoncount - 1]).push_back(*Opoint);
					(polygons[polygoncount - 1]).push_back(*Opoint);
					oldPoint = true;
					break;
				}
			}
	}
	return oldPoint;
}
void sCad::mouse_3(int btn, int state, int x, int y)
{
	if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_UP)
	{
		//if (chosenOption == POLYGON)
		{
			polygoncount++;
			vector<Vector3> polyPoints;
			polygons.push_back(polyPoints);
			polystart = false;
		}
	}
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		if (polygons.size() > 0)
		{
			(polygons[polygoncount - 1]).pop_back();
		}
	}
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		Vector3 xyz{ x - window_center[0],  y - window_center[1], 0 };
		//	if (chosenOption == POLYGON)
		{
			if (polygons.size() == 0)
			{
				polygoncount = 1;
				vector<Vector3> polyPoints;
				polygons.push_back(polyPoints);
			}
			if ((polygons[polygoncount - 1]).size() == 0)
			{
				if (!selectedOldPoint_3(xyz.getVector3x(), xyz.getVector3y()))
				{
					(polygons[polygoncount - 1]).push_back(xyz);
					(polygons[polygoncount - 1]).push_back(xyz);
				}
			}
			else if (!selectedOldPoint_3(xyz.getVector3x(), xyz.getVector3y()))
				(polygons[polygoncount - 1]).push_back(xyz);
			polystart = true;
		}
	}
	std::cout << "S_X = " << x << " , S_Y = " << y << endl;
	std::cout << "X = " << xyz[0] << " , Y = " << xyz[1] << " , Z = " << xyz[2] << endl;
}
void sCad::reshape_3(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);
	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	gluOrtho2D(-window_center[0], window_center[1], window_center[1], -window_center[0]);


	glMatrixMode(GL_MODELVIEW);
}
void sCad::display_3(void)
{
	char *p;

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //Clear the screen

	drawpolygon_3();
	point3();
	glFlush();
	glutSwapBuffers();
}

void sCad::drawTest_4()
{
	glColor3fv(BLUE);
	glPointSize(point);
	glBegin(GL_POINTS);
	glVertex2i(window_size[1] - xyz[2], xyz[1]);
	glEnd();
	glutPostRedisplay();
}
void sCad::point4()
{
	glColor3f(0.0, 0.0, 1.0);
	glPointSize(point);
	glBegin(GL_POINTS);

	for (unsigned int j = 0; j <polygoncount; j++)
	{
		for (unsigned int i = 0; i <polygons[j].size(); i++)
		{
			Vector3 vec[2];
			vec[0] = polygons[j][i];
			glVertex2i(vec[0].getVector3z(), vec[0].getVector3y());
		}
	}
	glEnd();
	glutPostRedisplay();
}
void sCad::drawpolygon_4()
{
	//	unsigned int lPoints = mousePoints[POLYGON].size() - mousePoints[POLYGON].size() % 2;
	for (unsigned int j = 0; j <polygoncount; j++)
	{
		glColor3f(1.0, 0.0, 1.0);
		glBegin(GL_LINE_LOOP);
		for (unsigned int i = 0; i <polygons[j].size(); i++)
		{
			Vector3 vec[2];

			vec[0] = polygons[j][i];
			//vec[1] = mousePoints[POLYGON][i + 1];

			glVertex2i(vec[0].getVector3z(), vec[0].getVector3y());
		}
		glEnd();
	}
	glutPostRedisplay();
}
bool sCad::selectedOldPoint_4(int x, int y)
{
	bool oldPoint = false;
	Vector3 *Opoint = NULL;
	for (int z = 0; z < polygons.size(); z++)
	{
		if (!oldPoint)
			for (int a = 0; a < polygons[z].size(); a++)
			{
				int Vertexpointx = polygons[z].at(a).getVector3z();
				int Vertexpointy = polygons[z].at(a).getVector3y();
				int clickpointx = x;
				int clickpointy = y;
				if ((Vertexpointx > clickpointx - 10 && Vertexpointx < clickpointx + 10) &&
					(Vertexpointy > clickpointy - 10 && Vertexpointy < clickpointy + 10))
				{
					Opoint = &polygons[z].at(a);
					(polygons[polygoncount - 1]).push_back(*Opoint);
					(polygons[polygoncount - 1]).push_back(*Opoint);
					oldPoint = true;
					break;
				}
			}
	}
	return oldPoint;
}
void sCad::mouse_4(int btn, int state, int x, int y)
{
	if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_UP)
	{
		//if (chosenOption == POLYGON)
		{
			polygoncount++;
			vector<Vector3> polyPoints;
			polygons.push_back(polyPoints);
			polystart = false;
		}
	}
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		if (polygons.size() > 0)
		{
			(polygons[polygoncount - 1]).pop_back();
		}
	}
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		Vector3 xyz{ 0,  y - window_center[1], x - window_center[0] };
		//	if (chosenOption == POLYGON)
		{
			if (polygons.size() == 0)
			{
				polygoncount = 1;
				vector<Vector3> polyPoints;
				polygons.push_back(polyPoints);
			}
			if ((polygons[polygoncount - 1]).size() == 0)
			{
				if (!selectedOldPoint_4(xyz.getVector3z(), xyz.getVector3y()))
				{
					(polygons[polygoncount - 1]).push_back(xyz);
					(polygons[polygoncount - 1]).push_back(xyz);
				}
			}
			else if (!selectedOldPoint_4(xyz.getVector3z(), xyz.getVector3y()))
				(polygons[polygoncount - 1]).push_back(xyz);
			polystart = true;
		}
	}
	std::cout << "S_X = " << x << " , S_Y = " << y << endl;
	std::cout << "X = " << xyz[0] << " , Y = " << xyz[1] << " , Z = " << xyz[2] << endl;

}
void sCad::reshape_4(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);
	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	gluOrtho2D(-window_center[0], window_center[1], window_center[1], -window_center[0]);

	glMatrixMode(GL_MODELVIEW);
}
void sCad::display_4(void)
{
	char *p;

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //Clear the screen

	drawpolygon_4();
	point4();
	glFlush();
	glutSwapBuffers();
}

void sCad::draw_s(int vao)
{
	float vertices1[] = {
		0.0f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f, 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,  0.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f, 1.0f,  0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,  0.0f, 0.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f,  1.0f, 0.0f, 1.0f, 1.0f
	};
	unsigned int faceIndex[] = {
		0,1,2,0,2,3,
		4,5,6,4,6,7,
		8,9,10,8,10,11,
		12,13,14,12,14,15,
		16,17,18,16,18,19,
		20,21,22,20,22,23
	};
	if (polygons.size()>0){
		size_t arr_size = polygons[0].size() * 4;
		GLfloat *vertices = new float[arr_size];
		long Fcnt =0;
		for (unsigned int i = 0; i <polygons[0].size(); i++)
		{
			Vector3 vec = polygons[0][i];
			vertices[Fcnt] = vec.getVector3x() / 100.0;
			Fcnt++;
			vertices[Fcnt] = vec.getVector3y() / 100.0; 
			Fcnt++;
			vertices[Fcnt] = vec.getVector3z() / 100.0;
			Fcnt++;
			vertices[Fcnt] = 1.0;
			Fcnt++;
			//glVertex2i(vec[0].getVector3z(), vec[0].getVector3y());
		}	
		glBindVertexArray(vao);
		// create buffers for our vertex data
		
		//vertex coordinates buffer
		glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*4* polygons[0].size(), vertices);
		//glEnableVertexAttribArray(VSShaderLib::VERTEX_COORD_ATTRIB);
		//glVertexAttribPointer(VSShaderLib::VERTEX_COORD_ATTRIB, 4, GL_FLOAT, GL_FALSE, 0, 0);

		//index buffer
	/*	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(faceIndex), faceIndex, GL_STATIC_DRAW);*/

		// unbind the VAO
		glBindVertexArray(0);
		delete vertices;
	}
	else
	{
		// create the VAO
		glBindVertexArray(vao);

		// create buffers for our vertex data
		
		//vertex coordinates buffer
		glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*96, vertices1);
		/*glEnableVertexAttribArray(VSShaderLib::VERTEX_COORD_ATTRIB);
		glVertexAttribPointer(VSShaderLib::VERTEX_COORD_ATTRIB, 4, GL_FLOAT, 0, 0, 0);*/
/*
		//texture coordinates buffer
		glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
		glEnableVertexAttribArray(VSShaderLib::TEXTURE_COORD_ATTRIB);
		glVertexAttribPointer(VSShaderLib::TEXTURE_COORD_ATTRIB, 2, GL_FLOAT, 0, 0, 0);

		//normals buffer
		glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
		glEnableVertexAttribArray(VSShaderLib::NORMAL_ATTRIB);
		glVertexAttribPointer(VSShaderLib::NORMAL_ATTRIB, 3, GL_FLOAT, 0, 0, 0);
*/
	//index buffer
	/*	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(faceIndex), faceIndex, GL_STATIC_DRAW);*/

		// unbind the VAO
		glBindVertexArray(0);
	}
	
}