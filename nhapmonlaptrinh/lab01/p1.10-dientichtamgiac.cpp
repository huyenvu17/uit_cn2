#include <iostream>
#include <cmath> 
#include <iomanip> 
using namespace std;
int main() {
    int a, b, c;
    cin >> a >> b >> c;
    double p = double(a + b + c) / 2.0;
    double dien_tich = sqrt(p * (p - a) * (p - b) * (p - c));
    cout << fixed << setprecision(2) << dien_tich << endl;
    return 0;
}