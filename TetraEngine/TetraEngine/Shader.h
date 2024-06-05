#ifndef SHADER_H
#define SHADER_H


#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
	public:
        static Shader* billboardShader;
		unsigned int ID;
        Shader(const char* vertexPath, const char* fragmentPath);
        void Use();
        void SetBool(const std::string& name, bool value) const;
        void SetInt(const std::string& name, int value) const;
        void SetFloat(const std::string& name, float value) const;
        void SetMat4(const std::string& name, glm::mat4 &value) const;
        static void InitialiseShaders();
};
#endif
