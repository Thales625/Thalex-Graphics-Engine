#pragma once

#include "engine/game_object.hpp"
#include "engine/camera.hpp"

#include <vector>

class Scene {
public:
    Scene();

    glm::vec3 sun_dir;

    glm::mat4 GetProjectionMatrix(Window* window) const;

    void Render(Window* window) const;

    void Update(const float delta_time) const;

    GameObject* AddGameObject(GameObject* game_obj_ptr) { game_objects.push_back(game_obj_ptr); return game_obj_ptr; };
    std::vector<GameObject*> GetGameObjects() const { return game_objects; };

    Camera* GetCamera() { return &camera; };

private:
    Camera camera;

    std::vector<GameObject*> game_objects;
};