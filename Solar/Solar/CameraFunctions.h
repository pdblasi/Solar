/************************************************************************//**
*  @file
*
*  @brief This file contains the Camera State function declarations and
*   global variables, and global constants. The global constants are the 
*   amount to increment by on a given camera state change. The state changes 
*   include Zoom In, Zoom Out, Rotate Up, Rotate Down, Pan Up, Pan Down, Pan
*   left, and Pan Right. 
***************************************************************************/

#ifndef __CAMERAFUNCTIONS_H__
#define __CAMERAFUNCTIONS_H__

//includes 
#include <GL/freeglut.h>
#include <GL/glu.h>
#include "Structs.h"

/*!
* @brief the state of the camera position, what it is looking at, and what direction is up
*/
extern CameraState CamState;

/*!
* @brief the amount to pan left and right 
*/
const float HORIZONTAL_PAN_INC = 100000;
/*!
* @brief the amount to pan up and down 
*/
const float VERTICAL_PAN_INC = 100000;
/*!
* @brief the amount to zoom in and out 
*/
const float ZOOM_INC = 100000;
/*!
* @brief the amount to rotate in radians 
*/
const float VERTICAL_ROTATE_INC = .01;
/*!
* @brief the current angle the camera is at 
*/
extern float angle; 

/*!
* @brief definition of PI 
*/
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/*!
* @brief Zooms the camera in 
*/
void ZoomIn();
/*!
* @brief zooms the camera out 
*/
void ZoomOut();
/*!
* @brief rotates the camera up 
*/
void RotateUp();
/*!
* @brief rotates the camera down 
*/
void RotateDown();
/*!
* @brief pans the camera left 
*/
void PanLeft();
/*!
* @brief pans the camera right 
*/
void PanRight();
/*!
* @brief pans the camera up 
*/
void PanUp();
/*!
* @brief pans the camera down 
*/
void PanDown();

#endif

