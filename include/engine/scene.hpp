#pragma once

#include "engine/game_object.hpp"
#include "engine/camera.hpp"

#include <vector>

class Scene {
public:
    Scene(Camera* camera);

    void AddGameObject(GameObject* object);

    glm::vec3 sun_dir;

    glm::mat4 GetProjectionMatrix(Window* window) const;

    void Render(Window* window) const;

    void SetCamera(Camera* new_camera) { camera = new_camera; };
    Camera* GetCamera() const { return camera; };

    void Update(const float delta_time) const;

private:
    Camera* camera;

    std::vector<GameObject*> game_objects;
};