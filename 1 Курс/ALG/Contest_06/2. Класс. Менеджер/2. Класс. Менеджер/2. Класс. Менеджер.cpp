#include<iostream>
#include<string>
#include<map>

std::map<std::string, double> bonuses;

class Employee {
public:
    std::string name; // Имя сотрудника
    std::string job_title; // Должность сотрудника
    int job_money; // Оклад

    // Конструктор сотрудника
    Employee(std::string name, std::string job_title, int job_money) {
        this->name = name;
        this->job_title = job_title;
        this->job_money = job_money;
    };

    // вычисление надбавки
    virtual int bonus(double procent) {
        return int(this->job_money * procent);
    };

    // вычисление итоговой зарплаты
    int salary(std::string job_title) {
        return this->job_money + this->bonus(bonuses[this->job_title]);
    };

    // подключение дружественной функции
    friend std::ostream& operator<<(std::ostream& out, Employee& emp);
};

// оператор вывода объекта Employee
std::ostream& operator<<(std::ostream& out, Employee& emp) {
    out << emp.name << " (" << emp.job_title << "): " << emp.salary(emp.job_title);
    return out;
};

class Manager : public Employee {
public:
    // Конструктор менеджера
    Manager(std::string name, int job_money = 16242) : Employee(name, "manager", job_money) {
        this->name = name;
        this->job_money = job_money;
    };

    // переопределение метода вычисление надбавки
    int bonus(double procent) override {
        return int(this->job_money * std::max(0.1, procent));
    };
};

class Boss : public Employee {
public:
    Boss(std::string name, int money = 16242)
        :Employee(name, "boss", money) {
    }
};

int main() {
    double boss_bonus, manager_bonus;
    std::cin >> boss_bonus >> manager_bonus;
    bonuses["manager"] = manager_bonus;
    bonuses["boss"] = boss_bonus;

    int john_money, bob_money, alice_money;
    std::cin >> john_money >> bob_money >> alice_money;
    Boss john("John", john_money);
    Manager bob("Bob", bob_money);
    Manager alice("Alice", alice_money);

    std::cout << john << '\n' << bob << '\n' << alice << std::endl;
}