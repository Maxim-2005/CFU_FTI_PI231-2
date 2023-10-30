#include <numeric>

using namespace std;

// нахождение наименьшего общего кратного
tuple<int, int, int> find_lcm(int a, int b) {
    int c = lcm(a, b);
    return make_tuple(c, c/a, c/b);
}

// нахождение наибольшего общего делителя
tuple<int, int> reduce(int a, int b) {
    int c = gcd(a, b);
    return make_tuple(a/c, b/c);
}