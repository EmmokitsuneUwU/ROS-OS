#include <stdint.h>
#include "keyboardUtils.hpp"
#include "Colors.hpp"
#include "VGA.hpp"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

unsigned int vidMemory;
int characters;

char commandsBuffer[32];
int commandsBufferIndex = 0;

bool onCommandMode = false;
bool onGraphicsMode = false;

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

extern "C" void charPrint(int chr,uint8_t color = 0x0F)
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

extern "C" void strPrint(const char str[], uint8_t color = 0x0F)
{
    int i = 0;
    while(str[i] != '\0')
    {
        charPrint(str[i],color);
        i += 1;
    }
}

// BASIC DECLARATIONS

// NORMAL DECLARATIONS

extern "C" void printROSLogo()
{
    //Print ROS in ASCII art
    strPrint("\xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB \n",colorBrown);
    strPrint("\xDB    \xDB  \xDB   \xDB  \xDB \n",colorBrown);
    strPrint("\xDB\xDB\xDB\xDB\xDB\xDB  \xDB   \xDB  \xDB\xDB\xDB\xDB\xDB \n",colorBrown);
    strPrint("\xDB   \xDB   \xDB   \xDB      \xDB \n",colorBrown);
    strPrint("\xDB   \xDB   \xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB \n\n",colorBrown);
    strPrint(" \xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF\xDF \n\n",colorBrown);
}

// NORMAL DECLARATIONS

extern "C" void main() {
    vidMemory = 0xb8000;
    characters = 0;

    printROSLogo();

    strPrint("Welcome to the");
    strPrint(" ROS OS \n\n",colorRed);

    strPrint("Press '");
    charPrint('C',colorRed);
    strPrint("' to enter command mode | Press '");
    charPrint('S',colorRed);
    strPrint("' to shutdown | Press '");
    charPrint('G',colorRed);
    strPrint("' to enter graphics mode \n");

    bool bgdraw = false;

    while(1)
    {
        uint8_t scancode = read_key_polling();
        
        if(!onCommandMode && !onGraphicsMode)
        {
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
            case 0x22:
                onGraphicsMode = true;
                VGAMODEGRAPHICS();
                clear_screen(0x01);
                break;

            default:
                break;
            }
        }
        else if (onCommandMode)
        {
            /* code */
        }
        else if (onGraphicsMode)
        {
            /* code */
        }

    }

    return;
}
