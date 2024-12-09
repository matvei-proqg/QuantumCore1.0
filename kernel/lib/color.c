/*
*
* color.c | VGA Color Codes for the terminal
* (c) The QuantumCore Project & Wqreloxzz 2024-2025
*
*/

#include <QuantumCore/terminal.h>

void displayAllColors(){
        for(int i = 0; i < 256; i++)
                printt("0", i);
}
