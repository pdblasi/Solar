#ifndef __CAMERAFUNCTIONS_H__
#define __CAMERAFUNCTIONS_H__

#include <gl\freeglut.h>
#include <gl\GLU.h>

#include "Structs.h"

//the camera state
extern CameraState CamState;

//increment amounts 
const float HORIZONTAL_PAN_INC = 100000;
const float VERTICAL_PAN_INC = 100000;
const float ZOOM_INC = 100000;
const float VERTICAL_ROTATE_INC = .01;
extern float angle; 

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

