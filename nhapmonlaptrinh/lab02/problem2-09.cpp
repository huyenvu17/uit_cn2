#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;

int main() {
    double a, b, c;

    // Đọc 3 cạnh từ input
    cin >> a >> b >> c;

    // Kiểm tra điều kiện tam giác
    if (a > 0 && b > 0 && c > 0 && (a + b > c) && (a + c > b) && (b + c > a)) {
        const double EPSILON = 1e-9;

        // Kiểm tra các loại tam giác
        bool isDeu = (a == b && b == c);
        bool isCan = (a == b || b == c || a == c);
        
        // Kiểm tra tam giác vuông
        double sides[3] = {a, b, c};
        sort(sides, sides + 3);
        bool isVuong = (fabs(sides[0] * sides[0] + sides[1] * sides[1] - sides[2] * sides[2]) < EPSILON);

        // Tính diện tích bằng công thức Heron
        double s = (a + b + c) / 2.0;
        double area = sqrt(s * (s - a) * (s - b) * (s - c));

        // In kết quả theo thứ tự ưu tiên
        if (isDeu) {
            cout << "Tam giac deu, dien tich = " << fixed << setprecision(2) << area;
        } else if (isCan) {
            cout << "Tam giac can, dien tich = " << fixed << setprecision(2) << area;
        } else if (isVuong) {
            cout << "Tam giac vuong, dien tich = " << fixed << setprecision(2) << area;
        } else {
            cout << "Tam giac thuong, dien tich = " << fixed << setprecision(2) << area;
        }
    } else {
        cout << "Khong phai tam giac";
    }

    return 0;
}
