#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

struct Moon {
    string name;
    string description;
};

struct Planet {
    string name;
    string type;
    string description;
    vector<Moon> moons;
};

struct StarSystem {
    string name;
    string starType;
    string description;
    vector<Planet> planets;
};

struct Galaxy {
    string name;
    string description;
    vector<StarSystem> systems;
};

void static clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void static pause() {
    cout << "\nНажмите Enter, чтобы вернуться...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

Moon static createMoon(string name, string desc) {
    Moon m;
    m.name = name;
    m.description = desc;
    return m;
}

Planet static createPlanet(string name, string type, string desc) {
    Planet p;
    p.name = name;
    p.type = type;
    p.description = desc;
    return p;
}

StarSystem static createSystem(string name, string starType, string desc) {
    StarSystem s;
    s.name = name;
    s.starType = starType;
    s.description = desc;
    return s;
}

Galaxy static createGalaxy(string name, string desc) {
    Galaxy g;
    g.name = name;
    g.description = desc;
    return g;
}

void static printMoonInfo(const Moon& m) {
    cout << "   -> Спутник: " << m.name << endl;
    cout << "      Инфо: " << m.description << endl;
}

void static printPlanetInfo(const Planet& p) {
    cout << "\n========================================" << endl;
    cout << " ПЛАНЕТА: " << p.name << endl;
    cout << " ТИП: " << p.type << endl;
    cout << "========================================" << endl;
    cout << p.description << endl << endl;

    if (!p.moons.empty()) {
        cout << "--- СПУТНИКИ (" << p.moons.size() << ") ---" << endl;
        for (const auto& moon : p.moons) {
            printMoonInfo(moon);
            cout << endl;
        }
    }
    else {
        cout << "* У этой планеты нет известных спутников." << endl;
    }
}

void static printSystemInfo(const StarSystem& s) {
    cout << "\n*** ЗВЁЗДНАЯ СИСТЕМА: " << s.name << " ***" << endl;
    cout << "Тип звезды: " << s.starType << endl;
    cout << s.description << endl;
    cout << "---------------------------" << endl;
    cout << "Планеты в системе:" << endl;
    for (size_t i = 0; i < s.planets.size(); ++i) {
        cout << " " << i + 1 << ". " << s.planets[i].name << endl;
    }
}

void static printGalaxyInfo(const Galaxy& g) {
    cout << "\n########################################" << endl;
    cout << " ГАЛАКТИКА: " << g.name << endl;
    cout << "########################################" << endl;
    cout << g.description << endl << endl;
    cout << "Доступные звёздные системы:" << endl;
    for (size_t i = 0; i < g.systems.size(); ++i) {
        cout << " " << i + 1 << ". " << g.systems[i].name << endl;
    }
}

vector<Galaxy> static initUniverse() {
    vector<Galaxy> universe;

    Galaxy milkyWay = createGalaxy("Млечный Путь", "Спиральная галактика с перемычкой. Дом человечества.");

    StarSystem solar = createSystem("Солнечная система", "Жёлтый карлик (G2V)", "Возраст 4.57 млрд лет.");

    Planet mercury = createPlanet("Меркурий", "Земная группа", "Ближайшая к Солнцу. Перепады температур.");
    solar.planets.push_back(mercury);

    Planet venus = createPlanet("Венера", "Земная группа", "Адский парниковый эффект и дожди из кислоты.");
    solar.planets.push_back(venus);

    Planet earth = createPlanet("Земля", "Земная группа", "Колыбель жизни, 70% воды.");
    earth.moons.push_back(createMoon("Луна", "Влияет на приливы, стабилизирует ось."));
    solar.planets.push_back(earth);

    Planet mars = createPlanet("Марс", "Земная группа", "Красная планета, оксид железа.");
    mars.moons.push_back(createMoon("Фобос", "Падает на Марс."));
    mars.moons.push_back(createMoon("Деймос", "Похож на астероид."));
    solar.planets.push_back(mars);

    Planet jupiter = createPlanet("Юпитер", "Газовый гигант", "Король планет с Большим Красным Пятном.");
    jupiter.moons.push_back(createMoon("Ио", "Вулканический ад."));
    jupiter.moons.push_back(createMoon("Европа", "Подледный океан."));
    jupiter.moons.push_back(createMoon("Ганимед", "Есть магнитное поле."));
    solar.planets.push_back(jupiter);

    Planet saturn = createPlanet("Сатурн", "Газовый гигант", "Властелин колец.");
    saturn.moons.push_back(createMoon("Титан", "Метановые озера."));
    saturn.moons.push_back(createMoon("Энцелад", "Ледяные гейзеры."));
    solar.planets.push_back(saturn);

    milkyWay.systems.push_back(solar);

    StarSystem proxima = createSystem("Проксима Центавра", "Красный карлик", "Ближайшая звезда (4.24 св. года).");
    Planet proxB = createPlanet("Проксима b", "Суперземля", "В зоне обитаемости, возможна вода.");
    proxima.planets.push_back(proxB);
    milkyWay.systems.push_back(proxima);

    universe.push_back(milkyWay);

    Galaxy andromeda = createGalaxy("Андромеда", "Соседняя гигантская спиральная галактика.");

    StarSystem titawin = createSystem("Титавин", "Жёлто-белый карлик", "Система Ипсилон Андромеды.");
    Planet upsB = createPlanet("Саффар", "Горячий Юпитер", "Год длится 4.6 дня.");
    Planet upsD = createPlanet("Маджрити", "Газовый гигант", "В зоне обитаемости.");
    upsD.moons.push_back(createMoon("Экзо-Луна-1", "Гипотетический обитаемый мир."));

    titawin.planets.push_back(upsB);
    titawin.planets.push_back(upsD);
    andromeda.systems.push_back(titawin);

    universe.push_back(andromeda);

    return universe;
}

int main() {
    setlocale(LC_ALL, "Russian");

    vector<Galaxy> universe = initUniverse();

    while (true) {
        clearScreen();
        cout << "=== ПРОЦЕДУРНЫЙ АТЛАС ===" << endl;
        cout << "Доступные галактики:\n";
        for (size_t i = 0; i < universe.size(); ++i) {
            cout << i + 1 << ". " << universe[i].name << endl;
        }
        cout << "0. Выход" << endl;
        cout << "Ваш выбор: ";

        int gChoice;
        if (!(cin >> gChoice)) {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (gChoice == 0) break;
        if (gChoice < 1 || gChoice > universe.size()) continue;

        const Galaxy& currentGalaxy = universe[gChoice - 1];

        while (true) {
            clearScreen();
            printGalaxyInfo(currentGalaxy);
            cout << "\n0. Назад" << endl;
            cout << "Выберите систему: ";

            int sChoice;
            if (!(cin >> sChoice)) {
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (sChoice == 0) break;
            if (sChoice < 1 || sChoice > currentGalaxy.systems.size()) continue;

            const StarSystem& currentSystem = currentGalaxy.systems[sChoice - 1];

            while (true) {
                clearScreen();
                printSystemInfo(currentSystem);
                cout << "\n0. Назад" << endl;
                cout << "Выберите планету: ";

                int pChoice;
                if (!(cin >> pChoice)) {
                    cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                if (pChoice == 0) break;
                if (pChoice < 1 || pChoice > currentSystem.planets.size()) continue;

                clearScreen();
                printPlanetInfo(currentSystem.planets[pChoice - 1]);
                pause();
            }
        }
    }

    return 0;
}
