#include "MeshRenderer.h"

MeshRenderer MeshRenderer::defaultRenderer = MeshRenderer(nullptr, nullptr);

extern std::shared_ptr<VertexData> mesh;
extern Shader* shader;
extern Camera* camera;

MeshRenderer::MeshRenderer(std::shared_ptr<VertexData> vd, Shader* sh) : mesh(vd), shader(sh) {

}
void MeshRenderer::Render(glm::mat4 transform) {
    if (mesh != nullptr) {
        shader->Use();
        shader->SetMat4("projection", Camera::main->projectionView);
        glm::mat4 view = Camera::main->GetViewMatrix();
        shader->SetMat4("view", view);
        shader->SetMat4("transform", transform);
        mesh->Draw();
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
        vd->Draw();
    }
}

void MeshRenderer::InitialiseRenderer() {
    defaultRenderer = MeshRenderer(VertexData::GetPrefab(0), Shader::billboardShader);
}