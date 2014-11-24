#ifndef __CAMERAFUNCTIONS_H__
#define __CAMERAFUNCTIONS_H__

//includes 
#include <gl\freeglut.h>
#include <gl\GLU.h>
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

//function declarations 
void ZoomIn();
void ZoomOut();
void RotateUp();
void RotateDown();
void PanLeft();
void PanRight();
void PanUp();
void PanDown();

#endif

