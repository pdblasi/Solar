/************************************************************************//**
*  @file
*
*  @brief The planet class implementation. The planet class takes care of 
*   keeping the planet state, updates the planet as necessary, and draws the 
*   planet as necessary. 
***************************************************************************/

//includes 
#include "Planet.h"
#include "Ring.h"

/**************************************************************************//**
* @author Paul Blasi 
*
* Description: scales the distance between the planets, so that planets are 
* not (extremely) far away from each other
* 
* @param dist - the distance between the planet it is orbiting and the planet 
*   itself 
* 
* @return the new distance between the planet it is orbiting and the planet
*   itself 
*
*****************************************************************************/
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

/**************************************************************************//**
* @author Paul Blasi 
*
* Description: scales the size of the planet to not be too big or too small 
* 
* @param size - the radius of the planet 
* @return the new radius of the planet 
*
*****************************************************************************/
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

/**************************************************************************//**
* @author Paul Blasi 
*
* Description: the empty constructor for the planet class 
*
*****************************************************************************/
Planet::Planet()
{

}

/**************************************************************************//**
* @author Paul Blasi and Caitlin Taggart 
*
* Description: the constructor for the planet class. Initializes the quadric 
* used to draw the planet, the name, radius, orbit distance, day in year, earth
* days in day the axis the planet turns on, the color of the planet, the planet 
* it is orbiting, the initial position of the planet, and the texture map for
* the planet. 
*
*****************************************************************************/
Planet::Planet(string name, float radius, float orbitDistance, float daysInYear, float dayRatio, float axis[3], float color[4], Planet* orbiting)
{
    //create a new quadric object 
	_planet = gluNewQuadric();

    //set the passed in parameters 
	_name = name;
	_radius = radius;
	_orbitDistance = orbitDistance;
	_daysInYear = daysInYear;
	_dayRatio = dayRatio;

    //set the axis it turns on 
	for (int i = 0; i < 3; i++)
		_axis[i] = axis[i];

    //set the color of the object 
	for (int i = 0; i < 4; i++)
		_color[i] = color[i];

    //set what planet it is orbiting and its position based upon that.
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

    //set the initial angles 
	_orbitAngle = _dayAngle = 0; 
    //set the angle it travels per day 
	_orbitIncrement = (float)(2 * M_PI / _daysInYear);
	_rotationIncrement = (float)(2 * M_PI / _dayRatio);

    //set up the texture map for the planet 
    textureMap = TextureMap((_name + ".bmp").c_str(), _planet);
}


/**************************************************************************//**
* @author Paul Blasi 
*
* Description: the destructor for the planet class 
*
*****************************************************************************/
Planet::~Planet()
{
}

/**************************************************************************//**
* @author Paul Blasi 
*
* Description: creates the planets in the solar system
* 
* @param solarSystem - the list of planets in the solar system 
*
*****************************************************************************/
void Planet::CreateSolarSystem(Planet* solarSystem[])
{
    //create the solor system objects 
	solarSystem[0] = new Planet("Sun", scaleSize(696000), 0, 0, 25, new float[3]{0, 0, 1}, new float[4]{1.0, 1.0, 0.0, 1.0}, NULL);

	solarSystem[1] = new Planet("Mercury", scaleSize(2439), scaleDist(58), 88, 1416, new float[3]{0, 0, 1}, new float[4]{1.0, 0.0, 0.0, 1.0}, solarSystem[0]);
	solarSystem[2] = new Planet("Venus", scaleSize(6052), scaleDist(108), 225, 5832, new float[3]{0, 0, 1}, new float[4]{0.0, 1.0, 0.0, 1.0}, solarSystem[0]);
	solarSystem[3] = new Planet("Earth", scaleSize(6378), scaleDist(150), 365, 24, new float[3]{0, 0, 1}, new float[4]{0.0, 0.0, 1.0, 1.0}, solarSystem[0]);
	solarSystem[4] = new Planet("Mars", scaleSize(3394), scaleDist(228), 687, 24.6, new float[3]{0, 0, 1}, new float[4]{1.0, 0.0, 1.0, 1.0}, solarSystem[0]);
	solarSystem[5] = new Planet("Jupiter", scaleSize(71398), scaleDist(779), 4332, 9.8, new float[3]{0, 0, 1}, new float[4]{1.0, 1.0, 1.0, 1.0}, solarSystem[0]);
	solarSystem[6] = new Planet("Saturn", scaleSize(60270), scaleDist(1424), 10761, 10.2, new float[3]{0, 0, 1}, new float[4]{0.0, 1.0, 1.0, 1.0}, solarSystem[0]);
	solarSystem[7] = new Planet("Uranus", scaleSize(25550), scaleDist(2867), 30682, 15.5, new float[3]{0, 0, 1}, new float[4]{1.0, 1.0, 0.0, 1.0}, solarSystem[0]);
	solarSystem[8] = new Planet("Neptune", scaleSize(24750), scaleDist(4492), 60195, 15.8, new float[3]{0, 0, 1}, new float[4]{1.0, 1.0, 0.0, 1.0}, solarSystem[0]);

	solarSystem[9] = new Planet("Moon", scaleSize(1738), scaleDist(.384), 27.3, 27.3, new float[3]{0, 0, 1}, new float[4]{1, 1, 1, 1.0}, solarSystem[3]);
	solarSystem[10] = new Ring("Saturn' Rings", 90000, 140000, 0, 10761, 10.2, new float[3]{0, 0, 1}, new float[4]{0.0, 1.0, 1.0, 1.0}, solarSystem[6]);
}

