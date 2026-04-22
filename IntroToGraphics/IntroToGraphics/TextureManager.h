#pragma once
#include "Structures.h"

class TextureManager
{
	public:
	static Texture LoadTexture(const char* filename);
	static void FreeTexture(Texture& texture);

};