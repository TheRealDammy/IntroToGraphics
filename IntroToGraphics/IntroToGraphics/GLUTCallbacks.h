#pragma once
class HelloGL;

// Wrapper namespace that stores a pointer to the HelloGL instance and forwards GLUT callbacks.
// This isolates GLUT's C-style callback API from the HelloGL class.
namespace GLUTCallbacks
{
	void Init(HelloGL* gl);

	void Display();

	void Timer(int preferredRefresh);

	void Keyboard(unsigned char key, int x, int y);
	void MouseMotion(int x, int y);
	void MouseButton(int button, int state, int x, int y);
}