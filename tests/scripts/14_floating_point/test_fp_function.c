double add(double a, double b) { return a + b; }
double mul(double a, double b) { return a * b; }

int main() {
    double x = 3.0;
    double y = 7.0;
    double r1 = add(x, y);
    double r2 = mul(x, y);
    
    if (r1 == 10.0 && r2 == 21.0) return 0;
    return 1;
}
