#include "tetrapc.h"
#include "Texture2D.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "stb_image.h"

extern unsigned char* data;
extern unsigned int texture;
extern int width;
extern int height;
extern int channels;

Texture2D::Texture2D() {
	glGenTextures(1, &texture);
}
void Texture2D::Load(const char* name, bool flip_vertically) {

	glBindTexture(GL_TEXTURE_2D, texture);

	stbi_set_flip_vertically_on_load(flip_vertically);
	data = stbi_load(name, &width, &height, &channels, 0);
	if (data)
	{
		int channelMode = GL_RGB;
		if (channels == 1) channelMode = GL_RED;
		if (channels == 4) channelMode = GL_RGBA;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, channelMode, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	std::cout << "texture has been loaded\n";
}
void Texture2D::Bind(int id)
{
	if (this != nullptr)
	{
		glActiveTexture(GL_TEXTURE0 + id);
		glBindTexture(GL_TEXTURE_2D, texture);
	}
}
void Texture2D::Unbind(int id)
{
	if (this != nullptr)
	{
		glActiveTexture(GL_TEXTURE0 + id);
		glBindTexture(GL_TEXTURE_2D, NULL);
	}
}