/*
*
* interrupt.c | Interrupt handling
* (c) The QuantumCore Project & Wqreloxzz 2024-2025
*
*/

#include <QuantumCore/interrupt.h>

void interrupt(u8 irq, interrupt_t handler){
	interrupt_t* intv = (interrupt_t)0x10000;
	intv[irq] = handler;
}
