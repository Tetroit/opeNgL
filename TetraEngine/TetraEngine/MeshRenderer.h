#pragma once

#include "Shader.h"
#include "VertexData.h"
#include "Camera.h"
#include "Material.h"
#include "Skybox.h"

#define DIFFUSE_TEXTURE_BIT 0x1
#define SPECULAR_TEXTURE_BIT 0x2
#define EMISSION_TEXTURE_BIT 0x4

class MeshRenderer
{

public:
	static MeshRenderer defaultRenderer;
	static MeshRenderer skyboxRenderer;

	std::shared_ptr<VertexData> mesh;
	Texture2D* diffuseTexture;
	Texture2D* specularTexture;
	Texture2D* emissionTexture;
	int textureFlags;
	Shader* shader;
	Camera* camera;
	Material* material;
	virtual void Render(glm::mat4 transform = glm::mat4(1));
	MeshRenderer(std::shared_ptr<VertexData> vd, Shader* sh);
	void setTexture(Texture2D* texture, int texBit = 1);
	void setTexture(const char* name);
	static void InitialiseRenderer();
};

