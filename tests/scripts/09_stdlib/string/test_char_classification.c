#include <ctype.h>

int main() {
    char test_chars[] = {'0', '9', 'A', 'Z', 'a', 'z', ' ', '\n', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '\0'};
    int i;
    
    printf("Testing character classification functions...\n");
    
    for (i = 0; test_chars[i] != '\0'; i++) {
        char c = test_chars[i];
        printf("Character: '%c' (0x%02X)\n", c, (unsigned char)c);
        
        // Test isdigit
        printf("  isdigit: %d\n", isdigit((unsigned char)c));
        
        // Test isalpha
        printf("  isalpha: %d\n", isalpha((unsigned char)c));
        
        // Test isalnum
        printf("  isalnum: %d\n", isalnum((unsigned char)c));
        
        // Test isspace
        printf("  isspace: %d\n", isspace((unsigned char)c));
        
        // Test isupper
        printf("  isupper: %d\n", isupper((unsigned char)c));
        
        // Test islower
        printf("  islower: %d\n", islower((unsigned char)c));
        
        // Test isgraph
        printf("  isgraph: %d\n", isgraph((unsigned char)c));
        
        // Test isprint
        printf("  isprint: %d\n", isprint((unsigned char)c));
        
        // Test ispunct
        printf("  ispunct: %d\n", ispunct((unsigned char)c));
        
        // Test iscntrl
        printf("  iscntrl: %d\n", iscntrl((unsigned char)c));
        
        printf("\n");
    }
    
    return 0;
}
