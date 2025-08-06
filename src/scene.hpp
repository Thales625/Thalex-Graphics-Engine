#pragma once

#include "game_object.hpp"
#include "camera.hpp"

#include <vector>

class Scene {
public:
    Scene();

    glm::vec3 sun_dir;

    glm::mat4 GetProjectionMatrix(Window* const window) const;

    void Render(Window* const window) const;

    void Update(const float delta_time, const float current_time);

    inline GameObject* AddGameObject(GameObject* game_obj_ptr) { game_objects.push_back(game_obj_ptr); return game_obj_ptr; };
    inline std::vector<GameObject*> GetGameObjects() const { return game_objects; };

    inline Camera* GetCamera() { return &camera; };

private:
    Camera camera;

    std::vector<GameObject*> game_objects;
};