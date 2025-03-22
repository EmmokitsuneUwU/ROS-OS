#ifndef UTIL_HPP
#define UTIL_HPP
#include <stdint.h>

extern void cpuid(int code, uint32_t* a, uint32_t* d);

extern void shutdownAPM();

extern bool StrCmp(const char* str1, const char* str2);
extern int StrLen(const char* str);
extern void StrCpy(char* dest, const char* src);
extern int StrSlit(const char *str, char partes[3][32], char delim);

extern char kernelVersion[6];

#endif // UTIL_HPP