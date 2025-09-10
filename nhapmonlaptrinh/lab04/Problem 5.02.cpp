#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    double x;
    cin >> x;
    
    double result = 0.0;
    double term = x;
    int n = 0;
    
    // Taylor series: sin(x) = x - x^3/3! + x^5/5! - x^7/7! + ...
    // General term: (-1)^n * x^(2n+1) / (2n+1)!
    while (abs(term) >= 0.00001) {
        result += term;
        n++;
        // Calculate next term: (-1)^n * x^(2n+1) / (2n+1)!
        term = term * (-1) * x * x / ((2*n) * (2*n + 1));
    }
    
    cout << fixed << setprecision(4) << result << endl;
    
    return 0;
}
