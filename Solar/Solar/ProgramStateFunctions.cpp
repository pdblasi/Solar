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
	if (State.AnimTime > ANIM_TIME_INC)
		State.AnimTime -= ANIM_TIME_INC;
}

void SlowDownSimulation()
{
	if (State.AnimTime < 500)
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