#include <iostream>
using namespace std;

int largest_input(){
    int x;
    cin >> x;
    if (x == 0) return 0;
    int next_max = largest_input();
    if (next_max == 0) return x;
    return (x > next_max) ? x : next_max;
}
int main(){
	cout << largest_input();
}
