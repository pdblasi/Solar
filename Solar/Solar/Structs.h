#ifndef __STRUCTS_H__
#define __STRUCTS_H__


/**************************************************************************//**
* @author Paul Blasi
*
* Description: Handles the program state. Including whethere wireframe or 
* solid objects are used, whether flat or smooth shading is used, if texture 
* mapping is on or off, and if the program is paused (taking single steps) or 
* animating. This also includes the resolution of the wireframe models, and 
* the time between animations (since this can change if the user speeds up, or 
* slows down the animation). Also determines what frame the user is on.
*
*****************************************************************************/
struct ProgramState
{
    /*!
    * @brief wireframe or solid object should be used 
    */
    bool Wireframe;
    /*!
    * @brief whether flat or smooth shading should be used 
    */
    bool Flat;
    /*!
    * @brief flag for if texture mapping is on or off 
    */
    bool Texture;
    /*!
    * @brief determines if the program is paused or not 
    */
    bool Paused;
    /*!
    * @brief determines the resolution of the wireframe
    */
	int Resolution; 
    /*!
    * @brief determins the amount of time between animation and updates 
    */
	unsigned int AnimTime;
    /*!
    * @brief what frame the program is currently on
    */
	int Frame;

    /**************************************************************************//**
    * @author Paul Blasi
    *
    * Description: Initializes the program state to have wireframe models of the 
    * spheres and flat shading. Also the program starts with texture off and not
    * paused. The animation time starts at one frame every 30 miliseconds, and 
    * starts on frame 1. 
    *
    *****************************************************************************/
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
    /*!
    * @brief the position of the camera 
    */
    float Position[3];
    /*!
    * @brief the position the camera is looking at 
    */
    float LookAt[3];
    /*!
    * @brief the direction of up
    */
    float Up[3];

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