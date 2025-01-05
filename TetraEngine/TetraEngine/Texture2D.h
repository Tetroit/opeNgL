#pragma once

class Texture2D
{
public:
	Texture2D();
	int width;
	int height;
	int channels;
	unsigned int texture;
	unsigned char* data;
	void Load(const char* name, bool flip_vertically = false);
	void Bind(int id = 0);
	void Unbind(int id = 0);
};

