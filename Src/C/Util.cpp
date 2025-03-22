#include "Util.hpp"
#include <stdbool.h>
#include <stdint.h>

char kernelVersion[6] = "0.0.4";

void cpuid(int code, uint32_t* a, uint32_t* d) {
    asm volatile("cpuid"
                : "=a" (*a), "=d" (*d)
                 : "a" (code)
                 : "ecx", "ebx");
}



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

int StrLen(const char* str)
{
    int len = 0;
    while (str[len] != '\0')
    {
        len++;
    }
    return len;
}

void StrCpy(char* dest, const char* src)
{
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
}

int StrSlit(const char *str, char partes[3][32], char delim)
{
    int len = StrLen(str);
    int part = 0;
    int pos = 0;

    for (int i = 0; i <= len; i++) {
        if (str[i] == delim || str[i] == '\0') {
            partes[part][pos] = '\0';
            part++;
            pos = 0;
        } else {
            partes[part][pos++] = str[i];
        }
    }
    return part;
}
