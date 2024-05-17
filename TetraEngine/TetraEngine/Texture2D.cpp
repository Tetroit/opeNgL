#include "Texture2D.h"
#include <iostream>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

extern unsigned char* data;
extern unsigned int texture;
extern int width;
extern int height;
extern int channels;

Texture2D::Texture2D() {
	glGenTextures(1, &texture);
}
void Texture2D::Load(const char* name) {

	glBindTexture(GL_TEXTURE_2D, texture);

	data = stbi_load(name, &width, &height, &channels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
}
void Texture2D::Bind()
{
	glBindTexture(GL_TEXTURE_2D, texture);
}