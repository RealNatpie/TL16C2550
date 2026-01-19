#include <stdio.h>
#include "tl16c2550.h"

int main(void) {
    unsigned char i;
    unsigned char result;
    
    printf("Library Test - Adding 5 to values\n");
    printf("==================================\n\n");
    
    for (i = 0; i < 10; i++) {
        result = libtest(i);
        printf("Input: %d, Output: %d\n", i, result);
    }
    
    printf("\nTest complete!\n");
    
    return 0;
}
