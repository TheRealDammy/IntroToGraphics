#include "HelloGL.h"

HelloGL::HelloGL(int argc, char* argv[])
{
	rotation = 0.0f;
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Hello OpenGL");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(0, GLUTCallbacks::Timer, REFRESHRATE);
	glutMainLoop();
}

void HelloGL::Display() 
{
	glClear(GL_COLOR_BUFFER_BIT);
	HelloGL::DrawPolygon();	
	HelloGL::DrawPolygon2();
	HelloGL::DrawPolygon3();
	HelloGL::DrawPolygon4();
	glFlush();
}

void HelloGL::DrawPolygon() 
{	
	glPushMatrix();
	glTranslatef(-0.5, 0, 0);
	glRotatef(rotation, 0.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON); 
	{
		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
		glVertex2f(-0.2f, -0.2f);
		glColor4f(0.0f, 1.0f, 0.0f, 0.0f);
		glVertex2f(0.2f, -0.2f);
		glColor4f(0.0f, 0.0f, 1.0f, 0.0f);
		glVertex2f(0.2f, 0.2f);
		glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
		glVertex2f(-0.2f, 0.2f);
		glEnd();
	}
	glPopMatrix();
}

void HelloGL::DrawPolygon2()
{	
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glRotatef(rotation, 0.0f, 0.0f, -1.0f);
	glBegin(GL_POLYGON);
	{
		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
		glVertex2f(-0.2f, -0.2f);
		glColor4f(0.0f, 1.0f, 0.0f, 0.0f);
		glVertex2f(0.2f, -0.2f);
		glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
		glVertex2f(-0.2f, 0.2f);
		glEnd();
	}
	glPopMatrix();
}

void HelloGL::DrawPolygon3()
{
	glPushMatrix();
	glTranslatef(0.6, 0, 0);
	glRotatef(rotation, 0.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
	{
		glColor4f(0.2f, 0.4f, 0.0f, 0.0f);
		glVertex2f(-0.2f, -0.8f);
		glColor4f(0.0f, 1.0f, 0.0f, 0.0f);
		glVertex2f(0.2f, -0.7f);
		glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
		glVertex2f(-0.2f, 0.6f);
		glEnd();
	}
	glPopMatrix();
}

void HelloGL::DrawPolygon4()
{
	glPushMatrix();
	glTranslatef(-0.2, 0.5, 0);
	glRotatef(rotation, 0.0f, 0.0f, -1.0f);
	glBegin(GL_POLYGON);
	{
		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
		glVertex2f(-0.3f, -0.2f);
		glColor4f(0.0f, 1.0f, 0.0f, 0.0f);
		glVertex2f(0.5f, -0.2f);
		glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
		glVertex2f(-0.6f, 0.2f);
		glEnd();
	}
	glPopMatrix();
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

HelloGL::~HelloGL(void)
{

}