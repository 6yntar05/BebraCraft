#pragma once
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
// #define TINYGLTF_NOEXCEPTION // optional. disable exception handling.
#include "tiny_gltf.h"
#include <string>

namespace bebra::objects {

class Model {
private:
public:
    tinygltf::Model model;


    Model(const std::string path) {
        tinygltf::TinyGLTF loader;
        std::string err;
        std::string warn;

        bool ret = loader.LoadASCIIFromFile(&model, &err, &warn, path.c_str());
        //bool ret = loader.LoadBinaryFromFile(&model, &err, &warn, path.c_str()); // for binary glTF(.glb)


        if (!warn.empty()) {
            printf("Warn: %s\n", warn.c_str());
        }

        if (!err.empty()) {
            printf("Err: %s\n", err.c_str());
        }

        if (!ret) {
            printf("Failed to parse glTF\n");
        }
    }
};

} // namespace bebra::objects