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

    }

    virtual int bonus(int job_money, int procent) {
        return job_money * procent;
    }

    int salary() {
        return job_money + bonus()
    }
};

class Manager: public Employee {
public:
    Manager(std::string name, int job_money = 16242) {
        this->name = name;
        this->job_money = job_money;
    }
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