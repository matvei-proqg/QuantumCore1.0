/*
*
* terminal.h | Terminal output
* (c) The QuantumCore Project & Wqreloxzz 2024-2025
*
*/

#include <QuantumCore/ctypes.h>

#define VGA_ADDR 0xB8000;

void printerr(char* str);
void printt(char* str, u8 color);
void printchar(char str, u8 color);
void cls(void);
void _sleep(u32 ms);
