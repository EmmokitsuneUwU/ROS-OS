#ifndef VGA_HPP
#define VGA_HPP
#include <stdint.h>
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

extern unsigned int vidMemory;
extern int characters;

extern bool onCommandMode;
extern bool onGraphicsMode;

extern volatile uint8_t* vga_memory;

extern "C"
{
    extern void VGAMODETEXT();
    extern void VGAMODEGRAPHICS();
    extern void clearScreen();
    extern void charPrint(unsigned char chr,uint8_t color);
    extern void strPrint(const char str[], uint8_t color);
    extern void printROSLogo();
    
    extern void GRAPHICSMODEClearScreen(uint8_t color);
    extern void GRAPHICSMODEDrawPixel(int pos_x, int pos_y, uint8_t VGA_COLOR);
}

#endif
