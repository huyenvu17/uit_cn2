#include <iostream>
using namespace std;

int main() {
    long so, ket_qua;
    cin >> so;
    int la_so_am = (so < 0);
    ket_qua = so - la_so_am * (2 * so);

    cout << ket_qua << "\n";

    return 0;
}