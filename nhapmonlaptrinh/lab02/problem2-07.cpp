#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    double a, b, c;

    cin >> a;
    cin >> b;
    cin >> c;

    double delta = b * b - 4 * a * c;

    if (delta > 0) {
        double x1 = (-b - sqrt(delta)) / (2 * a);
        double x2 = (-b + sqrt(delta)) / (2 * a);
        cout << "PT co hai nghiem phan biet:" << endl;
        cout << "x1 = " << x1 << endl;
        cout << "x2 = " << x2 << endl;
    }
    else if (delta == 0) {
        double x = -b / (2 * a);
        cout << "PT co nghiem kep: x1 = x2 = " << x << endl;
    }
    else {
        cout << "PTVN";
    }

    return 0;
}
