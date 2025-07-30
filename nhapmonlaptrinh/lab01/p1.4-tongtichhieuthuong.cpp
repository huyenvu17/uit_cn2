#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int a,b, tong, hieu, tich;
    float thuong;
    cin >> a;
    cin >> b;
    tong =  a + b;
    hieu =  a - b;
    tich =  a * b;
    thuong =  double(a) / b;
    cout << a  << " + " << b << " = " << tong << "\n";
    cout << a  << " - " << b << " = " << hieu << "\n";
    cout << a  << " x " << b << " = " << tich << "\n";
    cout << a  << " : " << b << " = " << fixed << setprecision(2) << thuong;
    return 0;
    
}