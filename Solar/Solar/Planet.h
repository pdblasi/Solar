#ifndef __PLANET_H__
#define __PLANET_H__

#include <gl\freeglut.h>
#include <gl\GLU.h>
#include <string>
#include <cmath>
#include <vector>
#include "TextureMap.h"
#include "Structs.h"

using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Planet
{
public:
    //constructors and deconstructors 
	Planet();
	Planet(string name, float radius, float orbitDistance, float daysInYear, float dayRatio, float axis[3], float color[4], Planet* orbiting);
	~Planet();

    //draw functions 
	virtual void Draw(ProgramState state);
	virtual void Update();

    //used for parent child relations 
	const float* GetPosition();
	float GetRadius();
	string GetName();

    //creates the solar system 
	static void CreateSolarSystem(Planet* solarSystem[]);

protected:
	string _name; //name of the planet 
	GLUquadricObj* _planet; //object used to draw spheres
	TextureMap textureMap; //texture map for the class 

    //planet parameters
	float _radius, _orbitDistance, _daysInYear, _dayRatio;
	float _dayAngle, _rotationIncrement;
	float _orbitAngle, _orbitIncrement;
	float _position[3], _axis[3];

    //color of the planet 
	float _color[4];

    //what planet it is orbitting (if null it is the sun) 
	Planet* _orbiting;

    //scale the planet size and distance. 
	static float scaleDist(float dist);
	static float scaleSize(float radius);
};

#endif

