#include <stdint.h>
#include "keyboardUtils.hpp"
#include "Colors.hpp"
#include "VGA.hpp"
#include "Util.hpp"

char commandsBuffer[32];
int commandsBufferIndex = 0;

bool onCommandMode = false;
bool onGraphicsMode = false;

bool isKeyPressed[256] = {false};

extern "C" void main() {
    printROSLogo();

    strPrint("Welcome to the", colorBrightWhite);
    strPrint(" ROS OS \n\n", colorRed);

    strPrint("Press '", colorBrightWhite);
    charPrint('C', colorRed);
    strPrint("' to enter command mode | Press '", colorBrightWhite);
    charPrint('S', colorRed);
    strPrint("' to shutdown | Press '", colorBrightWhite);
    charPrint('G', colorRed);
    strPrint("' to enter graphics mode \n", colorBrightWhite);

    bool bgdraw = false;

    while (1) {
        uint8_t scancode = read_key_polling();

        if (scancode != 0) {
            bool isPressed = (scancode & 0x80) == 0;

            if (isPressed && !isKeyPressed[scancode]) {
                isKeyPressed[scancode] = true;

                if (!onCommandMode && !onGraphicsMode) {
                    switch (scancode) {
                        case 0x01:
                            clearScreen();
                            break;
                        case 0x9F:
                            shutdownAPM();
                            break;
                        case 0x2E:
                            clearScreen();
                            strPrint("Welcome to command mode \n", colorBrightWhite);
                            strPrint("Type 'exit' to quit \n", colorBrightWhite);
                            strPrint("Enjoy! \n", colorBrightWhite);
                            strPrint(">", colorRed);
                            onCommandMode = true;
                            break;
                        case 0x22:
                            VGAMODEGRAPHICS();
                            GRAPHICSMODEClearScreen(0x01);
                            for (int y = 0; y < 6; y++) {
                                for (int i = 0; i < 50; i++) {
                                    GRAPHICSMODEDrawPixel(i + 120, y + 10, 0x04);
                                }
                            }
                            onGraphicsMode = true;
                            break;

                        default:
                            break;
                    }
                } else if (onCommandMode) {

                    char c = scancodeToIntChar(scancode);
                    if (c != '?' && commandsBufferIndex < 32)
                    {
                        commandsBuffer[commandsBufferIndex++] = c;
                        charPrint(c, colorBrightWhite);
                    }
                    else if (scancode == 0x1C)
                    {
                        clearScreen();
                        strPrint("OK \n", colorBrightWhite);

                        if(StrCmp(commandsBuffer, "EXIT"))
                        {
                            onCommandMode = false;
                            clearScreen();
                            printROSLogo();

                            strPrint("Exiting command mode \n", colorBrightWhite);

                            strPrint("Welcome to the", colorBrightWhite);
                            strPrint(" ROS OS \n\n", colorRed);
                        
                            strPrint("Press '", colorBrightWhite);
                            charPrint('C', colorRed);
                            strPrint("' to enter command mode | Press '", colorBrightWhite);
                            charPrint('S', colorRed);
                            strPrint("' to shutdown | Press '", colorBrightWhite);
                            charPrint('G', colorRed);
                            strPrint("' to enter graphics mode \n", colorBrightWhite);
                        }
                        
                        // Clean command buffer
                        for(int i = 0; i < 32; i++)
                        {
                            commandsBuffer[i] = '\0';
                        }
                        commandsBufferIndex = 0;

                        if(onCommandMode)
                        {
                            strPrint(">", colorRed);
                        }
                    }
                    
                }
            }
        }

        if (scancode != 0 && (scancode & 0x80)) {
            isKeyPressed[scancode & 0x7F] = false;
        }
    }

    return;
}
