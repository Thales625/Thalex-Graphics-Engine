#include "engine/engine.hpp"
#include "engine/game_object.hpp"

#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#define VERTEX_SHADER_FILE "shaders/vertex.glsl"
#define FRAGMENT_SHADER_FILE "shaders/fragment.glsl"

GameObject* LoadObj(const std::string& obj_file_path, const glm::vec3 color) {
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals; 
    std::vector<Mesh::Vertex> vertices;
    std::vector<unsigned int> indices;

    std::ifstream file(obj_file_path);
    
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << obj_file_path << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.substr(0, 2) == "v ") { // position
            glm::vec3 position;
            std::istringstream iss(line.substr(2));
            if (iss >> position.x >> position.y >> position.z) {
                positions.push_back(position);
            }
        }
        else if (line.substr(0, 3) == "vt ") { // UV
            glm::vec2 uv;
            std::istringstream iss(line.substr(3));
            if (iss >> uv.x >> uv.y) {
                uvs.push_back(uv);
            }
        }
        else if (line.substr(0, 3) == "vn ") { // normal
            glm::vec3 normal;
            std::istringstream iss(line.substr(3));
            if (iss >> normal.x >> normal.y >> normal.z) {
                normals.push_back(normal);
            }
        }
        else if (line.substr(0, 2) == "f ") { // face
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            std::istringstream iss(line.substr(2));

            char separator;
            for (int i = 0; i < 3; ++i) {
                if (iss >> vertexIndex[i] >> separator >> uvIndex[i] >> separator >> normalIndex[i]) {
                    vertices.push_back({positions[vertexIndex[i] - 1], uvs[uvIndex[i] - 1], normals[normalIndex[i] - 1]});
                    indices.push_back(vertices.size() - 1);
                }
            }
        }
    }
    
    file.close();

    Mesh* mesh = new Mesh(vertices, indices);
    Shader* shader = new Shader(VERTEX_SHADER_FILE, FRAGMENT_SHADER_FILE);
    Material* material = new Material(shader, color);
    
    return new GameObject(mesh, material);
}

// constructor
Engine::Engine(uint32_t width, uint32_t height, const std::string& title) : window(new Window(width, height, title)), scene(nullptr), running(false) {}

// deconstructor
Engine::~Engine() {
    Shutdown();
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

// main loop
void Engine::Shutdown() const {
    window->Close();
    delete window;
}

// main loop
void Engine::Run() {
    running = true;

    float last_time = 0.0f;

    Camera* new_camera = new Camera(glm::vec3(0, 0, 0), 0, 0);
    Scene* new_scene = new Scene(new_camera);
    // GameObject* new_game_obj = LoadObj("/home/thales/Dropbox/Codes/Cpp/OpenGL/TGE/assets/cube.obj", glm::vec3(1, 1, 1));
    GameObject* new_game_obj = LoadObj("/home/thales/Dropbox/Codes/Cpp/OpenGL/TGE/assets/suzanne.obj", glm::vec3(1, 1, 1));
    
    new_scene->AddGameObject(new_game_obj);

    SetScene(new_scene);

    while (running && !window->ShouldClose()) {
        current_time = static_cast<float>(glfwGetTime());
        delta_time = current_time - last_time;
        last_time = current_time;

        // DEBUG
        //new_game_obj->transform.rotation.x += delta_time; 
        // new_game_obj->transform.rotation.y += delta_time; 

        window->PollEvents();

        if (scene) {
            scene->GetCamera()->ProcessKeyboardInput(window, delta_time);
            scene->GetCamera()->ProcessMouseMovement(window, delta_time);
            scene->Update(delta_time);
            scene->sun_dir = glm::vec3(0, glm::cos(current_time), glm::sin(current_time));

            Render();
        }

        window->SwapBuffers();
    }

    // shutdown when the loop exits
    Shutdown();
}

// render scene
void Engine::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene->Render(window);
}