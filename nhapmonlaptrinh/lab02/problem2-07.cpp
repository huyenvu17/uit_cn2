#include <iostream>
#include <cmath>

int main() {
    double a, b, c;
    std::cin >> a >> b >> c;
    
    if(a == 0) {
        std::cout << "Khong phai phuong trinh bac hai" << std::endl;
    } else {
        double delta = b*b - 4*a*c;
        if(delta < 0) {
            std::cout << "PTVN" << std::endl;
        } else if(delta == 0) {
            std::cout << "PT co nghiem kep: x1 = x2 = " << -b/(2*a) << std::endl;
        } else {    
            std::cout << "PT co hai nghiem phan biet:" << std::endl;
            std::cout << "x1 = " << (-b + sqrt(delta))/(2*a) << std::endl;
            std::cout << "x2 = " << (-b - sqrt(delta))/(2*a) << std::endl;
        }
    }

    return 0;
}