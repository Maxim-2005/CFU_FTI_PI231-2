#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n; // количество чисел в первой последовательности
    std::cin >> n;
    std::vector<int> arrN(n);

    // заполнение массива с консоли
    for (int i = 0; i < n; i++){
        std::cin >> arrN[i];
    }

    int m; // количество чисел во второй последовательности
    std::cin >> m;
    std::vector<int> arrM(m);

    // заполнение массива с консоли
    for (int i = 0; i < m; i++){ 
        std::cin >> arrM[i];
    }

    // добавление чисел в массив
    arrN.insert(arrN.end(), arrM.begin(), arrM.end());
    
    // сортировка массива чисел
    std::sort(arrN.begin(), arrN.end());
    
    // вывод чисел из массив в консоль
    for (int i : arrN)
        std::cout << i << " ";

    return 0;
}