#ifndef __STRUCTS_H__
#define __STRUCTS_H__

struct ProgramState
{
	bool Wireframe, Flat, Texture, Paused;
	int Resolution;
	unsigned int AnimTime;
	int Frame;

	ProgramState()
	{
		Wireframe = Flat = true;
		Texture = Paused = false;
		Resolution = 30;
		AnimTime = 30;
		Frame = 1;
	}
};

struct CameraState
{
	float Position[3], LookAt[3];

	CameraState()
	{
		for (int i = 0; i < 3; i++)
			LookAt[i] = 0;

		Position[0] = 0;
		Position[1] = -1;
		Position[2] = 0;
	}
};

#endif