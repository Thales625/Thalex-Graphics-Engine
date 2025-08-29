#include "universe.hpp"

int main() {
    Universe universe = Universe(800, 600, "Rocket Landing");

    if (universe.Init()) {
        universe.Run();
    }

    return 0;
}