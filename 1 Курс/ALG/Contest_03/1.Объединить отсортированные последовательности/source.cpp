#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> arrN(n);
    for (int i = 0; i < n; i++){
        std::cin >> arrN[i];
    }

    int m;
    std::cin >> m;
    std::vector<int> arrM(m);
    for (int i = 0; i < m; i++){
        std::cin >> arrM[i];
    }

    arrN.insert(arrN.end(), arrM.begin(), arrM.end());
    
    std::sort(arrN.begin(), arrN.end());
    
    for (int i : arrN)
        std::cout << i << " ";

    return 0;
}