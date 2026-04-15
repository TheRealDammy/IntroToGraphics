#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include "GLUTCallbacks.h"

#define REFRESHRATE 16

class HelloGL
{
public:
	HelloGL(int argc, char* argv[]);

	~HelloGL(void) = default;

	void Display();

	void Update();

private:
	float rotation;
};

