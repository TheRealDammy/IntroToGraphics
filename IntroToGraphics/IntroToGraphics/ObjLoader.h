#pragma once
#include "Structures.h"

// Very small .obj loader tailored to the project's Sphere.obj (triangles only).
// Returns a heap-allocated Mesh* that the caller must delete.
class ObjLoader
{
public:
	static Mesh* Load(const char* filename);
};