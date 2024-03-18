#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double a, b; // слагаемые a и b
    
    cin >> a;
    cin >> b;

    // вычисление длины гипотенузы
    cout << sqrt(pow(a, 2.0) + pow(b, 2.0));

    return 0;
}