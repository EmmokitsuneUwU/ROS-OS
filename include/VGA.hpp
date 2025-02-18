#ifndef VGA_HPP
#define VGA_HPP
#include <stdint.h>

void VGAMODETEXT();
void VGAMODEGRAPHICS();

extern volatile uint8_t* vga_memory;

void clear_screen(uint8_t color);


#endif