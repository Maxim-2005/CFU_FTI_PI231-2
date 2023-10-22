#include <iostream>
#include <map>
#include <string>
#include <vector>

int main() {
    int n = 0; // колличество значений
    std::vector<std::string> v; // список логинов
    std::string line; // строка ввода
    std::map<std::string, int> m; // база счетов
    
    // прием данных
    std::cin >> n;
    for (int i = 0; i < n; i++){
        std::cin >> line;
        std::size_t d = line.find(";");
        m[line.substr(0, d)] = stoi(line.substr(d + 1));
    }
    
    // принимаем список логинов
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> line;
        v.push_back(line);
    }
    
    // вывод счетов
    for (const auto& i : v)
        std::cout << m[i] << " ";

    return 0;
}