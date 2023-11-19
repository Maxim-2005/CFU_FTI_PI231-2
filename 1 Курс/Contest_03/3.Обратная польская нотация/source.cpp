#include <iostream> 
#include <stack> 
#include <string> 

// определение приоретета знака
int getPriority(char operation) {
    if (operation == '+' || operation == '-')
        return 1;
    else if (operation == '*' || operation == '/' || operation == '%')
        return 2;
    else if (operation == '^')
        return 3;

    return 0;
}

int main() {
    std::string expression, answer; // выражение, ответ
    std::stack<char> operators; // операторы

    std::getline(std::cin, expression); // получение выражения

    // обход выражения посимвально
    for (char c : expression) {
        if (std::isdigit(c))
            answer += c;
        else if (c == '(')
            operators.push(c);
        else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                answer += " ";
                answer += operators.top();
                operators.pop();
            }
            operators.pop();
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^') {
            while (!operators.empty() && (getPriority(operators.top()) > getPriority(c)
                || (getPriority(operators.top()) == getPriority(c) && c != '^'))) {
                answer += " ";
                answer += operators.top();
                operators.pop();
            }
            answer += " ";
            operators.push(c);
        }
    }

    // добавление пробелов
    while (!operators.empty()) {
        answer += " ";
        answer += operators.top();
        operators.pop();
    }

    std::cout << answer << std::endl;
}