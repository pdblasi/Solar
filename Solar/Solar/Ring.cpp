/************************************************************************//**
*  @file
*
*  @brief This file contains the implementation for the ring class. 
*   The ring class is used to draw Saturn's rings, but uses much of the same
*   information that the planet class uses, which is why it is subclassed. 
*   The main difference between the ring class and the planet class is that 
*   the gluCylinder is used instead of a gluSphere. 
***************************************************************************/

#include "Ring.h"

/**************************************************************************//**
* @author Paul Blasi and Caitlin Taggart 
*
* Description: the default constructor for the ring class 
*
*****************************************************************************/
Ring::Ring()
{
}

/**************************************************************************//**
* @author Paul Blasi and Caitlin Taggart 
*
* Description: the constructor for the ring class. Initializes the quadric 
* used to draw the ring, the name, radius, orbit distance, day in year, earth
* days in day the axis the ring turns on, the color of the ring, the planet 
* it is orbiting, the initial position of the ring, and the texture map for
* the ring. 
*
*****************************************************************************/
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

    map = TextureMap("SaturnRings.bmp ", _planet); 
}

/**************************************************************************//**
* @author Paul Blasi and Caitlin Taggart 
*
* Description: the default destructor for the ring class 
*
*****************************************************************************/
Ring::~Ring()
{
}

/**************************************************************************//**
* @author Paul Blasi and Caitlin Taggart
*
* Description: Draws the ring in the given state by setting up the material
* properties, drawing the orbital path drawing the label, rotating as needed 
* for the day, and drawing the ring in the given state (wireframe or not, 
* smooth or flat shading, texture mapping or not). 
* 
* @param state - the state of the program to draw the ring in 
*
*****************************************************************************/
void Ring::Draw(ProgramState state)
{
	//Reset transformations
	glPushMatrix();

	//Set up color
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, _color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, _color);

	//Translate to position
	glTranslatef(_position[0], _position[1], _position[2]);

	//Rotate along axis by day based increment
	glRotatef(_dayAngle, _axis[0], _axis[1], _axis[2]);

	if (state.Texture)
	{
		//Draw Textured object
        glEnable(GL_TEXTURE_2D);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
        glBindTexture(GL_TEXTURE_2D, map.Texture);
        gluCylinder(_planet, _radius, _outerRadius, 0, 30, 30); 
        glDisable(GL_TEXTURE_2D);
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
