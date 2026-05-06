#include "GLUTCallbacks.h"
#include "HelloGL.h"

namespace GLUTCallbacks
{
	namespace
	{
		// Stored HelloGL instance to forward callbacks to.
		HelloGL* helloGL = nullptr;
	}
	// Initialize callback wrapper with pointer to application instance.
	void Init(HelloGL* gl)
	{
		helloGL = gl;
	}
	// Forward display callback to HelloGL::Display()
	void Display()
	{
		if (helloGL != nullptr)
		{
			helloGL->Display();
		}
	}

	// Timer callback: calls Update() then schedules the next timer call.
	void Timer(int preferredRefresh)
	{
		int updateTime = glutGet(GLUT_ELAPSED_TIME);

		if (helloGL != nullptr)
		{
			helloGL->Update();
			// Compute how long update took so we can try to maintain a stable refresh interval.
			updateTime = glutGet(GLUT_ELAPSED_TIME) - updateTime;
		}

		// Schedule next timer; subtract update time to attempt steady frame spacing.
		glutTimerFunc(preferredRefresh - updateTime, Timer, preferredRefresh);
	}

	// Input forwarding
	void Keyboard(unsigned char key, int x, int y)
	{
		if (helloGL != nullptr)
			helloGL->Keyboard(key, x, y);
	}

	void MouseMotion(int x, int y)
	{
		if (helloGL != nullptr)
			helloGL->MouseMotion(x, y);
	}

	void MouseButton(int button, int state, int x, int y)
	{
		if (helloGL != nullptr)
			helloGL->MouseButton(button, state, x, y);
	}
}