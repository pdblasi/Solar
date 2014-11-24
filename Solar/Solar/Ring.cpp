#include "Ring.h"

Ring::Ring()
{
}

Ring::Ring(string name, float innerRadius, float outerRadius, float orbitDistance, float daysInYear, float dayRatio, float axis[3], float color[4], Planet* orbiting)
{
	_planet = gluNewQuadric();

	_name = name;
	_radius = innerRadius;
	_outerRadius = outerRadius;

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

Ring::~Ring()
{
}

void Ring::Draw(ProgramState state)
{
	//Reset transformations
	glPushMatrix();

	//Set up color
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, _color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, _color);

	//Draw Orbital Path
	const float* orbitingPosition = _orbiting == NULL ? new float[]{ 0, 0, 0 } : (*_orbiting).GetPosition();
	glBegin(GL_POINTS);
	for (int i = 0; i < 360; i++)
	{
		float angle = float(i) / 180.0 * M_PI;
		float y = orbitingPosition[0] + _orbitDistance * cos(angle);
		float z = orbitingPosition[1] + _orbitDistance * sin(angle);
		glVertex3f(y, z, 0);
	}
	glEnd();

	//Draw the Label
	glRasterPos3f(_position[0], _position[1], _position[2] + 1.5 *_radius);
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	glutBitmapString(GLUT_BITMAP_HELVETICA_12, (const unsigned char*)_name.c_str());

	//Translate to position
	glTranslatef(_position[0], _position[1], _position[2]);

	//Rotate to proper axis
	//glRotatef(_axis[0], 1.0, 0.0, 0.0);
	//glRotatef(_axis[1], 0.0, 1.0, 0.0);
	//glRotatef(_axis[2], 0.0, 0.0, 1.0);

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
			gluQuadricDrawStyle(_planet, GLU_LINE);
		}
		else
		{
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
		gluCylinder(_planet, _outerRadius, _radius, 0, state.Resolution, state.Resolution);
	}

	glPopMatrix();
}
