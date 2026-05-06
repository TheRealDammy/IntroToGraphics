#include "HelloGL.h"
#include "ObjLoader.h"
#include "TextureManager.h"
#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>

// Main application class implementation for the simple solar system.
// Responsible for initializing GLUT, loading assets, maintaining camera state,
// handling input, and delegating update/draw to the scene graph.
HelloGL::HelloGL(int argc, char* argv[])
{
	// Initial camera placement and orientation
	camX = 0.0f; camY = 150.0f; camZ = 280.0f;
	camYaw = 0.0f; camPitch = -0.5f;
	mouseDown = false;
	selectedPlanet = -1;
	trackingMode = false;

	// Initialize GLUT callback wrapper and create window/context
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Solar System Simulation - GDEV40026");

	// Register callbacks for display, timing and input
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(0, GLUTCallbacks::Timer, REFRESHRATE);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glutMotionFunc(GLUTCallbacks::MouseMotion);
	glutMouseFunc(GLUTCallbacks::MouseButton);

	// Basic GL state
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Load basic sphere mesh used for planets. If this fails we exit early.
	sphereMesh = ObjLoader::Load("OBJs\\Sphere.obj");
	if (sphereMesh == nullptr)
	{
		std::cerr << "HelloGL: Failed to load mesh. Check path and file existence.\n";
		exit(EXIT_FAILURE);
	}

	// Load textures for planets and sun.
	// Each texture load is validated (texture.id != 0) and will exit on failure.
	Texture earthtex = TextureManager::LoadTexture("OBJs\\Textures\\Earth.bmp");
	if (earthtex.id == 0)
	{
		std::cerr << "HelloGL: Failed to load texture (texture id == 0). Check path, file format and expected dimensions.\n";
		exit(EXIT_FAILURE);
	}
	earthTex = new Texture(earthtex);

	Texture mercurytex = TextureManager::LoadTexture("OBJs\\Textures\\Mercury.bmp");
	if (mercurytex.id == 0)
	{
		std::cerr << "HelloGL: Failed to load texture (texture id == 0). Check path, file format and expected dimensions.\n";
		exit(EXIT_FAILURE);
	}
	mercuryTex = new Texture(mercurytex);

	Texture venustex = TextureManager::LoadTexture("OBJs\\Textures\\Venus.bmp");
	if (venustex.id == 0)
	{
		std::cerr << "HelloGL: Failed to load texture (texture id == 0). Check path, file format and expected dimensions.\n";
		exit(EXIT_FAILURE);
	}
	venusTex = new Texture(venustex);

	Texture marstex = TextureManager::LoadTexture("OBJs\\Textures\\Mars.bmp");
	if (marstex.id == 0)
	{
		std::cerr << "HelloGL: Failed to load texture (texture id == 0). Check path, file format and expected dimensions.\n";
		exit(EXIT_FAILURE);
	}
	marsTex = new Texture(marstex);

	Texture jupitertex = TextureManager::LoadTexture("OBJs\\Textures\\Jupiter.bmp");
	if (jupitertex.id == 0)
	{
		std::cerr << "HelloGL: Failed to load texture (texture id == 0). Check path, file format and expected dimensions.\n";
		exit(EXIT_FAILURE);
	}
	jupiterTex = new Texture(jupitertex);

	Texture saturntex = TextureManager::LoadTexture("OBJs\\Textures\\Saturn.bmp");
	if (saturntex.id == 0)
	{
		std::cerr << "HelloGL: Failed to load texture (texture id == 0). Check path, file format and expected dimensions.\n";
		exit(EXIT_FAILURE);
	}
	saturnTex = new Texture(saturntex);

	Texture uranustex = TextureManager::LoadTexture("OBJs\\Textures\\Uranus.bmp");
	if (uranustex.id == 0)
	{
		std::cerr << "HelloGL: Failed to load texture (texture id == 0). Check path, file format and expected dimensions.\n";
		exit(EXIT_FAILURE);
	}
	uranusTex = new Texture(uranustex);

	Texture neptunetex = TextureManager::LoadTexture("OBJs\\Textures\\Neptune.bmp");
	if (neptunetex.id == 0)
	{
		std::cerr << "HelloGL: Failed to load texture (texture id == 0). Check path, file format and expected dimensions.\n";
		exit(EXIT_FAILURE);
	}
	neptuneTex = new Texture(neptunetex);

	// Create planet objects with simple parameters: size, distance, rotation speed, mesh, texture.
	// Note: orbits are simplified (circular) and not to scale on purpose for clarity/performance.
	planets[0] = new Planet(3.0f, 25.0f, 87.0f, sphereMesh, mercuryTex, 0.0f, 7.0f);  // Mercury
	planets[1] = new Planet(4.5f, 40.0f, 62.0f, sphereMesh, venusTex, 45.0f, 3.4f);  // Venus
	planets[2] = new Planet(5.0f, 58.0f, 50.0f, sphereMesh, earthTex, 90.0f, 0.0f);  // Earth
	planets[3] = new Planet(3.5f, 76.0f, 40.0f, sphereMesh, marsTex, 135.0f, 1.9f);  // Mars
	planets[4] = new Planet(9.0f, 100.0f, 25.0f, sphereMesh, jupiterTex, 180.0f, 1.3f);  // Jupiter
	planets[5] = new Planet(7.5f, 128.0f, 20.0f, sphereMesh, saturnTex, 225.0f, 2.5f);  // Saturn
	planets[6] = new Planet(6.5f, 155.0f, 14.0f, sphereMesh, uranusTex, 270.0f, 0.8f);  // Uranus
	planets[7] = new Planet(6.0f, 182.0f, 11.0f, sphereMesh, neptuneTex, 315.0f, 1.8f);  // Neptune

	// Give Saturn rings (inner/outer radius)
	planets[5]->SetRings(2.0f, 4.0f);

	// Create and add Moon as a child of Earth (planets[2]) for hierarchical transforms
	Texture moontex = TextureManager::LoadTexture("OBJs\\Textures\\Moon.bmp");
	if (moontex.id == 0)
	{
		std::cerr << "HelloGL: Failed to load Moon texture (texture id == 0). Check path, file format and expected dimensions.\n";
		exit(EXIT_FAILURE);
	}
	moonTex = new Texture(moontex);

	Planet* moon = new Planet(0.5f, 2.0f, 120.0f, sphereMesh, moonTex, 0.0f);
	planets[2]->AddChild(moon); // Attach moon to Earth

	// Sun: large, stationary light source
	Texture sunTexture = TextureManager::LoadTexture("OBJs\\Textures\\Sun.bmp");
	if (sunTexture.id == 0)
	{
		std::cerr << "HelloGL: Failed to load Sun texture (texture id == 0). Check path, file format and expected dimensions.\n";
		exit(EXIT_FAILURE);
	}
	sunTex = new Texture(sunTexture);

	sun = new Planet(20.0f, 0.0f, 5.0f, sphereMesh, sunTex, 0.0f);
	sun->isLightSource = true;

	// Build a simple flat linked-list scene graph
	sceneGraph = new SceneGraph();
	sceneGraph->Add(planets[0]);
	sceneGraph->Add(planets[1]);
	sceneGraph->Add(planets[2]);
	sceneGraph->Add(planets[3]);
	sceneGraph->Add(planets[4]);
	sceneGraph->Add(planets[5]);
	sceneGraph->Add(planets[6]);
	sceneGraph->Add(planets[7]);
	sceneGraph->Add(sun);
	
	// Enter GLUT main loop
	glutMainLoop();
}

