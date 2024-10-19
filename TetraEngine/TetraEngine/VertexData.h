#pragma once
#include "Shader.h"
#include "Texture2D.h"
#include "Time.h"
#include "OBJParser.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <map>
#include "Material.h"

#define VD_RECTANGLE 0
#define VD_CUBE 1
#define VD_SUZANNE 2

struct Vertex
{
	float x, y, z;
	float u, v;
	float nx, ny, nz;
	Vertex(float x, float y, float z, float u, float v, float nx, float ny, float nz) : x(x), y(y), z(z), nx(nx), ny(ny), nz(nz), u(u), v(v)
	{
	}
};

class VertexData
{
	public:
		static int lastId;
		static std::vector<std::shared_ptr<VertexData>> collection;
		static void InitialisePrefabs();
		static std::shared_ptr<VertexData> GetPrefab(int id);
		static std::shared_ptr<VertexData> CreateVertexData();

		int id;
		std::vector<int> materialMap;
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

