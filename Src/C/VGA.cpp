#include "VGA.hpp"
#include <stdint.h>
#include "Colors.hpp"

#define VGA_MISC_PORT 0x3C2
#define VGA_CRTC_INDEX 0x3D4
#define VGA_CRTC_DATA  0x3D5
#define VGA_SEQ_INDEX 0x3C4
#define VGA_SEQ_DATA  0x3C5
#define VGA_GFX_INDEX 0x3CE
#define VGA_GFX_DATA  0x3CF

volatile uint8_t* vga_memory = (uint8_t*) 0xA0000;
unsigned int vidMemory = 0xb8000;
int characters = 0;
bool onCommandMode = false;
bool onGraphicsMode = false;

static inline void outb(uint16_t port, uint8_t val) {
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

void VGAMODETEXT() {
    outb(0x3C2, 0x67);
    outb(VGA_CRTC_INDEX, 0x11);
    outb(VGA_CRTC_DATA, 0x20);

    outb(VGA_CRTC_INDEX, 0x03);
    outb(VGA_CRTC_DATA, 0x82);

    outb(VGA_CRTC_INDEX, 0x14);
    outb(VGA_CRTC_DATA, 0x40);

    outb(0x3D8, 0x63);
}

void VGAMODEGRAPHICS() {
    outb(0x3C2, 0x63);


    outb(VGA_SEQ_INDEX, 0x00); outb(VGA_SEQ_DATA, 0x03);
    outb(VGA_SEQ_INDEX, 0x01); outb(VGA_SEQ_DATA, 0x00);
    outb(VGA_SEQ_INDEX, 0x02); outb(VGA_SEQ_DATA, 0x0F);
    outb(VGA_SEQ_INDEX, 0x03); outb(VGA_SEQ_DATA, 0x00);
    outb(VGA_SEQ_INDEX, 0x04); outb(VGA_SEQ_DATA, 0x0E);

    outb(VGA_GFX_INDEX, 0x05); outb(VGA_GFX_DATA, 0x40);
    outb(VGA_GFX_INDEX, 0x06); outb(VGA_GFX_DATA, 0x05);

    outb(0x3D8, 0xA0);
}

void GRAPHICSMODEClearScreen(uint8_t color) {
    for (int i = 0; i < 320 * 200; i++)
        vga_memory[i] = color;
}
void GRAPHICSMODEDrawPixel(int x, int y, uint8_t color) {
    unsigned short offset = y * 320 + x;
    vga_memory[offset] = color;
}

void clearScreen()
{
    for(int i = 0; i < characters; i++)
    {
        *(char*)(vidMemory - 2)= ' ';
        vidMemory -= 2;
    }
    characters = 0;
    vidMemory = 0xb8000;
}

void charPrint(int chr,uint8_t color = 0x0F)
{
    if(vidMemory < 0xB8F95)
    {
        if (chr == '\n') {
            unsigned int offset = vidMemory - 0xB8000;
            unsigned int row = offset / (VGA_WIDTH * 2);
            vidMemory = 0xB8000 + (row + 1) * VGA_WIDTH * 2;
            characters += 80;
        } else {
            *(char*)vidMemory = chr;
            *(char*)(vidMemory + 1) = color;
            vidMemory += 2;
        }
        characters += 1;
    }
    else{
        clearScreen();
    }

}

void strPrint(const char str[], uint8_t color = 0x0F)
{
    int i = 0;
    while(str[i] != '\0')
    {
        charPrint(str[i],color);
        i += 1;
    }
}

void printROSLogo()
{
    //Print ROS in ASCII art
    strPrint("\xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB \n",colorBrown);
    strPrint("\xDB    \xDB  \xDB   \xDB  \xDB \n",colorBrown);
    strPrint("\xDB\xDB\xDB\xDB\xDB\xDB  \xDB   \xDB  \xDB\xDB\xDB\xDB\xDB \n",colorBrown);
    strPrint("\xDB   \xDB   \xDB   \xDB      \xDB \n",colorBrown);
    strPrint("\xDB   \xDB   \xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB \n\n",colorBrown);
    strPrint(" \xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF \n\n",colorBrown);
}