#include "include_asm.h"

typedef unsigned char u8;
extern void *func_003361A8(void *);
extern char *func_00336968(char *);
extern void *func_003363D0(void *);
extern void *func_003366D0(void *);
extern void *func_003361A8(void *);
extern char *func_00336968(char *);
extern void *func_003363D0(void *);
extern void *func_003366D0(void *);

u8 *func_PAL_00342D98(u8 *self)
{
    func_003361A8(self);
    func_003361A8(self + 76);
    func_00336968((char *)self + 152);
    func_003361A8(self + 240);
    func_003363D0(self + 316);
    func_003366D0(self + 388);
    return self;
}


typedef struct {
    char reserved00[6];
    short value;
    char reserved08[2];
} MenuEntry;
extern MenuEntry D_001FCE0[];
extern int func_002E5E58(int, unsigned int, void *);
extern void *func_00115484(void *, int, unsigned int);
extern void func_00335E38(void *, float, float, float, float);

/* func_00340D68 is in 0033F030-grid-g8.c. */

/* Moves the selection of a menu grid and keeps the selected entry's value at
   0x214: the buttons 0x1000 and 0x4000 step the row (0x208, wrapping at the row
   count at 0x210), 0x8000 and 0x2000 the column (0x204, wrapping at 0x20C). A
   step down is stored, read back and stored again after the wrap test. */
int func_PAL_003430B0(char *self, unsigned int buttons, MenuEntry *table)
{
    float offset[2];
    func_00115484(offset, 0, 8);
    if (table) {
        float *position;
        *(int *)(self + 0x224) = 0;
        position = *(float **)(self + 0x1C0);
        func_00335E38(self, offset[0] + position[0], offset[1] + position[1], 0.0f, 0.0f);
        if (buttons & 0x1000) {
            int n;
            func_002E5E58(3, 0, 0);
            *(int *)(self + 0x218) -= 1;
            n = *(int *)(self + 0x218);
            if (n < 0) n = *(int *)(self + 0x220) - 1;
            *(int *)(self + 0x218) = n;
        } else if (buttons & 0x4000) {
            int n;
            func_002E5E58(3, 0, 0);
            n = *(int *)(self + 0x218) + 1;
            *(int *)(self + 0x218) = n < *(int *)(self + 0x220) ? n : 0;
        } else if (buttons & 0x8000) {
            int n;
            func_002E5E58(3, 0, 0);
            *(int *)(self + 0x214) -= 1;
            n = *(int *)(self + 0x214);
            if (n < 0) n = *(int *)(self + 0x21C) - 1;
            *(int *)(self + 0x214) = n;
        } else if (buttons & 0x2000) {
            int n;
            func_002E5E58(3, 0, 0);
            n = *(int *)(self + 0x214) + 1;
            *(int *)(self + 0x214) = n < *(int *)(self + 0x21C) ? n : 0;
        }
        *(int *)(self + 0x224) = table[*(int *)(self + 0x214) + *(int *)(self + 0x218) * *(int *)(self + 0x21C)].value;
    }
    return 0;
}


INCLUDE_ASM("asm/pal/game", func_PAL_00343230);

extern void func_L00_0042BAD0_6(u8 *);
extern void func_L00_0042BFF8_5(u8 *);
extern void func_L00_0042C290_6(u8 *);
extern void func_00347EA0_1(u8 *);

/* initialises eight in-place sub-records of one object by four routines, then returns the object pointer */
u8 *func_PAL_00343240(u8 *a0) {
    func_L00_0042BAD0_6(a0);
    func_L00_0042BAD0_6(a0 + 76);
    func_L00_0042BAD0_6(a0 + 152);
    func_L00_0042BAD0_6(a0 + 228);
    func_L00_0042BAD0_6(a0 + 304);
    func_L00_0042BFF8_5(a0 + 380);
    func_L00_0042C290_6(a0 + 464);
    func_00347EA0_1(a0 + 568);
    return a0;
}

typedef int s32;

/* stores three consecutive words; byte-identical across all 27 levels. */
void func_PAL_003435C0(u8 *a0, s32 a1, s32 a2, s32 a3) { *(s32 *)(a0 + 0x310) = a1; *(s32 *)(a0 + 0x314) = a2; *(s32 *)(a0 + 0x318) = a3; }

/* Measured target: byte-identical across all 27 levels. */
void func_PAL_003435D0(u8 *a0, s32 a1) { *(s32 *)(a0 + 0x230) = a1; }

