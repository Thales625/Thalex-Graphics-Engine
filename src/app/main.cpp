#include "engine/engine.hpp"

#include <memory>


int main() {
    std::unique_ptr<Engine> engine = std::make_unique<Engine>(800, 600, "ThaleX Graphics Engine");

    engine->Init();
    engine->Run();

    glfwTerminate();
}