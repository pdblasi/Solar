#include "ProgramStateFunctions.h"

ProgramState State = ProgramState();

void ToggleWireframe()
{
	State.Wireframe = !State.Wireframe;
}

void ToggleShading()
{
	State.Flat = !State.Flat;
}

void ToggleTexture()
{
	State.Texture = !State.Texture;
}

void IncreaseWireframeResolution()
{
	State.Resolution += RESOLUTION_INC;
}

void DecreaseWireframeResolution()
{
	State.Resolution -= RESOLUTION_INC;
}

void SpeedUpSimulation()
{
	State.AnimTime -= ANIM_TIME_INC;
}

void SlowDownSimulation()
{
	State.AnimTime += ANIM_TIME_INC;
}

void TogglePause()
{
	State.Paused = !State.Paused;
}

void Step()
{
	State.Paused = true;
	glutPostRedisplay();
}