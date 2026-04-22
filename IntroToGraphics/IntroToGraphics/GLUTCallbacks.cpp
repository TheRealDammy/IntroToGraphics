#include "GLUTCallbacks.h"
#include "HelloGL.h"

namespace GLUTCallbacks
{
	namespace
	{
		HelloGL* helloGL = nullptr;
	}
	void Init(HelloGL* gl)
	{
		helloGL = gl;
	}
	void Display()
	{
		if (helloGL != nullptr)
		{
			helloGL->Display();
		}
	}

	void Timer(int preferredRefresh)
	{
		int updateTime = glutGet(GLUT_ELAPSED_TIME);

		if (helloGL != nullptr)
		{
			helloGL->Update();
			updateTime = glutGet(GLUT_ELAPSED_TIME) - updateTime;
		}

		glutTimerFunc(preferredRefresh - updateTime, Timer, preferredRefresh);
	}

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