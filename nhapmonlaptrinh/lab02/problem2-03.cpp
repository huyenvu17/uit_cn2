#include <iostream>
using namespace std;

int main() {
    double a, b;
    cin >> a >> b;

    if (a == 0) {
        if (b == 0) {
            cout << "ℝ" << endl;  // vô số nghiệm
        } else {
            cout << "Ø" << endl;  // vô nghiệm
        }
    } else {
        double x = -b / a;
        cout << "{"<< x <<"}"<< endl;
    }

    return 0;
}