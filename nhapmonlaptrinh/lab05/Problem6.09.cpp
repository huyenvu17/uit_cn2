#include <iostream>
using namespace std;
#define MAX 200

int main()
{
	int n;
	int a[MAX];
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		cin >> a[i];
	}
	int p, k;
	cin >> p >> k;
	if (p < 0) p = 0;
	if (p > n) p = n;
	if (k < 0) k = 0;
	if (k > n - p) k = n - p;
	for (int i = p + k; i < n; ++i)
	{
		a[i - k] = a[i];
	}
	n -= k;
	for (int i = 0; i < n; ++i)
	{
		if (i) cout << " ";
		cout << a[i];
	}
	cout << endl;
	return 0;
}


