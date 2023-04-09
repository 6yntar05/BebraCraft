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
    void readMeshes() {

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
        
        this->readMeshes();

        tinygltf::Image tex = this->model.images.at(0);
        bebra::graphics::loadTexture(&_TMP_tex, tex.image, tex.width, tex.height, tex.component);
    }

    void render() const {
        for (auto& mesh : this->meshes)
            mesh.render();
    }
};

} // namespace bebra::objects