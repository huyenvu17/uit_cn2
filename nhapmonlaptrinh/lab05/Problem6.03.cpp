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
	bool firstPrinted = false;
	for (int i = 1; i < n; i += 2)
	{
		if (firstPrinted) cout << " ";
		cout << a[i];
		firstPrinted = true;
	}
	cout << endl;
	return 0;
}


