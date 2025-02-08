#include "keyboardUtils.hpp"

static inline uint8_t inb(uint16_t port) {
    uint8_t value;
    asm volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

char read_key_polling() {
    return inb(KEYBOARD_PORT);
}

extern "C" char scancodeToIntChar(uint8_t scancode)
{
    switch (scancode) {
        case 0x1C: return 'A';
        case 0x32: return 'B';
        case 0x21: return 'C';
        case 0x23: return 'D';
        case 0x24: return 'E';
        case 0x2B: return 'F';
        case 0x34: return 'G';
        case 0x33: return 'H';
        case 0x43: return 'I';
        case 0x3B: return 'J';
        case 0x42: return 'K';
        case 0x4B: return 'L';
        case 0x3A: return 'M';
        case 0x31: return 'N';
        case 0x44: return 'O';
        case 0x4D: return 'P';
        case 0x15: return 'Q';
        case 0x2D: return 'R';
        case 0x1B: return 'S';
        case 0x2C: return 'T';
        case 0x3C: return 'U';
        case 0x2A: return 'V';
        case 0x1D: return 'W';
        case 0x22: return 'X';
        case 0x35: return 'Y';
        case 0x1A: return 'Z';
        default: return '?';
    }
}
