#ifndef __STRUCTS_H__
#define __STRUCTS_H__

struct ProgramState
{
	bool Wireframe, Flat, Texture, Paused;
	int Resolution; 
	unsigned int AnimTime;
	int Frame;

	ProgramState()
	{
		Wireframe = Flat = true;
		Texture = Paused = false;
		Resolution = 10;
		AnimTime = 30;
		Frame = 1;
	}
};


/**************************************************************************//**
* @author Caitlin Taggart and Paul Blasi 
*
* Description: Structure that stores the camera state - position, look at, and 
* up vector. 
*
*****************************************************************************/
struct CameraState
{
    //the position of the camera, what the camera is looking at, and what direction is up 
    float Position[3], LookAt[3], Up[3]; 

/**************************************************************************//**
* @author Paul Blasi and Caitlin Taggart 
*
* Description: Constructor for the Camera State structure. Initializes the 
* position the "camera" is looking at and the position of the "camera" and 
* the up direction for the camera. 
*
*****************************************************************************/
	CameraState()
	{
        //star looking at the sun 
		for (int i = 0; i < 3; i++)
			LookAt[i] = 0;

        //have the camera start at this position 
		Position[0] = 0;
		Position[2] = 1110000;
		Position[1] = 431000;

        //star with up in the z direction 
        Up[0] = 0; 
        Up[1] = 0; 
        Up[2] = 1; 
	}
};

#endif