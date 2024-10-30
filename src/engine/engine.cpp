#include "engine/engine.hpp"
#include "engine/mesh.hpp"
#include "utils/utils.hpp"
#include "engine/game_object.hpp"

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
    unsigned int texture_id = LoadTexture(texture_path);

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
    Mesh* mesh_jeep;
    if (!LoadMesh(mesh_jeep, "./assets/jeep.obj", VERTEX_SHADER_FILE, FRAGMENT_SHADER_FILE, "./assets/jeep.jpg")) return;

    Mesh* mesh_starship;
    if (!LoadMesh(mesh_starship, "./assets/starship.obj", VERTEX_SHADER_FILE, FRAGMENT_SHADER_FILE, "./assets/starship.png")) return;

    Mesh* mesh_cube;
    if (!LoadMesh(mesh_cube, "./assets/cube.obj", VERTEX_SHADER_FILE, FRAGMENT_NO_TEX_SHADER_FILE)) return;

    Mesh* mesh_suzanne;
    if (!LoadMesh(mesh_suzanne, "./assets/suzanne.obj", VERTEX_SHADER_FILE, FRAGMENT_NO_TEX_SHADER_FILE)) return;

    Mesh* mesh_raptor;
    if (!LoadMesh(mesh_raptor, "./assets/raptor.obj", VERTEX_SHADER_FILE, FRAGMENT_NO_TEX_SHADER_FILE)) return;

    Mesh* mesh_tank;
    if (!LoadMesh(mesh_tank, "./assets/tank.obj", VERTEX_SHADER_FILE, FRAGMENT_NO_TEX_SHADER_FILE)) return;

    // create objects
    GameObject* jeep = scene.AddGameObject(new GameObject(mesh_jeep));
    GameObject* raptor = scene.AddGameObject(new GameObject(mesh_raptor, {125, 125, 125}));
    GameObject* tank = scene.AddGameObject(new GameObject(mesh_tank, {125, 125, 125}));
    GameObject* starship = scene.AddGameObject(new GameObject(mesh_starship));
    GameObject* suzanne = scene.AddGameObject(new GameObject(mesh_suzanne, {0.5f, 0, 0.4f}));
    GameObject* ground = scene.AddGameObject(new GameObject(mesh_cube, {0.3f, 0.3f, 0.3f}));

    // transform
    jeep->transform.position = {40.0f, 0.15f, 0};
    jeep->transform.rotation = {0, glm::pi<float>() * 0.2f, 0};

    raptor->transform.position = {20.0f, 1.0f, 0};
    raptor->transform.rotation = {0, 0, glm::pi<float>()};

    tank->transform.position = {20.0f, 1.2f, 0};
    tank->transform.rotation = {0, 0, 0};

    starship->transform.scale = glm::vec3(0.3f);

    suzanne->transform.position = {40.0f, 1.0f, 3.0f};
    suzanne->transform.rotation = {0, glm::pi<float>()*0.5f, 0};
    suzanne->transform.scale = glm::vec3(0.5f);

    ground->transform.scale = {50.0f, 0.1f, 50.0f};

    // move camera
    scene.GetCamera()->SetPosition({40.0f, 0, 0});

    // main loop
    while (!window->GetShouldClose()) {
        current_time = static_cast<float>(glfwGetTime());
        delta_time = current_time - last_time;
        last_time = current_time;

        scene.GetCamera()->ProcessKeyboardInput(window, delta_time);
        scene.GetCamera()->ProcessMouseMovement(window, delta_time);

        scene.Update(delta_time, current_time);

        // specific updates
        // jeep->transform.rotation = glm::vec3(0, glm::pi<float>() + current_time, 0);
        // jeep->transform.position = 5.0f * glm::vec3(glm::sin(current_time), 0, glm::cos(current_time));
        suzanne->transform.rotation = {0, current_time, 0};

		raptor->transform.rotation = {current_time, 0, glm::pi<float>() + current_time};

        Render();

        window->SwapBuffers();
        window->PollEvents();
    }
}

// render scene
void Engine::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene.Render(window);
}
