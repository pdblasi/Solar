#ifndef __PLANET_H__
#define __PLANET_H__

#include <string>
#include <cmath>

#include "Structs.h"

using namespace std;

class Planet
{
public:
	Planet(string name, float radius, float orbitDistance, float daysInYear, float dayRatio, double color[3], Planet* orbiting);
	~Planet();

	void Draw(ProgramState state);
	void Update();

	float* GetPosition();
	float GetRadius();
	float GetName();

private:
	string name;

	float _radius, _orbitDistance, _daysInYear, _dayRatio;
	float _position[3], _positionIncrements[3];
	float _rotationInc;

	double _color[3];

	Planet* _orbiting;
};

#endif

