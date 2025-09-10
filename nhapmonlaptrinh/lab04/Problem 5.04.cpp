#include<iostream>

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

int reverseNumber(int x) {
    int rev = 0;
    while (x > 0) {
        rev = rev * 10 + x % 10;
        x /= 10;
    }
    return rev;
}

int main() {
    int a, b;
    cin >> a >> b;
    int count = 0;
    for (int x = a; x <= b; ++x) {
        if (isPrime(x)) {
            int rev = reverseNumber(x);
            if (isPrime(rev)) {
                count++;
            }
        }
    }
    cout << count;
    return 0;
}
