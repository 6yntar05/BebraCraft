#pragma once
#include "engine/graphics/shaders.h"
#include "engine/graphics/textures.h"
#include "engine/objects/mesh.h"

#include "tiny_gltf.h"
#include <string>
#include <glm/glm.hpp>

namespace bebra::objects {

class Model {
private:
    void nodeTransformation(const tinygltf::Node& node, glm::mat4& transform);

    template<typename T>
    void readIndices(const tinygltf::Model& model, const tinygltf::Primitive& primitive, std::vector<GLuint>& indices);

    bebra::objects::Mesh processMesh(const tinygltf::Mesh& srcmesh, bebra::objects::Mesh& mesh);
    void processNodeRecursive(const tinygltf::Node& node, glm::mat4 parentTransform);

    void readModel();

public:
    tinygltf::Model model;
    std::vector<Mesh> meshes;

    Model(const std::string& path);
    void render(glm::vec3 pos, graphics::BlockShaderApi& shader) const;
};

} // namespace bebra::objects