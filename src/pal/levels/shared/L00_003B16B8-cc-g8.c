/* func_PAL_L00_003B16B8, the PAL copy of func_L00_003ADEA0: the same C, where rename func_L00_003ADCD8 becomes func_PAL_L00_003B14C8; rename func_002A7470 becomes func_PAL_002A7E68; lit 7 becomes 6; swap locals i n. */
#include "common.h"

/* Small-data sibling of L00_003A8E28.c: the body below reaches the level's
   globals through $gp (the file gets -G8 by its name, see config/cflags.txt). */

/* Builds the local vector {scale, 0, 0, 1}, transforms its copy, then adds the object position. */
/* Resets the two slot cursors, then releases the 256-entry slot table. */
extern int D_L00_001B19C8 MACRO_ADDR;
/* One 28-byte entry of the slot table (layout as in L00_003B0CE8-g8.c): used holds the frame it was taken. */
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
/* Releases slot-table entries taken 480 or more frames ago, steps the moby's state 0, 1, 2, and in
   state 2 spawns a particle at the hero when the hero's button word has a bit of D_00138320 set
   (recording it in a new slot when func_L00_003B0DA0 gives one); then hands both slot cursors to
   ref_L00_003B1270_0. */
/* Moby index list: entry 0 is the count, entries 1..count index the 256-byte moby array. */
extern short ref_L00_003ADEA0_0[];
/* Base of the moby array. */
extern char *ref_L00_003ADEA0_1 MACRO_ADDR;
/* Frame counter: an absolute macro load in ordinary flow, a $gp load in a delay slot. */
extern int ref_L00_003ADEA0_2 MACRO_ADDR;
/* Per-row links drawn by func_L00_003ADA30: up to eight mobys and a null terminator. */
extern char *ref_L00_003ADEA0_3[10][9];
typedef struct { char pad[0x18]; char *hit; int count; float point[4]; } CollisionADEA0;
extern CollisionADEA0 ref_L00_003ADEA0_4;
extern void func_00282A28(void);
extern float func_00282E48(void *, void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern void func_PAL_L00_003B14C8(void *, void *);
extern void func_PAL_002A7E68(void *, int, int, int);
extern int func_002E5CF8(int, int, void *);
extern void func_L00_002E6CF0(void *, void *);
extern void func_L00_003ADA30(char *);

/* Once per frame, links each listed active moby to every other active moby of class 0x81F within
   12 units and in line of sight (up to eight, in the moby's row of ref_L00_003ADEA0_3), registers
   func_L00_003ADA30 to draw the links, and when a flagged moby of another class (not the hero's)
   blocks a link, marks whichever end of it is nearer to that moby and records the blocker. */
void func_PAL_L00_003B16B8(void)
{
    int n, j, i, row;
    char *moby, *other, *vars, *hit;

    for (i = 1; i <= ref_L00_003ADEA0_0[0]; i++) {
        moby = ref_L00_003ADEA0_1 + (ref_L00_003ADEA0_0[i] << 8);
        {
            char *first = *(char **)(moby + 0x68);

            if (*(int *)(first + 0x7C) == ref_L00_003ADEA0_2)
                return;
            *(int *)(first + 0x7C) = ref_L00_003ADEA0_2;
            *(short *)(first + 0x4A) = i - 1;
        }
        if (i >= 11)
            func_00282A28();
        row = i - 1;
        if (*(unsigned char *)(moby + 0x20) != 6)
            continue;
        n = 0;
        for (j = 1; j <= ref_L00_003ADEA0_0[0]; j++) {
            other = ref_L00_003ADEA0_1 + (ref_L00_003ADEA0_0[j] << 8);
            if (*(unsigned char *)(other + 0x20) != 6 || other == moby || *(short *)(other + 0xAA) != 0x81F)
                continue;
            if (!(func_00282E48(moby + 0x10, other + 0x10) < 12.0f))
                continue;
            if (*(int *)(*(char **)(other + 0x68) + 0x7C) == ref_L00_003ADEA0_2)
                continue;
            if (func_002761F8(other + 0x10, moby + 0x10, 2, 0, 0))
                continue;
            func_PAL_L00_003B14C8(moby, other);
            if (n >= 8)
                func_00282A28();
            ref_L00_003ADEA0_3[row][n++] = other;
            ref_L00_003ADEA0_3[row][n] = 0;
            if (!func_002761F8(moby + 0x10, other + 0x10, 0, moby, 0))
                continue;
            hit = ref_L00_003ADEA0_4.hit;
            if (!hit || *(short *)(hit + 0xAA) == *(short *)(moby + 0xAA) || hit == D_00189E20.moby
                || !(*(unsigned short *)(hit + 0x34) & 0x1000))
                continue;
            if (func_00282E48(hit + 0x10, moby + 0x10) < func_00282E48(hit + 0x10, other + 0x10))
                other = moby;
            *(unsigned char *)(other + 0x20) |= 8;
            vars = *(char **)(other + 0x68);
            func_PAL_002A7E68(other, 1, 0, 2);
            func_002E5CF8(0, 0, other);
            *(char **)(vars + 0x54) = hit;
            *(int *)(vars + 0x58) = 500;
            *(short *)(vars + 0x52) = 1;
            *(short *)(vars + 0x48) = 6;
            *(int *)(vars + 0x40) = 0;
        }
        if (n)
            func_L00_002E6CF0(func_L00_003ADA30, moby);
    }
}
