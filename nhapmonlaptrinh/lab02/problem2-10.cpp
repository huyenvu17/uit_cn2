#include <iostream>
#include <cmath>
using namespace std;

bool isLeap(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int main() {
    int d, m, y;
    if (!(cin >> d >> m >> y)) return 0;

    // Ưu tiên kiểm tra: năm -> tháng -> ngày
    if (y <= 0) {
        cout << "Nam khong hop le.";
        return 0;
    }

    if (m < 1 || m > 12) {
        cout << "Thang khong hop le.";
        return 0;
    }

    int maxDay;
    if (m == 2) {
        maxDay = isLeap(y) ? 29 : 28;
    } else if (m == 4 || m == 6 || m == 9 || m == 11) {
        maxDay = 30;
    } else {
        maxDay = 31;
    }

    if (d >= 1 && d <= maxDay) {
        cout << d << "/" << m << "/" << y << " la ngay hop le.";
    } else {
        cout << d << "/" << m << "/" << y << " la ngay khong hop le.";
    }

    return 0;
}
