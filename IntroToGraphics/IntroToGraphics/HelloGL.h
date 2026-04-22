#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include "GLUTCallbacks.h"
#include "Structures.h"
#include "Planet.h"
#include "SceneNode.h"

#define REFRESHRATE 16

class HelloGL
{
public:
	HelloGL(int argc, char* argv[]);

	~HelloGL(void);

	void Display();

	void Update();

	static const int NUM_PLANETS = 9; // 8 planets + Moon

	Planet* planets[NUM_PLANETS];

	Mesh* sphereMesh;

	Texture* sharedTex;

	Texture* sunTex;

	SceneNode* sun;

private:
	float rotation;
};

