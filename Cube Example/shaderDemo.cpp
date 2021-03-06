#include <math.h>
#include <string>

#include "shaderDemo.h"

// include GLEW to access OpenGL 3.3 functions
//#include <GL/glew.h>
#include "glew.h"

// GLUT is the toolkit to interface with the OS
#include <GL/freeglut.h>

// Use Very Simple Libs
#include "VSMathlib.h"
#include "VSShaderlib.h"
#include"sCad.h"
using namespace std;
sCad cObj;

VSMathLib *vsml;
VSShaderLib shader;

// Camera Position
float camX, camY, camZ;

// Mouse Tracking Variables
int startX, startY, tracking = 0;

// Camera Spherical Coordinates
float alpha = -43.0f, beta = 48.0f;
float r = 5.25f;

// Frame counting and FPS computation
long myTime,timebase = 0,frame = 0;
char s[32];

GLuint vao;

// ------------------------------------------------------------
//
// Reshape Callback Function
//

void changeSize(int w, int h) {

	float ratio;
	// Prevent a divide by zero, when window is too short
	if(h == 0)
		h = 1;
	// set the viewport to be the entire window
	glViewport(0, 0, w, h);
	// set the projection matrix
	ratio = (1.0f * w) / h;
	vsml->loadIdentity(VSMathLib::PROJECTION);
	vsml->perspective(53.13f, ratio, 0.1f, 1000.0f);
}

// ------------------------------------------------------------
//
// Render stuff
//

void renderScene(void) {

	cObj.draw_s(vao);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// load identity matrices
	vsml->loadIdentity(VSMathLib::VIEW);
	vsml->loadIdentity(VSMathLib::MODEL);
	// set the camera using a function similar to gluLookAt
	vsml->lookAt(camX, camY, camZ, 0,0,0, 0,1,0);
	// use our shader
	glUseProgram(shader.getProgramIndex());
	// send matrices to uniform buffer
	vsml->matricesToGL();
	// render VAO
	glBindVertexArray(vao);
	//glDrawElements(GL_LINE_LOOP, faceCount*3, GL_UNSIGNED_INT, 0);
	//int points = 0;
	//if (cObj.polygons.size()>0) points = cObj.polygons[0].size();
	
	glDrawArrays(GL_LINE_LOOP, 0, cObj.tPoints);
	//glDrawArrays(GL_POINTS, 0, 8);

	glutPostRedisplay();
	 //swap buffers
	glutSwapBuffers();
}

// ------------------------------------------------------------
//
// Events from the Keyboard
//

void processKeys(unsigned char key, int xx, int yy)
{
	switch(key) 
	{
		case 27:
			glutLeaveMainLoop();
			break;
		case 'c': 
			printf("Camera Spherical Coordinates (%f, %f, %f)\n", alpha, beta, r);
			break;
	}

//  uncomment this if not using an idle func
//	glutPostRedisplay();
}

// ------------------------------------------------------------
//
// Mouse Events
//

void processMouseButtons(int button, int state, int xx, int yy)
{
	// start tracking the mouse
	if (state == GLUT_DOWN)  {
		startX = xx;
		startY = yy;
		if (button == GLUT_LEFT_BUTTON)
			tracking = 1;
		else if (button == GLUT_RIGHT_BUTTON)
			tracking = 2;
	}

	//stop tracking the mouse
	else if (state == GLUT_UP) {
		if (tracking == 1) {
			alpha -= (xx - startX);
			beta += (yy - startY);
		}
		else if (tracking == 2) {
			r += (yy - startY) * 0.01f;
			if (r < 0.1f)
				r = 0.1f;
		}
		tracking = 0;
	}
}

// Track mouse motion while buttons are pressed

