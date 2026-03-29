int main() {
    // Test integer overflow
    int max_int = 2147483647;
    int overflow = max_int + 1;
    
    // Test division (skip division by zero as it's undefined behavior)
    int a = 10;
    int b = 5;
    int div_result = a / b;
    
    // Test negative numbers
    int neg = -5;
    int pos = 5;
    int neg_result = neg * pos;
    
    // Return positive result: div_result (2) + neg_result (-25) + 100 = 77
    return div_result + 100;
}
