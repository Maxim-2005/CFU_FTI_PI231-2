#include <iostream>
#include <stack>
#include <string>

int main() {
    std::string gl; // строка
    std::stack<char> s; // символ
    bool line = true;
    
    while (line) {
        std::getline(std::cin, gl); // получение строки с консоли

        // добавление скобок в стак и удаление пар
        for (char c : gl) {
            line = c != '!';
            if (c == '(' || c == '{' || c == '[')
                s.push(c);
            else if (c == ')' || c == '}' || c == ']') {
                if (s.empty()) {
                    s.push(c);
                    line = false;
                    break;
                } else if ((c == ')' && s.top() == '(') ||
                           (c == '}' && s.top() == '{') ||
                           (c == ']' && s.top() == '[')) {
                    s.pop();
                } else {
                    s.push(c);
                    line = false;
                    break;
                }
            }
        }
    }

    std::cout << (s.empty() ? "YES" : "NO") << std::endl;

    return 0;
}