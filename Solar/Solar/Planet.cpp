#include "Planet.h"

Planet::Planet(string name, float radius, float orbitDistance, float daysInYear, float dayRatio, double color[3], Planet* orbiting)
{
}

Planet::~Planet()
{
}

vector<Planet> Planet::CreateSolarSystem()
{
	static vector<Planet> solarSystem;

	return solarSystem;
}

//vector<Planet> Planet::CreateTrueScaleSolarSystem()
//{
//	static vector<Planet> solarSystem;
//
//	return solarSystem;
//}

void Planet::Draw(ProgramState state)
{
	//Set up color

	if (state.Texture)
	{
		//Draw Textured object
	}
	else
	{
		if (state.Wireframe)
		{
			//Draw Wireframe object
		}
		else
		{
			if (state.Flat)
			{
				//Enable flat shading
			}
			else
			{
				//Enable smooth shading
			}

			//Draw polygon object
		}
	}
}

void Planet::Update()
{

}
