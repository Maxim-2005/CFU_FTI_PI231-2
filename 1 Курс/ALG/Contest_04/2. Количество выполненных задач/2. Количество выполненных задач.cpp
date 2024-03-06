#include <iostream>
#include <fstream>
#include <string>
#include "dependencies\single_include\nlohmann\json.hpp"

int main() {
    int n; // идентификатор пользователя
    int s = 0; // сумма решенных задач

    // чтение файла в объект json
    std::ifstream file("data.json");
    nlohmann::json data;
    file >> data;

    std::cin >> n;

    // обход файла и поиск необходимых значений
    for (const auto& project : data) {
        for (const auto& task : project["tasks"]) {
            if (task["user_id"] == n && task["completed"] == true) {
                s++;
            }
        }
    }

    std::cout << s << std::endl;

    return 0;
}