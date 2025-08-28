#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double a, b, c;
    cin >> a >> b >> c;
    
    if (a == 0) {
        cout << "PTVN";
        return 0;
    }
    
    double delta = b*b - 4*a*c;
    
    if (delta < 0) {
        cout << "PTVN";
    }
    else if (delta == 0) {
        double x = -b/(2*a);
        cout << "PT co nghiem kep: x1 = x2 = " << x;
    }
    else {
        double x1 = (-b + sqrt(delta))/(2*a);
        double x2 = (-b - sqrt(delta))/(2*a);
        if (x1 > x2) {
            swap(x1, x2);
        }
        cout << "PT co hai nghiem phan biet:" << endl;
        cout << "x1 = " << x1 << endl;
        cout << "x2 = " << x2;
    }
    
    return 0;
}