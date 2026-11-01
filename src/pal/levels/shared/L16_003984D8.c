#include "include_asm.h"


#include "common.h"
typedef struct {
    char pad[0xc28];
    int flags;
    char pad2[0x2290 - 0xc2c];
    char *current;
} ResidentState;
extern ResidentState D_00189E20;
extern void func_PAL_L00_002D2668(int, int, float);

void func_PAL_L16_00398AE0(char *object)
{
    char *state = *(char **)(object + 0x68);
    if ((D_00189E20.flags & 2) && *(unsigned char *)(D_00189E20.current + 0x43) == 0x44)
        func_PAL_L00_002D2668(0x3f, 0, 6.0f);
    else if (*(unsigned char *)(D_00189E20.current + 0x43) == 0x3f && *(float *)(state + 0x30) != 0.0f)
        func_PAL_L00_002D2668(0x40, 0, 8.0f);
    else if (*(unsigned char *)(D_00189E20.current + 0x43) == 0x40) {
        if (*(float *)(state + 0x30) > 0.060000002f)
            func_PAL_L00_002D2668(0x41, 0, 8.0f);
        else if (*(float *)(state + 0x30) == 0.0f)
            func_PAL_L00_002D2668(0x3f, 0, 8.0f);
        else
            goto finalTest;
    } else {
finalTest:
        /* This path tests the current state again after the float checks. */
        if (*(unsigned char *)(D_00189E20.current + 0x43) == 0x41 && *(float *)(state + 0x30) < 0.060000002f)
            func_PAL_L00_002D2668(0x40, 0, 8.0f);
    }
}



