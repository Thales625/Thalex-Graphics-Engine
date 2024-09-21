#pragma once

#include <memory>

#include "engine/window.hpp"
#include "engine/scene.hpp"

class Engine {
public:
    Engine(uint32_t width, uint32_t height, const std::string& title);

    bool Init();
    void Run();
    void Stop() { running = false; };
    void Shutdown() { window->Close(); };

    void SetScene(std::shared_ptr<Scene> new_scene) { scene = new_scene; };
    std::shared_ptr<Scene> GetScene() const { return scene; };

private:
    std::unique_ptr<Window> window;
    std::shared_ptr<Scene> scene;

    bool running;

    float current_time, delta_time;

    void ProcessInput();

    void Update(const float delta_time);

    void Render();
};