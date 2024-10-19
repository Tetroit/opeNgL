#include "LightRenderer.h"


LightRenderer LightRenderer::defaultRenderer = LightRenderer(nullptr, nullptr);\

LightRenderer::LightRenderer() : MeshRenderer(VertexData::GetPrefab(0), Shader::billboardShader) {
}
LightRenderer::LightRenderer(std::shared_ptr<VertexData> vd, Shader* sh) : MeshRenderer(vd, sh) {
}

void LightRenderer::Render(glm::mat4 transform) {

    glm::mat4 view = Camera::main->GetViewMatrix();

    shader->Use();
    shader->SetVec3("color", light.diffuse);
    shader->SetMat4("projection", Camera::main->projectionView);
    shader->SetMat4("view", view);
    shader->SetMat4("transform", transform);

    mesh->Draw();
}
void LightRenderer::InitialiseRenderer() {
    defaultRenderer = LightRenderer();
}