HelloGL::~HelloGL()
{
	// Clean up allocated resources
	if (sceneGraph != nullptr)
	{
		delete sceneGraph;
		sceneGraph = nullptr;
	}

	if (sphereMesh != nullptr)
	{ 
		delete sphereMesh;
		sphereMesh = nullptr;
	}

	// Free textures allocated with new Texture(...) in constructor
	if (earthTex != nullptr)
	{
		delete earthTex;
		earthTex = nullptr;
	}

	if (mercuryTex != nullptr)
	{
		delete mercuryTex;
		mercuryTex = nullptr;
	}

	if (venusTex != nullptr)
	{
		delete venusTex;
		venusTex = nullptr;
	}

	if (marsTex != nullptr)
	{
		delete marsTex;
		marsTex = nullptr;
	}

	if (jupiterTex != nullptr)
	{
		delete jupiterTex;
		jupiterTex = nullptr;
	}

	if (saturnTex != nullptr)
	{
		delete saturnTex;
		saturnTex = nullptr;
	}

	if (uranusTex != nullptr)
	{
		delete uranusTex;
		uranusTex = nullptr;
	}

	if (neptuneTex != nullptr)
	{
		delete neptuneTex;
		neptuneTex = nullptr;
	}

	if (moonTex != nullptr)
	{
		delete moonTex;
		moonTex = nullptr;
	}

	if (sunTex != nullptr)
	{
		delete sunTex;
		sunTex = nullptr;
	}
}

