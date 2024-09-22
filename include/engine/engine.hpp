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

    bool LoadMesh(Mesh*& mesh_ptr, const std::string& obj_file_path, const std::string& vertex_shader_path, const std::string& fragment_shader_path, const std::string& texture_path);

    std::vector<Mesh*> GetMeshes() const { return meshes; };

private:
    Window* window;
    Scene scene;

    std::vector<Mesh*> meshes;

    void ProcessInput();

    void Update(const float delta_time);

    void Render();
};