#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

int main() {
    std::string s; // набор слов
    std::map<std::string, int> m; // словарь <слово, кол-во>
    std::vector<std::string> v; // повторяющиеся слова
    
    // запонляем словарь словами их количеством
    while (std::cin >> s && s != "end")
        m[s]++;

    // заполняем вектор словами которых больше 1
    for (const auto& i : m)
        if (i.second > 1)
            v.push_back(i.first);

    // сортировка вектора
    std::sort(v.begin(), v.end());

    // вывод повторяющихся слов
    for (const auto& s : v)
        std::cout << s << " ";

    return 0;
}
