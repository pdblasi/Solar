/*************************************************************************//**
* @file
*
* @mainpage Program 3 - Solar System Simulation
*
* @section course_section Course Information
*
* @author Paul Blasi, Caitlin Taggart
*
* @date 18 November, 2014
*
* @par Professor:
*         Dr. Weiss
*
* @par Course:
*         Graphics  -  9 AM
*
* @par Location:
*         McLaury - 313
*
* @section program_section Program Information
*
* @details This program is a simplified solar system simulation. It will
* simulate eight planets, the sun, the Earth's moon, and Saturn's rings.
*
* @section compile_section Compiling and Usage
*
* @par Compiling Instructions:
@verbatim
c:\> make solar
@endverbatim
*
* @par Usage:
@verbatim
On Windows:
c:\> solar.exe

On Linux:
c:\> ./solar
@endverbatim
*
* @section todo_bugs_modification_section Todo, Bugs, and Modifications
*
* @par Modifications and Development Timeline:
@verbatim
Date          Modification
------------  --------------------------------------------------------------
Nov 04, 2014  Initial project setup. Registered callback functions and set
			  keyboard input to map straight to the Menu function.

Nov 08, 2014  Started to implement viewing. Basic set up for black screen.

Nov 11, 2014  Set up basic program flow and created structs to hold the
			  program and camera state to minimize global variables. Got
			  some of the simple state updates for the program state and
			  camera state started. Rotation and zoom hasn't been touched.

Nov 11, 2014  Set up basic data for planet and the constructor. Not yet
			  implemented.

Nov 16, 2014  Split Camera and ProgramState functions out of main and into
			  seperate files to make it easier to split up work.

Nov 16, 2014  Got a single planet up and displaying on screen.

Nov 16, 2014  Initial attempts at camera functions completed.

Nov 17, 2014  Created initial scaling as macros, then moved into private
			  static functions for easier modification.

Nov 23, 2014  Major effort towards completion. Added lighting model.
			  Added labels to planets. Added texture mapping. Added ring
			  system to Saturn.

Nov 24, 2014  Added texture mapping to rings. Made the rings fit into the
			  Planets array by making Planets an array of pointers. Removed
			  unneccesary code. Commented and cleaned all files.
@endverbatim
*
*****************************************************************************/
#include <GL/freeglut.h>
#include <GL/glu.h>
#include <vector>
#include <string>

#include "Planet.h"
#include "Ring.h"
#include "Structs.h"
#include "CameraFunctions.h"
#include "ProgramStateFunctions.h"

using namespace std;

//Callbacks
void Display();
void Reshape(int width, int height);
void Keyboard(unsigned char key, int x, int y);
void SpecialKeys(int key, int x, int y);
void Menu(int val);
void Animate(int frame);

//Other Functions
void CreateClickMenu();

//Constants
const unsigned char ESCAPE_KEY = 27;

const int INIT_SCREEN_WIDTH = 500;
const int INIT_SCREEN_HEIGHT = 500;

const int NUM_PLANETS = 11;

//Global Data
Planet* Planets[NUM_PLANETS];

int ScreenWidth; 
int ScreenHeight;

//light settings
GLfloat LightPosition[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat PointLight[] = { 1, 1, 1, 1 };
GLfloat AmbientLight[] = { 0.0001, 0.0001, 0.0001, 1.0 };

GLfloat ConstAttenuation[] = { 0 };
GLfloat LinearAttenuation[] = { 1 };

/**************************************************************************//**
* @author Paul Blasi, Caitlin Taggart
*
* @par Description:
* Main execution point of the app. Initializes the windows. Creates the planets
* Sets up the lighting. Enters the main loop. 
*
* @returns Execution outcome.
*
*****************************************************************************/
int main(int argc, char *argv[])
{
	//Init Glut and GL
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glutInitWindowSize(INIT_SCREEN_WIDTH, INIT_SCREEN_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Solar System");

	//Register Callbacks
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeys);
	glutTimerFunc(State.AnimTime, Animate, State.Frame);

	//Create Menu
	CreateClickMenu();

	//Create Planets
	Planet::CreateSolarSystem(Planets);

	//Set up light sources
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);

	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, PointLight);
	glLightfv(GL_LIGHT1, GL_CONSTANT_ATTENUATION, ConstAttenuation);
	glLightfv(GL_LIGHT1, GL_LINEAR_ATTENUATION, LinearAttenuation);

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	//Enable coloring
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glColorMaterial(GL_FRONT, GL_AMBIENT);

	//Start window
	glutMainLoop();

	for (int i = 0; i < NUM_PLANETS; i++)
	{
		delete Planets[i];
	}

	delete Planets;

	return 0;
}

