/*
*
* interrupt.c | Interrupt handling
* (c) The QuantumCore Project & Wqreloxzz 2024-2025
*
*/


#include <QuantumCore/ctypes.h>

typedef void (*interrupt_t)(void);

void interrupt(u8 irq, interrupt_t handler);
