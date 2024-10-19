#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <iostream>
#include <string>

class Cubemap
{
public:
	Cubemap();
	int width;
	int height;
	int channels;
	unsigned int texture;
	unsigned char* data;
	void Load(const char* name, const char* ext = "png");
	void Bind(int id = 0);
	void Unbind(int id = 0);
};

