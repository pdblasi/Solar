/************************************************************************//**
*  @file
*
*  @brief This file contains the header information for the ring class. 
*   The ring class is used to draw Saturn's rings, but uses much of the same
*   information that the planet class uses, which is why it is subclassed. 
*   The main difference between the ring class and the planet class is that 
*   the gluCylinder is used instead of a gluSphere. 
***************************************************************************/
#ifndef __RING_H__
#define __RING_H__

//includes 
#include "Planet.h"
#include "Structs.h"


/*!
* @brief The ring class draws rings using a quadric cylinder. 
*/
class Ring : 
	public Planet
{
public:
    /*!
    * @brief the default constructor for the ring class 
    */
	Ring();
    /*!
    * @brief the constructor for the ring class 
    */
	Ring(string name, float innerRadius, float outerRadius, float orbitDistance, float daysInYear, float dayRatio, float axis[3], float color[4], Planet* orbiting);
    /*!
    * @brief the destructor for the ring class 
    */
    ~Ring();


    /*!
    * @brief draws the planet in the current state 
    */
	void Draw(ProgramState state);
	//void Update();

	//const float* GetPosition();
	//float GetRadius();
	//string GetName();

protected:
    /*!
    * @brief the outer radius of the rings 
    */
	float _outerRadius;
    /*!
    * @brief the texture map for the rings 
    */
    TextureMap map; 
};

#endif

