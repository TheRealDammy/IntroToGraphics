#include "Camera.h"

Camera::Camera(float x, float y, float z)
	: x(x), y(y), z(z), yaw(0.0f), pitch(-0.5f)
{
}

void Camera::MoveForward(float speed)
{
	x += cos(pitch) * sin(yaw) * speed;
	z += -cos(pitch) * cos(yaw) * speed;
}

void Camera::MoveBackward(float speed)
{
	x -= cos(pitch) * sin(yaw) * speed;
	z -= -cos(pitch) * cos(yaw) * speed;
}

void Camera::StrafeLeft(float speed)
{
	x -= cos(yaw) * speed;
	z -= sin(yaw) * speed;
}

void Camera::StrafeRight(float speed)
{
	x += cos(yaw) * speed;
	z += sin(yaw) * speed;
}

void Camera::MoveUp(float speed)
{
	y += speed;
}

void Camera::MoveDown(float speed)
{
	y -= speed;
}

void Camera::Rotate(float deltaYaw, float deltaPitch)
{
	yaw += deltaYaw;
	pitch += deltaPitch;
	// Clamp pitch to avoid flipping
	if (pitch > 1.5f) pitch = 1.5f;
	if (pitch < -1.5f) pitch = -1.5f;
}

void Camera ::SetPosition(float newX, float newY, float newZ)
{
	x = newX;
	y = newY;
	z = newZ;
}

void Camera::ApplyView()
{
	float lookX = x + cos(pitch) * sin(yaw);
	float lookY = y + sin(pitch);
	float lookZ = z + -cos(pitch) * cos(yaw);
	gluLookAt(x, y, z, lookX, lookY, lookZ, 0.0f, 1.0f, 0.0f);
}