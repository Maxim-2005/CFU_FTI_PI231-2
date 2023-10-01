#include <iostream>
#include <string>

using namespace std;

string getColumnTitle(int n) {
    string result = "";
    
    while (n > 0) {
        char digit = 'A' + (n - 1) % 26;
        result = digit + result;
        n = (n - 1) / 26;
    }
    
    return result;
}

int main() {
    int n;
    cin >> n;
    
    string columnTitle = getColumnTitle(n);
    
    cout << columnTitle << endl;
    
    return 0;
}