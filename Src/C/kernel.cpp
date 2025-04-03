#include <stdint.h>
#include "keyboardUtils.hpp"
#include "Colors.hpp"
#include "VGA.hpp"
#include "Util.hpp"
#include "Pong.hpp"
#include "Math.hpp"

#define MAX_ARGS 5

char commandsBuffer[75];
int commandsBufferIndex = 0;
bool isKeyPressed[256] = {false};

extern "C" void main() {
    printROSLogo();

    strPrint("Welcome to the", colorBrightWhite);
    strPrint(" ROS OS \n\n", colorRed);

    strPrint("Press '", colorBrightWhite);
    charPrint('C', colorRed);
    strPrint("' to enter command mode '", colorBrightWhite);
    charPrint('G', colorRed);
    strPrint("' to enter graphics mode \n", colorBrightWhite);

    while (1) {
        uint8_t scancode = read_key_polling();

        if (scancode != 0) {
            bool isPressed = (scancode & 0x80) == 0;

            if (isPressed && !isKeyPressed[scancode]) {
                isKeyPressed[scancode] = true;

                if (!onCommandMode && !onGraphicsMode) {
                    switch (scancode) {
                        case 0x2E:
                            clearScreen();
                            strPrint("Welcome to command mode \n", colorBrightWhite);
                            strPrint("Type 'exit' to quit \n", colorBrightWhite);
                            strPrint(">", colorRed);
                            onCommandMode = true;
                            break;
                        case 0x22:
                            VGAMODEGRAPHICS();
                            GRAPHICSMODEClearScreen(0x01);
                            for (int y = 0; y < 6; y++) {
                                for (int i = 0; i < 50; i++) {
                                    GRAPHICSMODEDrawPixel(i, y, 0x04);
                                }
                            }
                            onGraphicsMode = true;
                            GRAPHICSMODEDrawPixel(0, 0, 0x03);
                            break;
                        default:
                            break;
                    }
                } 
                else if (onCommandMode)
                {
                    // Enter commands.
                    char c = scancodeToIntChar(scancode);
                    if (c != '?' && commandsBufferIndex < 74)
                    {
                        commandsBuffer[commandsBufferIndex++] = c;
                        charPrint(c, colorBrightWhite);
                    }

                    // If enter key is pressed, process the command.
                    else if (scancode == 0x1C) 
                    {
                        charPrint('\n', colorBrightWhite);
                        commandsBuffer[commandsBufferIndex] = '\0';

                        char *args[MAX_ARGS];
                        int argc = 0;
                        parse_command(commandsBuffer, args, &argc);

                        // arg 0 is the command itself.
                        if (argc > 0) 
                        {
                            if (StrCmp(args[0], "EXIT")) 
                            {
                                strPrint("OK\n", colorBrightGreen);
                                onCommandMode = false;
                                clearScreen();
                                printROSLogo();

                                strPrint("Welcome to the", colorBrightWhite);
                                strPrint(" ROS OS \n\n", colorRed);
                            
                                strPrint("Press '", colorBrightWhite);
                                charPrint('C', colorRed);
                                strPrint("' to enter command mode '", colorBrightWhite);
                                charPrint('G', colorRed);
                                strPrint("' to enter graphics mode \n", colorBrightWhite);
                            }
                            else if (StrCmp(args[0], "TEST") && argc > 1)
                            {
                                if(StrCmp(args[1], "DIGITCOUNT"))
                                {
                                    charPrint(intToChar(digitCount(1234)), colorBrightWhite);
                                    strPrint("\n", colorBrightWhite);
                                }
                                if(StrCmp(args[1], "MDP"))
                                {
                                    int num = 12345;
                                    int digitcount = digitCount(num);
                                    int arr[digitcount];
                                    int size;
                                    
                                    intToArray(num, arr, &size);

                                    for(int i = 0; i < digitcount; i++)
                                    {
                                        charPrint(intToChar(arr[i]), colorBrightWhite);
                                    }
                                }
                            }
                            else if (StrCmp(args[0], "CLEAR")) 
                            {
                                strPrint("OK\n", colorBrightGreen);
                                clearScreen();
                            } 
                            else if (StrCmp(args[0], "KERNEL"))
                            {
                                strPrint("OK\n", colorBrightGreen);
                                strPrint("Running ROS Kernel version: ", colorBrightWhite);
                                strPrint(kernelVersion, colorRed);
                                strPrint("\n", colorBrightWhite);
                            } 
                            else if (StrCmp(args[0], "PONG"))
                            {
                                strPrint("OK\n", colorBrightGreen);
                                pongInit();
                                while (1) {
                                    pongUpdate();
                                }
                            }
                            else if(StrCmp(args[0], "SHUTDOWN"))
                            {
                                strPrint("OK\n", colorBrightGreen);
                                shutdownAPM();
                            }
                            else if (StrCmp(args[0], "ECHO") && argc > 1) 
                            {
                                strPrint("OK\n", colorBrightGreen);
                                for (int i = 1; i < argc; i++)
                                {
                                    strPrint(args[i], colorBrightWhite);
                                    strPrint(" ", colorBrightWhite);
                                }
                                strPrint("\n", colorBrightWhite);
                            }
                            else if (StrCmp(args[0], "HOW") && argc > 1 )
                            {
                                strPrint("OK\n", colorBrightGreen);
                                if(StrCmp(args[1],"SUM"))
                                {
                                    strPrint("SUM ARG1 ARG2 \n",colorBrightWhite);
                                    strPrint("SUM 3 3 \n",colorBrightWhite);
                                }
                                if(StrCmp(args[1],"ECHO"))
                                {
                                    strPrint("ECHO ARG1 ARG2 ... \n",colorBrightWhite);
                                    strPrint("ECHO HELLO COMPUTER \n",colorBrightWhite);
                                }
                            }
                            else if (StrCmp(args[0], "SUM") && argc > 2)
                            {
                                strPrint("OK\n", colorBrightGreen);
                            	char* chs = args[1];
                            	char* chs2 = args[2];
                            	int op;
                            	
                                op = intCharToInt(chs[0]) + intCharToInt(chs2[0]);
                                charPrint(intToChar(op),colorBrightWhite);
                                strPrint("\n", colorBrightWhite);
                            }
                            else
                            {
                                strPrint("ERROR\n", colorRed);
                            }
                        }

                        commandsBufferIndex = 0;
                        commandsBuffer[0] = '\0';

                        if (onCommandMode) {
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
}
