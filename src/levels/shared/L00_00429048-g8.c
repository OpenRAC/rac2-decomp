#include "common.h"

extern char *D_L00_001B8E10[];
extern char *D_L00_001B1844 __attribute__((sda));
extern float D_L00_001B18E0 MACRO_ADDR;

/* Tells whether the camera trigger at this index is ready. Returns 1 when it is, otherwise it checks a camera state value. */
int func_L00_00429048(int index)
{
    char *camState;

    if (*(short *)(gFollowCameraObject[0] + 0x86) != 0x13)
        return 1;
    camState = (char *)(*(int *)(*(int *)(*(char **)(D_L00_001B1844 + index * 32 + 0x1C) + 4) + 0x70) + 0x40);
    if (*(short *)(camState + 0x14) == 1 && D_L00_001B18E0 != 0.0f)
        return 1;
    return *(short *)(camState + 0x14) == 3;
}
