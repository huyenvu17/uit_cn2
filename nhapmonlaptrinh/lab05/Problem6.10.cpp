#include <iostream>
using namespace std;
#define MAX 300

int main()
{
	int na, nb;
	int a[MAX], b[MAX], c[MAX];
	cin >> na;
	for (int i = 0; i < na; ++i)
	{
		cin >> a[i];
	}
	cin >> nb;
	for (int i = 0; i < nb; ++i)
	{
		cin >> b[i];
	}
	int i = 0, j = 0, k = 0;
	while (i < na && j < nb)
	{
		if (a[i] <= b[j]) c[k++] = a[i++];
		else c[k++] = b[j++];
	}
	while (i < na) c[k++] = a[i++];
	while (j < nb) c[k++] = b[j++];
	for (int idx = 0; idx < k; ++idx)
	{
		if (idx) cout << " ";
		cout << c[idx];
	}
	cout << endl;
	return 0;
}


