#include "VGA.hpp"
#include <stdint.h>

#define VGA_MISC_PORT 0x3C2
#define VGA_CRTC_INDEX 0x3D4
#define VGA_CRTC_DATA  0x3D5
#define VGA_SEQ_INDEX 0x3C4
#define VGA_SEQ_DATA  0x3C5
#define VGA_GFX_INDEX 0x3CE
#define VGA_GFX_DATA  0x3CF

volatile uint8_t* vga_memory = (uint8_t*) 0xA0000;

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

void clear_screen(uint8_t color) {
    for (int i = 0; i < 320 * 200; i++)
        vga_memory[i] = color;
}