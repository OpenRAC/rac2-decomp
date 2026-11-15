#include "include_asm.h"
#include "names.h"


extern int D_L01_001A90C8 __attribute__((sda));
extern float D_L01_001A90C4 __attribute__((sda));
extern int D_L01_001A90CC __attribute__((sda));
extern int D_L01_001A90D0 __attribute__((sda));
extern int func_L01_002F1888(void);
extern int func_L01_002F1588(void);
extern int func_0029B7C0(int (*)(void),int (*)(void),int);

/* Starts the HUD overlay: stores the icon and a fade amount limited to 0 to 1, and registers the overlay update if it is not running. */
void func_L01_002F14E8(int iconId, int resultCode, float fade)
{
    if (D_L01_001A90C8 == 0)
        SetLevelObjectTableEntry(TickTimerAndGetStoredValue, DrawHudOverlay, 0);
    D_L01_001A90C8 = 5;
    D_L01_001A90C4 = fade;
    if (fade > 1.0f)
        D_L01_001A90C4 = 1.0f;
    else if (fade < 0.0f)
        D_L01_001A90C4 = 0.0f;
    D_L01_001A90D0 = resultCode;
    D_L01_001A90CC = iconId;
}
