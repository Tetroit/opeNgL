#pragma once
#include "Shader.h"
#include "Texture2D.h"
#include "Time.h"
#include "OBJParser.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#define VD_RECTANGLE 0
#define VD_CUBE 1
#define VD_SUZANNE 2

struct Vertex
{
	float x, y, z;
	float r, g, b;
	float u, v;
	Vertex(float x, float y, float z, float r, float g, float b, float u, float v) : x(x), y(y), z(z), r(r), g(g), b(b), u(u), v(v)
	{
	}
};

class VertexData
{
	public:
		static std::vector<std::shared_ptr<VertexData>> collection;
		static void InitialisePrefabs();
		static std::shared_ptr<VertexData> GetPrefab(int id);
		static std::shared_ptr<VertexData> CreateVertexData(int id);

		int id;
		std::vector<Vertex> verts;
		std::vector<unsigned int> faces;
		float* vert;
		unsigned int VBO;
		unsigned int VAO;
		unsigned int EBO;
		VertexData(int id);
		void Setup();
		void Update();
		void LoadVerts(Vertex* ptr, int size);
		void LoadFaces(unsigned int* ptr, int size);
		void AddVert(Vertex vert);
		void Draw();
		void Transform(glm::mat4 transform);
};

