/************************************************************************//**
*  @file
*
*  @brief The planet class definition. The planet class takes care of 
*   keeping the planet state, updates the planet as necessary, and draws the 
*   planet as necessary. 
***************************************************************************/

#ifndef __PLANET_H__
#define __PLANET_H__

//includes 
#include <GL/freeglut.h>
#include <GL/glu.h>
#include <string>
#include <cmath>
#include <vector>
#include "TextureMap.h"
#include "Structs.h"
using namespace std;

/*!
* @brief PI - the mathematical kind 
*/
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/*!
* @brief The planet class which takes care of keeping the state 
* of the planet and how to draw and update the planet. 
*/
class Planet
{
public:
    /*!
    * @brief the default constructor 
    */
	Planet();
    /*!
    * @brief the constructor for the planet class 
    */
	Planet(string name, float radius, float orbitDistance, float daysInYear, float dayRatio, float axis[3], float color[4], Planet* orbiting);
    /*!
    * @brief the destructor for the planet class 
    */
	~Planet();

    /*!
    * @brief draws the planet in its current state 
    */
	virtual void Draw(ProgramState state);
    /*!
    * @brief updates the position of the planet and rotation of its axis 
    */
	virtual void Update();

    /*!
    * @brief returns the position of the planet 
    */
	const float* GetPosition();
    /*!
    * @brief returns the radius of the planet 
    */
	float GetRadius();
    /*!
    * @brief returns the name of the planet 
    */
	string GetName();

    /*!
    * @brief creates the solar system 
    */
	static void CreateSolarSystem(Planet* solarSystem[]);

protected:
    /*!
    * @brief the name of the planet
    */
	string _name;
    /*!
    * @brief the glu object to draw the planet 
    */
	GLUquadricObj* _planet;
    /*!
    * @brief the texture map for the planet 
    */
	TextureMap textureMap;

    //planet parameters
    /*!
    * @brief the radius of the planet 
    */
    float _radius;
    /*!
    * @brief the distance from the object it is orbiting 
    */
    float _orbitDistance;
    /*!
    * @brief number of earth days in a year 
    */
    float _daysInYear;
    /*!
    * @brief number of earth days in a day 
    */
    float _dayRatio;
    /*!
    * @brief the angle the planet is at around its axis currently. 
    */
    float _dayAngle;
    /*!
    * @brief the angle that the planet turns on its axis per earth day 
    */
    float _rotationIncrement;
    /*!
    * @brief the angle around its orbitting planet currently 
    */
    float _orbitAngle;
    /*!
    * @brief the angle that the planet changes per earth day around its orbiting planet 
    */
    float _orbitIncrement;
    /*!
    * @brief the position of the planet in 3D coordinates 
    */
    float _position[3];
    /*!
    * @brief the vector that is the axis of rotation for the planet 
    */
    float _axis[3];

    /*!
    * @brief the color of the planet
    */
	float _color[4];

    /*!
    * @brief what planet this planet is orbitting (if NULL then the object is the sun)
    */
	Planet* _orbiting;

    /*!
    * @brief scales the distance between the planet it the planet it is rotating about 
    */
	static float scaleDist(float dist);
    /*!
    * @brief scales the size of the planet based on its actual size 
    */
	static float scaleSize(float radius);
};

#endif

