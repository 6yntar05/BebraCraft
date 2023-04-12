#pragma once
#include "engine/graphics/shaders.h"
#include "engine/graphics/textures.h"
#include "engine/objects/mesh.h"
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define TINYGLTF_NOEXCEPTION
#include "tiny_gltf.h"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace bebra::objects {

class Model {
private:
    void nodeTransformation(const tinygltf::Node& node, glm::mat4& transform) {
        glm::mat4 newTransform = glm::mat4(1.0f);
        if (!node.matrix.empty()) {
            std::vector<float> mat;
            mat.resize(4*4);
            for (int i = 0; i < 4*4; i ++)
                mat.at(i) = node.matrix.at(i);
            newTransform *= glm::make_mat4(mat.data());
        } else {
            if (!node.translation.empty()) newTransform = glm::translate(newTransform, glm::vec3(node.translation[0], node.translation[1], node.translation[2]));
            if (!node.rotation.empty())    newTransform*= glm::mat4_cast(glm::quat(node.rotation[3], node.rotation[0], node.rotation[1], node.rotation[2]));
            if (!node.scale.empty())       newTransform = glm::scale(newTransform, glm::vec3(node.scale[0], node.scale[1], node.scale[2]));
        }
        transform *= newTransform;
    }

    void processNodeRecursive(const tinygltf::Node& node, glm::mat4 parentTransform) {
        // Combine transformation matrix of the current node with its parent's transformation matrix
        nodeTransformation(node, parentTransform);

        if (node.mesh != -1) {
            // Process the meshes of the current node
            bebra::objects::Mesh mesh {node.name};

            // Buffers
            for (const tinygltf::Primitive& primitive : model.meshes.at(node.mesh).primitives) {
                // FIXME: material assigned to each primitive
                // but we only consider the last one, because fucked up
                if (primitive.material > -1) {
                    const tinygltf::Material& material = model.materials.at(primitive.material);
                    if (material.pbrMetallicRoughness.baseColorTexture.index >= 0) {
                        const tinygltf::Texture& texture = model.textures.at(material.pbrMetallicRoughness.baseColorTexture.index);
                        const tinygltf::Image& image = model.images.at(texture.source);
                        graphics::Texture tex {image.image, image.width, image.height, image.component};
                        mesh.setTexture(tex);
                    }
                }

                // Vertex data
                std::vector<bebra::objects::Vertex> vertices;
                for (auto& i : primitive.attributes) {
                    //std::cout << "Buffer index: " << i.second << '\n';

                    tinygltf::Accessor accessor = model.accessors.at(i.second);
                    const tinygltf::BufferView& bufferView = model.bufferViews[accessor.bufferView];
                    const float* data = reinterpret_cast<const float*>(&model.buffers.at(0).data[bufferView.byteOffset + accessor.byteOffset]);

                    //std::cout << "Accessors count: " << accessor.count << '\n';
                    if (vertices.size() < accessor.count)
                        vertices.resize(accessor.count);
                    
                    for (size_t k = 0; k < accessor.count; k++) {
                        if ((accessor.type == 3) && (!i.first.compare("POSITION"))) {
                            //std::cerr << "POSITION: " << data[k * 3 + 0] << " : " << data[k * 3 + 1] << " : " << data[k * 3 + 2] << '\n';
                            vertices.at(k).Position = {
                                data[k * 3 + 0], data[k * 3 + 1], data[k * 3 + 2]
                            };

                        } else if((accessor.type == 3) && (!i.first.compare("NORMAL"))) {
                            //std::cerr << "NORMAL: " << data[k * 3 + 0] << " : " << data[k * 3 + 1] << " : " << data[k * 3 + 2] << '\n';  
                            vertices.at(k).Normal = {
                                data[k * 3 + 0], data[k * 3 + 1], data[k * 3 + 2]
                            };
                            
                        } else if((accessor.type == 2) && (!i.first.compare("TEXCOORD_0"))) {
                            //std::cerr << "TEXCOORD_0: " << data[k * 2 + 0] << " : " << data[k * 2 + 1] << '\n';
                            vertices.at(k).TexCoords = { data[k * 2 + 0], data[k * 2 + 1] };
                        
                        } else throw std::bad_typeid();
                    }
                }
                mesh.vertices = vertices;

                // Inidices
                tinygltf::Accessor accessor = model.accessors.at(primitive.indices);
                const tinygltf::BufferView& bufferView = model.bufferViews[accessor.bufferView];
                const short* idata = reinterpret_cast<const short*>(&model.buffers.at(0).data[bufferView.byteOffset + accessor.byteOffset]);
                //std::cout << "indices:("<<accessor.count<<") " << primitive.indices << '\n';
                for (size_t i = 0; i < accessor.count; i++) {
                    //std::cout << '\t' << idata[i] << '\n';
                    mesh.indices.push_back(idata[i]);
                }
            }

            // Write mesh
            mesh.transform = parentTransform;
            mesh.updateMesh();
            meshes.push_back(mesh);
        }

        // Recursively process child nodes
        for (int childIndex : node.children)
            processNodeRecursive(model.nodes.at(childIndex), parentTransform);
    }

    void readModel() {
        // Recursive descend to every children nodes considering parent transition (=>mat4)
        const tinygltf::Scene& scene = model.scenes.at(model.defaultScene > -1 ? model.defaultScene : 0);
        processNodeRecursive(model.nodes.at(scene.nodes.at(0)), glm::mat4(1.0f));
    }

public:
    tinygltf::Model model;
    std::vector<Mesh> meshes;
    GLuint _TMP_tex;

    Model(const std::string& path) {
        tinygltf::TinyGLTF loader;
        std::string err, warn;

        bool ret = loader.LoadASCIIFromFile(&model, &err, &warn, path.c_str());
        //bool ret = loader.LoadBinaryFromFile(&model, &err, &warn, path.c_str()); // for binary glTF(.glb)
        if (!ret) {
            printf("Failed to parse glTF\n");
            return;
        }
        if (!warn.empty())
            printf("Warn: %s\n", warn.c_str());

        if (!err.empty())
            printf("Err: %s\n", err.c_str());
        
        this->readModel();

        tinygltf::Image tex = this->model.images.at(0);
        bebra::graphics::loadTexture(&_TMP_tex, tex.image, tex.width, tex.height, tex.component);
    }

    void render(glm::vec3 pos, graphics::BlockShaderApi& shader) const {
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
            mesh.render();
        }
    }
};

} // namespace bebra::objects