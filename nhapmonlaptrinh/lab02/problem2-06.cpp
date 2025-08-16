#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    float a, b, c;
    cin >> a;
    cin >> b;
    cin >> c;

    // Sắp xếp 3 số theo thứ tự tăng dần
    float temp;
    if (a > b) {
        temp = a;
        a = b;
        b = temp;
    }
    if (a > c) {
        temp = a;
        a = c;
        c = temp;
    }
    if (b > c) {
        temp = b;
        b = c;
        c = temp;
    }

    cout << a << " " << b << " " << c << endl;

    return 0;
}
