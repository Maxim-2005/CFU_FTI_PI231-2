class Water {
public:
    int temperature; // температура воды

    // конструктор по умолчанию
    Water() {
        this->temperature = 0;
    }

     // конструктор с температурой
    Water(int temperature) {
        this->temperature = temperature;
    }
};

class Teapot {
public:
    Water water; // подключаем объект класса 

    // конструктор
    Teapot(Water water) {
        this->water = water;
    }

    // проверка на кипение
    bool is_boiling() {
        return this->water.temperature >= 100;
    }

    // нагревание воды
    void heat_up(int t) {
        this->water.temperature += t;
    }
};