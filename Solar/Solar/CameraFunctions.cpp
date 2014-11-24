#include "CameraFunctions.h"
#include "math.h"

//global parameters  
CameraState CamState = CameraState();
float angle = atan(CamState.Position[1]/CamState.Position[2]); //the angle the camera is at 


/**************************************************************************//**
* @author Caitlin Taggart 
* 
* Description: Zooms the user in along the vector of their sight by using 
* the camer position and position they are looking at. 
*
*****************************************************************************/
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

/**************************************************************************//**
* @author Caitlin Taggart
*
* Description: Zooms the user out along the vector of their sight by using
* the camer position and position they are looking at.
*
*****************************************************************************/
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

/**************************************************************************//**
* @author Caitlin Taggart
*
* Description: Rotates the camera position up on the y - axis of the object the 
* camera is looking at 
*
*****************************************************************************/
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
    angle -= VERTICAL_ROTATE_INC; //increment the angle 

    if (angle < 0) //check if the angle has "overflowed" and change the up direction if necessary 
    {
        angle += float(2 * M_PI);
        CamState.Up[2] *= -1;
    }
    if (angle_before >= M_PI && angle < M_PI) //change the direction of up if we passed 180 degrees 
    {
        CamState.Up[2] *= -1;
    }

    //change the camera position 
    CamState.Position[1] = CamState.LookAt[1] + mag * sin(angle);
    CamState.Position[2] = CamState.LookAt[2] + mag * cos(angle);
}


/**************************************************************************//**
* @author Caitlin Taggart
*
* Description: Rotates the camera position down on the y - axis of the object the
* camera is looking at
*
*****************************************************************************/
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
    angle += VERTICAL_ROTATE_INC; //increment the angle 

    if (angle >  2 * M_PI) //check if the angle has "overflowed" and change the up direction if necessary 
    {
        angle -=  float(2 * M_PI); 
        CamState.Up[2] *= -1; 
    }
    if (angle_before <= M_PI && angle > M_PI) //change the up direction if past 180 degrees 
    {
        CamState.Up[2] *= -1; 
    }
    
    //check the camera position 
    CamState.Position[1] = CamState.LookAt[1] + mag * sin(angle);
    CamState.Position[2] = CamState.LookAt[2] + mag * cos(angle);


}

/**************************************************************************//**
* @author Caitlin Taggart
*
* Description: Pans the camera left by moving the position the camera is
* looking at and the camera position. 
*
*****************************************************************************/
void PanLeft()
{
    //move what you are looking at and the position of your camera
	CamState.Position[0] += HORIZONTAL_PAN_INC;
	CamState.LookAt[0] += HORIZONTAL_PAN_INC;
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* Description: Pans the camera right by moving the position the camera is
* looking at and the camera position.
*
*****************************************************************************/
void PanRight()
{
    //move what you are looking at and the position of your camera
	CamState.Position[0] -= HORIZONTAL_PAN_INC;
	CamState.LookAt[0] -= HORIZONTAL_PAN_INC;
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* Description: Pans the camera up by moving the position the camera is
* looking at and the camera position.
*
*****************************************************************************/
void PanUp()
{
    //move what you are looking at and the position of your camera
	CamState.Position[2] += VERTICAL_PAN_INC;
	CamState.LookAt[2] += VERTICAL_PAN_INC;
}

/**************************************************************************//**
* @author Caitlin Taggart
*
* Description: Pans the camera down by moving the position the camera is
* looking at and the camera position.
*
*****************************************************************************/
void PanDown()
{
    //move what you are looking at and the position of your camera
    CamState.Position[2] -= VERTICAL_PAN_INC;
    CamState.LookAt[2] -= VERTICAL_PAN_INC;
}
