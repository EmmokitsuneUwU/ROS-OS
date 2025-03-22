#ifndef VGA_HPP
#define VGA_HPP
#include <stdint.h>
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

extern unsigned int vidMemory;
extern int characters;

extern bool onCommandMode;
extern bool onGraphicsMode;

void VGAMODETEXT();
void VGAMODEGRAPHICS();
extern void clearScreen();
extern void charPrint(int chr,uint8_t color);
extern void strPrint(const char str[], uint8_t color);
extern void printROSLogo();

extern volatile uint8_t* vga_memory;

void GRAPHICSMODEClearScreen(uint8_t color);
void GRAPHICSMODEDrawPixel(int x, int y, uint8_t color);

#endif