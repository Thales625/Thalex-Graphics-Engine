#include "engine/engine.hpp"

int main() {
    Engine engine = Engine(800, 600, "ThaleX Graphics Engine");

    if (engine.Init())
        engine.Run();

    return 0;
}