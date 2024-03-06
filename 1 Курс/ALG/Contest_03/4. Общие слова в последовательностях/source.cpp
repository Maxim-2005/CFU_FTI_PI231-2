#include <iostream>
#include <set>
#include <string>

int main() {
    int n;
    std::cin >> n;

    std::set<std::string> wordsSet;
    for (int i = 0; i < n; i++) {
        std::string word;
        std::cin >> word;
        wordsSet.insert(word);
    }

    int m;
    std::cin >> m;

    std::set<std::string> intersectSet;
    for (int i = 0; i < m; i++) {
        std::string word;
        std::cin >> word;
        if (wordsSet.count(word) > 0) {
            intersectSet.insert(word);
        }
    }

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