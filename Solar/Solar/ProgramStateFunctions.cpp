/************************************************************************//**
*  @file
*
*  @brief Contains the function implementations for the program state. The 
*   program state includes whether the file is is wireframe or not, and 
*   determines the type of shading used, and if texture mapping is used.
*   It also keeps track of the wirefram resolution, and takes care of 
*   speeding up and slowing down the planetary motion. Also it can pause the 
*   program and takes a single step. 
***************************************************************************/

//includes 
#include "ProgramStateFunctions.h"

/*!
* @brief the state of the program
*/
ProgramState State = ProgramState();

/**************************************************************************//**
* @author Paul Blasi 
* 
* Description: Toggles if the wireframe represenation if on or off 
*
*****************************************************************************/
void ToggleWireframe()
{
	State.Wireframe = !State.Wireframe;
}

/**************************************************************************//**
* @author Paul Blasi 
* 
* Description: Toggles if smooth shading or flat shading is used 
*
*****************************************************************************/
void ToggleShading()
{
	State.Flat = !State.Flat;
}

/**************************************************************************//**
* @author Paul Blasi 
* 
* Description: Toggles if texture mapping is used or not 
*
*****************************************************************************/
void ToggleTexture()
{
	State.Texture = !State.Texture;
}

/**************************************************************************//**
* @author Paul Blasi 
* 
* Description: increases the wireframe resolution 
*
*****************************************************************************/
void IncreaseWireframeResolution()
{
	State.Resolution += RESOLUTION_INC;
}

/**************************************************************************//**
* @author Paul Blasi 
* 
* Description: decreases the wireframe resolution 
*
*****************************************************************************/
void DecreaseWireframeResolution()
{
	State.Resolution -= RESOLUTION_INC;
}

/**************************************************************************//**
* @author Paul Blasi 
* 
* Description: Speeds up the animation by decrease the time between animations 
*
*****************************************************************************/
void SpeedUpSimulation()
{
	if (State.AnimTime > ANIM_TIME_INC)
		State.AnimTime -= ANIM_TIME_INC;
}

/**************************************************************************//**
* @author Paul Blasi 
* 
* Description: Slows down the animation by increase the time between animations 
*
*****************************************************************************/
void SlowDownSimulation()
{
	if (State.AnimTime < 500)
		State.AnimTime += ANIM_TIME_INC;
}

/**************************************************************************//**
* @author Paul Blasi 
* 
* Description: Toggles if the animation is paused or not 
*
*****************************************************************************/
void TogglePause()
{
	State.Paused = !State.Paused;
}

/**************************************************************************//**
* @author Paul Blasi 
* 
* Description: Ttakes a single step for the animation  
*
*****************************************************************************/
void Step()
{
	State.Paused = true;
	glutPostRedisplay();
}