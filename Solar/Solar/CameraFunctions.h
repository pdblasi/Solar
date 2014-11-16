#ifndef __CAMERAFUNCTIONS_H__
#define __CAMERAFUNCTIONS_H__

#include <gl\freeglut.h>
#include <gl\GLU.h>

#include "Structs.h"

extern CameraState CamState;

const double HORIZONTAL_PAN_INC = .1;
const double VERTICAL_PAN_INC = .1;
const double ZOOM_INC = .1;
const double VERTICAL_ROTATE_INC = .2;

void ZoomIn();
void ZoomOut();
void RotateUp();
void RotateDown();
void PanLeft();
void PanRight();
void PanUp();
void PanDown();

#endif

