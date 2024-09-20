#pragma once

#include <memory>

#include "engine/scene.hpp"
#include "engine/window.hpp"

class Engine {
public:
    Engine(uint32_t width, uint32_t height, const std::string& title);

    bool Init();
    void Run();
    void Stop();
    void Shutdown();

    void SetScene(std::shared_ptr<Scene> scene);

private:
    std::unique_ptr<Window> window;
    std::shared_ptr<Scene> scene;

    bool running;

    float current_time, delta_time;

    void ProcessInput();

    void Update(const float delta_time);

    void Render();
};