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
	int x;
	cin >> x;
	int m = 0;
	for (int i = 0; i < n; ++i)
	{
		if (a[i] != x)
		{
			a[m++] = a[i];
		}
	}
	for (int i = 0; i < m; ++i)
	{
		if (i) cout << " ";
		cout << a[i];
	}
	cout << endl;
	return 0;
}


