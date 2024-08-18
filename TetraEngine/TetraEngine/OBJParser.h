#pragma once

#include "VertexData.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

static class OBJParser
{
private:
	static std::ifstream stream;

public:
	static void OBJRead(const char* path);
};

