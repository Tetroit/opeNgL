#include "MeshRenderer.h"

MeshRenderer MeshRenderer::defaultRenderer = MeshRenderer(nullptr, nullptr);

extern std::shared_ptr<VertexData> mesh;
extern Texture2D* texture = nullptr;
extern Material* material = nullptr;
extern Shader* shader;
extern Camera* camera;

MeshRenderer::MeshRenderer(std::shared_ptr<VertexData> vd, Shader* sh) : mesh(vd), shader(sh), camera(Camera::main), material(&Material::defaultMaterial) {
    texture = nullptr;
}

void MeshRenderer::Render(glm::mat4 transform) {

    //if (texture == nullptr)
    //    setTexture("Assets/container.jpg");

    if (mesh == nullptr) {

        mesh = VertexData::GetPrefab(0);
        shader = Shader::billboardShader;
    }
    if (material != nullptr) {
        shader->SetVec3("surface.ambient", material->ambient);
        shader->SetVec3("surface.diffuse", material->diffuse);
        shader->SetVec3("surface.specular", material->specular);
        shader->SetFloat("surface.smoothness", material->smoothness);
    }
    glm::mat4 view = Camera::main->GetViewMatrix();

    shader->Use();
    shader->SetMat4("projection", Camera::main->projectionView);
    shader->SetMat4("view", view);
    shader->SetMat4("transform", transform);

    if (texture) texture->Bind();
    mesh->Draw();
    if (texture) texture->Unbind();
}

void MeshRenderer::setTexture(Texture2D* tex)
{
    texture = tex;
}
void MeshRenderer::setTexture(const char* path)
{
    texture = new Texture2D();
    texture->Load(path);
}

void MeshRenderer::InitialiseRenderer() {
    defaultRenderer = MeshRenderer(VertexData::GetPrefab(0), Shader::billboardShader);
    defaultRenderer.setTexture("Assets/default.png");
}