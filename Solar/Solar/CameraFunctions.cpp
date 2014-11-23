#include "CameraFunctions.h"
#include "math.h"

CameraState CamState = CameraState();
float angle = M_PI / 2; 

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

    double angle_before = angle;
    angle -= VERTICAL_ROTATE_INC;
    if (angle < 0)
    {
        angle += 2 * M_PI;
        CamState.Up[2] *= -1;
    }
    if (angle_before >= M_PI && angle < M_PI)
    {
        CamState.Up[2] *= -1;
    }

    CamState.Position[1] = CamState.LookAt[1] + mag * sin(angle);
    CamState.Position[2] = CamState.LookAt[2] + mag * cos(angle);
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
 
    double angle_before = angle; 
    angle += VERTICAL_ROTATE_INC; 
    if (angle >  2 * M_PI)
    {
        angle -=  2 * M_PI;
        CamState.Up[2] *= -1; 
    }
    if (angle_before <= M_PI && angle > M_PI)
    {
        CamState.Up[2] *= -1; 
    }
    
    CamState.Position[1] = CamState.LookAt[1] + mag * sin(angle);
    CamState.Position[2] = CamState.LookAt[2] + mag * cos(angle);


}

void PanLeft()
{
	CamState.Position[0] += HORIZONTAL_PAN_INC;
	CamState.LookAt[0] += HORIZONTAL_PAN_INC;
}

void PanRight()
{
	CamState.Position[0] -= HORIZONTAL_PAN_INC;
	CamState.LookAt[0] -= HORIZONTAL_PAN_INC;
}

void PanUp()
{
	CamState.Position[1] += VERTICAL_PAN_INC;
	CamState.LookAt[1] += VERTICAL_PAN_INC;
}

void PanDown()
{
    CamState.Position[1] -= VERTICAL_PAN_INC;
    CamState.LookAt[1] -= VERTICAL_PAN_INC;
}
