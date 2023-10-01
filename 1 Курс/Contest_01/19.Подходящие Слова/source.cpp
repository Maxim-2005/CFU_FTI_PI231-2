#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

int main() {
    std::string s;
    std::map<std::string, int> m;
    while (std::cin >> s && s != "end")
        m[s]++;
    std::vector<std::string> v;
    for (const auto& pair : m)
        if (pair.second > 1)
            v.push_back(pair.first);
    std::sort(v.begin(), v.end());
    for (const auto& s : v)
        std::cout << s << " ";

    return 0;
}