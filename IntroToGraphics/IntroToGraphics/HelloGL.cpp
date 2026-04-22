#include "HelloGL.h"
#include "ObjLoader.h"
#include "TextureManager.h"
#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>


HelloGL::HelloGL(int argc, char* argv[])
{
	camX = 0.0f; camY = 150.0f; camZ = 280.0f;
	camYaw = 0.0f; camPitch = -0.5f;
	mouseDown = false;

	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Hello OpenGL");

	// Set display and timer callbacks
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(0, GLUTCallbacks::Timer, REFRESHRATE);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glutMotionFunc(GLUTCallbacks::MouseMotion);
	glutMouseFunc(GLUTCallbacks::MouseButton);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	sphereMesh = ObjLoader::Load("C:\\Users\\gdola\\OneDrive\\Desktop\\Course\\Modules\\First Year\\Intro To Graphics Programming\\OBJs\\Sphere.obj");
	if (sphereMesh == nullptr)
	{
		std::cerr << "HelloGL: Failed to load mesh. Check path and file existence.\n";
		exit(EXIT_FAILURE);
	}
	// Load textures
	// Earth texture
	Texture earthtex = TextureManager::LoadTexture("C:\\Users\\gdola\\OneDrive\\Desktop\\Course\\Modules\\First Year\\Intro To Graphics Programming\\OBJs\\Textures\\Earth.bmp");
	if (earthtex.id == 0)
	{
		std::cerr << "HelloGL: Failed to load texture (texture id == 0). Check path, file format and expected dimensions.\n";
		exit(EXIT_FAILURE);
	}

	earthTex = new Texture(earthtex);

	// Mercury texture
	Texture mercurytex = TextureManager::LoadTexture("C:\\Users\\gdola\\OneDrive\\Desktop\\Course\\Modules\\First Year\\Intro To Graphics Programming\\OBJs\\Textures\\Mercury.bmp");
	if (mercurytex.id == 0)
	{
		std::cerr << "HelloGL: Failed to load texture (texture id == 0). Check path, file format and expected dimensions.\n";
		exit(EXIT_FAILURE);
	}

	mercuryTex = new Texture(mercurytex);

	// Venus texture
	Texture venustex = TextureManager::LoadTexture("C:\\Users\\gdola\\OneDrive\\Desktop\\Course\\Modules\\First Year\\Intro To Graphics Programming\\OBJs\\Textures\\Venus.bmp");
	if (venustex.id == 0)
	{
		std::cerr << "HelloGL: Failed to load texture (texture id == 0). Check path, file format and expected dimensions.\n";
		exit(EXIT_FAILURE);
	}

	venusTex = new Texture(venustex);

	// Mars texture
	Texture marstex = TextureManager::LoadTexture("C:\\Users\\gdola\\OneDrive\\Desktop\\Course\\Modules\\First Year\\Intro To Graphics Programming\\OBJs\\Textures\\Mars.bmp");
	if (marstex.id == 0)
	{
		std::cerr << "HelloGL: Failed to load texture (texture id == 0). Check path, file format and expected dimensions.\n";
		exit(EXIT_FAILURE);
	}

	marsTex = new Texture(marstex);

	//Jupiter texture
	Texture jupitertex = TextureManager::LoadTexture("C:\\Users\\gdola\\OneDrive\\Desktop\\Course\\Modules\\First Year\\Intro To Graphics Programming\\OBJs\\Textures\\Jupiter.bmp");
	if (jupitertex.id == 0)
	{
		std::cerr << "HelloGL: Failed to load texture (texture id == 0). Check path, file format and expected dimensions.\n";
		exit(EXIT_FAILURE);
	}

	jupiterTex = new Texture(jupitertex);

	// Saturn texture
	Texture saturntex = TextureManager::LoadTexture("C:\\Users\\gdola\\OneDrive\\Desktop\\Course\\Modules\\First Year\\Intro To Graphics Programming\\OBJs\\Textures\\Saturn.bmp");
	if (saturntex.id == 0)
	{
		std::cerr << "HelloGL: Failed to load texture (texture id == 0). Check path, file format and expected dimensions.\n";
		exit(EXIT_FAILURE);
	}

	saturnTex = new Texture(saturntex);

	// Uranus texture
	Texture uranustex = TextureManager::LoadTexture("C:\\Users\\gdola\\OneDrive\\Desktop\\Course\\Modules\\First Year\\Intro To Graphics Programming\\OBJs\\Textures\\Uranus.bmp");
	if (uranustex.id == 0)
	{
		std::cerr << "HelloGL: Failed to load texture (texture id == 0). Check path, file format and expected dimensions.\n";
		exit(EXIT_FAILURE);
	}

	uranusTex = new Texture(uranustex);

	// Neptune texture
	Texture neptunetex = TextureManager::LoadTexture("C:\\Users\\gdola\\OneDrive\\Desktop\\Course\\Modules\\First Year\\Intro To Graphics Programming\\OBJs\\Textures\\Neptune.bmp");
	if (neptunetex.id == 0)
	{
		std::cerr << "HelloGL: Failed to load texture (texture id == 0). Check path, file format and expected dimensions.\n";
		exit(EXIT_FAILURE);
	}

	neptuneTex = new Texture(neptunetex);

	// Create planets
	
	planets[0] = new Planet(3.0f, 25.0f, 87.0f, sphereMesh, mercuryTex, 0.0f, 7.0f);  // Mercury
	planets[1] = new Planet(4.5f, 40.0f, 62.0f, sphereMesh, venusTex, 45.0f, 3.4f);  // Venus
	planets[2] = new Planet(5.0f, 58.0f, 50.0f, sphereMesh, earthTex, 90.0f, 0.0f);  // Earth
	planets[3] = new Planet(3.5f, 76.0f, 40.0f, sphereMesh, marsTex, 135.0f, 1.9f);  // Mars
	planets[4] = new Planet(9.0f, 100.0f, 25.0f, sphereMesh, jupiterTex, 180.0f, 1.3f);  // Jupiter
	planets[5] = new Planet(7.5f, 128.0f, 20.0f, sphereMesh, saturnTex, 225.0f, 2.5f);  // Saturn
	planets[6] = new Planet(6.5f, 155.0f, 14.0f, sphereMesh, uranusTex, 270.0f, 0.8f);  // Uranus
	planets[7] = new Planet(6.0f, 182.0f, 11.0f, sphereMesh, neptuneTex, 315.0f, 1.8f);  // Neptune

	//Saturns Rings
	planets[5]->SetRings(2.0f, 4.0f);

	// Moon texture
	Texture moontex = TextureManager::LoadTexture("C:\\Users\\gdola\\OneDrive\\Desktop\\Course\\Modules\\First Year\\Intro To Graphics Programming\\OBJs\\Textures\\Moon.bmp");
	if (moontex.id == 0)
	{
		std::cerr << "HelloGL: Failed to load Moon texture (texture id == 0). Check path, file format and expected dimensions.\n";
		exit(EXIT_FAILURE);
	}

	moonTex = new Texture(moontex);

	// Create Moon as a child of Earth
	Planet* moon = new Planet(0.5f, 2.0f, 120.0f, sphereMesh, moonTex, 0.0f);
	planets[2]->AddChild(moon); // Earth's child
	
	// Sun texture
	Texture sunTexture = TextureManager::LoadTexture("C:\\Users\\gdola\\OneDrive\\Desktop\\Course\\Modules\\First Year\\Intro To Graphics Programming\\OBJs\\Textures\\Sun.bmp");
	if (sunTexture.id == 0)
	{
		std::cerr << "HelloGL: Failed to load Sun texture (texture id == 0). Check path, file format and expected dimensions.\n";
		exit(EXIT_FAILURE);
	}

	sunTex = new Texture(sunTexture);

	// Create Sun
	sun = new Planet(20.0f, 0.0f, 5.0f, sphereMesh, sunTex, 0.0f);
	sun->isLightSource = true;

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
	
	glutMainLoop();
}

