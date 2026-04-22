#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"

struct Vertex
{
    float x, y, z;
    float nx, ny, nz;
    float u, v;
};

struct Color
{
    float r, g, b;
};

struct Texture
{
    unsigned int id; // OpenGL texture ID
    int width;
    int height;
};

struct Mesh
{
    Vertex* vertices = nullptr;
	int numVertices = 0;
};

struct Vector3
{
    float x, y, z;
};

struct Vector2
{
    float x, y;
};  