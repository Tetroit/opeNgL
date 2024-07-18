#pragma once

#include "VertexData.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

static class OBJParser
{

public:
	static void OBJRead(const char* path, int id);
	static void Words(std::string line, std::vector<std::string>& res, char separator, bool ignoreEmpty = true);
};

