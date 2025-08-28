
#include <iostream>
#include <cmath>


int main()
{
    double a;
    int n;
    std::cin >> a >> n;

    if (n < 0) {
        std::cout << "n phai la so nguyen duong" << std::endl;
        return 1;
    }

    double rounded = (int)(a * n + 0.5) / (double)n;
    std::cout.precision(10);
    std::cout << rounded << "\n";
    return 0; 
}
