#ifndef __STRUCTS_H__
#define __STRUCTS_H__

struct ProgramState
{
	bool Wireframe, Flat, Texture, Paused;
	double Resolution;
	int AnimTime;
	long long Frame;

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
};

#endif