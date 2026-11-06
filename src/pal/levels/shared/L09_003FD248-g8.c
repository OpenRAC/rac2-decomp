#include "common.h"

/* func_PAL_L09_003FD248, the PAL copy of func_L09_003F8898: the same C, where the spawn counters
   are scaled to 50 Hz. */
extern int D_L09_001B0F50 __attribute__((sda));
extern int D_L09_001B0F54 __attribute__((sda));
extern int D_L09_001B0F58 __attribute__((sda));
extern int D_L09_001B0F4C __attribute__((sda));

extern int func_002A7820(int a0, int a1);
extern int func_00282978(char *a0);
extern void func_002B0990(int a0, void *a1, int a2, int a3, f32 f12);

/* Re-arms the frame's four spawn slots, bumps the object's counter and re-runs the stage. */
void func_PAL_L09_003FD248(char *object) {
    char *frame = *(char **)(object + 0x68);

    if (*(unsigned char *)(frame + 0x2EA) != 0) {
        *(unsigned char *)(frame + 0x2EA) = 0;
        if (*(short *)(frame + 0x2E0) < ((s32)(D_L09_001B0F50) * 5 + 2) / 6)
            *(short *)(frame + 0x2E0) =
                ((s32)(func_002A7820(D_L09_001B0F54, D_L09_001B0F58)) * 5 + 2) / 6;
    }
    if (func_00282978(frame + 0x2E0) == 0)
        *(unsigned short *)(frame + 0x2E8) = ((s32)(D_L09_001B0F4C) * 5 + 2) / 6;
    func_00282978(frame + 0x2E2);
    func_00282978(frame + 0x2E6);
    func_00282978(frame + 0x2E8);
    if (*(unsigned short *)(object + 0x96) <= 0xFFFE)
        *(unsigned short *)(object + 0x96) = *(unsigned short *)(object + 0x96) + 1;
    func_002B0990(*(int *)(frame + 0x2F8), frame + 0x430, 4, 1, 1.9f);
}
