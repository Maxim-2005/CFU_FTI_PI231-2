#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int a, b, c, dB, dC; // точка a, точка b, точка c, расстояние от а до b, расстояние от a до с
    
    cin >> a;
    cin >> b;
    cin >> c;
    
    dB = abs(b - a);
    dC = abs(c - a);

    if (dB < dC) {
        cout << "B " << dB;
    } else {
        cout << "C " << dC;
    } 

    return 0;
}