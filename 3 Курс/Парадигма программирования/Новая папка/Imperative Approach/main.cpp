#include <iostream>
#include <vector>
#include <algorithm>
#include <clocale>

// Функция для поиска максимальной длины ПОДРЯД идущих элементов (Subarray)
void solve_contiguous(const std::vector<int>& arr) {
    if (arr.empty()) {
        std::cout << "Массив пуст." << std::endl;
        return;
    }

    int max_inc = 1, cur_inc = 1;
    int max_dec = 1, cur_dec = 1;

    for (size_t i = 1; i < arr.size(); ++i) {
        // Логика для возрастающей подпоследовательности
        if (arr[i] > arr[i - 1]) {
            cur_inc++;
        }
        else {
            if (cur_inc > max_inc) max_inc = cur_inc;
            cur_inc = 1;
        }

        // Логика для убывающей подпоследовательности
        if (arr[i] < arr[i - 1]) {
            cur_dec++;
        }
        else {
            if (cur_dec > max_dec) max_dec = cur_dec;
            cur_dec = 1;
        }
    }
    // Проверка хвостов
    if (cur_inc > max_inc) max_inc = cur_inc;
    if (cur_dec > max_dec) max_dec = cur_dec;

    std::cout << "--- Подряд идущие элементы ---" << std::endl;
    std::cout << "Макс. длина возрастающей: " << max_inc << std::endl;
    std::cout << "Макс. длина убывающей: " << max_dec << std::endl;
}

// Функция для поиска максимальной длины произвольно расположенных элементов (Subsequence)
// Используем классический DP подход O(N^2)
void solve_arbitrary(const std::vector<int>& arr) {
    if (arr.empty()) return;

    size_t n = arr.size();
    std::vector<int> dp_inc(n, 1);
    std::vector<int> dp_dec(n, 1);

    int max_inc = 1;
    int max_dec = 1;

    for (size_t i = 1; i < n; ++i) {
        for (size_t j = 0; j < i; ++j) {
            // Для возрастающей
            if (arr[i] > arr[j] && dp_inc[i] < dp_inc[j] + 1) {
                dp_inc[i] = dp_inc[j] + 1;
            }
            // Для убывающей
            if (arr[i] < arr[j] && dp_dec[i] < dp_dec[j] + 1) {
                dp_dec[i] = dp_dec[j] + 1;
            }
        }
        if (dp_inc[i] > max_inc) max_inc = dp_inc[i];
        if (dp_dec[i] > max_dec) max_dec = dp_dec[i];
    }

    std::cout << "--- Произвольные элементы (LIS/LDS) ---" << std::endl;
    std::cout << "Макс. длина возрастающей: " << max_inc << std::endl;
    std::cout << "Макс. длина убывающей: " << max_dec << std::endl;
}

int main() {
    std::setlocale(LC_ALL, "Russian");

    // Пример данных
    std::vector<int> data = { 10, 22, 9, 33, 21, 50, 41, 60, 80, 1 };

    std::cout << "Исходный массив: ";
    for (int x : data) std::cout << x << " ";
    std::cout << "\n\n";

    solve_contiguous(data);
    std::cout << "\n";
    solve_arbitrary(data);

    return 0;
}