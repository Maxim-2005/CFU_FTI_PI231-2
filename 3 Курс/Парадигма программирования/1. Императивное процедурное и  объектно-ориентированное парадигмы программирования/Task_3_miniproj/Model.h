#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>
#include <memory>

class SpaceObject {
protected:
    std::string name;
    std::string description;
public:
    SpaceObject(const std::string& name, const std::string& description);
    virtual ~SpaceObject() = default;
    virtual void displayInfo() const;
    std::string getName() const;
    std::string getDescription() const;
};

class Moon : public SpaceObject {
public:
    Moon(const std::string& name, const std::string& description);
};

class Planet : public SpaceObject {
    std::vector<Moon> moons;
public:
    Planet(const std::string& name, const std::string& description);
    void addMoon(const Moon& moon);
    void displayInfo() const override;
    const std::vector<Moon>& getMoons() const;
};

class StarSystem : public SpaceObject {
    std::vector<Planet> planets;
public:
    StarSystem(const std::string& name, const std::string& description);
    void addPlanet(const Planet& planet);
    void displayInfo() const override;
    const std::vector<Planet>& getPlanets() const;
};

class Galaxy : public SpaceObject {
    std::vector<StarSystem> starSystems;
public:
    Galaxy(const std::string& name, const std::string& description);
    void addStarSystem(const StarSystem& system);
    void displayInfo() const override;
    const std::vector<StarSystem>& getStarSystems() const;
};

class PlanetariumModel {
    std::vector<Galaxy> galaxies;
public:
    PlanetariumModel();
    void initializeData();
    const std::vector<Galaxy>& getGalaxies() const;
    Galaxy* getGalaxy(int index);
    StarSystem* getStarSystem(int galaxyIndex, int systemIndex);
    Planet* getPlanet(int galaxyIndex, int systemIndex, int planetIndex);
};

#endif