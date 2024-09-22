#pragma once

#include "engine/window.hpp"
#include "engine/scene.hpp"

class Engine {
public:
    Engine(uint32_t width, uint32_t height, const std::string& title);
    ~Engine();

    float current_time, delta_time;

    bool Init();
    void Run();

private:
    Window* window;
    Scene scene;

    void ProcessInput();

    void Update(const float delta_time);

    void Render();
};