#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

int main() {
    int n, t = 0; // число слов, максимальное кол-во повторений
    std::string s; // набор слов
    std::map<std::string, int> m; // словарь <слово, кол-во>
    std::vector<std::string> v; // максимально повторяющиеся слова
    
    // запонляем словарь словами и их количеством
    std::cin >> n;
    for (int i = 0; i < n; i++){
        std::cin >> s;
        m[s]++;
    }

    // заполняем вектор словами которых больше 1
    for (const auto& i : m) {
        if (t < i.second) {
            t = i.second;
            v.clear();
            v.push_back(i.first);
        } else if (t == i.second) {
            v.push_back(i.first);
        }
    }

    // сортировка вектора
    std::sort(v.begin(), v.end());

    // вывод максимально повторяющихся слов
    for (const std::string& i : v)
        std::cout << i << " ";

    return 0;
}