#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double calculate(int n) {
    if (n == 1) return sqrt(1);
    return sqrt(n + calculate(n - 1));
}

int main() {
    int n;
    cin >> n;
    cout << setprecision(3) << calculate(n);
    return 0;
}