// Render the 3D scene and HUD
void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int winW = glutGet(GLUT_WINDOW_WIDTH);
	int winH = glutGet(GLUT_WINDOW_HEIGHT);
	double aspect = (winH == 0) ? 1.0 : static_cast<double>(winW) / static_cast<double>(winH);

	// Setup projection matrix (perspective)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, aspect, 0.1, 3000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Configure a simple point light at origin (Sun position)
	float lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f }; // 1.0 = point light
	float lightColour[] = { 1.0f, 1.0f, 0.9f, 1.0f }; // warm white
	float ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColour);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	float matDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float matSpecular[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	float matShininess = 10.0f;

	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, matShininess);

	// Compute camera lookAt target. If trackingMode is on, position camera relative to the tracked planet
	float lookX, lookY, lookZ;

	if (trackingMode && selectedPlanet >= 0 && planets[selectedPlanet] != nullptr)
	{
		Planet* target = planets[selectedPlanet];

		// Position camera behind and slightly above the target for a third-person view
		camX = target->worldX - 20.0f;
		camY = target->worldY + 15.0f;
		camZ = target->worldZ + 20.0f;

		// Look directly at the planet's world position
		lookX = target->worldX;
		lookY = target->worldY;
		lookZ = target->worldZ;
	}
	else
	{
		// Compute a forward vector from yaw/pitch for free-look mode
		lookX = camX + cos(camPitch) * sin(camYaw);
		lookY = camY + sin(camPitch);
		lookZ = camZ - cos(camPitch) * cos(camYaw);
	}

	// Set view transform
	gluLookAt(camX, camY, camZ, lookX, lookY, lookZ, 0.0, 1.0, 0.0);

	// Background stars and the scene graph drawing
	DrawStarfield();
	sceneGraph->DrawAll();

	// Draw on-screen info (FPS, controls etc.)
	DrawHUD();

	// Swap buffers (double buffering)
	glutSwapBuffers();
}

// Called by GLUT timer via wrapper; advances the simulation and requests redisplay
void HelloGL::Update()
{
	// Update scene graph with deltaTime computed from REFRESHRATE and simSpeed multiplier.
	sceneGraph->UpdateAll((REFRESHRATE / 1000.0f) * simSpeed);

	// Simple FPS counter
	frameCount++;
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	if (currentTime - lastTime >= 1000)
	{
		fps = frameCount * 1000.0f / (currentTime - lastTime);
		frameCount = 0;
		lastTime = currentTime;
	}

	// Post redisplay for next frame
	glutPostRedisplay();
}

