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

	~HelloGL(void);

	void Display();

	void DrawPolygon();

	void DrawPolygon2();

	void DrawPolygon3();

	void DrawPolygon4();

	void Update();

private:
	float rotation;
};

