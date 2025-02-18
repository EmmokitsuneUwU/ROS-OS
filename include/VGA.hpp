#ifndef VGA_HPP
#define VGA_HPP
#include <stdint.h>

void VGAMODETEXT();
void VGAMODEGRAPHICS();

extern volatile uint8_t* vga_memory;

void GRAPHICSMODEClearScreen(uint8_t color);
void GRAPHICSMODEDrawPixel(int x, int y, uint8_t color);

#endif