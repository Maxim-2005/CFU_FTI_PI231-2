class Cat {
public:
    bool live; // жизнь или смерть кота
    bool show; // закрыт или открыт кот

    // Конструктор
    Cat() {
        this->live = rand() % 2;
        this->show = false;
    }

    // Демонстрируем состояние кота
    bool is_alive() {
        if (this->show)
            this->live;
        else
            this->live = rand() % 2;
        return this->live;
    };
};

class Box {
public:
    // Открываем коробку
    Cat open() {
        Cat cat;
        cat.show = true;
        return cat;
    };
};