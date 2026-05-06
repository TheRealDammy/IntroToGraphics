#pragma once
#include "Structures.h"

// Small utility to load/free textures. Implementation uses simple BMP reader and OpenGL calls.
class TextureManager
{
	public:
	// Load texture from file. Returns Texture with id==0 on failure.
	static Texture LoadTexture(const char* filename);

	// Free texture (if implemented/needed). Presently declared but not used in code.
	static void FreeTexture(Texture& texture);

};