#pragma once

#include "engine/window.hpp"
#include "engine/scene.hpp"

class Engine {
public:
    Engine(uint32_t width, uint32_t height, const std::string& title);
    ~Engine();

    bool Init();
    void Run();
    void Stop() { running = false; };
    void Shutdown() { window->Close(); };

    void SetScene(Scene* new_scene) { scene = new_scene; };
    Scene* GetScene() const { return scene; };

private:
    Window* window;
    Scene* scene;

    bool running;

    float current_time, delta_time;

    void ProcessInput();

    void Update(const float delta_time);

    void Render();
};