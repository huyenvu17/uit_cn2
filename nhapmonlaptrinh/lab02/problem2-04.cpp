
#include <iostream>
#include <cmath>


int main()
{
    double a;
    int n;
    std::cin >> a >> n;

    // thêm code duoi day
    // Tách phần nguyên
    int integer_part = (int)a;
    // Lấy phần thập phân
    double decimal_part = a - integer_part;
    
    // Nhân phần thập phân với n và làm tròn
    double rounded_decimal = round(decimal_part * n);
    
    // Tính kết quả cuối cùng: phần nguyên + phần thập phân đã làm tròn/n
    double result = integer_part + rounded_decimal/n;
    
    std::cout.precision(10);
    std::cout.setf(std::ios::fixed);
    std::cout << result;
}
