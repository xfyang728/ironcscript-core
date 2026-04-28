int main() {
    double a = 3.0;
    double b = 5.0;
    double c = 3.0;
    int ok = 0;
    
    if (a < b) ok = ok + 1;
    if (b > a) ok = ok + 1;
    if (a <= c) ok = ok + 1;
    if (a >= c) ok = ok + 1;
    if (a == c) ok = ok + 1;
    if (a != b) ok = ok + 1;
    
    if (ok == 6) return 0;
    return 1;
}
