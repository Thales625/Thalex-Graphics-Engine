#include "engine.hpp"
#include "GLFW/glfw3.h"
#include "mesh.hpp"
#include "utils.hpp"
#include "game_object.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glm/fwd.hpp>

#include <iostream>
#include <ostream>
#include <string>
#include <vector>

// #define WIREFRAME

// constructor
Engine::Engine(uint32_t width, uint32_t height, const std::string& title) : window(new Window(width, height, title)) {}

// deconstructor
Engine::~Engine() {
    // free gameobjects
    for (auto& object : this->scene.GetGameObjects()) {
        delete object;
    }
    
    // free meshs
    for (auto& mesh : GetMeshes()) {
        delete mesh;
    }

    // free window
    delete this->window;
}

// init engine (OpenGL, GLFW, etc)
bool Engine::Init() {
    if (!this->window->Init()) {
        std::cerr << "Failed to initialize window!" << std::endl;
        return false;
    }

    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_STENCIL_TEST);
    glClearColor(0.5f, 0.85f, 1.0f, 1.0f);
    glClearDepth(1.0f);
    glDepthFunc(GL_LESS);
    glEnable(GL_MULTISAMPLE);
	#ifdef WIREFRAME
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe
	#else
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // fill
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);
	#endif

    return true;
}

bool Engine::LoadMesh(Mesh*& mesh_ptr, const std::string& obj_file_path, const std::string& vertex_shader_path, const std::string& fragment_shader_path, const std::string& texture_path) {
    // TODO: check if mesh is loaded -> mesh loader

    // texture
    const unsigned int texture_id = LoadTexture(texture_path);

    if (texture_id) {
        std::cout << "Loaded texture: " << texture_path << std::endl;
    } else {
        std::cerr << "Failed to load texture: " << texture_path << std::endl;
        return false;
    }

    // object
    std::vector<Mesh::Vertex> vertices_array;
    std::vector<unsigned int> indices_array;

    if (LoadObj(obj_file_path, vertices_array, indices_array)) {
        std::cout << "Loaded object: " << obj_file_path << std::endl;
    } else {
        std::cerr << "Failed to load object: " << obj_file_path << std::endl;
        return false;
    }

    // create new mesh
    mesh_ptr = new Mesh(vertices_array, indices_array, vertex_shader_path, fragment_shader_path, texture_id);

    meshes.push_back(mesh_ptr);

    return true;
}

bool Engine::LoadMesh(Mesh*& mesh_ptr, const std::string& obj_file_path, const std::string& vertex_shader_path, const std::string& fragment_shader_path) {
    // TODO: check if mesh is loaded -> model loader

    // object
    std::vector<Mesh::Vertex> vertices_array;
    std::vector<unsigned int> indices_array;

    if (LoadObj(obj_file_path, vertices_array, indices_array)) {
        std::cout << "Loaded object: " << obj_file_path << std::endl;
    } else {
        std::cerr << "Failed to load object: " << obj_file_path << std::endl;
        return false;
    }

    // create new mesh
    mesh_ptr = new Mesh(vertices_array, indices_array, vertex_shader_path, fragment_shader_path);

    meshes.push_back(mesh_ptr);

    return true;
};

// run loop
void Engine::Run() {
    float last_time = 0.0f;

    #define VERTEX_SHADER_FILE "assets/shaders/vertex.glsl"
    #define FRAGMENT_SHADER_FILE "assets/shaders/fragment.glsl"
    #define FRAGMENT_NO_TEX_SHADER_FILE "assets/shaders/fragment_no_tex.glsl"

    // load meshes
    Mesh* mesh_starship;
    if (!this->LoadMesh(mesh_starship, "assets/models/starship.obj", VERTEX_SHADER_FILE, FRAGMENT_SHADER_FILE, "assets/textures/starship.png")) return;

    Mesh* mesh_penguin;
    if (!this->LoadMesh(mesh_penguin, "assets/models/penguin.obj", VERTEX_SHADER_FILE, FRAGMENT_SHADER_FILE, "assets/textures/penguin.png")) return;

    Mesh* mesh_cube;
    if (!this->LoadMesh(mesh_cube, "assets/models/cube.obj", VERTEX_SHADER_FILE, FRAGMENT_NO_TEX_SHADER_FILE)) return;

    Mesh* mesh_bunny;
    if (!this->LoadMesh(mesh_bunny, "assets/models/bunny.obj", VERTEX_SHADER_FILE, FRAGMENT_NO_TEX_SHADER_FILE)) return;

    Mesh* mesh_suzanne;
    if (!this->LoadMesh(mesh_suzanne, "assets/models/suzanne.obj", VERTEX_SHADER_FILE, FRAGMENT_NO_TEX_SHADER_FILE)) return;

    // create objects
    GameObject* starship = this->scene.AddGameObject(new GameObject(mesh_starship));
    GameObject* penguin = this->scene.AddGameObject(new GameObject(mesh_penguin));
    GameObject* cube = this->scene.AddGameObject(new GameObject(mesh_cube));
    GameObject* bunny = this->scene.AddGameObject(new GameObject(mesh_bunny));
    GameObject* suzanne = this->scene.AddGameObject(new GameObject(mesh_suzanne));

    // move camera
    this->scene.GetCamera()->SetPosition({0, 0, 0});

    // setup game objects
    cube->transform.position.x = -2.0f;

    bunny->transform.position.x = 2.0f;
    bunny->transform.rotation.x = glm::radians(90.0f);

    suzanne->transform.position.y = 4.0f;

    // main loop
    while (!this->window->GetShouldClose()) {
        this->current_time = static_cast<float>(glfwGetTime());
        this->delta_time = this->current_time - last_time;
        last_time = this->current_time;

        this->scene.GetCamera()->ProcessKeyboardInput(this->window, this->delta_time);
        this->scene.GetCamera()->ProcessMouseMovement(this->window, this->delta_time);

        this->scene.Update(this->delta_time, this->current_time);

        this->window->PollEvents();
        this->Render();
        this->ImGuiRender();
        this->window->SwapBuffers();
    }
}

// render this->scene
void Engine::Render() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->scene.Render(this->window);
}

void Engine::ImGuiRender() {
    // update ImGui
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // ImGui Window
    ImGui::Begin("Thalex Graphics Engine");

    // performance info
    ImGui::SeparatorText("Performance Info");
    ImGui::Text("current time: %.2f s", this->current_time);
    ImGui::Text("delta time: %.2f ms", this->delta_time*100);
    ImGui::Text("fps: %.2f", 1/this->delta_time);

    // camera settings
    ImGui::SeparatorText("Camera Settings");
    ImGui::SliderFloat("Speed", &this->scene.GetCamera()->camera_speed, 0.1f, 10.0f, "%.1f m/s");

    ImGui::End();

    // render ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}