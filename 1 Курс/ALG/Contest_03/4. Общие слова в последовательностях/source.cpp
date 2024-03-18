#include <iostream>
#include <set>
#include <string>

int main() {
    int n; // колличество слов
    std::cin >> n;

    // получение ряда слов
    std::set<std::string> wordsSet;
    for (int i = 0; i < n; i++) {
        std::string word;
        std::cin >> word;
        wordsSet.insert(word);
    }

    int m; // колличество слов
    std::cin >> m;

    // получение ряда слов
    std::set<std::string> intersectSet;
    for (int i = 0; i < m; i++) {
        std::string word;
        std::cin >> word;
        if (wordsSet.count(word) > 0) {
            intersectSet.insert(word);
        }
    }

    // вывод в лексикографическом порядке и проверка на кол-во общих слов
    if (intersectSet.size() == 0) {
        std::cout << -1 << std::endl;
    } else {
        for (const std::string& word : intersectSet) {
            std::cout << word << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}