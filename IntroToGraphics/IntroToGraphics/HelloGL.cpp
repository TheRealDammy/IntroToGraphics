#include "HelloGL.h"

HelloGL::HelloGL(int argc, char* argv[])
{
	rotation = 0.0f;
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Hello OpenGL");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(0, GLUTCallbacks::Timer, REFRESHRATE);
	glutMainLoop();	
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glRotatef(rotation, 1.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	{		
		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
		glVertex2f(-0.2f, -0.2f);
		glColor4f(0.0f, 1.0f, 0.0f, 0.0f);
		glVertex2f(0.2f, -0.2f);
		glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
		glVertex2f(-0.2f, 0.2f);		
	}	
	glEnd();
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

void HelloGL::Update()
{
	glutPostRedisplay();

	rotation += 0.5f;

	if (rotation > 360.0f)
	{
		rotation = 0.0f;
	}
}