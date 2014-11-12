#include "Planet.h"

Planet::Planet()
{
}

Planet::~Planet()
{
}

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
