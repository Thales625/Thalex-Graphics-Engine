#include "../../include/engine/scene.hpp"

#include <iostream>

// Constructor
Scene::Scene(std::shared_ptr<Camera> camera)
    : main_camera(camera) {}

// Add a GameObject to the scene
void Scene::AddGameObject(std::shared_ptr<GameObject> object) {
    game_objects.push_back(object);
}

// Update all objects in the scene
void Scene::Update(float delta_time) const {
    for (auto& object : game_objects) {
        object->Update(delta_time);
    }
} 

// Render all objects in the scene
void Scene::Render(std::unique_ptr<Window>& window) const {
    glm::mat4 m_model;
    glm::mat4 m_view = main_camera->GetViewMatrix();
    glm::mat4 m_projection = GetProjectionMatrix(window);

    for (auto& object : game_objects) {
        m_model = glm::translate(glm::mat4(1.0f), object->GetTransform().position);

        std::cout << object->GetTransform().position.x << std::endl;

        object->Render(m_model, m_view, m_projection);
    }
    std::cout << "+++++++++++++++++++++" << std::endl;
}

glm::mat4 Scene::GetProjectionMatrix(std::unique_ptr<Window>& window) const {
    int width, height;
    window->GetFrameBufferSize(&width, &height);
    return glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 100.0f);
}

// Set the main camera
void Scene::SetMainCamera(std::shared_ptr<Camera> camera) {
    main_camera = camera;
}

// Get the main camera
std::shared_ptr<Camera> Scene::GetMainCamera() const {
    return main_camera;
}
