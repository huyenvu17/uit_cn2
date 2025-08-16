#include <iostream>

using namespace std;

int main() {
    double a, b;
    cin >> a >> b;
    if (a != 0) {
        double x = -b / a;
        cout << x << endl;
    } 
    else {
        if (b == 0) {
            cout << "ℝ" << endl;
        } 
        else {
            cout << "Ø" << endl;
        }
    }
    return 0;
}
