#include <iostream>
using namespace std;

long long double_factorial(int n) {
    if (n <= 0) return 1;
    
    long long result = 1;
    if (n % 2 == 0) {
        for (int i = 2; i <= n; i += 2) {
            result *= i;
        }
    }
    else {
        for (int i = 1; i <= n; i += 2) {
            result *= i;
        }
    }
    return result;
}

int main() {
    int n;
    cin >> n;
    cout << double_factorial(n);
    return 0;
}
