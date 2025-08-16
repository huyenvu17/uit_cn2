#include <iostream>
#include <cmath>    // Thư viện cho hàm floor()
#include <cstdio>   // Thư viện cho hàm printf()

int main() {
    double a;
    int n;

    std::cin >> a >> n;

    double scaled_a = a * n;
    
    double rounded_scaled_a = floor(scaled_a + 0.5); 
    
    double final_result = rounded_scaled_a / static_cast<double>(n);

    printf("%.10f\n", final_result);

    return 0;
}
