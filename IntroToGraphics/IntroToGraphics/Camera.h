#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <cmath>

class Camera
{
public:
	Camera(float x, float y, float z);
	
	void MoveForward(float speed);
	void MoveBackward(float speed);
	void StrafeLeft(float speed);
	void StrafeRight(float speed);
	void MoveUp(float speed);
	void MoveDown(float speed);
	void Rotate(float yaw, float pitch);
	void ApplyView();

	float GetX() const { return x; }
	float GetY() const { return y; }
	float GetZ() const { return z; }

	void SetPosition(float newX, float newY, float newZ);
private:
	float x, y, z; // Position
	float yaw, pitch; // Orientation in radians
};