void processMouseMotion(int xx, int yy)
{

	int deltaX, deltaY;
	float alphaAux, betaAux;
	float rAux;

	deltaX =  - xx + startX;
	deltaY =    yy - startY;

	// left mouse button: move camera
	if (tracking == 1) {


		alphaAux = alpha + deltaX;
		betaAux = beta + deltaY;

		if (betaAux > 85.0f)
			betaAux = 85.0f;
		else if (betaAux < -85.0f)
			betaAux = -85.0f;
		rAux = r;
	}
	// right mouse button: zoom
	else if (tracking == 2) {

		alphaAux = alpha;
		betaAux = beta;
		rAux = r + (deltaY * 0.01f);
		if (rAux < 0.1f)
			rAux = 0.1f;
	}

	camX = rAux * sin(alphaAux * 3.14f / 180.0f) * cos(betaAux * 3.14f / 180.0f);
	camZ = rAux * cos(alphaAux * 3.14f / 180.0f) * cos(betaAux * 3.14f / 180.0f);
	camY = rAux *   						       sin(betaAux * 3.14f / 180.0f);

//  uncomment this if not using an idle func
//	glutPostRedisplay();
}

void mouseWheel(int wheel, int direction, int x, int y) {

	r += direction * 0.1f;
	if (r < 0.1f)
		r = 0.1f;

	camX = r * sin(alpha * 3.14f / 180.0f) * cos(beta * 3.14f / 180.0f);
	camZ = r * cos(alpha * 3.14f / 180.0f) * cos(beta * 3.14f / 180.0f);
	camY = r *   						     sin(beta * 3.14f / 180.0f);

//  uncomment this if not using an idle func
//	glutPostRedisplay();
}

// --------------------------------------------------------
//
// Shader Stuff
//

GLuint setupShaders() {

	// Shader for models
	shader.init();
	shader.loadShader(VSShaderLib::VERTEX_SHADER, "shaders/helloWorld.vert");
	shader.loadShader(VSShaderLib::FRAGMENT_SHADER, "shaders/helloWorld.frag");

	// set semantics for the shader variables
	shader.setProgramOutput(0,"outputF");
	shader.setVertexAttribName(VSShaderLib::VERTEX_COORD_ATTRIB, "position");

	shader.prepareProgram();

	printf("InfoLog for Hello World Shader\n%s\n\n", shader.getAllInfoLogs().c_str());
	
	return(shader.isProgramValid());
}

// ------------------------------------------------------------
//
// Model loading and OpenGL setup
//

