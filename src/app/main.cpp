#include "engine/engine.hpp"

int main() {
    Engine engine = Engine(800, 600, "ThaleX Graphics Engine");

    engine.Init();
    engine.Run();

    glfwTerminate();

    return 0;
}