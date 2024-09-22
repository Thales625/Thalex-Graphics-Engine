#include "engine/engine.hpp"
#include "engine/game_object.hpp"
#include "engine/mesh.hpp"
#include "utils/utils.hpp"

#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#define VERTEX_SHADER_FILE "shaders/vertex.glsl"
#define FRAGMENT_SHADER_FILE "shaders/fragment.glsl"

// constructor
Engine::Engine(uint32_t width, uint32_t height, const std::string& title) : window(new Window(width, height, title)) {}

// deconstructor
Engine::~Engine() {
    // free gameobjects
    for (auto& object : scene.GetGameObjects()) {
        delete object;
    }
    
    // free meshs
    for (auto& mesh : GetMeshes()) {
        delete mesh;
    }

    // free window
    delete window;
}

// init engine (OpenGL, GLFW, etc)
bool Engine::Init() {
    if (!window->Init()) {
        std::cerr << "Failed to initialize window!" << std::endl;
        return false;
    }

    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_STENCIL_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClearDepth(1.0f);
    glDepthFunc(GL_LESS);
    glEnable(GL_MULTISAMPLE);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // fill
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);

    return true;
}

/*
TODO
Engine add a vector for MeshRenderer (LoadObj save in this vector)
    LoadObj search in this vector first

LoadObj receive a name, e.g starship -> starship.obj and starship.png/jpg
    search .obj and .image from name

Delete new objects in LoadObj
*/

Mesh* Engine::LoadMesh(const std::string& obj_file_path, const std::string& vertex_shader_path, const std::string& fragment_shader_path, const std::string& texture_path) {
    // TODO: check if mesh is loaded

    unsigned int texture_id = LoadTexture(texture_path);

    std::vector<Mesh::Vertex> vertices_array;
    std::vector<unsigned int> indices_array;
    if (!LoadObj(obj_file_path, vertices_array, indices_array)) {
        std::cerr << "Failed to open file: " << obj_file_path << std::endl;
        exit(EXIT_FAILURE);
    }

    Mesh* new_mesh = new Mesh(vertices_array, indices_array, vertex_shader_path, fragment_shader_path, texture_id);

    meshes.push_back(new_mesh);

    return new_mesh;
}

// main loop
void Engine::Run() {
    float last_time = 0.0f;

    Mesh* mesh_1 = LoadMesh("/home/thales/Dropbox/Codes/Cpp/OpenGL/TGE/assets/jeep.obj", VERTEX_SHADER_FILE, FRAGMENT_SHADER_FILE, "/home/thales/Dropbox/Codes/Cpp/OpenGL/TGE/assets/jeep.jpg");
    Mesh* mesh_2 = LoadMesh("/home/thales/Dropbox/Codes/Cpp/OpenGL/TGE/assets/starship.obj", VERTEX_SHADER_FILE, FRAGMENT_SHADER_FILE, "/home/thales/Dropbox/Codes/Cpp/OpenGL/TGE/assets/starship.png");

    GameObject* new_game_obj = scene.AddGameObject(new GameObject(mesh_1));
    scene.AddGameObject(new GameObject(mesh_2));

    while (!window->GetShouldClose()) {
        current_time = static_cast<float>(glfwGetTime());
        delta_time = current_time - last_time;
        last_time = current_time;

        window->PollEvents();

        scene.GetCamera()->ProcessKeyboardInput(window, delta_time);
        scene.GetCamera()->ProcessMouseMovement(window, delta_time);
        scene.Update(delta_time);
        scene.sun_dir = glm::vec3(0, glm::cos(current_time), glm::sin(current_time));
        new_game_obj->transform.position = glm::vec3(0, 0, current_time);

        Render();

        window->SwapBuffers();
    }
}

// render scene
void Engine::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene.Render(window);
}