#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int a, b, c, dB, dC;
    
    cin >> a;
    cin >> b;
    cin >> c;
    
    dB = abs(b - a);
    dC = abs(c - a);
    
    if (dB < dC) {
        cout << "B " << dB;
    }
    else {
        cout << "C " << dC;
    }
    

    return 0;
}