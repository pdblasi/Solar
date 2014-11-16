#include "CameraFunctions.h"
#include "math.h"

CameraState CamState = CameraState();

void ZoomIn()
{ 
    float vector[3];
    float mag = 0; 
    for (int i = 0; i < 3; i++)
    {
        //initialize the vector we are along
        vector[i] = CamState.Position[i] - CamState.LookAt[i]; 
        //find the magnitude
        mag += vector[i] * vector[i];
    }
    // finish finding the magnitude
    mag = sqrt(mag); 

    for (int i = 0; i < 3; i++)
    {
        //normalize the vector
        vector[i] /= mag; 
        //adjust the camera position
        CamState.Position[i] -= vector[i] * ZOOM_INC;
    }
    gluLookAt(CamState.Position[0], CamState.Position[1], CamState.Position[2],
        CamState.LookAt[0], CamState.LookAt[1], CamState.LookAt[2], 0, 0, 1); 
}

void ZoomOut()
{
    float vector[3];
    float mag = 0;
    for (int i = 0; i < 3; i++)
    {
        //initialize the vector we are along
        vector[i] = CamState.Position[i] - CamState.LookAt[i];
        //find the magnitude
        mag += vector[i] * vector[i];
    }
    // finish finding the magnitude
    mag = sqrt(mag);

    for (int i = 0; i < 3; i++)
    {
        //normalize the vector
        vector[i] /= mag;
        //adjust the camera position
        CamState.Position[i] += vector[i] * ZOOM_INC;
    }
    gluLookAt(CamState.Position[0], CamState.Position[1], CamState.Position[2],
        CamState.LookAt[0], CamState.LookAt[1], CamState.LookAt[2], 0, 0, 1);
}

void RotateUp()
{
    float vector[3];
    float mag = 0;
    for (int i = 0; i < 3; i++)
    {
        //initialize the vector we are along
        vector[i] = CamState.Position[i] - CamState.LookAt[i];
        //find the magnitude
        mag += vector[i] * vector[i];
    }
    // finish finding the magnitude
    mag = sqrt(mag);

    float angle = atan(vector[2] / vector[1]); 
    angle -= VERTICAL_ROTATE_INC; 

    CamState.Position[1] = CamState.LookAt[1] + mag * sin(angle); 
    CamState.Position[2] = CamState.LookAt[2] + mag * cos(angle); 

    gluLookAt(CamState.Position[0], CamState.Position[1], CamState.Position[2],
        CamState.LookAt[0], CamState.LookAt[1], CamState.LookAt[2], 0, 0, 1);
}

void RotateDown()
{
    float vector[3];
    float mag = 0;
    for (int i = 0; i < 3; i++)
    {
        //initialize the vector we are along
        vector[i] = CamState.Position[i] - CamState.LookAt[i];
        //find the magnitude
        mag += vector[i] * vector[i];
    }
    // finish finding the magnitude
    mag = sqrt(mag);

    float angle = atan(vector[2] / vector[1]);
    angle += VERTICAL_ROTATE_INC;

    CamState.Position[1] = CamState.LookAt[1] + mag * sin(angle);
    CamState.Position[2] = CamState.LookAt[2] + mag * cos(angle);

    gluLookAt(CamState.Position[0], CamState.Position[1], CamState.Position[2],
        CamState.LookAt[0], CamState.LookAt[1], CamState.LookAt[2], 0, 0, 1);
}

void PanLeft()
{
	CamState.Position[0] -= HORIZONTAL_PAN_INC;
	CamState.LookAt[0] -= HORIZONTAL_PAN_INC;
    gluLookAt(CamState.Position[0], CamState.Position[1], CamState.Position[2],
        CamState.LookAt[0], CamState.LookAt[1], CamState.LookAt[2], 0, 0, 1);
}

void PanRight()
{
	CamState.Position[0] += HORIZONTAL_PAN_INC;
	CamState.LookAt[0] += HORIZONTAL_PAN_INC;
    gluLookAt(CamState.Position[0], CamState.Position[1], CamState.Position[2],
        CamState.LookAt[0], CamState.LookAt[1], CamState.LookAt[2], 0, 0, 1);
}

void PanUp()
{
	CamState.Position[1] += VERTICAL_PAN_INC;
	CamState.LookAt[1] += VERTICAL_PAN_INC;
    gluLookAt(CamState.Position[0], CamState.Position[1], CamState.Position[2],
        CamState.LookAt[0], CamState.LookAt[1], CamState.LookAt[2], 0, 0, 1);
}

void PanDown()
{
	CamState.Position[1] -= VERTICAL_PAN_INC;
	CamState.Position[1] -= VERTICAL_PAN_INC;
    gluLookAt(CamState.Position[0], CamState.Position[1], CamState.Position[2],
        CamState.LookAt[0], CamState.LookAt[1], CamState.LookAt[2], 0, 0, 1);                 
}
