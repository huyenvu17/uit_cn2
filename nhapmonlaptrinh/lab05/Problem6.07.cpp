#include <iostream>
using namespace std;
#define MAX 100

int main()
{
	int n;
	int a[MAX];
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		cin >> a[i];
	}
	if (n == 0)
	{
		cout << 0 << endl;
		return 0;
	}
	int maxVal = a[0];
	for (int i = 1; i < n; ++i)
	{
		if (a[i] > maxVal) maxVal = a[i];
	}
	bool hasSecond = false;
	int secondVal = 0;
	for (int i = 0; i < n; ++i)
	{
		if (a[i] < maxVal)
		{
			if (!hasSecond || a[i] > secondVal)
			{
				secondVal = a[i];
				hasSecond = true;
			}
		}
	}
	if (hasSecond) cout << secondVal << endl; else cout << 0 << endl;
	return 0;
}


