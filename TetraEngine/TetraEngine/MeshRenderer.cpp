#include "MeshRenderer.h"

MeshRenderer MeshRenderer::defaultRenderer = MeshRenderer(nullptr, nullptr);

extern std::shared_ptr<VertexData> mesh;
extern Texture2D* texture = nullptr;
extern Shader* shader;
extern Camera* camera;

MeshRenderer::MeshRenderer(std::shared_ptr<VertexData> vd, Shader* sh) : mesh(vd), shader(sh), camera(Camera::main) {
}
void MeshRenderer::Render(glm::mat4 transform) {

    if (texture == nullptr)
        setTexture("Assets/container.jpg");

    if (mesh != nullptr) {
        shader->Use();
        shader->SetMat4("projection", Camera::main->projectionView);
        glm::mat4 view = Camera::main->GetViewMatrix();
        shader->SetMat4("view", view);
        shader->SetMat4("transform", transform);

        texture->Bind();
        mesh->Draw();
        texture->Unbind();
    }
    else
    {
        std::shared_ptr<VertexData> vd =VertexData::GetPrefab(0);
        Shader* sh = Shader::billboardShader;
        sh->Use();
        sh->SetMat4("projection", Camera::main->projectionView);
        glm::mat4 view = Camera::main->GetViewMatrix();
        sh->SetMat4("view", view);
        sh->SetMat4("transform", transform);

        texture->Bind();
        vd->Draw();
        texture->Unbind();
    }
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
    defaultRenderer.setTexture("Assets/container.jpg");
}