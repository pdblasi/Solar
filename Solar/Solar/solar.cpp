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
* @section todo_bugs_modification_section Todo, Bugs, and Modificationss
*
* @par Modifications and Development Timeline:
@verbatim
Date          Modification
------------  --------------------------------------------------------------

@endverbatim
*
*****************************************************************************/
#include <gl\freeglut.h>
#include <gl\GLU.h>
#include <vector>
#include <string>

#include "Planet.h"

using namespace std;

//Callbacks
void Display();
void Reshape(int width, int height);
void Keyboard(unsigned char key, int x, int y);
void SpecialKeys(int key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Menu(int val);

//Constants
const unsigned char ESCAPE_KEY = 27;

const int INIT_SCREEN_WIDTH = 500;
const int INIT_SCREEN_HEIGHT = 500;

//Global Data
vector<Planet> Planets;

/**************************************************************************//**
* @author Paul Blasi, Caitlin Taggart
*
* @par Description:
* Main execution point of the app. Initializes the windows.
*
* @returns Execution outcome.
*
*****************************************************************************/
int main(int argc, char *argv[])
{
	//Init Glut and GL
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glutInitWindowSize(INIT_SCREEN_WIDTH, INIT_SCREEN_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Solar System");

	//Register Callbacks
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeys);
	glutMouseFunc(Mouse);

	//Create Menu
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

	//Create Heavenly Bodies

	//Start window
	glutMainLoop();

	return 0;
}


void Display()
{
    glClear(GL_COLOR_BUFFER_BIT); 

    //ask the planets to draw themselves. 
    for (int i = 0; i < Planets.size(); i++)
    {
        //Draw Planet
    }

    glutSwapBuffers(); 
}

void Reshape(int width, int height)
{
    glViewport(0, 0, width, height); 
    double ratio = double(width) / height; 

    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();
    gluPerspective(60.0, ratio, 1.0, 30.0);
}

void Mouse(int button, int state, int x, int y)
{

}

void Menu(int val)
{
	switch (val)
	{
	case 0:		//Toggle Wireframe/Polygon Rendering
		break;
	case 1:		//Toggle Flat/Smooth Shading
		break;
	case 2:		//Toggle Texture Mapping
		break;
	case 3:		//Zoom In
		break;
	case 4:		//Zoom Out
		break;
	case 5:		//Rotate Up
		break;
	case 6:		//Rotate Down
		break;
	case 7:		//Pan Left
		break;
	case 8:		//Pan Right
		break;
	case 9:		//Pan Up
		break;
	case 10:	//Pan Down
		break;
	case 11:	//Increase Wireframe Resolution
		break;
	case 12:	//Decrease Wireframe Resolution
		break;
	case 13:	//Speed Up Simulation
		break;
	case 14:	//Slow Down Simulation
		break;
	case 15:	//Suspend/Resume Animation
		break;
	case 16:	//Single Step
		break;
	case 17:	//Quit
		glutLeaveMainLoop();
		break;
	}
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'p':
		Menu(0);
		break;
	case 'f':
		Menu(1);
		break;
	case 't':
		Menu(2);
		break;
	case '+':
	case 'Z':
		Menu(3);
		break;
	case '-':
	case 'z':
		Menu(4);
		break;
	case 'x':
		Menu(7);
		break;
	case 'X':
		Menu(8);
		break;
	case 'Y':
		Menu(9);
		break;
	case 'y':
		Menu(10);
		break;
	case 'N':
		Menu(11);
		break;
	case 'n':
		Menu(12);
		break;
	case 'A':
		Menu(13);
		break;
	case 'a':
		Menu(14);
		break;
	case 'r':
		Menu(15);
		break;
	case 's':
		Menu(16);
		break;
	case ESCAPE_KEY:
		Menu(17);
		break;
	}
}

void SpecialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		Menu(5);
		break;
	case GLUT_KEY_DOWN:
		Menu(6);
		break;
	case GLUT_KEY_LEFT:
		Menu(7);
		break;
	case GLUT_KEY_RIGHT:
		Menu(8);
		break;
	}
}