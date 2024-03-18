#include <iostream>
#include <cmath>

bool is_prime(int number) {
    if (number < 2) {
        return false;
    }

    // Проверка числа на простоту методом перебора до корня из числа
    for (int i = 2; i < sqrt(number + 1); i++){
        if (number % i == 0) {
            return false;
        }
    }
    
    return true;
}