int main() {
    int i = 42;
    double d = 3.14;
    
    double di = (double)i;
    int id = (int)d;
    
    if (di == 42.0 && id == 3) return 0;
    return 1;
}
