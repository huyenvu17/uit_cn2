#include <iostream>

using namespace std;

void input(int &n) {
    cin >> n;
}

int sumDigits(int n) {
    if (n == 0) return 0;
    return n % 10 + sumDigits(n / 10);
}

void sum(int n, int &s) {
    s = sumDigits(n);
}



int main() {
    int n, s=0;
    input(n);
    sum(n, s);
    cout << s;
}
