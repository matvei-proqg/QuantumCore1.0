/*
*
* std/stdlib.h | A reduced version of <stdlib.h>
* (c) The QuantumCore Project & Wqreloxzz 2024-2025
*
*/

#include <QuantumCore/ctypes.h>
#include <QuantumCore/terminal.h>

u32 strlen(const char* str);
void printf(const char* format, ...);
void *memset(void *dst, char c, u32 n);
