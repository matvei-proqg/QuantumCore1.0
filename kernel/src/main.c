/*
*
* main.c | The entry point
* (c) The QuantumCore Project & Copy05 2023
*
*/

#include <QuantumCore/ctypes.h>
#include <QuantumCore/color.h>
#include <QuantumCore/terminal.h>
#include <QuantumCore/drivers/keyboard.h>
#include <QuantumCore/err.h>
#include <QuantumCore/interrupt.h>

// Keyboard Handling
char buffer[256];
u32 buf_pos = 0;

int main(){
	cls();
	printt("Loading Lennox 1.0.0 x86_64", WHITE);
	newline();
	_sleep(2000);
	printt("Loaded", BRIGHT_GREEN);
	newline();
	interrupt(0x21, keyboard_handler);
	return 0;
}
