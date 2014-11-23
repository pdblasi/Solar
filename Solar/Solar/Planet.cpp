#include "Planet.h"

float Planet::scaleDist(float dist)
{
	//Moons and rings
	if (dist < 58)
	{
		return dist * 100000;
	}
	//Planets
	else
	{
		//Normalizes the distances from the distance to mercury to
		//five times the distance of mars
		return (((dist - 58) * 1082 / 4434) + 58) * 10000 - 69600;
	}
}

float Planet::scaleSize(float size)
{
	//Inner planets and moons
	if (size < 10000)
	{
		return size * 2;
	}
	//Ice Giants
	else if (size < 30000)
	{
		return size;
	}
	//Gas Giants
	else if (size < 100000)
	{
		return size / 2;
	}
	//Stars
	else
	{
		return size / 10;
	}
}

Planet::Planet()
{

}

Planet::Planet(string name, float radius, float orbitDistance, float daysInYear, float dayRatio, float axis[3], float color[4], Planet* orbiting)
{
	_planet = gluNewQuadric();

	_name = name;
	_radius = radius;
	_orbitDistance = orbitDistance;
	_daysInYear = daysInYear;
	_dayRatio = dayRatio;

	for (int i = 0; i < 3; i++)
		_axis[i] = axis[i];

	for (int i = 0; i < 4; i++)
		_color[i] = color[i];

	_orbiting = orbiting;
	if (_orbiting == NULL)
	{
		for (int i = 0; i < 3; i++)
			_position[i] = 0;
	}
	else
	{
		_position[0] = (*orbiting).GetPosition()[0] + _orbitDistance;
		_position[1] = 0;
		_position[2] = 0;
	}

	_orbitAngle = _dayAngle = 0; 
	_orbitIncrement = (float)(2 * M_PI / _daysInYear);
	_rotationIncrement = (float)(2 * M_PI / _dayRatio);
}

Planet::~Planet()
{
}

void Planet::CreateSolarSystem(Planet solarSystem[])
{
	solarSystem[0] = Planet("Sun", scaleSize(696000), 0, 0, 25, new float[]{0, 0, 1}, new float[]{1.0, 1.0, 0.0, 1.0}, NULL);

	solarSystem[1] = Planet("Mercury", scaleSize(2439), scaleDist(58), 88, 1416, new float[]{0, 0, 1}, new float[]{1.0, 0.0, 0.0, 1.0}, &solarSystem[0]);
	solarSystem[2] = Planet("Venus", scaleSize(6052), scaleDist(108), 225, 5832, new float[]{0, 0, 1}, new float[]{0.0, 1.0, 0.0, 1.0}, &solarSystem[0]);
	solarSystem[3] = Planet("Earth", scaleSize(6378), scaleDist(150), 365, 24, new float[]{0, 0, 1}, new float[]{0.0, 0.0, 1.0, 1.0}, &solarSystem[0]);
	solarSystem[4] = Planet("Mars", scaleSize(3394), scaleDist(228), 687, 24.6, new float[]{0, 0, 1}, new float[]{1.0, 0.0, 1.0, 1.0}, &solarSystem[0]);
	solarSystem[5] = Planet("Jupiter", scaleSize(71398), scaleDist(779), 4332, 9.8, new float[]{0, 0, 1}, new float[]{1.0, 1.0, 1.0, 1.0}, &solarSystem[0]);
	solarSystem[6] = Planet("Saturn", scaleSize(60270), scaleDist(1424), 10761, 10.2, new float[]{0, 0, 1}, new float[]{0.0, 1.0, 1.0, 1.0}, &solarSystem[0]);
	solarSystem[7] = Planet("Uranus", scaleSize(25550), scaleDist(2867), 30682, 15.5, new float[]{0, 0, 1}, new float[]{1.0, 1.0, 0.0, 1.0}, &solarSystem[0]);
	solarSystem[8] = Planet("Neptune", scaleSize(24750), scaleDist(4492), 60195, 15.8, new float[]{0, 0, 1}, new float[]{1.0, 1.0, 0.0, 1.0}, &solarSystem[0]);

	solarSystem[9] = Planet("Moon", scaleSize(1738), scaleDist(.384), 27.3, 27.3, new float[]{0, 0, 1}, new float[]{1, 1, 1, 1.0}, &solarSystem[3]);
}

