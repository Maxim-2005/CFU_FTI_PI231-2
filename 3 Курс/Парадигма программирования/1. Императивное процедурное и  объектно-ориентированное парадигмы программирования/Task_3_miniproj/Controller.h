#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Model.h"
#include "View.h"

class PlanetariumController {
    PlanetariumModel model;
    PlanetariumView view;

    void showGalaxySelection();
    void showStarSystemSelection(int galaxyIndex);
    void showPlanetSelection(int galaxyIndex, int systemIndex);

public:
    void run();
};

#endif