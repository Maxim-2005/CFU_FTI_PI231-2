#include <iostream>
#include <string>

using namespace std;

string compressString(const string& s) {
    string compressedString = "";
    
    int count = 1;
    for (int i = 1; i <= s.length(); i++) {
        if (i == s.length() || s[i] != s[i-1]) {
            compressedString += s[i-1];
            if (count > 1) {
                compressedString += to_string(count);
            }
            count = 1;
        }
        else {
            count++;
        }
    }
    
    return compressedString;
}

int main() {
    string inputString;
    getline(cin, inputString);
    
    string compressedString = compressString(inputString);
    
    cout << compressedString << endl;
    
    return 0;
}