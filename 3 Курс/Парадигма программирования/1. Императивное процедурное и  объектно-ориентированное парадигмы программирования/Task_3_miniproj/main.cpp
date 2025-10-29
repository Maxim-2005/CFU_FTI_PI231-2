#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ===== Базовый класс =====
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

// ===== Класс планеты =====
class Planet : public SpaceObject {
private:
    vector<string> moons;

public:
    Planet(const string& n, const string& d)
        : SpaceObject(n, d) {}

    void addMoon(const string& moon) {
        moons.push_back(moon);
    }

    void display() const override {
        cout << "\nПланета: " << name << endl;
        cout << "Описание: " << description << endl;
        if (!moons.empty()) {
            cout << "Спутники: ";
            for (size_t i = 0; i < moons.size(); ++i) {
                cout << moons[i];
                if (i < moons.size() - 1) cout << ", ";
            }
            cout << endl;
        }
        else {
            cout << "Нет спутников." << endl;
        }
    }
};

// ===== Класс звёздной системы =====
class StarSystem : public SpaceObject {
private:
    vector<Planet> planets;

public:
    StarSystem(const string& n, const string& d)
        : SpaceObject(n, d) {}

    void addPlanet(const Planet& p) {
        planets.push_back(p);
    }

    void display() const override {
        cout << "\n=== " << name << " ===" << endl;
        cout << description << endl;
        cout << "Планеты:\n";
        for (size_t i = 0; i < planets.size(); ++i) {
            cout << " " << i + 1 << ". " << planets[i].getName() << endl;
        }
    }

    size_t planetCount() const {
        return planets.size();
    }

    const Planet& getPlanet(size_t index) const {
        return planets.at(index);
    }
};

// ===== Точка входа =====
int main() {
    setlocale(LC_ALL, "Russian");

    // Создаём планеты
    Planet merkuriy("Меркурий", "Самая ближайшая планета к солнцу");

    Planet venera("Венера", "Вторая по удалённости от Солнца и шестая по размеру планета Солнечной системы");

    Planet earth("Земля", "Планета, на которой есть жизнь");
    earth.addMoon("Луна");

    Planet mars("Марс", "Красная планета");
    mars.addMoon("Фобос");
    mars.addMoon("Деймос");

    Planet jupiter("Юпитер", "Самая большая планета в Солнечной системе, пятая по удалённости от Солнца. Наряду с Сатурном Юпитер классифицируется как газовый гигант");
    jupiter.addMoon("Европа");
    jupiter.addMoon("Ио");
    jupiter.addMoon("Ганимед");
    jupiter.addMoon("Каллисто");
    jupiter.addMoon("Амальтея");

    Planet saturn("Сатурн", "Шестая планета по удалённости от Солнца и вторая по размерам планета в Солнечной системе после Юпитера. Сатурн классифицируется как газовый гигант.");
    saturn.addMoon("Титан");
    saturn.addMoon("Энцелад");
    saturn.addMoon("Мимас");
    saturn.addMoon("Диона");
    saturn.addMoon("Ялет");

    Planet uran("Уран", "Планета Солнечной системы, седьмая по удалённости от Солнца, третья по диаметру и четвёртая по массе.");
    uran.addMoon("Сетебос");
    uran.addMoon("Титания");
    uran.addMoon("Миранда");
    uran.addMoon("Умбриэль");
    uran.addMoon("Оберон");

    Planet neptune("Нептун", "Восьмая и самая дальняя от Солнца планета Солнечной системы.");
    neptune.addMoon("Тритон");
    neptune.addMoon("Таласса");
    neptune.addMoon("Гиппокамп");
    neptune.addMoon("Нереида");
    neptune.addMoon("Галатея");


    // Создаём систему
    StarSystem solar("Солнечная система", "Наша домашняя звёздная система");
    solar.addPlanet(merkuriy);
    solar.addPlanet(venera);
    solar.addPlanet(earth);
    solar.addPlanet(mars);
    solar.addPlanet(jupiter);
    solar.addPlanet(saturn);
    solar.addPlanet(uran);
    solar.addPlanet(neptune);

    // Главное меню
    while (true) {
        cout << "\n=== ПЛАНЕТАРИЙ ===" << endl;
        solar.display();
        cout << "0. Выход\n";

        cout << "Выберите планету: ";
        int choice;
        cin >> choice;

        if (choice == 0) break;

        if (choice > 0 && static_cast<size_t>(choice) <= solar.planetCount()) {
            system("cls"); // Для Windows (можно убрать, если не нужно)
            solar.getPlanet(choice - 1).display();
            cout << "\nНажмите Enter для возврата...";
            cin.ignore();
            cin.get();
        }
        else {
            cout << "Неверный выбор!" << endl;
        }
    }

    return 0;
}
