#include "Controller.h"
#include <iostream>
#include <limits>

void PlanetariumController::run() {
    view.displayWelcome();

    while (true) {
        showGalaxySelection();
    }
}

void PlanetariumController::showGalaxySelection() {
    view.clearScreen();
    view.displayGalaxies(model.getGalaxies());

    int choice;
    std::cout << "�������� ���������: ";
    std::cin >> choice;

    if (choice == 0) {
        std::cout << "�� ��������!" << std::endl;
        exit(0);
    }

    if (choice > 0 && choice <= model.getGalaxies().size()) {
        showStarSystemSelection(choice - 1);
    }
    else {
        view.displayError("�������� �����!");
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }
}

void PlanetariumController::showStarSystemSelection(int galaxyIndex) {
    Galaxy* galaxy = model.getGalaxy(galaxyIndex);
    if (!galaxy) return;

    while (true) {
        view.clearScreen();

        // ���������� ��������� � �� �������
        std::cout << "=== ���������: " << galaxy->getName() << " ===" << std::endl;
        galaxy->displayInfo();

        int choice;
        std::cout << "�������� ������� ��� 0 ��� ��������: ";
        std::cin >> choice;

        if (choice == 0) return;

        if (choice > 0 && choice <= galaxy->getStarSystems().size()) {
            StarSystem* system = model.getStarSystem(galaxyIndex, choice - 1);
            if (system) {
                showPlanetSelection(galaxyIndex, choice - 1);
            }
        }
        else {
            view.displayError("�������� �����!");
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
    }
}

void PlanetariumController::showPlanetSelection(int galaxyIndex, int systemIndex) {
    StarSystem* system = model.getStarSystem(galaxyIndex, systemIndex);
    if (!system) return;

    while (true) {
        view.clearScreen();
        view.displayStarSystem(*system);  // ������ �������� ���������� ���

        int choice;
        std::cout << "�������� ������� ��� 0 ��� ��������: ";
        std::cin >> choice;

        if (choice == 0) return;

        if (choice > 0 && choice <= system->getPlanets().size()) {
            Planet* planet = model.getPlanet(galaxyIndex, systemIndex, choice - 1);
            if (planet) {
                view.clearScreen();
                view.displayPlanet(*planet);
                std::cout << "������� Enter ��� �����������...";
                std::cin.ignore();
                std::cin.get();
            }
        }
        else {
            view.displayError("�������� �����!");
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
    }
}