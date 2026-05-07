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
#include "Camera.h"

#define REFRESHRATE 16 // target milliseconds between frames (~60 FPS)

// Header for main application class that owns scene, camera, and input handling.
class HelloGL
{
public:
	HelloGL(int argc, char* argv[]);

	~HelloGL(void);

	// Rendering entry point called each frame
	void Display();

	// Update simulation step called from timer
	void Update();

	// HUD / overlay drawing
	void DrawHUD();

	// Draw background stars
	void DrawStarfield();

	// Helper to render bitmap text
	void DrawText(float x, float y, const char* text);

	// Simple FPS tracking variables
	int frameCount;
	float fps;
	int lastTime;
	float simSpeed = 1.0f;

	// Planet selection and tracking
	int selectedPlanet;
	bool trackingMode;

	// Scene graph root manager
	SceneGraph* sceneGraph;

	static const int NUM_PLANETS = 9;

	// Planet pointers (array indexed 0..7 for planets, optionally a null slot)
	Planet* planets[NUM_PLANETS];

	// Shared mesh for spheres and per-planet textures
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

	// Camera state (position + orientation)
	Camera* camera;
	int lastMouseX, lastMouseY;
	bool mouseDown;

	// Input handlers invoked via GLUTCallbacks wrapper
	void Keyboard(unsigned char key, int x, int y);
	void MouseMotion(int x, int y);
	void MouseButton(int button, int state, int x, int y);

private:
	float rotation;
};