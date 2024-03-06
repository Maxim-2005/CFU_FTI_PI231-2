#include <iostream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

int main() {
    int s = 0;

    std::ifstream a("data.json"); // чтение файла
    json b;
    a >> b;

    int user_id; // идентификатор пользователя
    std::cin >> user_id;

    // обход файла и поиск необходимых значений
    for (const auto& project : b) {
        for (const auto& task : project["tasks"]) {
            if (task["user_id"] == user_id && task["completed"] == true) {
                s++;
            }
        }
    }

    std::cout << s << std::endl;

    return 0;
}