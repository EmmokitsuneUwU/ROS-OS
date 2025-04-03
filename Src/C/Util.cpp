#include "Util.hpp"
#include <stdbool.h>
#include <stdint.h>

#define MAX_ARGS 5

char kernelVersion[6] = "0.0.7";

void cpuid(int code, uint32_t* a, uint32_t* d) {
    asm volatile("cpuid"
                : "=a" (*a), "=d" (*d)
                 : "a" (code)
                 : "ecx", "ebx");
}

static inline void outw(uint16_t port, uint16_t val) {
    __asm__ volatile ("outw %0, %1" : : "a"(val), "Nd"(port));
}

void shutdownAPM()
{
    outw(0xB004, 0x0000);
    outw(0x604, 0x2000); 
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

void parse_command(char *input, char *args[], int *argc) {
    *argc = 0;

    while (*input) {
        while (*input == ' ') input++;
        if (*input == '\0') break;

        args[(*argc)++] = input;

        while (*input && *input != ' ') input++;
        if (*input) *(input++) = '\0';

        if (*argc >= MAX_ARGS) break;
    }
}