#include "HelloGL.h"
#include "ObjLoader.h"
#include "TextureManager.h"
#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>


HelloGL::HelloGL(int argc, char* argv[])
{
	rotation = 0.0f;

	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Hello OpenGL");

	// Set display and timer callbacks
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(0, GLUTCallbacks::Timer, REFRESHRATE);

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
	Texture tex = TextureManager::LoadTexture("C:\\Users\\gdola\\OneDrive\\Desktop\\Course\\Modules\\First Year\\Intro To Graphics Programming\\OBJs\\Textures\\Earth.bmp");
	if (tex.id == 0)
	{
		std::cerr << "HelloGL: Failed to load texture (texture id == 0). Check path, file format and expected dimensions.\n";
		exit(EXIT_FAILURE);
	}

	sharedTex = new Texture(tex);

	planets[0] = new Planet(1.5f, 8.0f, 87.0f, sphereMesh, sharedTex, 0.0f);    // Mercury
	planets[1] = new Planet(2.5f, 13.0f, 62.0f, sphereMesh, sharedTex, 45.0f);   // Venus
	planets[2] = new Planet(2.8f, 18.0f, 50.0f, sphereMesh, sharedTex, 90.0f);   // Earth
	planets[3] = new Planet(1.8f, 23.0f, 40.0f, sphereMesh, sharedTex, 135.0f);  // Mars
	planets[4] = new Planet(6.0f, 30.0f, 25.0f, sphereMesh, sharedTex, 180.0f);  // Jupiter
	planets[5] = new Planet(5.0f, 38.0f, 20.0f, sphereMesh, sharedTex, 225.0f);  // Saturn
	planets[6] = new Planet(4.0f, 45.0f, 14.0f, sphereMesh, sharedTex, 270.0f);  // Uranus
	planets[7] = new Planet(3.8f, 52.0f, 11.0f, sphereMesh, sharedTex, 315.0f);  // Neptune
	
	Texture sunTexture = TextureManager::LoadTexture("C:\\Users\\gdola\\OneDrive\\Desktop\\Course\\Modules\\First Year\\Intro To Graphics Programming\\OBJs\\Textures\\Sun.bmp");
	if (sunTexture.id == 0)
	{
		std::cerr << "HelloGL: Failed to load Sun texture (texture id == 0). Check path, file format and expected dimensions.\n";
		exit(EXIT_FAILURE);
	}

	sunTex = new Texture(sunTexture);

	sun = new Planet(5.0f, 0.0f, 5.0f, sphereMesh, sunTex, 0.0f);
	
	glutMainLoop();
}

HelloGL::~HelloGL()
{
	if (planets != nullptr)
	{
		for (int i = 0; i < NUM_PLANETS; i++)
		{
			if (planets[i] != nullptr)
			{
				delete planets[i];
				planets[i] = nullptr;
			}
		}
	}
	if (sphereMesh != nullptr)
	{ 
		delete sphereMesh;
		sphereMesh = nullptr;
	}

	if (sharedTex != nullptr)
	{
		delete sharedTex;
		sharedTex = nullptr;
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
	gluPerspective(45.0, aspect, 0.1, 500.0);

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
	gluLookAt(0.0, 60.0, 100.0,   // camera position
	          0.0, 0.0, 0.0,    // looking at
	          0.0, 1.0, 0.0);   // up vector

	// Draw scene
	if (sun != nullptr) 
	{
		glDisable(GL_LIGHTING);
		sun->Draw();
		glEnable(GL_LIGHTING);
	}

	for (int i = 0; i < NUM_PLANETS; i++)
	{
		if (planets[i] != nullptr)
			planets[i]->Draw();
	}

	glutSwapBuffers();
}

void HelloGL::Update()
{
	if (sun != nullptr)
		sun->Update(REFRESHRATE / 1000.0f);

	for (int i = 0; i < NUM_PLANETS; i++)
	{
		if (planets[i] != nullptr)
			planets[i]->Update(REFRESHRATE / 1000.0f);
	}

	glutPostRedisplay();
}