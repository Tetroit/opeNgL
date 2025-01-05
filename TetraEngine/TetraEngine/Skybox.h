#pragma once

#include "MeshRenderer.h"
#include "VertexData.h"
#include "Shader.h"
#include "Camera.h"
#include "Cubemap.h"
#include "Texture2D.h"

class Skybox
{
public:
	enum Mode {
		BOX,
		SPHERE
	};

	static Skybox* current;
	Skybox(Mode mode = SPHERE, const char* path = "Assets/skybox.jpg");
	~Skybox();
	void Render();
	Cubemap* cubemap;


private:
	const Mode mode;
	Texture2D* texture;
	Shader* shader;
	std::shared_ptr<VertexData> mesh;
};