// Draw on-screen text and HUD in an orthographic projection
void HelloGL::DrawHUD()
{
	// Switch to 2D orthographic projection for HUD rendering
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// Turn off lighting and depth test while drawing text
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glColor3f(1.0f, 1.0f, 1.0f);

	char camPos[100];
	sprintf_s(camPos, "Camera: (%.1f, %.1f, %.1f)", camX, camY, camZ);
	DrawText(10.0f, glutGet(GLUT_WINDOW_HEIGHT) - 110.0f, camPos);

	char fpsText[50];
	sprintf_s(fpsText, "FPS: %.1f", fps);
	DrawText(10.0f, glutGet(GLUT_WINDOW_HEIGHT) - 130.0f, fpsText);

	DrawText(10.0f, glutGet(GLUT_WINDOW_HEIGHT) - 30.0f, "Use WASD to move, QE to move up/down, and mouse to look around.");
	DrawText(10.0f, glutGet(GLUT_WINDOW_HEIGHT) - 50.0f, "Planets are not to scale and orbits are circular for simplicity.");
	DrawText(10.0f, glutGet(GLUT_WINDOW_HEIGHT) - 70.0f, "Textures are low-res for performance reasons.");

	const char* planetNames[] = {
	"Mercury", "Venus", "Earth", "Mars",
	"Jupiter", "Saturn", "Uranus", "Neptune"
	};

	// Show tracking status if a planet is selected
	if (trackingMode && selectedPlanet >= 0)
	{
		char trackText[50];
		sprintf_s(trackText, "Tracking: %s", planetNames[selectedPlanet]);
		DrawText(10.0f, glutGet(GLUT_WINDOW_HEIGHT) - 90.0f, trackText);
	}
	else
	{
		DrawText(10.0f, glutGet(GLUT_WINDOW_HEIGHT) - 90.0f, "Press 1-8 to track a planet");
	}

	char speedText[50];
	sprintf_s(speedText, "Sim Speed: %.1fx", simSpeed);
	DrawText(10.0f, glutGet(GLUT_WINDOW_HEIGHT) - 150.0f, speedText);
	DrawText(10.0f, glutGet(GLUT_WINDOW_HEIGHT) - 170.0f, "Press +/- to adjust simulation speed");

	// Restore state
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

// Simple utility to draw bitmap text at screen coordinates
void HelloGL::DrawText(float x, float y, const char* text)
{
	glRasterPos2f(x, y);
	for (const char* c = text; *c != '\0'; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
}

// Draw a simple starfield. Using a fixed seed ensures the stars remain static.
void HelloGL::DrawStarfield()
{
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(1.5f);
	glBegin(GL_POINTS);
	// Use a fixed seed so stars don't move
	srand(42);
	for (int i = 0; i < 1000; i++)
	{
		float x = (rand() % 2000) - 1000.0f;
		float y = (rand() % 2000) - 1000.0f;
		float z = (rand() % 2000) - 1000.0f;
		glVertex3f(x, y, z);
	}
	glEnd();
	glEnable(GL_LIGHTING);
}

// Keyboard input handler — simple WASD flight-style camera + other controls
void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	float speed = 2.0f;
	float forwardX = cos(camPitch) * sin(camYaw);
	float forwardZ = -cos(camPitch) * cos(camYaw);

	if (key == 'w') { camX += forwardX * speed; camZ += forwardZ * speed; }
	if (key == 's') { camX -= forwardX * speed; camZ -= forwardZ * speed; }
	if (key == 'a') { camX -= cos(camYaw) * speed; camZ -= sin(camYaw) * speed; }
	if (key == 'd') { camX += cos(camYaw) * speed; camZ += sin(camYaw) * speed; }
	if (key == 'q') { camY += speed; }
	if (key == 'e') { camY -= speed; }
	if (key == 't') { trackingMode = !trackingMode; } // toggle tracking
	if (key == 27) { exit(0); } // ESC exit

	// Number keys 1-8 select planets and enable tracking mode
	if (key >= '1' && key <= '8')
	{
		selectedPlanet = key - '1';
		trackingMode = true;
	}
	if (key == '0')
	{
		// Reset camera and stop tracking
		selectedPlanet = -1;
		trackingMode = false;
		camX = 0.0f; camY = 150.0f; camZ = 280.0f;
		camYaw = 0.0f; camPitch = -0.5f;
	}

	// Simulation speed control
	if (key == '+') simSpeed += 0.5f;
	if (key == '-') simSpeed -= 0.5f;
	if (simSpeed < 0.1f) simSpeed = 0.1f;
}

// Mouse button handling: left-click drag rotates camera
void HelloGL::MouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		mouseDown = (state == GLUT_DOWN);
		lastMouseX = x;
		lastMouseY = y;
	}
}

// Mouse motion handler while dragging — updates yaw/pitch
void HelloGL::MouseMotion(int x, int y)
{
	if (mouseDown)
	{
		float sensitivity = 0.005f;
		camYaw += (x - lastMouseX) * sensitivity;
		camPitch -= (y - lastMouseY) * sensitivity;
		lastMouseX = x;
		lastMouseY = y;
	}
}