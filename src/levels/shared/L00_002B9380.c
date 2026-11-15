#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;
typedef unsigned int u32;
typedef int TI_F41eb487e __attribute__((mode(TI)));
extern char D_00189E20_5[];
extern void func_L00_002B91C0(void);
extern void func_L00_002B3DC0(float, float, float);
extern float func_002AA898(float *position, float target, float *velocity,
                          float acceleration, float damping, float limit, int direction);
/* Eases the hero's lean back toward upright in most states, or runs the full lean update in modes 1 and 2. */
void func_L00_002B9380(void)
{
    char *base = (char *)&D_00189E20_5;
    TI_F41eb487e v;
    int mode;
    int x;

    mode = *(u8 *)(base + 0x22C3);
    if (*(short *)(base + 0x218) != 0)
        mode = 1;

    if (mode == 0) {
        x = *(int *)(base + 0x2294);
        if ((u32)(x - 0x24) < 2)
            return;
        if (*(int *)(base + 0x229C) == 0x11 || *(int *)(base + 0x229C) == 0x15 ||
            *(int *)(base + 0x229C) == 0x16 || *(int *)(base + 0x229C) == 0x1F)
            return;
        if (x == 0x74 || x == 0x30 || x == 0x2C || x == 0x2B)
            return;
        v = *(TI_F41eb487e *)(base + 0x90);
        ApproachWithVelocity((float *)&v, 0.0f, (float *)(base + 0xA0), 0.015f, 0.3f, 0.087266475f, 0);
        ApproachWithVelocity((float *)&v + 1, 0.0f, (float *)(base + 0xA4), 0.015f, 0.3f, 0.087266475f, 0);
        RotateHeroMatrix(*(float *)(base + 0xA0), *(float *)(base + 0xA4), 0.0f);
        return;
    }
    if (mode < 0)
        return;
    if (mode >= 3)
        return;
    UpdateHeroLeanReference();
}
