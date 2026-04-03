#include <stdio.h>
#include <math.h>

int main() {
    double x = 0.5;
    double y = 0.5;
    double angle = 0.0;
    double value = 2.71828;
    double positive_value = 100.5;
    double negative_value = -100.5;
    
    // Test inverse trigonometric functions
    printf("Testing math functions...\n");
    
    // Test asin
    double asin_result = asin(x);
    printf("asin(%.2f) = %.4f\n", x, asin_result);
    
    // Test acos
    double acos_result = acos(x);
    printf("acos(%.2f) = %.4f\n", x, acos_result);
    
    // Test atan
    double atan_result = atan(x);
    printf("atan(%.2f) = %.4f\n", x, atan_result);
    
    // Test atan2
    double atan2_result = atan2(y, x);
    printf("atan2(%.2f, %.2f) = %.4f\n", y, x, atan2_result);
    
    // Test hyperbolic functions
    // Test sinh
    double sinh_result = sinh(x);
    printf("sinh(%.2f) = %.4f\n", x, sinh_result);
    
    // Test cosh
    double cosh_result = cosh(x);
    printf("cosh(%.2f) = %.4f\n", x, cosh_result);
    
    // Test tanh
    double tanh_result = tanh(x);
    printf("tanh(%.2f) = %.4f\n", x, tanh_result);
    
    // Test exponential and logarithmic functions
    // Test exp
    double exp_result = exp(x);
    printf("exp(%.2f) = %.4f\n", x, exp_result);
    
    // Test log (natural logarithm)
    double log_result = log(value);
    printf("log(%.4f) = %.4f\n", value, log_result);
    
    // Test log10 (base 10 logarithm)
    double log10_result = log10(100.0);
    printf("log10(100.0) = %.4f\n", log10_result);
    
    // Test log2 (base 2 logarithm)
    double log2_result = log2(8.0);
    printf("log2(8.0) = %.4f\n", log2_result);
    
    // Test rounding functions
    // Test floor
    double floor_result = floor(positive_value);
    printf("floor(%.2f) = %.2f\n", positive_value, floor_result);
    
    // Test ceil
    double ceil_result = ceil(negative_value);
    printf("ceil(%.2f) = %.2f\n", negative_value, ceil_result);
    
    return 0;
}
