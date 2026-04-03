#include <stdio.h>
#include <stdlib.h>

int main() {
    void* ptr1;
    void* ptr2;
    int* int_array;
    int i;
    
    // Test calloc
    printf("Testing memory allocation functions...\n");
    
    int_array = (int*)calloc(5, sizeof(int));
    if (int_array) {
        printf("calloc(5, sizeof(int)) = %p\n", int_array);
        
        // Verify all elements are initialized to 0
        for (i = 0; i < 5; i++) {
            printf("int_array[%d] = %d\n", i, int_array[i]);
        }
        
        // Test realloc to increase size
        ptr1 = realloc(int_array, 10 * sizeof(int));
        if (ptr1) {
            printf("realloc(ptr1, 10 * sizeof(int)) = %p\n", ptr1);
            int_array = (int*)ptr1;
            
            // Initialize new elements
            for (i = 5; i < 10; i++) {
                int_array[i] = i * 10;
            }
            
            // Print all elements
            for (i = 0; i < 10; i++) {
                printf("int_array[%d] = %d\n", i, int_array[i]);
            }
            
            // Test realloc to decrease size
            ptr2 = realloc(int_array, 3 * sizeof(int));
            if (ptr2) {
                printf("realloc(ptr2, 3 * sizeof(int)) = %p\n", ptr2);
                int_array = (int*)ptr2;
                
                // Print remaining elements
                for (i = 0; i < 3; i++) {
                    printf("int_array[%d] = %d\n", i, int_array[i]);
                }
                
                free(int_array);
                printf("free(int_array) done\n");
            } else {
                printf("realloc to smaller size failed\n");
                free(int_array);
            }
        } else {
            printf("realloc failed\n");
            free(int_array);
        }
    } else {
        printf("calloc failed\n");
    }
    
    return 0;
}
