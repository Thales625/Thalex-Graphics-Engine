#include "engine/engine.hpp"

#include <glm/ext/vector_float3.hpp>

#include <iostream>
#include <memory>
#include <vector>

#define VERTEX_SHADER_FILE "shaders/vertex.glsl"
#define FRAGMENT_SHADER_FILE "shaders/fragment.glsl"

std::shared_ptr<GameObject> CubeTest(glm::vec3 c);

// Constructor: initialize window, scene, and other components
Engine::Engine(uint32_t width, uint32_t height, const std::string& title)
    : window(std::make_unique<Window>(width, height, title)),
      running(false) {}

// Initialize the engine (OpenGL, window, scene, etc.)
bool Engine::Init() {
    if (!window->Init()) {
        std::cerr << "Failed to initialize window!" << std::endl;
        return false;
    }

    // Initialize OpenGL settings, scene, etc.
    glEnable(GL_DEPTH_TEST);

    return true;
}

// Start the main loop of the engine
void Engine::Run() {
    running = true;

    float last_time = 0.0f;

    // DEBUG
    auto camera = std::make_shared<Camera>(glm::vec3(0, 0, 0), 0, 0);
    auto scene = std::make_shared<Scene>(camera);
    SetScene(scene);

    auto cube_0 = CubeTest(glm::vec3(1.0f, 0, 0));

    scene->AddGameObject(cube_0);

    while (running && !window->ShouldClose()) {
        current_time = static_cast<float>(glfwGetTime());
        delta_time = current_time - last_time;
        last_time = current_time;

        window->PollEvents();

        if (scene) {
            scene->GetMainCamera()->ProcessKeyboardInput(window, delta_time);
            scene->GetMainCamera()->ProcessMouseMovement(window, delta_time);
            scene->Update(delta_time);
        }

        Render();

        window->SwapBuffers();
    }

    // Shutdown when the loop exits
    Shutdown();
}


// Render the current scene
void Engine::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (scene) {
        scene->Render(window);
    }
}


std::shared_ptr<GameObject> CubeTest(glm::vec3 color) {
    #include "../assets/suzanne.hpp"

    std::cout << "NORMALS: " << vertices_normals.size() << std::endl;
    std::cout << "POSITIONS: " << vertices_pos.size() << std::endl;
    std::cout << "FACES: " << faces.size() << std::endl;
    

    unsigned int i = 0;
    for (auto& vertex : vertices_pos) {
        vertex.normal = vertices_normals[i];
        i++;
    }

    auto mesh = std::make_shared<Mesh>(vertices_pos, faces);

    auto shader = std::make_shared<Shader>(VERTEX_SHADER_FILE, FRAGMENT_SHADER_FILE);
    auto material = std::make_shared<Material>(shader, color);

    return std::make_shared<GameObject>(mesh, material);
}