/**************************************************************************//**
* @author Paul Blasi, Caitlin Taggart
*
* @par Description:
* Updates the placement of the of the planet and the day placement of the planet 
* also calls the animate function again. 
*
* @param frame - the frame that we are on
*
*****************************************************************************/
void Animate(int frame)
{
	State.Frame = frame + 1;

	//Ask planet to update itself
	for (unsigned int i = 0; i < NUM_PLANETS; i++)
	{
		Planets[i]->Update();
	}

    //If not paused then call the animate function again. 
	if (State.Paused == false)
	{
		glutTimerFunc(State.AnimTime, Animate, State.Frame);
	}

	glutPostRedisplay();
}

/**************************************************************************//**
* @author Paul Blasi, Caitlin Taggart
*
* @par Description:
* The display function for the planet. Updates the perspective, the place
* the user is looking at and draws the planets.
*
*****************************************************************************/
void Display()
{
    //clear the screen. 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Set up camera using CamState
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, double(ScreenWidth/ScreenHeight), 1, 100000000);

    //set what we are looking at 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(CamState.Position[0], CamState.Position[1], CamState.Position[2],
        CamState.LookAt[0], CamState.LookAt[1], CamState.LookAt[2],
        CamState.Up[0], CamState.Up[1], CamState.Up[2]);

    //Ask the planets to draw themselves.
    for (unsigned int i = 0; i < NUM_PLANETS; i++)
    {
		Planets[i]->Draw(State);
    }

    glutSwapBuffers(); 
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* @par Description:
* Callback function for the reshape in OpenGL. Stores the width and height, 
* sets the viewport and sets the perspective (including the gluLookAt). 
* 
* @param width - the width of the screen in pixels 
* @param height - the height of the screen in pixels 
*
*****************************************************************************/
void Reshape(int width, int height)
{
    //find the screen dimensions
    ScreenWidth = width; 
    ScreenHeight = height; 

    //set up the viewport 
    glViewport(0, 0, width, height); 
    double ratio = double(width) / height;

    //set up the perspective 
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();
	gluPerspective(60.0, ratio, 10, 100000000);
    gluLookAt(CamState.Position[0], CamState.Position[1], CamState.Position[2],
        CamState.LookAt[0], CamState.LookAt[1], CamState.LookAt[2], 
        CamState.Up[0], CamState.Up[1], CamState.Up[2]);
}


