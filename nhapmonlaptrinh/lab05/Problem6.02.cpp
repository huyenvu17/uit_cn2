



#include <iostream>
#include <math.h>
using namespace std;
#define MAX 100

void NhapmangSNT(int a[], int &n);
int SoPhanTuChuaY(int a[], int n,int y);

//Write your code here

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

void NhapmangSNT(int a[], int &n)
{
	cin >> n;
	int count = 0;
	int num = 2;
	while (count < n)
	{
		if (isPrime(num))
		{
			a[count++] = num;
		}
		++num;
	}
}

int SoPhanTuChuaY(int a[], int n, int y)
{
	int result = 0;
	for (int i = 0; i < n; ++i)
	{
		int value = a[i];
		if (value == 0)
		{
			if (y == 0) ++result;
			continue;
		}
		int t = value;
		while (t > 0)
		{
			if (t % 10 == y)
			{
				++result;
				break;
			}
			t /= 10;
		}
	}
	return result;
}

int main()
{
	int a[MAX], n, y;
	cin >>y;
	NhapmangSNT(a,n);
	cout << SoPhanTuChuaY(a, n, y) << endl;;
	return 0;
}