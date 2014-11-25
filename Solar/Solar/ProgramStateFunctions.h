/************************************************************************//**
*  @file
*
*  @brief Contains the function declarations for the program state. The 
*   program state includes whether the file is is wireframe or not, and 
*   determines the type of shading used, and if texture mapping is used.
*   It also keeps track of the wirefram resolution, and takes care of 
*   speeding up and slowing down the planetary motion. Also it can pause the 
*   program and takes a single step. 
***************************************************************************/
#ifndef __PROGRAMSTATEFUNCTIONS_H__
#define __PROGRAMSTATEFUNCTIONS_H__

#include <GL/freeglut.h>
#include <GL/glu.h>
#include "Structs.h"

/*!
* @brief the state of the program 
*/
extern ProgramState State;

/*!
* @brief the increment to change the resolution by each time 
*/
const int RESOLUTION_INC = 1;
/*!
* @brief the amount to change the animation time by when speeding up or slowing down 
*/
const int ANIM_TIME_INC = 1;

/*!
* @brief turns wireframe on and off 
*/
void ToggleWireframe();
/*!
* @brief toggles between smooth and solid shading 
*/
void ToggleShading();
/*!
* @brief toggles between texture mapping and not 
*/
void ToggleTexture();
/*!
* @brief increases the wireframe resolution 
*/
void IncreaseWireframeResolution();
/*!
* @brief decreases the wireframe resolution 
*/
void DecreaseWireframeResolution();
/*!
* @brief speeds up the simulation
*/
void SpeedUpSimulation();
/*!
* @brief slows down the simulation 
*/
void SlowDownSimulation();
/*!
* @brief turns pause on and off 
*/
void TogglePause();
/*!
* @brief takes a single step 
*/
void Step();

#endif
