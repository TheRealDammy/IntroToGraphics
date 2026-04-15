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
}