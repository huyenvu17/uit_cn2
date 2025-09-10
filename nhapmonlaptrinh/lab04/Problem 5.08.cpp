
#include <iostream>
using namespace std;

int reverse(int n, int reversed = 0) {
    // Base case: if n is 0, return the accumulated reversed number
    if (n == 0) {
        return reversed;
    }
    
    // Recursive case: 
    // Extract last digit and add to reversed number
    int digit = n % 10;
    int newReversed = reversed * 10 + digit;
    
    // Recursively process the remaining number
    return reverse(n / 10, newReversed);
}

int main() {
    int n;
    cin >> n;
    cout << reverse(n);
    return 0;
}
