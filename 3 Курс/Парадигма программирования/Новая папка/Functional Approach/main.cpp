#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <clocale>
#include <functional>

// --- ЧАСТЬ 1: Подряд идущие элементы (Contiguous) ---

struct ContiguousState {
    int max_len;
    int current_len;
    int last_val;
};

// Чистая функция для вычисления длины подряд идущей последовательности
// comparator: std::greater (для возрастания) или std::less (для убывания)
template <typename Comp>
int get_contiguous_len(const std::vector<int>& arr, Comp comp) {
    if (arr.empty()) return 0;

    // Начальное состояние
    ContiguousState initial{ 1, 1, arr[0] };

    // Используем accumulate как "fold left". Проходим по массиву, пропуская первый элемент.
    auto result = std::accumulate(
        arr.begin() + 1, arr.end(),
        initial,
        [comp](ContiguousState acc, int val) -> ContiguousState {
            if (comp(val, acc.last_val)) {
                // Если условие (возрастание/убывание) выполняется, увеличиваем текущую серию
                return { std::max(acc.max_len, acc.current_len + 1), acc.current_len + 1, val };
            }
            else {
                // Иначе сбрасываем серию
                return { acc.max_len, 1, val };
            }
        }
    );
    return result.max_len;
}

// --- ЧАСТЬ 2: Произвольные элементы (Arbitrary LIS/LDS) ---

// Используем алгоритм Patience Sorting (O(N log N)) реализованный через accumulate.
// Суть: tails[i] хранит наименьший хвостовой элемент всех возрастающих подпоследовательностей длины i+1.
// comparator: std::less для возрастающей, std::greater для убывающей
template <typename Comp>
int get_arbitrary_len(const std::vector<int>& arr, Comp comp) {
    std::vector<int> tails;

    // fold над массивом
    std::vector<int> final_tails = std::accumulate(
        arr.begin(), arr.end(),
        tails, // Начальное значение аккумулятора - пустой вектор
        [comp](std::vector<int> acc, int val) {
            // Ищем первый элемент в acc, который >= val (для возрастающей)
            // Для этого используем lower_bound с переданным компаратором
            // Для строго возрастающей последовательности:
            // Если ищем возрастающую: lower_bound ищет первый элемент, который НЕ (val > elem) -> elem >= val
            auto it = std::lower_bound(acc.begin(), acc.end(), val, comp);

            if (it == acc.end()) {
                acc.push_back(val);
            }
            else {
                *it = val;
            }
            return acc;
        }
    );
    return final_tails.size();
}

int main() {
    std::setlocale(LC_ALL, "Russian");
    std::vector<int> data = { 10, 22, 9, 33, 21, 50, 41, 60, 80, 1 };

    std::cout << "Исходный массив: ";
    std::copy(data.begin(), data.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n\n";

    // --- Вызов функций для подряд идущих элементов ---
    int cont_inc = get_contiguous_len(data, std::greater<int>()); // Val > Last
    int cont_dec = get_contiguous_len(data, std::less<int>());    // Val < Last

    std::cout << "--- Подряд идущие элементы (Functional) ---" << std::endl;
    std::cout << "Макс. длина возрастающей: " << cont_inc << std::endl;
    std::cout << "Макс. длина убывающей: " << cont_dec << std::endl;

    // --- Вызов функций для произвольных элементов ---
    // Для возрастающей последовательности используем стандартный less (<) для lower_bound
    int arb_inc = get_arbitrary_len(data, std::less<int>());

    // Для убывающей последовательности используем greater (>) для lower_bound
    int arb_dec = get_arbitrary_len(data, std::greater<int>());

    std::cout << "\n--- Произвольные элементы (Functional LIS/LDS) ---" << std::endl;
    std::cout << "Макс. длина возрастающей: " << arb_inc << std::endl;
    std::cout << "Макс. длина убывающей: " << arb_dec << std::endl;

    return 0;
}