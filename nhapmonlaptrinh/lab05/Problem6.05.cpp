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
	int x, k;
	cin >> x >> k;
	if (k < 0) k = 0;
	if (k > n) k = n;
	for (int i = n; i > k; --i)
	{
		a[i] = a[i - 1];
	}
	a[k] = x;
	++n;
	for (int i = 0; i < n; ++i)
	{
		if (i) cout << " ";
		cout << a[i];
	}
	cout << endl;
	return 0;
}


