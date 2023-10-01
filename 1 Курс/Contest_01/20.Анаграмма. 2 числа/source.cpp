#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

string sortDigits(const string& num) {
    string sortedNum = num;
    sort(sortedNum.begin(), sortedNum.end());
    return sortedNum;
}

bool isPermutationPossible(const string& num1, const string& num2) {
    return sortDigits(num1) == sortDigits(num2);
}

int main() {
    string num1, num2;
    cin >> num1 >> num2;
    
    if (isPermutationPossible(num1, num2)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    
    return 0;
}