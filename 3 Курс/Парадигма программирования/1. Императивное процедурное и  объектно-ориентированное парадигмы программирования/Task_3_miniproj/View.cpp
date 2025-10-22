#include "View.h"
#include "Model.h"
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif

void PlanetariumView::displayWelcome() {
    std::cout << "=== ÂÈÐÒÓÀËÜÍÛÉ ÏËÀÍÅÒÀÐÈÉ ===" << std::endl;
    std::cout << "Èññëåäóéòå êîñìîñ!" << std::endl << std::endl;
}

void PlanetariumView::displayGalaxies(const std::vector<Galaxy>& galaxies) {
    std::cout << "=== ÂÛÁÎÐ ÃÀËÀÊÒÈÊÈ ===" << std::endl;
    for (size_t i = 0; i < galaxies.size(); ++i) {
        std::cout << i + 1 << ". ";
        galaxies[i].displayInfo();
        std::cout << std::endl;
    }
    std::cout << "0. Âûõîä" << std::endl;
}

void PlanetariumView::displayStarSystem(const StarSystem& system) {
    std::cout << "=== ÑÈÑÒÅÌÀ: " << system.getName() << " ===" << std::endl;
    std::cout << system.getDescription() << std::endl;
    std::cout << "Ïëàíåòû â ñèñòåìå:" << std::endl;

    const auto& planets = system.getPlanets();
    for (size_t i = 0; i < planets.size(); ++i) {
        std::cout << "  " << i + 1 << ". " << planets[i].getName() << std::endl;
    }
    std::cout << "0. Íàçàä" << std::endl;
}

void PlanetariumView::displayPlanet(const Planet& planet) {
    std::cout << "=== ÏËÀÍÅÒÀ: " << planet.getName() << " ===" << std::endl;
    planet.displayInfo();
    std::cout << "0. Íàçàä" << std::endl;
}

void PlanetariumView::displayError(const std::string& message) {
    std::cout << "Îøèáêà: " << message << std::endl;
}

void PlanetariumView::displayMenu(const std::string& title, const std::vector<std::string>& options) {
    std::cout << "=== " << title << " ===" << std::endl;
    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << i + 1 << ". " << options[i] << std::endl;
    }
    std::cout << "0. Íàçàä" << std::endl;
}

void PlanetariumView::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}