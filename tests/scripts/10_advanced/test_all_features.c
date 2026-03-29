// 测试所有新实现的功能

// 测试 switch-case 控制流
int test_switch_case(int value) {
    int result = 0;
    switch (value) {
        case 1:
            result = 10;
            break;
        case 2:
            result = 20;
            break;
        case 3:
            result = 30;
            break;
        default:
            result = 0;
            break;
    }
    return result;
}

// 测试数组操作
int test_array() {
    int arr[5] = {1, 2, 3, 4, 5};
    arr[2] = 10;
    return arr[0] + arr[2] + arr[4];
}

// 测试指针操作
int test_pointer() {
    int x = 10;
    int* p = &x;
    *p = 20;
    return x;
}

// 测试结构体
struct Point {
    int x;
    int y;
};

int test_struct() {
    struct Point p;
    p.x = 5;
    p.y = 10;
    return p.x + p.y;
}

// 测试联合体
union Value {
    int i;
    float f;
};

int test_union() {
    union Value v;
    v.i = 100;
    return v.i;
}

// 主函数，测试所有功能
int main() {
    int switch_result = test_switch_case(2);
    int array_result = test_array();
    int pointer_result = test_pointer();
    int struct_result = test_struct();
    int union_result = test_union();
    
    // 返回所有测试结果的和
    return switch_result + array_result + pointer_result + struct_result + union_result;
}
