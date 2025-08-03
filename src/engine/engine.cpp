#include "engine/engine.hpp"
#include "engine/mesh.hpp"
#include "utils/utils.hpp"
#include "engine/game_object.hpp"

// IMGUI
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <cstdlib>
#include <glm/fwd.hpp>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

//#define WIREFRAME

#define VERTEX_SHADER_FILE "shaders/vertex.glsl"
#define FRAGMENT_SHADER_FILE "shaders/fragment.glsl"
#define FRAGMENT_NO_TEX_SHADER_FILE "shaders/fragment_no_tex.glsl"

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
    // TODO: check if mesh is loaded -> model loader

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

    // load meshes
    Mesh* mesh_face;
    if (!this->LoadMesh(mesh_face, "./assets/pack/face.obj", VERTEX_SHADER_FILE, FRAGMENT_SHADER_FILE, "./assets/pack/face.png")) return;

    Mesh* mesh_jeep;
    if (!this->LoadMesh(mesh_jeep, "./assets/jeep.obj", VERTEX_SHADER_FILE, FRAGMENT_SHADER_FILE, "./assets/jeep.jpg")) return;

    Mesh* mesh_starship;
    if (!this->LoadMesh(mesh_starship, "./assets/starship.obj", VERTEX_SHADER_FILE, FRAGMENT_SHADER_FILE, "./assets/starship.png")) return;

    Mesh* mesh_cube;
    if (!this->LoadMesh(mesh_cube, "./assets/cube.obj", VERTEX_SHADER_FILE, FRAGMENT_NO_TEX_SHADER_FILE)) return;

    Mesh* mesh_suzanne;
    if (!this->LoadMesh(mesh_suzanne, "./assets/suzanne.obj", VERTEX_SHADER_FILE, FRAGMENT_NO_TEX_SHADER_FILE)) return;

    // Mesh* mesh_raptor;
    // if (!this->LoadMesh(mesh_raptor, "./assets/raptor.obj", VERTEX_SHADER_FILE, FRAGMENT_NO_TEX_SHADER_FILE)) return;

    // Mesh* mesh_tank;
    // if (!this->LoadMesh(mesh_tank, "./assets/tank.obj", VERTEX_SHADER_FILE, FRAGMENT_NO_TEX_SHADER_FILE)) return;

    // create objects
    GameObject* face = this->scene.AddGameObject(new GameObject(mesh_face));
    GameObject* jeep = this->scene.AddGameObject(new GameObject(mesh_jeep));
    // GameObject* raptor = this->scene.AddGameObject(new GameObject(mesh_raptor, {125, 125, 125}));
    // GameObject* tank = this->scene.AddGameObject(new GameObject(mesh_tank, {125, 125, 125}));
    GameObject* starship = this->scene.AddGameObject(new GameObject(mesh_starship));
    GameObject* suzanne = this->scene.AddGameObject(new GameObject(mesh_suzanne, {0.5f, 0, 0.4f}));
    GameObject* ground = this->scene.AddGameObject(new GameObject(mesh_cube, {0.3f, 0.3f, 0.3f}));

    // transform
    jeep->transform.position = {40.0f, 0.15f, 0};
    jeep->transform.rotation = {0, glm::pi<float>() * 0.2f, 0};

    // raptor->transform.position = {20.0f, 1.0f, 0};
    // raptor->transform.rotation = {0, 0, glm::pi<float>()};

    // tank->transform.position = {20.0f, 1.2f, 0};
    // tank->transform.rotation = {0, 0, 0};

    starship->transform.scale = glm::vec3(0.3f);

    suzanne->transform.position = {40.0f, 1.0f, 3.0f};
    suzanne->transform.rotation = {0, glm::pi<float>()*0.5f, 0};
    suzanne->transform.scale = glm::vec3(0.5f);

    ground->transform.scale = {50.0f, 0.1f, 50.0f};

    // move camera
    this->scene.GetCamera()->SetPosition({40.0f, 0, 0});

    // main loop
    while (!this->window->GetShouldClose()) {
        this->current_time = static_cast<float>(glfwGetTime());
        this->delta_time = this->current_time - last_time;
        last_time = this->current_time;

        this->scene.GetCamera()->ProcessKeyboardInput(this->window, this->delta_time);
        this->scene.GetCamera()->ProcessMouseMovement(this->window, this->delta_time);

        this->scene.Update(this->delta_time, this->current_time);

        // specific updates
        suzanne->transform.rotation = {0, this->current_time, 0};

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