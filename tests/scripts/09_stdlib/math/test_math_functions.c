#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
    double x = 4.0;
    double y = 2.0;
    double angle = 0.0;
    
    // Test sqrt
    double sqrt_result = sqrt(x);
    printf("sqrt(%.1f) = %.1f\n", x, sqrt_result);
    
    // Test pow
    double pow_result = pow(x, y);
    printf("pow(%.1f, %.1f) = %.1f\n", x, y, pow_result);
    
    // Test sin
    double sin_result = sin(angle);
    printf("sin(%.1f) = %.1f\n", angle, sin_result);
    
    // Test cos
    double cos_result = cos(angle);
    printf("cos(%.1f) = %.1f\n", angle, cos_result);
    
    // Test tan
    double tan_result = tan(angle);
    printf("tan(%.1f) = %.1f\n", angle, tan_result);
    
    // Test abs
    int int_value = -5;
    int abs_result = abs(int_value);
    printf("abs(%d) = %d\n", int_value, abs_result);
    
    // Test fabs
    double double_value = -3.14;
    double fabs_result = fabs(double_value);
    printf("fabs(%.2f) = %.2f\n", double_value, fabs_result);
    
    return 0;
}