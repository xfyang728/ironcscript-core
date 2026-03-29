// 详细测试所有新实现的功能

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

// 测试结构体指针
int test_struct_pointer() {
    struct Point p;
    p.x = 10;
    p.y = 20;
    struct Point* pp = &p;
    pp->x = 30;
    return pp->x + pp->y;
}

// 测试数组指针
int test_array_pointer() {
    int arr[3] = {1, 2, 3};
    int* p = arr;
    p[1] = 10;
    return arr[0] + arr[1] + arr[2];
}

// 主函数，测试所有功能
int main() {
    // 测试 switch-case
    int switch_result = test_switch_case(2);
    
    // 测试数组
    int array_result = test_array();
    
    // 测试指针
    int pointer_result = test_pointer();
    
    // 测试结构体
    int struct_result = test_struct();
    
    // 测试联合体
    int union_result = test_union();
    
    // 测试结构体指针
    int struct_ptr_result = test_struct_pointer();
    
    // 测试数组指针
    int array_ptr_result = test_array_pointer();
    
    // 打印所有测试结果
    // 注意：我们无法直接打印，所以通过返回值来验证
    
    // 返回所有测试结果的和
    return switch_result + array_result + pointer_result + struct_result + union_result + struct_ptr_result + array_ptr_result;
}
