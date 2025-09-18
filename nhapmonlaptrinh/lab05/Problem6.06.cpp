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
	int currentMax = a[0];
	for (int i = 1; i < n; ++i)
	{
		if (a[i] > currentMax) currentMax = a[i];
	}
	int countMax = 0;
	for (int i = 0; i < n; ++i)
	{
		if (a[i] == currentMax) ++countMax;
	}
	cout << currentMax << endl;
	cout << countMax;
	return 0;
}


