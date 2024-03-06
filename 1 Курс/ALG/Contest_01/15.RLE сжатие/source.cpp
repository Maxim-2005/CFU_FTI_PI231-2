#include <iostream>
#include <string>

using namespace std;

int main() {
    string s; // вводная строка
    string c = ""; // строка вывода
    int count = 1; // счечик повторений

    getline(cin, s);

    // обход строки и подсчет повторений
    for (int i = 1; i <= s.length(); i++) {
        if (i == s.length() || s[i] != s[i-1]) {
            c += s[i-1];
            if (count > 1) {
                c += to_string(count);
            }
            count = 1;
        } else
            count++;
    }
    cout << c << endl;
    
    return 0;
}