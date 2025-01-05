#pragma once

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

