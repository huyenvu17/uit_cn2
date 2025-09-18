
#include <iostream>
using namespace std;
#define MAX 100

//Write your code here
void Nhapmang(int a[], int n)
{
	for (int i = 0; i < n; ++i)
		cin >> a[i];
}

int firstDigit(int x)
{
	while (x >= 10)
		x /= 10;
	return x;
}

bool isBenford(int a[], int n)
{
	int count1 = 0, count4 = 0;
	for (int i = 0; i < n; ++i)
	{
		int fd = firstDigit(a[i]);
		if (fd == 1)
			++count1;
		else if (fd == 4)
			++count4;
	}
	return (count1 == 3 && count4 == 1);
}

int main()
{
	int a[MAX], n = 10;
	Nhapmang(a, n);
	if (isBenford(a, n) == true)
		cout << "TRUE" << endl;
	else
		cout << "FALSE" << endl;
	return 0;
}