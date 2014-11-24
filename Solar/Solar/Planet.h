#ifndef __PLANET_H__
#define __PLANET_H__

#include <gl\freeglut.h>
#include <gl\GLU.h>
#include <string>
#include <cmath>
#include <vector>

#include "Structs.h"

using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Planet
{
public:
	Planet();
	Planet(string name, float radius, float orbitDistance, float daysInYear, float dayRatio, float axis[3], float color[4], Planet* orbiting);
	~Planet();

	void Draw(ProgramState state);
	void Update();

	const float* GetPosition();
	float GetRadius();
	string GetName();

	static void CreateSolarSystem(Planet solarSystem[]);
	//static vector<Planet> CreateTrueScaleSolarSystem();

protected:
	string _name;
	GLUquadricObj* _planet;

	float _radius, _orbitDistance, _daysInYear, _dayRatio;
	float _dayAngle, _rotationIncrement;
	float _orbitAngle, _orbitIncrement;
	float _position[3], _axis[3];

	float _color[4];

	Planet* _orbiting;

	static float scaleDist(float dist);
	static float scaleSize(float radius);
};

#endif

