#include "Model.h"
#include <iostream>

// SpaceObject
SpaceObject::SpaceObject(const std::string& name, const std::string& description)
    : name(name), description(description) {
}

void SpaceObject::displayInfo() const {
    std::cout << name << ": " << description << std::endl;
}

std::string SpaceObject::getName() const { return name; }
std::string SpaceObject::getDescription() const { return description; }

// Moon
Moon::Moon(const std::string& name, const std::string& description)
    : SpaceObject(name, description) {
}

// Planet
Planet::Planet(const std::string& name, const std::string& description)
    : SpaceObject(name, description) {
}

void Planet::addMoon(const Moon& moon) {
    moons.push_back(moon);
}

void Planet::displayInfo() const {
    SpaceObject::displayInfo();
    if (!moons.empty()) {
        std::cout << "  Спутники (" << moons.size() << "): ";
        for (size_t i = 0; i < moons.size(); ++i) {
            std::cout << moons[i].getName();
            if (i < moons.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;
    }
}

const std::vector<Moon>& Planet::getMoons() const { return moons; }

// StarSystem
StarSystem::StarSystem(const std::string& name, const std::string& description)
    : SpaceObject(name, description) {
}

void StarSystem::addPlanet(const Planet& planet) {
    planets.push_back(planet);
}

void StarSystem::displayInfo() const {
    SpaceObject::displayInfo();
    std::cout << "Планеты в системе:" << std::endl;
    for (size_t i = 0; i < planets.size(); ++i) {
        std::cout << "  " << i + 1 << ". ";
        planets[i].displayInfo();
    }
}

const std::vector<Planet>& StarSystem::getPlanets() const { return planets; }

// Galaxy
Galaxy::Galaxy(const std::string& name, const std::string& description)
    : SpaceObject(name, description) {
}

void Galaxy::addStarSystem(const StarSystem& system) {
    starSystems.push_back(system);
}

void Galaxy::displayInfo() const {
    SpaceObject::displayInfo();
    std::cout << "Звездные системы:" << std::endl;
    for (size_t i = 0; i < starSystems.size(); ++i) {
        std::cout << "  " << i + 1 << ". " << starSystems[i].getName() << std::endl;
    }
}

const std::vector<StarSystem>& Galaxy::getStarSystems() const { return starSystems; }

// PlanetariumModel
PlanetariumModel::PlanetariumModel() {
    initializeData();
}

void PlanetariumModel::initializeData() {
    // Млечный Путь
    Galaxy milkyWay("Млечный Путь",
        "Спиральная галактика диаметром 100,000 световых лет");

    // Солнечная система
    StarSystem solarSystem("Солнечная система", "Наша домашняя система с 8 планетами");

    Planet mercury("Меркурий", "Самая маленькая планета, температура от -180°C до 430°C");
    Planet venus("Венера", "Вторая планета, атмосфера из CO2, температура 460°C");
    Planet earth("Земля", "Третья планета, единственная с жизнью, 71% воды");
    Planet mars("Марс", "Красная планета, тонкая атмосфера, два спутника");

    // Спутники
    earth.addMoon(Moon("Луна", "Естественный спутник, влияет на приливы"));
    mars.addMoon(Moon("Фобос", "Малый спутник, постепенно приближается к Марсу"));
    mars.addMoon(Moon("Деймос", "Меньший спутник, орбита дальше Фобоса"));

    solarSystem.addPlanet(mercury);
    solarSystem.addPlanet(venus);
    solarSystem.addPlanet(earth);
    solarSystem.addPlanet(mars);

    // Система Альфа Центавра
    StarSystem alphaCentauri("Альфа Центавра",
        "Ближайшая звездная система в 4.37 световых годах");

    Planet proximaB("Проксима Центавра b",
        "Экзопланета в зоне обитаемости, возможна жидкая вода");
    Planet alphaCentauriBb("Альфа Центавра Bb",
        "Горячая супер-Земля, очень близко к звезде");

    alphaCentauri.addPlanet(proximaB);
    alphaCentauri.addPlanet(alphaCentauriBb);

    milkyWay.addStarSystem(solarSystem);
    milkyWay.addStarSystem(alphaCentauri);

    // Галактика Андромеды
    Galaxy andromeda("Галактика Андромеды",
        "Спиральная галактика в 2.5 млн световых лет, больше Млечного Пути");

    galaxies.push_back(milkyWay);
    galaxies.push_back(andromeda);
}

const std::vector<Galaxy>& PlanetariumModel::getGalaxies() const {
    return galaxies;
}

Galaxy* PlanetariumModel::getGalaxy(int index) {
    if (index >= 0 && index < galaxies.size()) {
        return &galaxies[index];
    }
    return nullptr;
}

StarSystem* PlanetariumModel::getStarSystem(int galaxyIndex, int systemIndex) {
    Galaxy* galaxy = getGalaxy(galaxyIndex);
    if (galaxy && systemIndex >= 0 && systemIndex < galaxy->getStarSystems().size()) {
        return const_cast<StarSystem*>(&galaxy->getStarSystems()[systemIndex]);
    }
    return nullptr;
}

Planet* PlanetariumModel::getPlanet(int galaxyIndex, int systemIndex, int planetIndex) {
    StarSystem* system = getStarSystem(galaxyIndex, systemIndex);
    if (system && planetIndex >= 0 && planetIndex < system->getPlanets().size()) {
        return const_cast<Planet*>(&system->getPlanets()[planetIndex]);
    }
    return nullptr;
}