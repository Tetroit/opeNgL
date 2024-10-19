
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "VertexData.h"

std::vector<std::shared_ptr<VertexData>> VertexData::collection = std::vector<std::shared_ptr<VertexData>>{};

int VertexData::lastId = 0;

extern std::vector<int> materialMap;
extern std::vector<Vertex> verts;
extern std::vector<unsigned int> faces;
extern float* vert;
extern unsigned int VBO;
extern unsigned int VAO;
extern unsigned int EBO;

VertexData::VertexData(int id) : id(id)
{
    vert = NULL;
    verts = {};
    faces = {};
}
std::shared_ptr<VertexData> VertexData::CreateVertexData()
{
    int id = lastId++;
    std::shared_ptr<VertexData> vd = std::make_shared<VertexData>(id);
    collection.push_back(std::move(vd));
    return collection[id];
}
void VertexData::Setup() {

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    if (verts.size() == 0)
        std::cout << "VERTEX BUFFER IS EMPTY";
    else {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(Vertex), &verts[0], GL_STATIC_DRAW);
    }

    if (faces.size() == 0)
        std::cout << "ELEMENT BUFFER IS EMPTY";
    else {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (faces.size())*sizeof(unsigned int), &faces[0], GL_STATIC_DRAW);
    }

    if (materialMap.size() == 0)
        materialMap.push_back(faces.size());

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void VertexData::Update() {
    Draw();

    //transform = glm::rotate(transform, Time::deltaTime, glm::vec3(0.0f, 0.9f, 0.1f));
    //transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, 1.0f));
}
void VertexData::Draw()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, faces.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
void VertexData::AddVert(Vertex vert)
{
    verts.push_back(vert);
}
void VertexData::LoadVerts(Vertex* ptr, int size)
{
    verts.clear();
    for (int i = 0; i < size; i++)
    {
        verts.push_back(ptr[i]);
    }
}
void VertexData::LoadFaces(unsigned int* ptr, int size)
{
    faces.clear();
    for (int i = 0; i < size; i++)
    {
        faces.push_back(ptr[i]);
    }
}
void VertexData::InitialisePrefabs() {

    std::shared_ptr<VertexData> rect = VertexData::CreateVertexData();
    std::vector<Vertex> vertices = {
        Vertex(-1.0f, -1.0f, 0.0f, /*uv*/ 0.0f, 0.0f, /*color*/ 0.0f, 0.0f, 1.0f),
        Vertex(1.0f, -1.0f, 0.0f, /*uv*/ 1.0f, 0.0f, /*color*/ 0.0f, 0.0f, 1.0f),
        Vertex(-1.0f,  1.0f, 0.0f, /*uv*/ 0.0f, 1.0f,/*color*/ 0.0f, 0.0f, 1.0f),
        Vertex(1.0f,  1.0f, 0.0f, /*uv*/ 1.0f, 1.0f, /*color*/ 0.0f, 0.0f, 1.0f),
    };
    std::vector<unsigned int> index = {
        0, 1, 2,
        1, 2, 3,
    };

    rect.get()->LoadVerts(&vertices[0],4);
    rect.get()->LoadFaces(&index[0], 6);
    rect.get()->Setup();

    vertices.clear();
    index.clear();

    std::shared_ptr<VertexData> cube = VertexData::CreateVertexData();
    vertices.insert(vertices.end(), {

        Vertex(-0.5f, -0.5f, 0.5f,/*uv*/ 0.0f, 0.0f,/*color*/ 0.0f, 0.0f, 1.0f),
        Vertex(0.5f, -0.5f, 0.5f, /*uv*/ 1.0f, 0.0f, /*color*/ 0.0f, 0.0f, 1.0f),
        Vertex(-0.5f,  0.5f, 0.5f, /*uv*/ 0.0f, 1.0f,/*color*/ 0.0f, 0.0f, 1.0f),
        Vertex(0.5f,  0.5f, 0.5f, /*uv*/ 1.0f, 1.0f, /*color*/ 0.0f, 0.0f, 1.0f),

        Vertex(-0.5f, -0.5f, -0.5f, /*uv*/ 0.0f, 0.0f,/*color*/ 0.0f, 0.0f, -1.0f),
        Vertex(0.5f, -0.5f, -0.5f, /*uv*/ 1.0f, 0.0f, /*color*/ 0.0f, 0.0f, -1.0f),
        Vertex(-0.5f,  0.5f, -0.5f, /*uv*/ 0.0f, 1.0f,/*color*/ 0.0f, 0.0f, -1.0f),
        Vertex(0.5f,  0.5f, -0.5f, /*uv*/ 1.0f, 1.0f, /*color*/ 0.0f, 0.0f, -1.0f),

        Vertex(-0.5f, -0.5f, -0.5f, /*uv*/ 0.0f, 0.0f, /*color*/ 0.0f, -1.0f, 0.0f),
        Vertex(0.5f, -0.5f, -0.5f, /*uv*/ 1.0f, 0.0f, /*color*/ 0.0f, -1.0f, 0.0f),
        Vertex(-0.5f,  -0.5f, 0.5f, /*uv*/ 0.0f, 1.0f, /*color*/ 0.0f, -1.0f, 0.0f),
        Vertex(0.5f,  -0.5f, 0.5f, /*uv*/ 1.0f, 1.0f, /*color*/ 0.0f, -1.0f, 0.0f),

        Vertex(-0.5f, 0.5f, -0.5f, /*uv*/ 0.0f, 0.0f, /*color*/ 0.0f, 1.0f, 0.0f),
        Vertex(0.5f, 0.5f, -0.5f, /*uv*/ 1.0f, 0.0f, /*color*/ 0.0f, 1.0f, 0.0f),
        Vertex(-0.5f,  0.5f, 0.5f, /*uv*/ 0.0f, 1.0f, /*color*/ 0.0f, 1.0f, 0.0f),
        Vertex(0.5f,  0.5f, 0.5f, /*uv*/ 1.0f, 1.0f, /*color*/ 0.0f, 1.0f, 0.0f),

        Vertex(-0.5f, -0.5f, -0.5f, /*uv*/ 0.0f, 0.0f,/*color*/ -1.0f, 0.0f, 0.0f),
        Vertex(-0.5f, 0.5f, -0.5f, /*uv*/ 1.0f, 0.0f, /*color*/ -1.0f, 0.0f, 0.0f),
        Vertex(-0.5f,  -0.5f, 0.5f, /*uv*/ 0.0f, 1.0f,/*color*/ -1.0f, 0.0f, 0.0f),
        Vertex(-0.5f,  0.5f, 0.5f, /*uv*/ 1.0f, 1.0f, /*color*/ -1.0f, 0.0f, 0.0f),

        Vertex(0.5f, -0.5f, -0.5f, /*uv*/ 0.0f, 0.0f,/*color*/ 1.0f, 0.0f, 0.0f),
        Vertex(0.5f, 0.5f, -0.5f, /*uv*/ 1.0f, 0.0f, /*color*/ 1.0f, 0.0f, 0.0f),
        Vertex(0.5f,  -0.5f, 0.5f, /*uv*/ 0.0f, 1.0f,/*color*/ 1.0f, 0.0f, 0.0f),
        Vertex(0.5f,  0.5f, 0.5f, /*uv*/ 1.0f, 1.0f, /*color*/ 1.0f, 0.0f, 0.0f),
        });

    index.insert(index.end(), {
        0,1,2,
        1,2,3,
        4,5,6,
        5,6,7,
        8,9,10,
        9,10,11,
        12,13,14,
        13,14,15,
        16,17,18,
        17,18,19,
        20,21,22,
        21,22,23,
    });

    cube.get()->LoadVerts(&vertices[0], 6 * 4);
    cube.get()->LoadFaces(&index[0], 6 * 6);
    cube.get()->Setup();

    vertices.clear();
    index.clear();

    OBJParser::OBJRead("Assets/meshes/suzanne.obj");
}
std::shared_ptr<VertexData> VertexData::GetPrefab(int id) {
    return collection[id];
}
