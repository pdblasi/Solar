#include "Planet.h"

Planet::Planet(string name, float radius, float orbitDistance, float daysInYear, float dayRatio, float axis[3], double color[3], Planet* orbiting)
{
	_planet = gluNewQuadric(); 
	gluQuadricNormals(_planet, GLU_SMOOTH);
	gluQuadricTexture(_planet, GL_TRUE);

	_name = name;
	_radius = radius;
	_orbitDistance = orbitDistance;
	_daysInYear = daysInYear;
	_dayRatio = dayRatio;

	for (int i = 0; i < 3; i++)
		_axis[i] = axis[i];

	for (int i = 0; i < 3; i++)
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

vector<Planet> Planet::CreateSolarSystem()
{
	static vector<Planet> solarSystem;

	if (solarSystem.size() == 0)
	{
		solarSystem.push_back(Planet("Sun", 696000, 0, 0, 25, new float[]{0, 0, 1}, new double[]{1.0, 1.0, 0.0}, NULL));
	}

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
	glColor3dv(_color);

	//Reset transformations
    glPushMatrix();

	//Translate to position
	glTranslatef(_position[0], _position[1], _position[2]);

	//Rotate to proper axis
	glRotatef(_axis[0], 1.0, 0.0, 0.0);
	glRotatef(_axis[1], 0.0, 1.0, 0.0);
	glRotatef(_axis[2], 0.0, 0.0, 1.0);
		
	//Rotate along axis by day based increment
	glRotatef(_dayAngle, 0.0, 0.0, 1.0);

	if (state.Texture)
	{
		//Draw Textured object
	}
	else
	{
		if (state.Wireframe)
		{
			//Enable Wireframe
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			gluQuadricDrawStyle(_planet, GLU_LINE);
		}
		else
		{
			if (state.Flat)
			{
				//Enable flat shading
				glEnable(GL_FLAT);
			}
			else
			{
				//Enable smooth shading
				glEnable(GL_SMOOTH);
			}

			//Enable Polygon
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			gluQuadricDrawStyle(_planet, GLU_FILL);

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