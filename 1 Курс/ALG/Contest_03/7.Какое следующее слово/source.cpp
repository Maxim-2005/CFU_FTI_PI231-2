#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>

int main() {
    std::ifstream f("data.txt"); // открытие файла
    std::map<std::string, int> m; // создание словаря
    std::string target, w; // искомое слово, слово
    
    std::cin >> target;
    if (f.is_open()) {
        bool t = false;
        // обход файла и поиск искомого слова
        for (f >> w; !f.eof(); f >> w) {
            if (w == "stopword")
                break;
            else if (t == true) {
                t = false;
                m[w]++;
            } else if (w == target)
                t = true;
        }
        f.close();
    }
    
    // сортировка и вывод
    if (!m.empty()) {
        std::vector<std::pair<std::string, int>> s(m.begin(), m.end());
        std::sort(s.begin(), s.end(), [](const auto& a, const auto& b) {
            return a.second > b.second || (a.second == b.second && a.first < b.first);
        });
        for (size_t i = 0; i < std::min(s.size(), static_cast<size_t>(3)); i++) {
            std::cout << s[i].first;
            if (i != std::min(s.size(), static_cast<size_t>(3)) - 1)
                std::cout << " ";
        }
    } else
        std::cout << "-";

    return 0;
}