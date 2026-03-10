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
		glutPostRedisplay();
		glutTimerFunc(preferredRefresh, Timer, preferredRefresh);

		if (helloGL != nullptr)
			{
				helloGL->Update();
		}
	}
}