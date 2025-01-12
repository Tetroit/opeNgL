#pragma once

#include <string>
#include <glm/glm.hpp>

class Shader
{
	public:
        static Shader* billboardShader;
        static Shader* skysphereShader;
        static Shader* skyboxShader;
        static Shader* textShader;
        static Shader* currentShader;

		unsigned int ID;
        bool isUpdatedThisFrame = false;
        Shader(const char* vertexPath, const char* fragmentPath);
        void Use();
        void SetBool(const std::string& name, bool value) const;
        void SetInt(const std::string& name, int value) const;
        void SetFloat(const std::string& name, float value) const;
        void SetMat4(const std::string& name, glm::mat4& value) const;
        void SetVec3(const std::string& name, const glm::vec3& value) const;
        void SetVec4(const std::string& name, glm::vec4& value) const;
        void SetVec3(const std::string& name, float x, float y, float z) const;
        void SetVec4(const std::string& name, float x, float y, float z, float w) const;
        static void InitialiseShaders();
};