void initOpenGL()
{
	// set the camera position based on its spherical coordinates
	camX = r * sin(alpha * 3.14f / 180.0f) * cos(beta * 3.14f / 180.0f);
	camZ = r * cos(alpha * 3.14f / 180.0f) * cos(beta * 3.14f / 180.0f);
	camY = r *   						     sin(beta * 3.14f / 180.0f);

	// some GL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_MULTISAMPLE);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// create the VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// create buffers for our vertex data
	
	glGenBuffers(4, cObj.buffers);

	//vertex coordinates buffer
	glBindBuffer(GL_ARRAY_BUFFER, cObj.buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, 10000, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(VSShaderLib::VERTEX_COORD_ATTRIB);
	glVertexAttribPointer(VSShaderLib::VERTEX_COORD_ATTRIB, 4, GL_FLOAT, 0, 0, 0);
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

	//index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(faceIndex), faceIndex, GL_STATIC_DRAW);
*/
	// unbind the VAO
	glBindVertexArray(0);
}

void initVSL() {
	vsml = VSMathLib::getInstance();
	// tell VSL the uniform block name
	vsml->setUniformBlockName("Matrices");
	// set semantics for the matrix variable
	vsml->setUniformName(VSMathLib::PROJ_VIEW_MODEL, "pvm");
}

// ------------------------------------------------------------
//
// Main function
//

void d1(void) { cObj.display_1(); }
void r1(int w, int h) { cObj.reshape_1(w, h); }
void p1(int key, int xx, int yy) { cObj.pressSpecialKey(key, xx, yy); }
void d2(void) { cObj.display_2(); }
void r2(int w, int h) { cObj.reshape_2(w, h); }
void p2(unsigned char key, int x, int y) { cObj.processNormalKeys(key, x, y); }
void m2(int btn, int state, int x, int y) { cObj.mouse_2(btn, state, x, y); };
void d3(void) { cObj.display_3(); }
void r3(int w, int h) { cObj.reshape_3(w, h); }
void m3(int btn, int state, int x, int y) { cObj.mouse_3(btn, state, x, y); };
void d4(void) { cObj.display_4(); }
void r4(int w, int h) { cObj.reshape_4(w, h); }
void m4(int btn, int state, int x, int y) { cObj.mouse_4(btn, state, x, y); };

int main(int argc, char **argv) {

	bool shader = true;
	if (argc > 1) { 
		shader = (strcmp("i",argv[1]));
		//std::cerr << "Usage: " << argv[0] << "SOURCE DESTINATION" << std::endl;
		//return 1;
	}
//	if(!shader){

		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
		glutInitWindowSize(cObj.window_size[0], cObj.window_size[1]);

		//glutTimerFunc(10, TimeEvent, 1);
		//orthographic view
		glutInitWindowPosition(100, 0);
		cObj.window_1 = glutCreateWindow(argv[0]);
		glutSetWindowTitle("3D View");
		glutDisplayFunc(d1);
		glutReshapeFunc(r1);
		glutKeyboardFunc(p2);
		//glutKeyboardFunc(processNormalKeys);
		glutSpecialFunc(p1);
		// here are the new entries
		/*glutIgnoreKeyRepeat(1);
		glutSpecialUpFunc(releaseKey);*/

		// top view
		glutInitWindowPosition(450, 0);
		cObj.window_2 = glutCreateWindow(argv[0]);
		glutSetWindowTitle("Top View");
		glutDisplayFunc(d2);
		glutReshapeFunc(r2);
		glutKeyboardFunc(p2);
		glutInitWindowPosition(100, 340);
		glutMouseFunc(m2);

		//front view
		cObj.window_3 = glutCreateWindow(argv[0]);
		glutSetWindowTitle("Front View");
		glutDisplayFunc(d3);
		glutReshapeFunc(r3);
		glutKeyboardFunc(p2);
		glutInitWindowPosition(450, 340);
		glutMouseFunc(m3);

		// side view
		cObj.window_4 = glutCreateWindow(argv[0]);
		glutSetWindowTitle("Side View");
		glutKeyboardFunc(p2);
		glutDisplayFunc(d4);
		glutReshapeFunc(r4);
		glutMouseFunc(m4);

		glewInit();

		printf("Vendor: %s\n", glGetString(GL_VENDOR));
		printf("Renderer: %s\n", glGetString(GL_RENDERER));
		printf("Version: %s\n", glGetString(GL_VERSION));
		printf("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

		cObj.initOpenGL();

/*		glutMainLoop();
		return 0;
	}else 
	{
		//  GLUT initialization
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);

		glutInitContextVersion(3, 3);
		glutInitContextProfile(GLUT_CORE_PROFILE);
		glutInitContextFlags(GLUT_DEBUG);

		glutInitWindowPosition(100, 100);
		glutInitWindowSize(512, 512);
*/		
		glutInitWindowPosition(800, 0);
		glutCreateWindow("Shader's Demonstration");
		//  Callback Registration
		glutDisplayFunc(renderScene);
		glutReshapeFunc(changeSize);
		//glutIdleFunc(renderScene);

		//	Mouse and Keyboard Callbacks
		glutKeyboardFunc(processKeys);
		glutMouseFunc(processMouseButtons);
		glutMotionFunc(processMouseMotion);

		glutMouseWheelFunc(mouseWheel);

		//	return from main loop
		glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

		//	Init GLEW
		glewExperimental = GL_TRUE;
		glewInit();

		printf("Vendor: %s\n", glGetString(GL_VENDOR));
		printf("Renderer: %s\n", glGetString(GL_RENDERER));
		printf("Version: %s\n", glGetString(GL_VERSION));
		printf("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

		if (!setupShaders())
			return(1);

		initOpenGL();

		initVSL();

		//  GLUT main loop
		glutMainLoop();

		return(0);
//	}
	
}

