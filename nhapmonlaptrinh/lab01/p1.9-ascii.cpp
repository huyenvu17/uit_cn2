#include <iostream>
#include <cctype>
#include <cmath>
using namespace std;

int main()
{
    char c1, c2;
    int x;
    cin >> c1 >> c2 >> x;
    cout << "Ma ASCII cua ky tu `" << c1 << "', `" << c2 << "' lan luot la " << (int)c1 << " va " << (int)c2 << "\n";
    cout << "Khoang cach giua hai ky tu `" << c1 << "', `" << c2 << "' la " << abs(c1 - c2) << "\n";
    cout << "Dang viet hoa cua ky tu `" << c1 << "' la `" << (char)toupper(c1) << "'\n";
    cout << x << " la ma ASCII cua ky tu `" << char(x) << "'\n";
    return 0;
    
}