#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;
/*
class SpaceObject {
protected:
    string name;
    string description;

public:
    SpaceObject(const string& n, const string& d)
        : name(n), description(d) {}

    virtual ~SpaceObject() = default;

    virtual void display() const {
        cout << name << ": " << description << endl;
    }

    string getName() const { return name; }
};

class Moon : public SpaceObject {
public:
    Moon(const string& n, const string& d)
        : SpaceObject(n, d) {}

    void display() const override {
        cout << "   -> Спутник: " << name << endl;
        cout << "      Инфо: " << description << endl;
    }
};

class Planet : public SpaceObject {
private:
    vector<Moon> moons;
    string type;

public:
    Planet(const string& n, const string& typeName, const string& d)
        : SpaceObject(n, d), type(typeName) {}

    void addMoon(const string& n, const string& d) {
        moons.emplace_back(n, d);
    }

    void display() const override {
        cout << "\n========================================" << endl;
        cout << " ПЛАНЕТА: " << name << endl;
        cout << " ТИП: " << type << endl;
        cout << "========================================" << endl;
        cout << description << endl << endl;

        if (!moons.empty()) {
            cout << "--- СПУТНИКИ (" << moons.size() << ") ---" << endl;
            for (const auto& moon : moons) {
                moon.display();
                cout << endl;
            }
        }
        else {
            cout << "* У этой планеты нет известных спутников." << endl;
        }
    }
};

class StarSystem : public SpaceObject {
private:
    vector<Planet> planets;
    string starType;

public:
    StarSystem(const string& n, const string& sType, const string& d)
        : SpaceObject(n, d), starType(sType) {}

    void addPlanet(const Planet& p) {
        planets.push_back(p);
    }

    size_t planetCount() const { return planets.size(); }

    const Planet& getPlanet(size_t index) const {
        return planets.at(index);
    }

    void display() const override {
        cout << "\n*** ЗВЁЗДНАЯ СИСТЕМА: " << name << " ***" << endl;
        cout << "Тип звезды: " << starType << endl;
        cout << description << endl;
        cout << "---------------------------" << endl;
        cout << "Планеты в системе:" << endl;
        for (size_t i = 0; i < planets.size(); ++i) {
            cout << " " << i + 1 << ". " << planets[i].getName() << endl;
        }
    }
};

class Galaxy : public SpaceObject {
private:
    vector<StarSystem> systems;

public:
    Galaxy(const string& n, const string& d) : SpaceObject(n, d) {}

    void addSystem(const StarSystem& s) {
        systems.push_back(s);
    }

    size_t systemCount() const { return systems.size(); }

    const StarSystem& getSystem(size_t index) const {
        return systems.at(index);
    }

    void display() const override {
        cout << "\n########################################" << endl;
        cout << " ГАЛАКТИКА: " << name << endl;
        cout << "########################################" << endl;
        cout << description << endl << endl;
        cout << "Доступные звёздные системы:" << endl;
        for (size_t i = 0; i < systems.size(); ++i) {
            cout << " " << i + 1 << ". " << systems[i].getName() << endl;
        }
    }
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

vector<Galaxy> static initUniverse() {
    vector<Galaxy> universe;

    Galaxy milkyWay("Млечный Путь", "Спиральная галактика с перемычкой, в которой находится Земля и Солнечная система. Содержит от 200 до 400 миллиардов звёзд.");

    StarSystem solar("Солнечная система", "Жёлтый карлик (G2V)", "Наша домашняя система, возраст около 4.57 млрд лет.");

    Planet mercury("Меркурий", "Земная группа", "Ближайшая к Солнцу планета. Температура колеблется от -173°C ночью до +427°C днём. Атмосфера практически отсутствует.");
    solar.addPlanet(mercury);

    Planet venus("Венера", "Земная группа", "Самая горячая планета (462°C) из-за парникового эффекта. Атмосфера состоит на 96% из углекислого газа, идут дожди из серной кислоты.");
    solar.addPlanet(venus);

    Planet earth("Земля", "Земная группа", "Единственное известное место во Вселенной, где существует жизнь. 70% поверхности покрыто водой.");
    earth.addMoon("Луна", "Естественный спутник Земли. Пятый по величине спутник в Солнечной системе. Влияет на приливы и отливы, стабилизирует наклон оси Земли.");
    solar.addPlanet(earth);

    Planet mars("Марс", "Земная группа", "«Красная планета», богатая оксидом железа. Имеет самую высокую гору в системе (Олимп, 26 км).");
    mars.addMoon("Фобос", "Больший из двух спутников. Вращается очень близко к планете (6000 км) и постепенно падает на неё. Похож на астероид.");
    mars.addMoon("Деймос", "Меньший спутник. Имеет неправильную форму, похож на картофелину. Вероятно, захваченный астероид главного пояса.");
    solar.addPlanet(mars);

    Planet jupiter("Юпитер", "Газовый гигант", "Крупнейшая планета. Имеет Большое Красное Пятно — шторм, бушующий сотни лет.");
    jupiter.addMoon("Ио", "Самое вулканически активное тело в Солнечной системе. Гравитация Юпитера буквально 'мнёт' спутник, разогревая его недра.");
    jupiter.addMoon("Европа", "Покрыта толстым слоем льда. Ученые полагают, что под льдом находится огромный океан жидкой воды, где возможна жизнь.");
    jupiter.addMoon("Ганимед", "Крупнейший спутник в Солнечной системе (больше Меркурия). Единственный спутник, имеющий собственное магнитное поле.");
    jupiter.addMoon("Каллисто", "Самый кратерированный объект в системе. Его поверхность — одна из старейших, практически не менялась миллиарды лет.");
    solar.addPlanet(jupiter);

    Planet saturn("Сатурн", "Газовый гигант", "Знаменит своей обширной системой колец, состоящих из частиц льда и пыли.");
    saturn.addMoon("Титан", "Второй по размеру спутник в системе. Единственный спутник с плотной атмосферой и жидкостью на поверхности (озёра метана и этана).");
    saturn.addMoon("Энцелад", "Ледяной спутник с гейзерами, выбрасывающими водяной пар в космос. Под льдом скрыт глобальный океан.");
    saturn.addMoon("Мимас", "Из-за огромного кратера Гершель внешне очень напоминает «Звезду Смерти» из Звёздных Войн.");
    solar.addPlanet(saturn);

    Planet uranus("Уран", "Ледяной гигант", "Вращается «лежа на боку» (наклон оси 98 градусов). Самая холодная планетарная атмосфера (-224°C).");
    uranus.addMoon("Миранда", "Имеет самую разнообразную и экстремальную геологию: гигантские каньоны глубиной до 20 км.");
    uranus.addMoon("Титания", "Крупнейший спутник Урана. Поверхность покрыта сетью огромных разломов и долин.");
    solar.addPlanet(uranus);

    Planet neptune("Нептун", "Ледяной гигант", "Самая ветреная планета, скорость ветров достигает 2100 км/ч.");
    neptune.addMoon("Тритон", "Крупнейший спутник Нептуна. Уникален тем, что вращается в направлении, обратном вращению планеты (ретроградная орбита).");
    solar.addPlanet(neptune);

    milkyWay.addSystem(solar);

    StarSystem proxima("Проксима Центавра", "Красный карлик (M5.5Ve)", "Ближайшая к Солнцу звезда (4.24 световых года). Вспыхивающая звезда.");
    Planet proximaB("Проксима b", "Суперземля", "Находится в обитаемой зоне звезды. Получает примерно 65% света, который Земля получает от Солнца. Возможна жидкая вода.");
    Planet proximaC("Проксима c", "Мини-Нептун", "Гипотетическая планета, намного холоднее Земли, орбитальный период около 5 лет.");
    proxima.addPlanet(proximaB);
    proxima.addPlanet(proximaC);
    milkyWay.addSystem(proxima);

    StarSystem trappist("TRAPPIST-1", "Ультрахолодный карлик", "Находится в 39 световых годах. Известна тем, что содержит 7 землеподобных планет.");
    Planet trapE("TRAPPIST-1e", "Земная группа", "Наиболее вероятный кандидат на обитаемость. Железное ядро, возможен глобальный океан.");
    trapE.addMoon("Нет данных", "Вероятно, приливной захват не позволяет иметь крупные спутники.");
    trappist.addPlanet(trapE);

    Planet trapF("TRAPPIST-1f", "Земная группа", "Также находится в обитаемой зоне, но, вероятно, покрыта толстой паровой атмосферой.");
    trappist.addPlanet(trapF);
    milkyWay.addSystem(trappist);

    universe.push_back(milkyWay);

    Galaxy andromeda("Андромеда", "Ближайшая к нам крупная спиральная галактика. Содержит около 1 триллиона звёзд. Движется навстречу Млечному Пути.");

    StarSystem titawin("Титавин (Ипсилон Андромеды)", "Жёлто-белый карлик", "Одна из первых систем, где была открыта многопланетная система вокруг звезды главной последовательности.");
    Planet upsAndB("Саффар (b)", "Горячий Юпитер", "Газовый гигант, вращающийся экстремально близко к звезде. Год длится всего 4.6 дня.");
    Planet upsAndC("Самх (c)", "Газовый гигант", "Массивная планета с очень вытянутой орбитой, что вызывает резкие перепады температур.");
    Planet upsAndD("Маджрити (d)", "Газовый гигант", "Находится в обитаемой зоне, но это гигант. Однако его гипотетические луны могли бы быть обитаемы.");
    upsAndD.addMoon("Экзо-Луна I", "Гипотетический скалистый спутник с плотной атмосферой.");

    titawin.addPlanet(upsAndB);
    titawin.addPlanet(upsAndC);
    titawin.addPlanet(upsAndD);
    andromeda.addSystem(titawin);

    universe.push_back(andromeda);

    return universe;
}

int main() {
    setlocale(LC_ALL, "Russian");
    vector<Galaxy> universe = initUniverse();

    while (true) {
        clearScreen();
        cout << "=== ИНТЕРГАЛАКТИЧЕСКИЙ АТЛАС ===" << endl;
        cout << "Доступные галактики:\n";
        for (size_t i = 0; i < universe.size(); ++i) {
            cout << i + 1 << ". " << universe[i].getName() << endl;
        }
        cout << "0. Выход из программы" << endl;
        cout << "Ваш выбор: ";

        int gChoice;
        if (!(cin >> gChoice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (gChoice == 0) break;
        if (gChoice < 1 || gChoice > universe.size()) continue;

        const Galaxy& currentGalaxy = universe[gChoice - 1];
        while (true) {
            clearScreen();
            currentGalaxy.display();
            cout << "\n0. Вернуться к списку галактик" << endl;
            cout << "Выберите звёздную систему: ";

            int sChoice;
            if (!(cin >> sChoice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (sChoice == 0) break;
            if (sChoice < 1 || sChoice > currentGalaxy.systemCount()) continue;

            const StarSystem& currentSystem = currentGalaxy.getSystem(sChoice - 1);
            while (true) {
                clearScreen();
                currentSystem.display();
                cout << "\n0. Вернуться к обзору галактики" << endl;
                cout << "Выберите планету для детального анализа: ";

                int pChoice;
                if (!(cin >> pChoice)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                if (pChoice == 0) break;
                if (pChoice < 1 || pChoice > currentSystem.planetCount()) continue;

                clearScreen();
                currentSystem.getPlanet(pChoice - 1).display();
                pause();
            }
        }
    }

    cout << "Спасибо за использование атласа. Удачного полёта!" << endl;
    return 0;
}
*/