//vector<Planet> Planet::CreateTrueScaleSolarSystem()
//{
//	solarSystem[0] = Planet("Sun", 696000, 0, 0, 25, new float[]{0, 0, 1}, new double[]{1.0, 1.0, 0.0}, NULL);
//
//	solarSystem[1] = Planet("Mercury", 2439, 580000, 88, 1416, new float[]{0, 0, 1}, new double[]{1.0, 0.0, 0.0}, &solarSystem[0]);
//	solarSystem[2] = Planet("Venus", 6052, 1080000, 225, 5832, new float[]{0, 0, 1}, new double[]{0.0, 1.0, 0.0}, &solarSystem[0]);
//	solarSystem[3] = Planet("Earth", 6378, 1500000, 365, 24, new float[]{0, 0, 1}, new double[]{0.0, 0.0, 1.0}, &solarSystem[0]);
//	solarSystem[4] = Planet("Mars", 3394, 2280000, 687, 24.6, new float[]{0, 0, 1}, new double[]{1.0, 0.0, 1.0}, &solarSystem[0]);
//	solarSystem[5] = Planet("Jupiter", 71398, 7790000, 4332, 9.8, new float[]{0, 0, 1}, new double[]{1.0, 1.0, 1.0}, &solarSystem[0]);
//	solarSystem[6] = Planet("Saturn", 60270, 14240000, 10761, 10.2, new float[]{0, 0, 1}, new double[]{0.0, 1.0, 1.0}, &solarSystem[0]);
//	solarSystem[7] = Planet("Uranus", 25550, 28670000, 30682, 15.5, new float[]{0, 0, 1}, new double[]{1.0, 1.0, 0.0}, &solarSystem[0]);
//	solarSystem[8] = Planet("Neptune", 24750, 44920000, 60195, 15.8, new float[]{0, 0, 1}, new double[]{1.0, 1.0, 0.0}, &solarSystem[0]);
//}

void Planet::Draw(ProgramState state)
{
	//Set up color

	//Reset transformations
    glPushMatrix();

	//Translate to position
	glTranslatef(_position[0], _position[1], _position[2]);

	//Rotate to proper axis
	//glRotatef(_axis[0], 1.0, 0.0, 0.0);
	//glRotatef(_axis[1], 0.0, 1.0, 0.0);
	//glRotatef(_axis[2], 0.0, 0.0, 1.0);

	//Rotate to proper vertical orientation
	//glRotatef(M_PI / 2, 1.0, 0.0, 0.0);
		
	//Rotate along axis by day based increment
	glRotatef(_dayAngle, _axis[0], _axis[1], _axis[2]);


	if (state.Texture)
	{
		//Draw Textured object
	}
	else
	{

		if (state.Wireframe)
		{
			//Enable Wireframe
			glColor4fv(_color);
			gluQuadricDrawStyle(_planet, GLU_LINE);
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
		{
			glMaterialfv(GL_FRONT, GL_DIFFUSE, _color);
			glMaterialfv(GL_FRONT, GL_AMBIENT, _color);
			gluQuadricDrawStyle(_planet, GLU_FILL);

			if (state.Flat)
			{
				//Enable flat shading
				gluQuadricNormals(_planet, GLU_FLAT);
			}
			else
			{
				//Enable smooth shading
				gluQuadricNormals(_planet, GLU_SMOOTH);
			}
		}

		//Draw Object
		gluSphere(_planet, _radius, state.Resolution, state.Resolution);
	}

    glPopMatrix();
}

void Planet::Update()
{
	_dayAngle = _dayAngle + _rotationIncrement;// (float)(2 * M_PI);

	if (_orbiting == NULL)
	{
		return;
	}

	_orbitAngle = fmodf(_orbitAngle + _orbitIncrement, (float)(2 * M_PI));

	const float* orbitingPosition = (*_orbiting).GetPosition();

	_position[0] = orbitingPosition[0] + _orbitDistance * cos(_orbitAngle);
	_position[1] = orbitingPosition[1] + _orbitDistance * sin(_orbitAngle);
}

const float* Planet::GetPosition()
{
	return _position;
}

float Planet::GetRadius()
{
	return _radius;
}

string Planet::GetName()
{
	return _name;
}