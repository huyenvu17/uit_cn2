
#include <iostream>
#include <math.h>
using namespace std;


bool isPrime(int x) {
    if (x < 2) return false;
    if (x == 2) return true;
    if (x % 2 == 0) return false;
    for (int i = 3; i * 1LL * i <= x; i += 2) {
        if (x % i == 0) return false;
    }
    return true;
}

int main() {
    int n;
    while (true) {
        if (!(cin >> n)) return 0;
        if (n > 0 && n <= 50) break;
        cout << "Gia tri vua nhap la " << n << ", khong hop le. Vui long nhap lai." << endl;
    }

    long long sum = 0;
    int count = 0;
    int num = 2;
    while (count < n) {
        if (isPrime(num)) {
            sum += num;
            count++;
        }
        num++;
    }

    cout << "Tong " << n << " so nguyen to dau tien la: " << sum;
    return 0;
}