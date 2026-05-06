#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"

// Fundamental data structures used across the project

struct Vertex
{
    // Position
    float x, y, z;
    // Normal
    float nx, ny, nz;
    // Texture coordinates
    float u, v;
};

struct Color
{
    float r, g, b;
};

struct Texture
{
    unsigned int id; // OpenGL texture ID (0 indicates invalid)
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