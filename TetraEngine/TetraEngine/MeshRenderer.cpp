#include "MeshRenderer.h"

extern VertexData* mesh;
extern Shader* shader;

MeshRenderer::MeshRenderer(VertexData* vd, Shader* sh) : mesh(vd), shader(sh) {

}
void MeshRenderer::Render() {

    shader->Use();
    shader->SetMat4("transform", mesh->transform);
    mesh->Draw();
}