
#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int sum_common_prime(int m, int n) {
    int sum = 0;
    int minNum = min(m, n);
    
    for (int i = 1; i <= minNum; i++) {
        if (m % i == 0 && n % i == 0 && isPrime(i)) {
            sum += i;
        }
    }
    
    if (sum == 0) {
        return -1;
    }
    return sum;
}

int main() {
	int m, n;
	cin >> m >> n;
	cout << sum_common_prime(m, n);
}
