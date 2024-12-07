/*
*
* err.h | Error handling
* (c) The QuantumCore Project & Wqreloxzz 2024-2025
*
*/

#include <QuantumCore/terminal.h>

// thanks gcc...
void __stack_chk_fail_local(){
        printt("[ERROR] ", BRIGHT_RED);
        printt("__stack_chk_fail_local() has been called", WHITE);
        newline();
}
