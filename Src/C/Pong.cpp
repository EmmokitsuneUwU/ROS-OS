#include "Pong.hpp"
#include "VGA.hpp"
#include "Colors.hpp"

int disX = 1;

void pongInit()
{
    onGraphicsMode = true;
    VGAMODEGRAPHICS();
    GRAPHICSMODEClearScreen(0x01);
}
void pongUpdate()
{
    for (int y = 0; y < 6 ; y++) {
        for (int i = 0; i < 50; i++) {
            GRAPHICSMODEDrawPixel(i += disX, y + 9, 0x04);
        }
        
    }
}

void pongExit()
{

}

