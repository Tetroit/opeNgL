#pragma once

#include "Shader.h"
#include "VertexData.h"
#include "Camera.h"
#include "Material.h"

class MeshRenderer
{

public:
	static MeshRenderer defaultRenderer;

	std::shared_ptr<VertexData> mesh;
	Texture2D* texture;
	Shader* shader;
	Camera* camera;
	Material* material;
	void Render(glm::mat4 transform = glm::mat4(1));
	MeshRenderer(std::shared_ptr<VertexData> vd, Shader* sh);
	void setTexture(Texture2D* texture);
	void setTexture(const char* name);
	static void InitialiseRenderer();
};