HelloGL::~HelloGL()
{
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

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int winW = glutGet(GLUT_WINDOW_WIDTH);
	int winH = glutGet(GLUT_WINDOW_HEIGHT);
	double aspect = (winH == 0) ? 1.0 : static_cast<double>(winW) / static_cast<double>(winH);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, aspect, 0.1, 3000.0);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	// Set up a point light at the Sun's position
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

	// Camera transform
	float lookX = camX + cos(camPitch) * sin(camYaw);
	float lookY = camY + sin(camPitch);
	float lookZ = camZ - cos(camPitch) * cos(camYaw);
	gluLookAt(camX, camY, camZ, lookX, lookY, lookZ, 0.0, 1.0, 0.0);

	sceneGraph->DrawAll();

	DrawHUD();

	glutSwapBuffers();
}

void HelloGL::Update()
{
	sceneGraph->UpdateAll(REFRESHRATE / 1000.0f);

	frameCount++;
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	if (currentTime - lastTime >= 1000)
	{
		fps = frameCount * 1000.0f / (currentTime - lastTime);
		frameCount = 0;
		lastTime = currentTime;
	}

	glutPostRedisplay();
}

void HelloGL::DrawHUD()
{
	// Switch to 2D orthographic projection
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

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

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void HelloGL::DrawText(float x, float y, const char* text)
{
	glRasterPos2f(x, y);
	for (const char* c = text; *c != '\0'; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	float speed = 1.0f;
	if (key == 'w') { camZ -= speed; }
	if (key == 's') { camZ += speed; }
	if (key == 'a') { camX -= speed; }
	if (key == 'd') { camX += speed; }
	if (key == 'q') { camY += speed; }
	if (key == 'e') { camY -= speed; }
	if (key == 27) { exit(0); } // Escape to quit
}

void HelloGL::MouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		mouseDown = (state == GLUT_DOWN);
		lastMouseX = x;
		lastMouseY = y;
	}
}

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