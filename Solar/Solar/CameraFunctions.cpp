#include "CameraFunctions.h"

CameraState CamState = CameraState();

void ZoomIn()
{

}

void ZoomOut()
{

}

void RotateUp()
{

}

void RotateDown()
{

}

void PanLeft()
{
	CamState.Position[0] -= HORIZONTAL_PAN_INC;
	CamState.LookAt[0] -= HORIZONTAL_PAN_INC;
}

void PanRight()
{
	CamState.Position[0] += HORIZONTAL_PAN_INC;
	CamState.LookAt[0] += HORIZONTAL_PAN_INC;
}

void PanUp()
{
	CamState.Position[1] += VERTICAL_PAN_INC;
	CamState.LookAt[1] += VERTICAL_PAN_INC;
}

void PanDown()
{
	CamState.Position[1] -= VERTICAL_PAN_INC;
	CamState.Position[1] -= VERTICAL_PAN_INC;
}
