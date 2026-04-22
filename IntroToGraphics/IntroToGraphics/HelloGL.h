#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include "GLUTCallbacks.h"
#include "Structures.h"
#include "Planet.h"
#include "SceneNode.h"
#include "SceneGraph.h"

#define REFRESHRATE 16

class HelloGL
{
public:
	HelloGL(int argc, char* argv[]);

	~HelloGL(void);

	void Display();

	void Update();

	void DrawHUD();

	void DrawText(float x, float y, const char* text);

	int frameCount;
	float fps;
	int lastTime;

	SceneGraph* sceneGraph;

	static const int NUM_PLANETS = 9; // 8 planets + Moon

	Planet* planets[NUM_PLANETS];

	Mesh* sphereMesh;

	Texture* earthTex;

	Texture* jupiterTex;

	Texture* saturnTex;

	Texture* uranusTex;

	Texture* neptuneTex;

	Texture* marsTex;

	Texture* venusTex;

	Texture* mercuryTex;

	Texture* sunTex;

	Texture* moonTex;

	Planet* sun;

	// Camera
	float camX, camY, camZ;
	float camYaw, camPitch;
	int lastMouseX, lastMouseY;
	bool mouseDown;

	void Keyboard(unsigned char key, int x, int y);
	void MouseMotion(int x, int y);
	void MouseButton(int button, int state, int x, int y);

private:
	float rotation;
};