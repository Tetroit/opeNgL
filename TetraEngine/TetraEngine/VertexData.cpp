
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "VertexData.h"

std::vector<VertexData> VertexData::collection = std::vector<VertexData>{};

extern std::vector<Vertex> verts;
extern std::vector<unsigned int> faces;
extern float* vert;
extern Texture2D* texture = nullptr;
extern unsigned int VBO;
extern unsigned int VAO;
extern unsigned int EBO;
extern glm::mat4 transform;

VertexData::VertexData(int id) : id(id)
{
    vert = NULL;
    verts = {};
    faces = {};
    transform = glm::mat4(1.0f);
}
VertexData* VertexData::CreateVertexData(int id)
{
    if (id > collection.size() || id < 0)
    {
        id = collection.size();
        collection.push_back(VertexData(id));
    }
    else
    {
        collection.insert(collection.begin() + id,VertexData(id));
    }
    return GetPrefab(id);
}
void VertexData::Setup() {
    
    if (texture == nullptr)
    {
        setTexture("Assets/container.jpg");
    }
    setTexture("Assets/container.jpg");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.size()*sizeof(unsigned int), &faces[0], GL_STATIC_DRAW);
    }

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray(0);
        
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
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
    texture->Bind();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, faces.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    texture->Unbind();
}
void VertexData::Transform(glm::mat4 transform)
{
    this->transform = transform;
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
void VertexData::setTexture(Texture2D* tex)
{
    texture = tex;
}
void VertexData::setTexture(const char* path)
{
    texture = new Texture2D();
    texture->Load(path);
}
void VertexData::InitialisePrefabs() {

    VertexData* rect = VertexData::CreateVertexData(0);

    Vertex vertices[] = {
        Vertex(-0.5f, -0.5f, 0.0f,/*color*/ 1.0f, 1.0f, 1.0f, /*uv*/ 0.0f, 0.0f),
        Vertex(0.5f, -0.5f, 0.0f, /*color*/ 1.0f, 1.0f, 1.0f, /*uv*/ 1.0f, 0.0f),
        Vertex(-0.5f,  0.5f, 0.0f,/*color*/ 1.0f, 1.0f, 1.0f, /*uv*/ 0.0f, 1.0f),
        Vertex(0.5f,  0.5f, 0.0f, /*color*/ 1.0f, 1.0f, 1.0f, /*uv*/ 1.0f, 1.0f),
    };
    unsigned int index[] = {
        0, 1, 2,
        1, 2, 3,
    };

    rect->LoadVerts(vertices,4);
    rect->LoadFaces(index,6);
    rect->Setup();
    rect->transform = glm::scale(rect->transform, glm::vec3(2,2,2));

}
VertexData* VertexData::GetPrefab(int id) {
    return &collection[id];
}
