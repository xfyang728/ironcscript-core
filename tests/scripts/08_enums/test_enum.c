int main() {
    enum Color {
        RED,
        GREEN = 5,
        BLUE
    };
    
    enum Color c = BLUE;
    return c;
}