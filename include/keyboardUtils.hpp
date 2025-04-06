#ifndef KEYBOARD_UTILS
#define KEYBOARD_UTILS
#define KEYBOARD_PORT 0x60
#include <stdint.h>

extern "C"
{
extern "C" char scancodeToIntChar(uint8_t scancode);
static inline uint8_t inb(uint16_t port);
extern char read_key_polling();
}

#endif

