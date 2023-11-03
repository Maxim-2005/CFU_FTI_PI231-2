#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

struct Passager {
    std::string name;
    int age;
};

int main()
{
    int pclass, age; //класс и возраст
    std::string line, word; //строка и слово
    std::vector<std::string> t; //строка по словам
    std::vector<Passager> names; //список имен

    std::ifstream file("train.csv");
    std::cin >> pclass >> age;

    std::getline(file, line);
    while (not file.eof()) {
        std::getline(file, line, '\r');
        std::istringstream ss(line);
        while (std::getline(ss, word, ','))
            t.push_back(word);
        if (t[5] == "female" && stoi(t[6]) > age && stoi(t[2]) == pclass) {
            Passager p{ t[3], stoi(t[6]) };
            names.push_back(p);
        }
        t.clear();
    }
    file.close();

    // сортировка по условию

    for (auto& i : names) {
        std::cout << i.name << std::endl;
    }
}
