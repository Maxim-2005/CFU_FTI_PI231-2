#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;
/*
struct Moon {
    string name;
    string description;
};

struct Planet {
    string name;
    string type;
    string description;
    vector<Moon> moons;
    int moons_count;
};

struct StarSystem {
    string name;
    string starType;
    string description;
    vector<Planet> planets;
    int planets_count;
};

struct Galaxy {
    string name;
    string description;
    vector<StarSystem> systems;
    int systems_count;
};

struct Universe {
    vector<Galaxy> galaxies;
    int galaxies_count;
};


Universe universe;
int current_galaxy_index = -1;
int current_system_index = -1;
int current_planet_index = -1;


void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause_program() {
    cout << "\nНажмите Enter, чтобы продолжить...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int get_choice(int min_val, int max_val) {
    int choice;
    while (true) {
        if (cin >> choice) {
            if (choice >= min_val && choice <= max_val) {
                return choice;
            }
        }
        else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "Неверный выбор. Введите число от " << min_val << " до " << max_val << ": ";
    }
}

void create_moon(Moon* moon, const char* name, const char* desc) {
    moon->name = name;
    moon->description = desc;
}

void add_moon_to_planet(Planet* planet, Moon moon) {
    if (planet->moons_count < 100) {  // Простая проверка
        planet->moons.push_back(moon);
        planet->moons_count++;
    }
}

void create_planet(Planet* planet, const char* name, const char* type, const char* desc) {
    planet->name = name;
    planet->type = type;
    planet->description = desc;
    planet->moons_count = 0;
}

void add_planet_to_system(StarSystem* system, Planet planet) {
    if (system->planets_count < 100) {
        system->planets.push_back(planet);
        system->planets_count++;
    }
}

void create_system(StarSystem* system, const char* name, const char* starType, const char* desc) {
    system->name = name;
    system->starType = starType;
    system->description = desc;
    system->planets_count = 0;
}

void add_system_to_galaxy(Galaxy* galaxy, StarSystem system) {
    if (galaxy->systems_count < 100) {
        galaxy->systems.push_back(system);
        galaxy->systems_count++;
    }
}

void create_galaxy(Galaxy* galaxy, const char* name, const char* desc) {
    galaxy->name = name;
    galaxy->description = desc;
    galaxy->systems_count = 0;
}

void add_galaxy_to_universe(Universe* universe, Galaxy galaxy) {
    if (universe->galaxies_count < 100) {
        universe->galaxies.push_back(galaxy);
        universe->galaxies_count++;
    }
}

void show_moon_details(Moon* moon) {
    cout << "   -> Спутник: " << moon->name << endl;
    cout << "      Описание: " << moon->description << endl;
}

void show_planet_details(Planet* planet) {
    cout << "\n========================================" << endl;
    cout << " ПЛАНЕТА: " << planet->name << endl;
    cout << " ТИП: " << planet->type << endl;
    cout << "========================================" << endl;
    cout << planet->description << endl << endl;

    if (planet->moons_count > 0) {
        cout << "--- СПУТНИКИ (" << planet->moons_count << ") ---" << endl;
        for (int i = 0; i < planet->moons_count; i++) {
            show_moon_details(&planet->moons[i]);
        }
    }
    else {
        cout << "* Нет известных спутников" << endl;
    }
}

void show_system_details(StarSystem* system) {
    cout << "\n*** ЗВЁЗДНАЯ СИСТЕМА: " << system->name << " ***" << endl;
    cout << "Тип звезды: " << system->starType << endl;
    cout << system->description << endl;
    cout << "---------------------------" << endl;

    if (system->planets_count > 0) {
        cout << "Планеты в системе:" << endl;
        for (int i = 0; i < system->planets_count; i++) {
            cout << " " << (i + 1) << ". " << system->planets[i].name << endl;
        }
    }
    else {
        cout << "Нет известных планет" << endl;
    }
}

void show_galaxy_details(Galaxy* galaxy) {
    cout << "\n########################################" << endl;
    cout << " ГАЛАКТИКА: " << galaxy->name << endl;
    cout << "########################################" << endl;
    cout << galaxy->description << endl << endl;

    if (galaxy->systems_count > 0) {
        cout << "Звёздные системы в галактике:" << endl;
        for (int i = 0; i < galaxy->systems_count; i++) {
            cout << " " << (i + 1) << ". " << galaxy->systems[i].name << endl;
        }
    }
    else {
        cout << "Нет известных звёздных систем" << endl;
    }
}

void show_main_menu() {
    clear_screen();
    cout << "=== КОСМИЧЕСКИЙ АТЛАС ===" << endl;
    cout << "Выберите действие:" << endl;
    cout << "1. Просмотреть галактики" << endl;
    cout << "2. Выйти из программы" << endl;
    cout << "Выбор: ";
}

void show_galaxies_menu() {
    clear_screen();
    cout << "=== ВЫБОР ГАЛАКТИКИ ===" << endl;

    if (universe.galaxies_count == 0) {
        cout << "Нет доступных галактик" << endl;
        pause_program();
        return;
    }

    for (int i = 0; i < universe.galaxies_count; i++) {
        cout << (i + 1) << ". " << universe.galaxies[i].name << endl;
    }
    cout << "0. Назад в главное меню" << endl;
    cout << "Выберите галактику: ";
}

void show_systems_menu() {
    clear_screen();

    if (current_galaxy_index == -1) {
        cout << "Ошибка: галактика не выбрана" << endl;
        pause_program();
        return;
    }

    Galaxy* galaxy = &universe.galaxies[current_galaxy_index];
    show_galaxy_details(galaxy);

    if (galaxy->systems_count == 0) {
        cout << "\nВ этой галактике нет систем" << endl;
        pause_program();
        return;
    }

    cout << "\n0. Назад к выбору галактики" << endl;
    cout << "Выберите звёздную систему: ";
}

void show_planets_menu() {
    clear_screen();

    if (current_system_index == -1) {
        cout << "Ошибка: система не выбрана" << endl;
        pause_program();
        return;
    }

    Galaxy* galaxy = &universe.galaxies[current_galaxy_index];
    StarSystem* system = &galaxy->systems[current_system_index];
    show_system_details(system);

    if (system->planets_count == 0) {
        cout << "\nВ этой системе нет планет" << endl;
        pause_program();
        return;
    }

    cout << "\n0. Назад к выбору системы" << endl;
    cout << "Выберите планету: ";
}

void initialize_universe() {
    // Создаем Млечный Путь
    Galaxy milky_way;
    create_galaxy(&milky_way, "Млечный Путь", "Наша родная галактика");

    // Создаем Солнечную систему
    StarSystem solar_system;
    create_system(&solar_system, "Солнечная система", "Жёлтый карлик", "Наша родная система");

    // Создаем планеты для Солнечной системы
    Planet earth;
    create_planet(&earth, "Земля", "Земная группа", "Третья планета от Солнца");

    Planet mars;
    create_planet(&mars, "Марс", "Земная группа", "Красная планета");

    Planet jupiter;
    create_planet(&jupiter, "Юпитер", "Газовый гигант", "Крупнейшая планета системы");

    // Создаем спутники
    Moon earth_moon;
    create_moon(&earth_moon, "Луна", "Естественный спутник Земли");
    add_moon_to_planet(&earth, earth_moon);

    Moon mars_moon1;
    create_moon(&mars_moon1, "Фобос", "Спутник Марса");
    add_moon_to_planet(&mars, mars_moon1);

    Moon jupiter_moon1;
    create_moon(&jupiter_moon1, "Европа", "Ледяной спутник Юпитера");
    add_moon_to_planet(&jupiter, jupiter_moon1);

    // Добавляем планеты в систему
    add_planet_to_system(&solar_system, earth);
    add_planet_to_system(&solar_system, mars);
    add_planet_to_system(&solar_system, jupiter);

    // Создаем систему Проксима Центавра
    StarSystem proxima_system;
    create_system(&proxima_system, "Проксима Центавра", "Красный карлик", "Ближайшая к Солнцу");

    Planet proxima_b;
    create_planet(&proxima_b, "Проксима b", "Суперземля", "Планета в зоне обитаемости");
    add_planet_to_system(&proxima_system, proxima_b);

    // Добавляем системы в галактику
    add_system_to_galaxy(&milky_way, solar_system);
    add_system_to_galaxy(&milky_way, proxima_system);

    // Создаем Андромеду
    Galaxy andromeda;
    create_galaxy(&andromeda, "Андромеда", "Соседняя спиральная галактика");

    StarSystem andromeda_system;
    create_system(&andromeda_system, "Андромеда-1", "Жёлтый карлик", "Система в галактике Андромеда");

    Planet andromeda_planet;
    create_planet(&andromeda_planet, "Андромеда-b", "Газовый гигант", "Планета в другой галактике");
    add_planet_to_system(&andromeda_system, andromeda_planet);

    add_system_to_galaxy(&andromeda, andromeda_system);

    // Добавляем галактики во вселенную
    add_galaxy_to_universe(&universe, milky_way);
    add_galaxy_to_universe(&universe, andromeda);
}

void process_main_menu() {
    int choice = get_choice(1, 2);

    switch (choice) {
    case 1:
        current_galaxy_index = -1;
        current_system_index = -1;
        current_planet_index = -1;
        break;
    case 2:
        exit(0);
    }
}

void process_galaxies_menu() {
    int choice = get_choice(0, universe.galaxies_count);

    if (choice == 0) {
        current_galaxy_index = -1;
        return;
    }

    current_galaxy_index = choice - 1;
    current_system_index = -1;
    current_planet_index = -1;
}

void process_systems_menu() {
    Galaxy* galaxy = &universe.galaxies[current_galaxy_index];
    int choice = get_choice(0, galaxy->systems_count);

    if (choice == 0) {
        current_system_index = -1;
        return;
    }

    current_system_index = choice - 1;
    current_planet_index = -1;
}

void process_planets_menu() {
    Galaxy* galaxy = &universe.galaxies[current_galaxy_index];
    StarSystem* system = &galaxy->systems[current_system_index];
    int choice = get_choice(0, system->planets_count);

    if (choice == 0) {
        current_planet_index = -1;
        return;
    }

    current_planet_index = choice - 1;

    // Показать детали планеты
    clear_screen();
    Planet* planet = &system->planets[current_planet_index];
    show_planet_details(planet);
    pause_program();
}

void run_program() {
    // Инициализация
    initialize_universe();

    // Главный цикл программы
    while (true) {
        // Главное меню
        show_main_menu();
        process_main_menu();

        // Цикл выбора галактики
        while (current_galaxy_index == -1) {
            show_galaxies_menu();
            process_galaxies_menu();
        }

        // Цикл выбора системы
        while (current_system_index == -1) {
            show_systems_menu();
            if (current_system_index == -1) {
                process_systems_menu();
            }
        }

        // Цикл выбора планеты
        while (current_planet_index == -1) {
            show_planets_menu();
            if (current_planet_index == -1) {
                process_planets_menu();
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    run_program();
    return 0;
}
*/