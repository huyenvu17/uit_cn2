
#include <iostream>
using namespace std;

int sum_all_square(int n) {
    int sum = 0;
    for (int i = 1; i * i <= n; i++) {
        if (n % (i * i) == 0) {
            sum += i * i;
        }
    }
    return sum;
}


int main() {
    int n;
    cin>>n;
    cout << sum_all_square(n);
}
