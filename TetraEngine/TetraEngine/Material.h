#pragma once

#include <glm/glm.hpp>
#include <string>

class Material
{
private:
    inline static int lastId = 0;

    int id;

public:
    static Material defaultMaterial;

    glm::vec3 ambient = glm::vec3(1.f, 1.f, 1.f);
    glm::vec3 diffuse = glm::vec3(1.f, 1.f, 1.f);
    glm::vec3 specular = glm::vec3(1.f, 1.f, 1.f);
    float smoothness = 16;
    std::string name;
    Material(std::string name) : name(name) { id = lastId++; }
    Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) : ambient(ambient), diffuse(diffuse), specular(specular), name(name) { id = lastId++; }
};


