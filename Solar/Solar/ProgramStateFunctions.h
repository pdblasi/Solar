#ifndef __PROGRAMSTATEFUNCTIONS_H__
#define __PROGRAMSTATEFUNCTIONS_H__

#include <gl\freeglut.h>
#include <gl\GLU.h>

#include "Structs.h"

extern ProgramState State;

const int RESOLUTION_INC = 1;
const int ANIM_TIME_INC = 1;

void ToggleWireframe();
void ToggleShading();
void ToggleTexture();
void IncreaseWireframeResolution();
void DecreaseWireframeResolution();
void SpeedUpSimulation();
void SlowDownSimulation();
void TogglePause();
void Step();

#endif