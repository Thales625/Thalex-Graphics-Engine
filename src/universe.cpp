#include "universe.hpp"
#include "mesh.hpp"
#include "utils.hpp"
#include "vessel.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glm/fwd.hpp>

#include "GLFW/glfw3.h"

#include <iostream>
#include <ostream>
#include <string>
#include <vector>

// #define WIREFRAME

// constructor
Universe::Universe(uint32_t width, uint32_t height, const std::string& title) : window(new Window(width, height, title)) {}

// deconstructor
Universe::~Universe() {
    // free scene vessels
    for (auto& vessel : this->scene.GetVessels()) {
        delete vessel;
    }
    
    // free meshs
    for (auto& mesh : this->GetMeshes()) {
        delete mesh;
    }

    // free window
    delete this->window;
}

// init engine (OpenGL, GLFW, etc)
bool Universe::Init() {
    if (!this->window->Init()) {
        std::cerr << "Failed to initialize window!" << std::endl;
        return false;
    }

    glfwSwapInterval(1); // limit fps
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

bool Universe::LoadMesh(Mesh*& mesh_ptr, const std::string& obj_file_path, const std::string& vertex_shader_path, const std::string& fragment_shader_path, const std::string& texture_path) {
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

bool Universe::LoadMesh(Mesh*& mesh_ptr, const std::string& obj_file_path, const std::string& vertex_shader_path, const std::string& fragment_shader_path) {
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
void Universe::Run() {
    float last_time = 0.0f;

    #define VERTEX_SHADER_FILE "assets/shaders/default.vert"
    #define FRAGMENT_SHADER_FILE "assets/shaders/default.frag"
    #define FRAGMENT_NO_TEX_SHADER_FILE "assets/shaders/no_texture.frag"

    // load meshes
    Mesh* mesh_engine;
    if (!this->LoadMesh(mesh_engine, "assets/models/engine.obj", VERTEX_SHADER_FILE, FRAGMENT_NO_TEX_SHADER_FILE)) return;

    Mesh* mesh_vessel;
    if (!this->LoadMesh(mesh_vessel, "assets/models/rocket.obj", VERTEX_SHADER_FILE, FRAGMENT_SHADER_FILE, "assets/textures/rocket.png")) return;

    // terrain
    MeshTerrain* mesh_terrain;
    {
        auto [vertices_array, indices_array] = GenerateGrid(100, 100);
        
        unsigned int heightmap_id = LoadTexture("assets/textures/terrain_disp.png");
        unsigned int texture_id = LoadTexture("assets/textures/terrain.jpg");

        // unsigned int heightmap_id = LoadTexture("assets/textures/heightmap_mountain.png");
        // unsigned int texture_id = LoadTexture("assets/textures/terrain.jpg");

        // unsigned int heightmap_id = LoadTexture("assets/textures/heightmap_face.png");
        // unsigned int texture_id = LoadTexture("assets/textures/terrain.jpg");

        mesh_terrain = new MeshTerrain(vertices_array, indices_array, "assets/shaders/terrain.vert", "assets/shaders/terrain.frag", heightmap_id, texture_id);
    }
    
    Terrain* terrain = this->scene.SetTerrain(new Terrain(mesh_terrain));
    terrain->transform.scale.x = terrain->transform.scale.z = 50.0f;
    terrain->transform.scale.y = 2.0f;

    // vessel & engine
    Vessel* vessel = this->scene.AddVessel(new Vessel(mesh_vessel));
    Engine* engine = vessel->AddEngine(new Engine(mesh_engine, glm::radians(20.0f)));
    this->scene.SetActiveVessel(vessel);

    // scale
    vessel->transform.scale = glm::vec3(1.5f);
    engine->transform.scale = glm::vec3(1.5f);

    // camera
    Camera* camera = &this->scene.camera;

    camera->sensitivity = 40.0f;

    camera->SetPosition({0, 0, 0});

    // setup game objects

    glm::vec3 gravity = {0, -1.62f, 0};
    glm::vec3 velocity = {0, 0, 0};

    float pitch, yaw = 0.0f;

    // main loop
    while (!this->window->GetShouldClose()) {
        this->current_time = static_cast<float>(glfwGetTime());
        this->delta_time = this->current_time - last_time;
        last_time = this->current_time;

        camera->ProcessKeyboardInput(this->window, this->delta_time);
        camera->ProcessMouseMovement(this->window, this->delta_time);

        // update scene
        this->scene.Update(this->delta_time, this->current_time);

        this->window->PollEvents();
        this->Render();
        this->ImGuiRender();
        this->window->SwapBuffers();
    }
}

// render this->scene
void Universe::Render() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->scene.Render(this->window);
}

void Universe::ImGuiRender() {
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
    ImGui::SliderFloat("Speed", &this->scene.camera.speed, 0.1f, 10.0f, "%.1f m/s");
    ImGui::SliderFloat("Sensitivity", &this->scene.camera.sensitivity, 0.1f, 100.0f, "%.1f");

    ImGui::End();

    // render ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
