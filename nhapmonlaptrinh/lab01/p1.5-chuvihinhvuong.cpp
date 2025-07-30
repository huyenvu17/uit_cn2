#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    double a;
    cin >> a;
    if (a >= 0) {
        double chu_vi = a * 4;
        double dien_tich = a * a;
        cout << "Chu vi: " << fixed << setprecision(2) << chu_vi << "\n";
        cout << "Dien tich: " << fixed << setprecision(2) << dien_tich << "\n";
    } else {
        cout << "Do dai canh khong the la so am." << "\n";
    }
    return 0;
    
}