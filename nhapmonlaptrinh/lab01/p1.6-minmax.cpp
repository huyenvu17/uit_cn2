#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int a, b;
    cin >> a >> b;

    int maxVal = (a + b + abs(a - b)) / 2;
    int minVal = (a + b - abs(a - b)) / 2;

    cout << "max = " << maxVal << endl;
    cout << "min = " << minVal << endl;

    return 0;
}