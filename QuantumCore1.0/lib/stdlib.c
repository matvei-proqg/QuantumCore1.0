/*
*
* std/stdlib.h | A reduced version of <stdlib.h>
* (c) The QuantumCore Project & Wqreloxzz 2024-2025
*
*/

#include <QuantumCore/stdlib.h>
#include <QuantumCore/terminal.h>
#include <QuantumCore/color.h>

u32 strlen(const char* str){
	u32 len = 0;
	while(str[len]){
		len++;
	}
	return len;
}

void *memset(void *dst, char c, u32 n){
	char *temp = dst;
	for(; n != 0; n--) *temp++ = c;
	return dst;
}

void printf(const char *format, ...){
	char **args = (char**)&format;
	int c = 1;
	char buf[32];

	memset(buf, 0, sizeof(buf));
	while((c = *format++) != 0) {
		if(c != '%')
			printchar(c, WHITE);
		else {
			char *ptr, *ptr2;
			int pad = 0, pad1 = 0;

			c = *format++;
			switch(c){
				case 'd':
				case 's':
					ptr = *args++;
					if(!ptr) ptr = "?";
					for(; ptr2 < ptr + pad1; ptr2++)
						printchar(pad ? '0' : ' ', WHITE);
					while(*ptr)
						printchar(*ptr++, WHITE);
					break;
				default:
					printchar(*((int *)args++), WHITE);
					break;
			}
		}
	}
}
