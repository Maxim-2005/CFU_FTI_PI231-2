#include <iostream>
#include <vector>
#include <string>
using namespace std;

class SpaceObject {
public:
    string name;
    string description;

    SpaceObject(string n, string d) : name(n), description(d) {}

    void display() {
        cout << name << ": " << description << endl;
    }
};

class Planet : public SpaceObject {
public:
    vector<string> moons;

    Planet(string n, string d) : SpaceObject(n, d) {}

    void addMoon(string moon) {
        moons.push_back(moon);
    }

    void display() {
        SpaceObject::display();
        if (!moons.empty()) {
            cout << "Спутники: ";
            for (size_t i = 0; i < moons.size(); i++) {
                cout << moons[i];
                if (i < moons.size() - 1) cout << ", ";
            }
            cout << endl;
        }
    }
};

class StarSystem : public SpaceObject {
public:
    vector<Planet> planets;

    StarSystem(string n, string d) : SpaceObject(n, d) {}

    void addPlanet(Planet p) {
        planets.push_back(p);
    }

    void display() {
        cout << "=== " << name << " ===" << endl;
        cout << description << endl;
        for (size_t i = 0; i < planets.size(); i++) {
            cout << i + 1 << ". " << planets[i].name << endl;
        }
    }
};

int main() {
    // Создаем планеты
    Planet earth("Земля", "Планета с жизнью");
    earth.addMoon("Луна");

    Planet mars("Марс", "Красная планета");
    mars.addMoon("Фобос");
    mars.addMoon("Деймос");

    // Создаем звездную систему
    StarSystem solar("Солнечная система", "Наша домашняя система");
    solar.addPlanet(earth);
    solar.addPlanet(mars);

    // Главное меню
    while (true) {
        cout << "\n=== ПЛАНЕТАРИЙ ===" << endl;
        solar.display();
        cout << "0. Выход" << endl;

        int choice;
        cout << "Выберите планету: ";
        cin >> choice;

        if (choice == 0) break;

        if (choice > 0 && choice <= solar.planets.size()) {
            cout << "\n";
            solar.planets[choice - 1].display();
            cout << "Нажмите Enter...";
            cin.ignore();
            cin.get();
        }
        else {
            cout << "Неверный выбор!" << endl;
        }
    }

    return 0;
}