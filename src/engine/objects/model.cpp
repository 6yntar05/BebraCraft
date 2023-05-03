//#define DEBUG
#include "engine/graphics/textures.h"
#define TINYGLTF_IMPLEMENTATION
#define TINYGLTF_NOEXCEPTION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "engine/objects/model.h"
#include <glm/gtc/matrix_transform.hpp>

namespace bebra::objects {

// class Model:
// private:
void Model::nodeTransformation(const tinygltf::Node& node, glm::mat4& transform) {
    glm::mat4 newTransform = glm::mat4(1.0f);
    if (!node.matrix.empty()) {
        std::vector<float> mat;
        mat.resize(4*4);
        for (int i = 0; i < 4*4; i ++)
            mat.at(i) = node.matrix.at(i);
        newTransform *= glm::make_mat4(mat.data());
    } else {
        if (!node.translation.empty())
            newTransform = glm::translate(newTransform, glm::vec3(node.translation[0], node.translation[1], node.translation[2]));
        if (!node.rotation.empty())
            newTransform*= glm::mat4_cast(glm::quat(node.rotation[3], node.rotation[0], node.rotation[1], node.rotation[2]));
        if (!node.scale.empty())
            newTransform = glm::scale(newTransform, glm::vec3(node.scale[0], node.scale[1], node.scale[2]));
    }
    transform *= newTransform;
}

template<typename T>
void Model::readIndices(const tinygltf::Model& model, const tinygltf::Primitive& primitive, std::vector<GLuint>& indices) {
    tinygltf::Accessor accessor = model.accessors.at(primitive.indices);
    const tinygltf::BufferView& bufferView = model.bufferViews[accessor.bufferView];
    const T* idata = reinterpret_cast<const T*>(&model.buffers.at(0).data[bufferView.byteOffset + accessor.byteOffset]);

    #ifdef DEBUG
    std::cerr << "indices:("<<accessor.count<<") " << primitive.indices << '\n';
    #endif
    for (size_t i = 0; i < accessor.count; i++) {
        #ifdef DEBUG
        std::cerr << '\t' << idata[i] << '\n';
        #endif
        indices.push_back(idata[i]);
    }
}

bebra::objects::Mesh Model::processMesh(const tinygltf::Mesh& srcmesh, bebra::objects::Mesh& mesh) {
    // Buffers
    for (const tinygltf::Primitive& primitive : srcmesh.primitives) {
        // Vertex data
        std::vector<bebra::objects::Vertex> vertices;
        for (auto& i : primitive.attributes) {
            #ifdef DEBUG
            std::cerr << "Buffer index: " << i.second << '\n';
            #endif

            tinygltf::Accessor accessor = model.accessors.at(i.second);
            const tinygltf::BufferView& bufferView = model.bufferViews[accessor.bufferView];
            const float* data = reinterpret_cast<const float*>(&model.buffers.at(0).data[bufferView.byteOffset + accessor.byteOffset]);
            
            #ifdef DEBUG
            std::cerr << "Accessors count: " << accessor.count << '\n';
            #endif
            if (vertices.size() < accessor.count)
                vertices.resize(accessor.count);
            
            for (size_t k = 0; k < accessor.count; k++) {
                if ((accessor.type == 3) && (!i.first.compare("POSITION"))) {
                    #ifdef DEBUG
                    std::cerr << "POSITION: " << data[k * 3 + 0] << " : " << data[k * 3 + 1] << " : " << data[k * 3 + 2] << '\n';
                    #endif
                    vertices.at(k).Position = {
                        data[k * 3 + 0], data[k * 3 + 1], data[k * 3 + 2]
                    };

                } else if((accessor.type == 3) && (!i.first.compare("NORMAL"))) {
                    #ifdef DEBUG
                    std::cerr << "NORMAL: " << data[k * 3 + 0] << " : " << data[k * 3 + 1] << " : " << data[k * 3 + 2] << '\n';  
                    #endif
                    vertices.at(k).Normal = {
                        data[k * 3 + 0], data[k * 3 + 1], data[k * 3 + 2]
                    };
                    
                } else if((accessor.type == 2) && (!i.first.compare("TEXCOORD_0"))) {
                    #ifdef DEBUG
                    std::cerr << "TEXCOORD_0: " << data[k * 2 + 0] << " : " << data[k * 2 + 1] << '\n';
                    #endif
                    vertices.at(k).TexCoords = { data[k * 2 + 0], data[k * 2 + 1] };
                
                };
            }
        }
        mesh.vertices = vertices;

        // Inidices
        switch(model.accessors.at(primitive.indices).componentType) {
            case TINYGLTF_COMPONENT_TYPE_BYTE:          readIndices<int8_t>  (model, primitive, mesh.indices); break;
            case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE: readIndices<uint8_t> (model, primitive, mesh.indices); break;
            case TINYGLTF_COMPONENT_TYPE_SHORT:         readIndices<int16_t> (model, primitive, mesh.indices); break;
            case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:readIndices<uint16_t>(model, primitive, mesh.indices); break;
            case TINYGLTF_COMPONENT_TYPE_INT:           readIndices<int32_t> (model, primitive, mesh.indices); break;
            case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:  readIndices<uint32_t>(model, primitive, mesh.indices); break;
            default:
                std::cerr << "Unknown index component type! Trying uint\n";
                readIndices<uint32_t>(model, primitive, mesh.indices);
                break;
        }

        // Material data
        if (primitive.material > -1) {
            const tinygltf::Material& material = model.materials.at(primitive.material);
            if (material.pbrMetallicRoughness.baseColorTexture.index >= 0) {
                // If texture...
                const tinygltf::Texture& texture = model.textures.at(material.pbrMetallicRoughness.baseColorTexture.index);
                const tinygltf::Image& image = model.images.at(texture.source);
                mesh.setTexture({image.image, image.width, image.height, image.component});
                
            } else {
                // If base color...
                std::vector<double> basecolor = material.pbrMetallicRoughness.baseColorFactor;
                std::vector<unsigned char> color;

                for (auto channel : basecolor) {
                    double clamped_channel = std::clamp(channel, 0.0, 1.0);
                    unsigned char value = static_cast<unsigned char>(std::round(clamped_channel * 255.0));
                    color.push_back(value);
                }

                // Add missing color components if they are not defined
                if (color.size() == 3) 
                    color.push_back(255); // alpha = 255

                mesh.setTexture({color, 1, 1, static_cast<int>(color.size())});
            }
        }
    }
    return mesh;
}

void Model::processNodeRecursive(const tinygltf::Node& node, glm::mat4 parentTransform) {
    // Combine transformation matrix of the current node with its parent's transformation matrix
    nodeTransformation(node, parentTransform);

    if (node.mesh != -1) {
        // Process the meshes of the current node
        bebra::objects::Mesh mesh {node.name};
        #ifdef DEBUG
        std::cerr << "NAME: " << node.name << '\n';
        #endif
        processMesh(model.meshes.at(node.mesh), mesh);
        // Write mesh
        mesh.transform = parentTransform;
        mesh.updateMesh();
        meshes.push_back(mesh);
    }

    // Recursively process child nodes
    for (int childIndex : node.children)
        processNodeRecursive(model.nodes.at(childIndex), parentTransform);
}

void Model::readModel() {
    #ifdef DEBUG
    std::cout << "Scenes: " << model.scenes.size() << '\n';
    std::cout << "Nodes: "  << model.nodes.size()  << '\n';
    std::cout << "Meshed: " << model.meshes.size() << '\n';
    #endif

    // Recursive descend to every children nodes considering parent transition (=>mat4)
    const tinygltf::Scene& scene = model.scenes.at(model.defaultScene > -1 ? model.defaultScene : 0);
    for (auto nodeIndex : scene.nodes)
        processNodeRecursive(model.nodes.at(nodeIndex), glm::mat4(1.0f));

    // Process meshes that are not part of a scene node
    //for (const auto& srcmesh : model.meshes) {
    //    bebra::objects::Mesh mesh {};
    //    processMesh(srcmesh, mesh);
    //    // Write mesh
    //    mesh.transform = glm::mat4(1.0f);
    //    mesh.updateMesh();
    //    meshes.push_back(mesh);
    //}

    //for (const auto& node : model.nodes) {
    //    processNodeRecursive(node, glm::mat4(1.0f));
    //}
}

// public:
Model::Model(const std::string& path) {
    tinygltf::TinyGLTF loader;
    std::string err, warn;

    bool ret;
    if (!path.substr(path.size()-4, path.size()).compare(".glb"))
        ret = loader.LoadBinaryFromFile(&model, &err, &warn, path.c_str());
    else
        ret = loader.LoadASCIIFromFile(&model, &err, &warn, path.c_str());

    if (!ret) {
        printf("Failed to parse glTF\n");
        return;
    }
    if (!warn.empty())
        printf("Warn: %s\n", warn.c_str());

    if (!err.empty())
        printf("Err: %s\n", err.c_str());
    
    this->readModel();
}

void Model::render(glm::vec3 pos, graphics::BlockShaderApi& shader) const {
    shader.program.use();
    for (auto& mesh : this->meshes) {
        // Position
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, pos); // before rotating!
        model *= mesh.transform;
        shader.model(model);

        // Texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mesh.texture.texture);
        glUniform1i(glGetUniformLocation(shader.program.program, "texture"), 0);

        // Render
        mesh.render(); // glm::vec3 pos, graphics::BlockShaderApi& shader
    }
}

} // namespace bebra::objects
