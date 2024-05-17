#pragma once
#include "Shader.h"
#include "Texture2D.h"
#include "Time.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class VertexData
{
	public:
		int id;
		float* vert;
		Shader* shader;
		Texture2D* texture;
		unsigned int VBO;
		unsigned int VAO;
		unsigned int EBO;
		VertexData(int id);
		void Setup();
		void Update();
		void Transform(glm::mat4 transform);
		glm::mat4 transform = glm::mat4(1);
};

