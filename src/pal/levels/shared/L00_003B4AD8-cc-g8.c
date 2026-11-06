/* func_PAL_L00_003B4AD8, the PAL copy of func_L00_003B1270: the same C, where the 480-frame slot age
   becomes 400, D_L00_001AF82C and D_L00_001AF830 are read as ints, and both spawn values take the
   50 Hz scale. */
#include "common.h"

extern unsigned char D_L00_001AF810 __attribute__((sda));

extern unsigned char D_L00_001AF811 __attribute__((sda));

extern char D_L00_0023BB78[];

extern int D_L00_001AF82C __attribute__((sda));
extern int D_L00_001AF830 __attribute__((sda));
extern int D_L00_001B19C8 MACRO_ADDR;
/* One 28-byte entry of the slot table (layout as in L00_003B0CE8-g8.c): used holds the frame it was taken. */
typedef struct { unsigned char pad0[0xC]; int used; unsigned char pad10[4]; unsigned char id[8]; } SlotEntry1270;
/* The hero record: its position at 0x80, the pad buttons word at 0x1230 and the hero moby at 0x2290. */
typedef struct {
    char pad0[0x80];
    float position[4];
    char pad90[0x11A0];
    int buttons;
    char pad1234[0x105C];
    char *moby;
} HeroL00;
extern HeroL00 D_00189E20;
extern int D_00138320 NOT_SDA;
extern float D_L00_001AF838[4];
extern float D_L00_001AF848[4];
extern void func_L00_003B0CE8(int);
extern char *func_L00_003B0DA0(void *);
extern int func_001163B0(void);
extern int func_002C56B0(void *,int,int,int,int,int,void *,float,float);
extern void ref_L00_003B1270_0(int,int,int,void *,int);

/* Releases slot-table entries taken 400 or more frames ago, steps the moby's state 0, 1, 2, and in
   state 2 spawns a particle at the hero when the hero's button word has a bit of D_00138320 set
   (recording it in a new slot when func_L00_003B0DA0 gives one); then hands both slot cursors to
   ref_L00_003B1270_0. */
void func_PAL_L00_003B4AD8(char *m)
{
    int stop = 0, result;
    short random;
    short random2;
    unsigned char slot;
    char *entry;

    while (!stop && D_L00_001AF811 != D_L00_001AF810) {
        if (D_L00_001B19C8 - ((SlotEntry1270 *)D_L00_0023BB78)[D_L00_001AF811].used < 400)
            stop = 1;
        else
            func_L00_003B0CE8(D_L00_001AF811);
    }
    switch ((unsigned char)m[0x20]) {
    case 0:
        m[0x20] = 1;
        break;
    case 1:
        m[0x20] = 2;
        break;
    case 2:
        if (D_00138320 & D_00189E20.buttons) {
            entry = func_L00_003B0DA0(D_00189E20.position);
            if (entry) {
                slot = D_L00_001AF810 - 1;
                random = ((s32)(D_L00_001AF82C + (func_001163B0() & 7)) * 5 + 2) / 6;
                result = func_002C56B0(D_00189E20.position, slot, 0, random, 1, (unsigned char)(((s32)(D_L00_001AF830 + (func_001163B0() & 3)) * 5 + 2) / 6), m, 1, 1);
                *(int *)(entry + 0x10) = result;
            } else {
                random2 = ((s32)(D_L00_001AF82C + (func_001163B0() & 7)) * 5 + 2) / 6;
                func_002C56B0(D_00189E20.position, 0, 1, random2, 1, (unsigned char)(((s32)(D_L00_001AF830 + (func_001163B0() & 3)) * 5 + 2) / 6), m, 1, 1);
            }
        }
        break;
    }
    ref_L00_003B1270_0(0x41, 0x41, 0x80000000, D_L00_001AF838, D_L00_001AF810);
    ref_L00_003B1270_0(0x40, 0x40, 0x80F0F0F0, D_L00_001AF838, D_L00_001AF810);
    ref_L00_003B1270_0(0x41, 0x51, 0x80000000, D_L00_001AF848, D_L00_001AF811);
    ref_L00_003B1270_0(0x40, 0x50, 0x80F0F0F0, D_L00_001AF848, D_L00_001AF811);
}
