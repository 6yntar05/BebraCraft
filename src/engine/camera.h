#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <iostream>

namespace bebra {

struct Camera {
    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 up;
    float fov;

    float speed;
    float yaw;
    float pitch;

    Camera(
        glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f),
        float fov = 90.0, float speed = 0.05, float yaw = 0.0, float pitch = 0.0,
        glm::vec3 front = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f)
    ) : pos(pos), front(front), up(up), fov(fov), speed(speed), yaw(yaw), pitch(pitch) {}
};

} // namespace bebra