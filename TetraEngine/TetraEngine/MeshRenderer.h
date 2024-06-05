#pragma once

#include "Shader.h"
#include "VertexData.h"

class MeshRenderer
{

public:
	VertexData* mesh;
	Shader* shader;
	MeshRenderer(VertexData* vd, Shader* sh);
	void Render();
};

