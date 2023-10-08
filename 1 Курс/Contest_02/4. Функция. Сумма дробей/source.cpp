#include <numeric>

using namespace std;

tuple<int, int, int> find_lcm(int a, int b) {
    int c = lcm(a, b);
    return make_tuple(c, c/a, c/b);
}

tuple<int, int> reduce(int a, int b) {
    int c = gcd(a, b);
    return make_tuple(a/c, b/c);
}