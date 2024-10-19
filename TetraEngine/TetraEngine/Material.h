#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Utils.h"

class Material
{
private:
    inline static int lastId = 0;

    int id;

public:
    static Material* defaultMaterial;
    static std::vector<Material> collection;
    static void Initialize();
    static void ParseMTL(std::string path);
    static Material* GetBYName(std::string name);

    glm::vec3 ambient = glm::vec3(1.f, 1.f, 1.f);
    glm::vec3 diffuse = glm::vec3(1.f, 1.f, 1.f);
    glm::vec3 specular = glm::vec3(1.f, 1.f, 1.f);
    float shininess = 16;
    std::string name;
    Material(std::string name) : name(name) { id = lastId++; }
    Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) : ambient(ambient), diffuse(diffuse), specular(specular), name(name) { id = lastId++; }
};


