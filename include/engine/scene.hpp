#pragma once

#include <memory>

#include "engine/game_object.hpp"
#include "engine/camera.hpp"

class Scene {
public:
    // Constructor: initializes the scene with a main camera
    Scene(std::shared_ptr<Camera> camera);

    void AddGameObject(std::shared_ptr<GameObject> object);

    glm::mat4 GetProjectionMatrix(std::unique_ptr<Window>& window) const;

    void SetMainCamera(std::shared_ptr<Camera> camera);
    std::shared_ptr<Camera> GetMainCamera() const;

    // Updates the scene (could involve updating all game objects)
    void Update(const float delta_time) const;

    // Renders the scene by rendering all GameObjects
    void Render(std::unique_ptr<Window>& window) const;
private:
    // Main camera of the scene
    std::shared_ptr<Camera> main_camera;

    // List of GameObjects in the scene
    std::vector<std::shared_ptr<GameObject>> game_objects;
};