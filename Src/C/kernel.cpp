#include <stdint.h>
#include "keyboardUtils.hpp"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

unsigned int vidMemory;
int characters;

char commandsBuffer[32];

bool onCommandMode = false;

// BASIC DECLARATIONS

void shutdownAPM() {
    asm volatile (
        "mov $0x5307, %ax \n"
        "mov $0x0001, %bx \n"
        "mov $0x0003, %cx \n"
        "int $0x15"
    );
}

extern "C" void clearScreen()
{
    for(int i = 0; i < characters; i++)
    {
        *(char*)(vidMemory - 2)= ' ';
        vidMemory -= 2;
    }
    characters = 0;
    vidMemory = 0xb8000;
}

extern "C" void charPrint(int chr)
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
            vidMemory += 2;
        }
        characters += 1;
    }
    else{
        clearScreen();
    }

}

extern "C" void strPrint(const char str[])
{
    int i = 0;
    while(str[i] != '\0')
    {
        charPrint(str[i]);
        i += 1;
    }
}

// BASIC DECLARATIONS

// NORMAL DECLARATIONS

extern "C" void printROSLogo()
{
    //Print ROS in ASCII art
    strPrint("\xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB \n");
    strPrint("\xDB    \xDB  \xDB   \xDB  \xDB \n");
    strPrint("\xDB\xDB\xDB\xDB\xDB\xDB  \xDB   \xDB  \xDB\xDB\xDB\xDB\xDB \n");
    strPrint("\xDB   \xDB   \xDB   \xDB      \xDB \n");
    strPrint("\xDB   \xDB   \xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB \n\n");
    strPrint(" \xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF \n\n");
}

// NORMAL DECLARATIONS

extern "C" void main() {
    vidMemory = 0xb8000;
    characters = 0;

    printROSLogo();

    strPrint("Welcome to the ROS OS \n\n");

    strPrint("Press 'C' to enter command mode | Press 'S' to shutdown \n");

    while(1)
    {
        uint8_t scancode = read_key_polling();

        switch (scancode)
        {
        case 0x01:
            clearScreen();
            break;
        case 0x9F:
            shutdownAPM();
            break;
        case 0x2E:
            clearScreen();
            strPrint("Welcome to command mode \n");
            strPrint("Type 'exit' to quit \n");
            strPrint("Enjoy! \n");
            onCommandMode = true;
            break;
            
        default:
            break;
        }

    }

    return;
}