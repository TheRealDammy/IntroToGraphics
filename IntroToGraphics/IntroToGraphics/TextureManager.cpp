#include "TextureManager.h"
#include <fstream>
#include <iostream>

Texture TextureManager::LoadTexture(const char* filename)
{
	Texture texture;
	texture.id = 0;

	std::ifstream file(filename, std::ios::binary);
	if (!file.is_open())
	{
		std::cerr << "Failed to open texture: " << filename << std::endl;
		return texture;
	}
	// Read the full header (54 bytes for standard BMP)
	unsigned char header[54];
	file.read(reinterpret_cast<char*>(header), 54);

	// Extract width, height and data offset from header
	int width = *(int*)&header[18];
	int height = *(int*)&header[22];
	int dataOffset = *(int*)&header[10];

	// Read the pixel data
	int dataSize = width * height * 3;
	unsigned char* data = new unsigned char[dataSize];
	file.seekg(dataOffset);
	file.read(reinterpret_cast<char*>(data), dataSize);
	std::cout << "Texture loaded: " << filename << std::endl;
	std::cout << "Bytes read: " << file.gcount() << std::endl;
	std::cout << "Expected bytes: " << dataSize << std::endl;
	std::cout << "Width: " << width << ", Height: " << height << std::endl;

	glGenTextures(1, &texture.id);
	glBindTexture(GL_TEXTURE_2D, texture.id);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);

	delete[] data;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	file.close();
	return texture;
}