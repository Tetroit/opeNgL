
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "VertexData.h"

extern std::vector<Vertex> verts;
extern std::vector<unsigned int> faces;
extern float* vert;
extern Shader* shader;
extern Texture2D* texture;
extern unsigned int VBO;
extern unsigned int VAO;
extern unsigned int EBO;
extern glm::mat4 transform;

VertexData::VertexData(int id) : id(id)
{
    vert = NULL;
    verts = {};
    faces = {};
}
void VertexData::Setup() {
    
    shader = new Shader("shaders/vertexShader.glvs", "shaders/fragmentShader.glfs");
    texture = new Texture2D();
    texture->Load("Assets/container.jpg");

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
    shader->Use();

    transform = glm::mat4(1.0f);
    transform = glm::rotate(transform, Time::time, glm::vec3(0.0f, 0.9f, 0.1f));
    //transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, 1.0f));
    Transform(transform);

    texture->Bind();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
void VertexData::Transform(glm::mat4 transform)
{
    unsigned int transformLoc = glGetUniformLocation(shader->ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
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
