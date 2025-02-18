#include "Util.hpp"
#include <stdbool.h>

void shutdownAPM() {
    asm volatile (
        "mov $0x5307, %ax \n"
        "mov $0x0001, %bx \n"
        "mov $0x0003, %cx \n"
        "int $0x15"
    );
}

bool StrCmp(const char* str1, const char* str2)
{
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) {
            return false;
        }
            str1++;
            str2++;
        }
    
    return (*str1 == '\0' && *str2 == '\0');
}