/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* Menu callback function. Calls the appropriate function for that menu option. 
*
* @param val - the menu item that has been called.  
*****************************************************************************/
void Menu(int val)
{
	switch (val)
	{
	case 0:		//Toggle Wireframe/Polygon Rendering
		ToggleWireframe();
		break;
	case 1:		//Toggle Flat/Smooth Shading
		ToggleShading();
		break;
	case 2:		//Toggle Texture Mapping
		ToggleTexture();
		break;
	case 3:		//Zoom In
		ZoomIn();
		break;
	case 4:		//Zoom Out
		ZoomOut();
		break;
	case 5:		//Rotate Up
		RotateUp();
		break;
	case 6:		//Rotate Down
		RotateDown();
		break;
	case 7:		//Pan Left
		PanLeft();
		break;
	case 8:		//Pan Right
		PanRight();
		break;
	case 9:		//Pan Up
		PanUp();
		break;
	case 10:	//Pan Down
		PanDown();
		break;
	case 11:	//Increase Wireframe Resolution
		IncreaseWireframeResolution();
		break;
	case 12:	//Decrease Wireframe Resolution
		DecreaseWireframeResolution();
		break;
	case 13:	//Speed Up Simulation
		SpeedUpSimulation();
		break;
	case 14:	//Slow Down Simulation
		SlowDownSimulation();
		break;
	case 15:	//Suspend/Resume Animation
		State.Paused = !State.Paused;
		if (!State.Paused)
		{
			glutTimerFunc(State.AnimTime, Animate, State.Frame + 1);
		}
		break;
	case 16:	//Single Step
		State.Paused = true;
		Animate(State.Frame + 1);
		break;
	case 17:	//Quit
		glutLeaveMainLoop();
		break;
	}

	if (State.Paused == true)
		glutPostRedisplay();
}

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* Keyboard callback function. Calls the Menu function for the appropriate 
* menu option. 
*
* @param key - the key that was pressed
* @param x - the x position of the mouse when the key was pressed
* @param y - the y position of the mouse when the key was pressed
*
*****************************************************************************/
void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'p':
		Menu(0); //Toggle Wireframe/Polygon Rendering
		break;
	case 'f':
		Menu(1); //Toggle Flat/Smooth Shading
		break;
	case 't':
		Menu(2); //Toggle Texture Mapping 
		break;
	case '+':
	case 'Z':
		Menu(3); //Zoom In
		break;
	case '-':
	case 'z':
		Menu(4); //Zoom Out
		break;
	case 'x':
		Menu(7); //Pan Left 
		break;
	case 'X':
		Menu(8); //Pan Right 
		break;
	case 'Y':
		Menu(9); //Pan Up
		break;
	case 'y':
		Menu(10); //Pan Down 
		break;
	case 'N':
		Menu(11); //Increase wireframe resolution
		break;
	case 'n':
		Menu(12); //Decrease wireframe resolution 
		break;
	case 'A':
		Menu(13); //Speed Up simulation 
		break;
	case 'a':
		Menu(14); //Slow down simulation
		break;
	case 'r':
		Menu(15); //Suspend/Resume Animation
		break;
	case 's':       //Single Step 
		Menu(16);
		break;
	case ESCAPE_KEY:
		Menu(17);   //exit program 
		break;
	}
}

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* Special keys keyboard callback function. Calls the Menu function for the 
* appropriate menu option.
*
* @param key - the key that was pressed
* @param x - the x position of the mouse when the key was pressed
* @param y - the y position of the mouse when the key was pressed
*
*****************************************************************************/
void SpecialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		Menu(5);    //rotate up 
		break;
	case GLUT_KEY_DOWN:
		Menu(6);    //rotate down 
		break;
	case GLUT_KEY_LEFT:
		Menu(7);    //pan left 
		break;
	case GLUT_KEY_RIGHT:
		Menu(8);    //pan right 
		break;
	}
}

/**************************************************************************//**
* @author Paul Blasi
*
* @par Description:
* Creates the menu items for the menu in OpenGL, and attaches it to the right
* mouse button. 
*
*****************************************************************************/
void CreateClickMenu()
{
    //create the menu
	glutCreateMenu(Menu);
	glutAddMenuEntry("Solar System Simulator (PB & CT Nov 2014)", -1);
	glutAddMenuEntry("=========================================", -1);
	glutAddMenuEntry("Toggle Wireframe/Polygon Rendering   (p)", 0);
	glutAddMenuEntry("Toggle Flat/Smooth Shading           (f)", 1);
	glutAddMenuEntry("Toggle Texture Mapping               (t)", 2);
	glutAddMenuEntry("Zoom In                            (+/Z)", 3);
	glutAddMenuEntry("Zoom Out                           (-/z)", 4);
	glutAddMenuEntry("Rotate Up                      (UpArrow)", 5);
	glutAddMenuEntry("Rotate Down                  (DownArrow)", 6);
	glutAddMenuEntry("Pan Left                   (LeftArrow/x)", 7);
	glutAddMenuEntry("Pan Right                 (RightArrow/X)", 8);
	glutAddMenuEntry("Pan Up                               (Y)", 9);
	glutAddMenuEntry("Pan Down                             (y)", 10);
	glutAddMenuEntry("Increase Wireframe Resolution        (N)", 11);
	glutAddMenuEntry("Decrease Wireframe Resolution        (n)", 12);
	glutAddMenuEntry("Speed Up Simulation                  (A)", 13);
	glutAddMenuEntry("Slow Down Simulation                 (a)", 14);
	glutAddMenuEntry("Suspend/Resume Animation             (r)", 15);
	glutAddMenuEntry("Single Step                          (s)", 16);
	glutAddMenuEntry("Quit                               (Esc)", 17);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
