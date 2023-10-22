#include <iostream> 
#include <stack> 
#include <string> 

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
    std::string expression, answer;
    std::stack<char> operators;

    std::getline(std::cin, expression);

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

    while (!operators.empty()) {
        answer += " ";
        answer += operators.top();
        operators.pop();
    }

    std::cout << answer << std::endl;
}