#include <iostream>
#include <math.h>
using namespace std;
#define MAX 100

bool isPrime(int x)
{
	if (x < 2) return false;
	if (x == 2) return true;
	if (x % 2 == 0) return false;
	int limit = (int)sqrt((double)x);
	for (int i = 3; i <= limit; i += 2)
	{
		if (x % i == 0) return false;
	}
	return true;
}

int main()
{
	int n;
	int a[MAX];
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		cin >> a[i];
	}
	bool printed = false;
	for (int i = 0; i < n; ++i)
	{
		if (isPrime(a[i]))
		{
			if (printed) cout << " ";
			cout << a[i];
			printed = true;
		}
	}
	if (!printed) cout << 0;
	cout << endl;
	return 0;
}


