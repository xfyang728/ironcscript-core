extern void println(int value);

void testArrayBasic() {
    int arr[5];
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;
    arr[3] = 40;
    arr[4] = 50;

    println(arr[0]);
    println(arr[1]);
    println(arr[2]);
    println(arr[3]);
    println(arr[4]);
}

void testArrayInit() {
    int arr[3];
    arr[0] = 100;
    arr[1] = 200;
    arr[2] = 300;
    println(arr[0]);
    println(arr[1]);
    println(arr[2]);
}

void testArrayIndex() {
    int arr[5];
    int i;
    for (i = 0; i < 5; i = i + 1) {
        arr[i] = (i + 1) * 10;
    }
    for (i = 0; i < 5; i = i + 1) {
        println(arr[i]);
    }
}

void main() {
    println(1000);
    testArrayBasic();
    println(2000);
    testArrayInit();
    println(3000);
    testArrayIndex();
    println(9999);
}