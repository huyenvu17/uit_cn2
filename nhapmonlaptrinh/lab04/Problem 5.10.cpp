#include <iostream>
using namespace std;

int modulo(int m, int n) {
    // Không dùng toán tử %
    // Không dùng %, /, *
    // Tìm phần dư bằng cách trừ dần n khỏi m cho đến khi m < n
    if (m < n) return m;
    return modulo(m - n, n);
}


int main (){
    int m, n; cin >> m >> n;
	cout << modulo(m, n);
}