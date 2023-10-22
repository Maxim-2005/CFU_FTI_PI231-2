#include <iostream>
#include <algorithm>
#include <string>

int main() {
    std::string num1, num2; // первое число и второе число
    std::cin >> num1 >> num2;
    
    sort(num1.begin(), num1.end());
    sort(num2.begin(), num2.end());
    if (num1 == num2) {
        std::cout << "YES" << std::endl;
    } else
        std::cout << "NO" << std::endl;
    
    return 0;
}