
#include <iostream>
using namespace std;

int input() {
    int x;
    cin >> x;
    return x;
}

void input(int &x) {
    cin >> x;
}

int gcd(int m, int n) {
    while (n != 0) {
        int temp = n;
        n = m % n;
        m = temp;
    }
    return m;
}


int main() {
	int m, n;
	input(n);
	m=input();
	cout << gcd(m, n);
}
