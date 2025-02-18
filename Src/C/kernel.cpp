#include <stdint.h>
#include "keyboardUtils.hpp"
#include "Colors.hpp"
#include "VGA.hpp"
#include "Util.hpp"

char commandsBuffer[32];
int commandsBufferIndex = 0;

bool onCommandMode = false;
bool onGraphicsMode = false;

extern "C" void main() {
    printROSLogo();

    strPrint("Welcome to the",0x0F);
    strPrint(" ROS OS \n\n",colorRed);

    strPrint("Press '",0x0F);
    charPrint('C',colorRed);
    strPrint("' to enter command mode | Press '",0x0F);
    charPrint('S',colorRed);
    strPrint("' to shutdown | Press '",0x0F);
    charPrint('G',colorRed);
    strPrint("' to enter graphics mode \n",0x0F);

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
                strPrint("Welcome to command mode \n",0x0F);
                strPrint("Type 'exit' to quit \n",0x0F);
                strPrint("Enjoy! \n",0x0F);
                onCommandMode = true;
                break;
            case 0x22:
                VGAMODEGRAPHICS();
                GRAPHICSMODEClearScreen(0x01);
                for(int y = 0; y < 6; y++)
                {
                    for(int i = 0; i < 50; i++)
                    {
                        GRAPHICSMODEDrawPixel(i +120, y+10, 0x04);
                    }
                }
                onGraphicsMode = true;
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

        }

    }

    return;
}