/**************************************************************************//**
* @author Paul Blasi 
*
* Description: Draws the planet in the given state by setting up the material
* properties, drawing the orbital path drawing the label, rotating as needed 
* for the day, and drawing the planet in the given state (wireframe or not, 
* smooth or flat shading, texture mapping or not). 
* 
* @param state - the state of the program to draw the planet in 
*
*****************************************************************************/
void Planet::Draw(ProgramState state)
{
	//Set up color
	glMaterialfv(GL_FRONT, GL_DIFFUSE, _color);
	glMaterialfv(GL_FRONT, GL_AMBIENT, _color);

    //Draw Orbital Path
    const float* orbitingPosition = _orbiting == NULL ? new float[3]{ 0, 0, 0 } : (*_orbiting).GetPosition();
    glBegin(GL_POINTS);
    for (int i = 0; i < 360; i++)
    {
        float angle = float(i) / 180.0 * M_PI;
        float y = orbitingPosition[0] + _orbitDistance * cos(angle);
        float z = orbitingPosition[1] + _orbitDistance * sin(angle);
        glVertex3f(y, z, 0);
    }
        glEnd();

    //Reset transformations
    glPushMatrix();

    //Draw the Label
    glRasterPos3f(_position[0], _position[1], _position[2] + 1.5 *_radius); 
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
    glutBitmapString(GLUT_BITMAP_HELVETICA_12, (const unsigned char*)_name.c_str());

	//Translate to position
	glTranslatef(_position[0], _position[1], _position[2]);

		
	//Rotate along axis by day based increment
	glRotatef(_dayAngle, _axis[0], _axis[1], _axis[2]);

	if (state.Texture)
	{
        //draw the planet using the texture map for the planet 
        glEnable(GL_TEXTURE_2D); 
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
        glBindTexture(GL_TEXTURE_2D, textureMap.Texture);
        gluSphere(_planet, _radius, 100, 100);
        glDisable(GL_TEXTURE_2D); 
	}
	else
	{
		if (state.Wireframe)
		{
			glEnable(GL_COLOR_MATERIAL);
			//Enable Wireframe
			glColor4fv(_color);
			gluQuadricDrawStyle(_planet, GLU_LINE);
		}
		else
		{
			glDisable(GL_COLOR_MATERIAL);
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

    //reset the matric 
    glPopMatrix();
}

/**************************************************************************//**
* @author Paul Blasi 
*
* Description: updates the position of the planet including the position 
* around the planet it is orbiting, and amount it is tilted according to its
* day. 
*
*****************************************************************************/
void Planet::Update()
{
    //increment the amount the planet is rotated after a day 
	_dayAngle = _dayAngle + _rotationIncrement;

    //if it is the sun do not continue 
	if (_orbiting == NULL)
	{
		return;
	}

    //move the planet along its orbit path 
	_orbitAngle = fmodf(_orbitAngle + _orbitIncrement, (float)(2 * M_PI));

    //the position of the planet this planet is orbitting 
	const float* orbitingPosition = (*_orbiting).GetPosition();

    //update the position based upon the orbit angle 
	_position[0] = orbitingPosition[0] + _orbitDistance * cos(_orbitAngle);
	_position[1] = orbitingPosition[1] + _orbitDistance * sin(_orbitAngle);
}

/**************************************************************************//**
* @author Paul Blasi 
*
* Description: Returns the current position of the planet
* 
* @return the (x, y, z) coordinate of position of the planet 
*
*****************************************************************************/
const float* Planet::GetPosition()
{
    //returns the position of this planet 
	return _position;
}

/**************************************************************************//**
* @author Paul Blasi 
*
* Description: Getter for the radius of the planet 
* 
* @return the radius of the planet 
*
*****************************************************************************/
float Planet::GetRadius()
{
    //returns the radius of this planet 
	return _radius;
}

/**************************************************************************//**
* @author Paul Blasi 
*
* Description: Getter for the name of the planet 
* 
* @return the name of the planet  
*
*****************************************************************************/
string Planet::GetName()
{
    //returns the name of this planet 
	return _name;
}
