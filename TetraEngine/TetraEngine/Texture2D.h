#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Texture2D
{
public:
	Texture2D();
	int width;
	int height;
	int channels;
	unsigned int texture;
	unsigned char* data;
	void Load(const char* name);
	void Bind();
	void Unbind();
};

