
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

double calculate(int n) {
    // Base case: when n = 1, return sqrt(1) = 1
    if (n == 1) {
        return sqrt(1);
    }
    
    // Recursive case: S(n) = sqrt(n + S(n-1))
    return sqrt(n + calculate(n - 1));
}

int main() {
	int n;
	cin >> n;
    cout << fixed << setprecision(2) << calculate(n);
    return 0;
}
