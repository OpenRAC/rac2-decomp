#include "include_asm.h"
#include "names.h"

extern unsigned char D_L05_001B2000;
extern unsigned char D_L05_001B2001;
extern unsigned char D_L05_001B2002;
extern float D_L05_001B2004 __attribute__((sda));
extern float D_L05_001B2008 __attribute__((sda));
extern float D_L05_001B200C __attribute__((sda));
extern float D_L05_001B2010 __attribute__((sda));
extern int D_L05_001B2014 __attribute__((sda));
extern unsigned char D_L05_001B3630;
extern unsigned char D_L05_001B3631;
extern unsigned char D_L05_001B3632;
extern float D_L05_001B3634 __attribute__((sda));
extern float D_L05_001B3638 __attribute__((sda));
extern float D_L05_001B363C __attribute__((sda));
extern float D_L05_001B3640 __attribute__((sda));
extern int D_L05_001B3644;

/* The reverse copy of func_L05_00442720. */
/* Puts the ship's saved settings back as the current settings. */
void ship_restore_settings(void)
{
    unsigned int byte0 = D_L05_001B3630;
    unsigned int byte1 = D_L05_001B3631;
    unsigned int byte2 = D_L05_001B3632;
    float float0 = D_L05_001B3638;
    float float1 = D_L05_001B3640;
    float float2 = D_L05_001B3634;
    float float3 = D_L05_001B363C;
    unsigned int word = D_L05_001B3644;

    D_L05_001B2000 = byte0;
    D_L05_001B2001 = byte1;
    D_L05_001B2002 = byte2;
    D_L05_001B2008 = float0;
    D_L05_001B2010 = float1;
    D_L05_001B2004 = float2;
    D_L05_001B200C = float3;
    D_L05_001B2014 = word;
}
