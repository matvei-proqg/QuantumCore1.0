/*
*
* asm.c | Assembly Functions
* (c) The QuantumCore Project & Wqreloxzz 2024-2025
*
*/


#include <QuantumCore/asm.h>
#include <QuantumCore/ctypes.h>

u8 inb(u16 port)
{
  u8 ret;
  asm volatile("inb %1, %0" : "=a"(ret) : "d"(port));
  return ret;
}

void outb(u16 port, u8 data)
{
  asm volatile("outb %0, %1" : "=a"(data) : "d"(port));
}
