
#include <iostream>


using namespace std;

int reverse(int n) {
    int reversed = 0;
    while (n > 0) {
        reversed = reversed * 10 + n % 10;
        n /= 10;
    }
    return reversed;
}


int main() {
    int n;
    cin >> n;
    cout << reverse(n);
}
