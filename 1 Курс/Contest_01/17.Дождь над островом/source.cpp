#include <iostream>
#include <vector>

int main() {
    long int n, s = 0, l = 0, r, lm = 0, rm = 0; // размер острова, сумма, лево, право, максимум лево, максимум право 
    std::cin >> n;
    std::vector<int> v(n);
    for (int i = 0; i < n; i++)
        std::cin >> v[i];
    r = n - 1;

    // суммируем глубины впадин
    while (l < r) {
        if (v[l] < v[r]) {
            if (v[l] > lm)
                lm = v[l];
            else
                s += lm - v[l];
            l++;
        } else {
            if (v[r] > rm)
                rm = v[r];
            else
                s += rm - v[r];
            r--;
        }
    }
    std::cout << s;

    return 0;
}