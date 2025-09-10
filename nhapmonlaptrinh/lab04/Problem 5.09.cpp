
#include <iostream>
using namespace std;

int Fibo(int n) {
    // Base cases
    if (n == 1) return 1;
    if (n == 2) return 1;
    
    // Recursive case: F(n) = F(n-1) + F(n-2)
    return Fibo(n - 1) + Fibo(n - 2);
}

int main()
{
	int x;
	cin >> x;
	
	// Check if x is in range [1, 30]
	if (x < 1 || x > 30) {
		cout << "So " << x << " khong nam trong khoang [1,30]." << endl;
	} else {
		cout << Fibo(x) << endl;
	}
	
	return 0;
}