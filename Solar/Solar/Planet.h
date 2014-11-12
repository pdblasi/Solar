#ifndef __PLANET_H__
#define __PLANET_H__

#include "Structs.h"

class Planet
{
public:
	Planet();
	~Planet();

	void Draw(ProgramState state);
	void Update();
};

#endif

