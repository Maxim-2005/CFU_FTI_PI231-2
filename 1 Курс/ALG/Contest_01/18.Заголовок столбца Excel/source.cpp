#include <iostream>
#include <string>

using namespace std;

int main() {
    int n; // номер столбца
    string r = ""; // буквы столбца

    cin >> n;
    
    // подбор букв по номеру
    while (n > 0) {
        char d = 'A' + (n - 1) % 26;
        r = d + r;
        n = (n - 1) / 26;
    }
    
    cout << r << endl;
    
    return 0;
}