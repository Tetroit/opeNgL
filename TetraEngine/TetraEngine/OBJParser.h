#pragma once

#include <fstream>

static class OBJParser
{
private:
	static std::ifstream stream;

public:
	static int OBJRead(const char* path);
};

