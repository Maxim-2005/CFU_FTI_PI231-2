#ifndef VIEW_H
#define VIEW_H

#include <string>
#include <vector>

class Galaxy;
class StarSystem;
class Planet;

class PlanetariumView {
public:
    void displayWelcome();
    void displayGalaxies(const std::vector<Galaxy>& galaxies);
    void displayStarSystem(const StarSystem& system);
    void displayPlanet(const Planet& planet);
    void displayError(const std::string& message);
    void displayMenu(const std::string& title, const std::vector<std::string>& options);
    void clearScreen();
};

#endif