#pragma once

#include "camera.hpp"
#include "vessel.hpp"
#include "terrain.hpp"

#include <vector>

class Scene {
public:
    Scene();
    
    Camera camera;

    void Render(Window* const window) const;
    void Update(const float delta_time, const float current_time);

    inline Terrain* SetTerrain(Terrain* terrain_ptr) { this->terrain = terrain_ptr; return terrain_ptr; };
    inline void SetActiveVessel(Vessel* vessel_ptr) { this->active_vessel = vessel_ptr; };

    inline Vessel* AddVessel(Vessel* vessel_ptr) { this->vessels.push_back(vessel_ptr); return vessel_ptr; };
    inline std::vector<Vessel*> GetVessels() const { return vessels; };
private:
    Terrain* terrain;
    Vessel* active_vessel;
    
    std::vector<Vessel*> vessels;
    glm::mat4 GetProjectionMatrix(Window* const window) const;
};