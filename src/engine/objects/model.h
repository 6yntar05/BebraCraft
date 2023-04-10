#pragma once
#include "engine/objects/mesh.h"
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
// #define TINYGLTF_NOEXCEPTION // optional. disable exception handling.
#include "tiny_gltf.h"
#include <string>

namespace bebra::objects {

class Model {
private:
    void processNodeRecursive(const tinygltf::Node& node, glm::mat4 parentTransform) {
        // Combine transformation matrix of the current node with its parent's transformation matrix
        glm::mat4 transform = glm::mat4(1.0f);
        if (!node.matrix.empty()) {
            std::vector<float> mat;
            mat.resize(4*4);
            for (int i = 0; i < 4*4; i ++)
                mat.at(i) = node.matrix.at(i);
            transform *= glm::make_mat4(mat.data());
        } else
        {
            if (!node.translation.empty()) transform = glm::translate(transform, glm::vec3(node.translation[0], node.translation[1], node.translation[2]));
            if (!node.rotation.empty())    transform*= glm::mat4_cast(glm::quat(node.rotation[3], node.rotation[0], node.rotation[1], node.rotation[2]));
            if (!node.scale.empty())       transform = glm::scale(transform, glm::vec3(node.scale[0], node.scale[1], node.scale[2]));
            transform = parentTransform * transform;
        }

        if (node.mesh != -1) {
            // Process the meshes of the current node
            bebra::objects::Mesh mesh;

            // Buffers
            for (const tinygltf::Primitive& primitive : model.meshes.at(node.mesh).primitives) {
                // Vertex data
                std::vector<bebra::objects::Vertex> vertexes;
                for (auto& i : primitive.attributes) {
                    //std::cout << "Buffer index: " << i.second << '\n';

                    tinygltf::Accessor accessor = model.accessors.at(i.second);
                    const tinygltf::BufferView& bufferView = model.bufferViews[accessor.bufferView];
                    const float* data = reinterpret_cast<const float*>(&model.buffers.at(0).data[bufferView.byteOffset + accessor.byteOffset]);

                    //std::cout << "Accessors count: " << accessor.count << '\n';
                    if (vertexes.size() < accessor.count)
                        vertexes.resize(accessor.count);
                    
                    for (size_t k = 0; k < accessor.count; k++) {
                        if ((accessor.type == 3) && (!i.first.compare("POSITION"))) {
                            //std::cerr << "POSITION: " << data[k * 3 + 0] << " : " << data[k * 3 + 1] << " : " << data[k * 3 + 2] << '\n';

                            vertexes.at(k).Position = {
                                data[k * 3 + 0], 
                                data[k * 3 + 1], 
                                data[k * 3 + 2]
                            };

                        } else if((accessor.type == 3) && (!i.first.compare("NORMAL"))) {
                            //std::cerr << "NORMAL: " << data[k * 3 + 0] << " : " << data[k * 3 + 1] << " : " << data[k * 3 + 2] << '\n';
                            
                            vertexes.at(k).Normal = {
                                data[k * 3 + 0], 
                                data[k * 3 + 1], 
                                data[k * 3 + 2]
                            };
                            
                        } else if((accessor.type == 2) && (!i.first.compare("TEXCOORD_0"))) {
                            //std::cerr << "TEXCOORD_0: " << data[k * 2 + 0] << " : " << data[k * 2 + 1] << '\n';
                            // 3D texcoords for texture arrays

                            vertexes.at(k).TexCoords = {
                                data[k * 2 + 0], 
                                data[k * 2 + 1], 
                            };
                        
                        } else throw std::bad_typeid();
                    }
                }
                mesh.vertices = vertexes;

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
            mesh.transform = transform;
            mesh.updateMesh();
            meshes.push_back(mesh);
        }

        // Recursively process child nodes
        for (int childIndex : node.children)
            processNodeRecursive(model.nodes.at(childIndex), transform);
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

    Model(const std::string path) {
        tinygltf::TinyGLTF loader;
        std::string err, warn;

        bool ret = loader.LoadASCIIFromFile(&model, &err, &warn, path.c_str());
        //bool ret = loader.LoadBinaryFromFile(&model, &err, &warn, path.c_str()); // for binary glTF(.glb)
        if (!ret) 
            printf("Failed to parse glTF\n");

        if (!warn.empty())
            printf("Warn: %s\n", warn.c_str());

        if (!err.empty())
            printf("Err: %s\n", err.c_str());
        
        this->readModel();

        tinygltf::Image tex = this->model.images.at(0);
        bebra::graphics::loadTexture(&_TMP_tex, tex.image, tex.width, tex.height, tex.component);
    }

    void render() const {
        for (auto& mesh : this->meshes)
            mesh.render();
    }
};

} // namespace bebra::objects