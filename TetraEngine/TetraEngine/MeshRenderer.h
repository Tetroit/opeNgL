#pragma once

#include "Shader.h"
#include "VertexData.h"
#include "Camera.h"

class MeshRenderer
{

public:
	static MeshRenderer defaultRenderer;

	std::shared_ptr<VertexData> mesh;
	Shader* shader;
	Camera* camera;
	void Render(glm::mat4 transform = glm::mat4(1));
	MeshRenderer(std::shared_ptr<VertexData> vd, Shader* sh);
	static void InitialiseRenderer();
};

