#pragma once
#include "Structures.h"

class ObjLoader
{
public:
	static Mesh* Load(const char* filename);
};