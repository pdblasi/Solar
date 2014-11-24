#ifndef __RING_H__
#define __RING_H__

#include "Planet.h"
#include "Structs.h"

class Ring : 
	public Planet
{
public:
	Ring();
	Ring(string name, float innerRadius, float outerRadius, float orbitDistance, float daysInYear, float dayRatio, float axis[3], float color[4], Planet* orbiting);
	~Ring();

	void Draw(ProgramState state);
	//void Update();

	//const float* GetPosition();
	//float GetRadius();
	//string GetName();

protected:
	float _outerRadius;
};

#endif

