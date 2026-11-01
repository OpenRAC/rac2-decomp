/* func_L01_002B5EA0: near miss, 1052/1048 bytes, 0 of 3 places (USA v1.01, 31 October 2026).

   Profile: its own unit, `-O2 -G0 -ffunction-sections -frac2-qcopy` (with -fno-gcse: 1036 bytes).

   The branches, calls, constants and the clamp tail follow retail. The collision loop does not:
   - retail keeps the contact vector's address (D_L01_001BF930) and the constant 1 in $s4/$fp
     across the loop and forms every other address inside it, including `hero + 0x80` once per
     pass (reorg copies it into both branch delay slots); here loop.c/gcse hoist the hero
     position (D_00189EA0) instead and fold the contact address back into the loop.
   - retail reads the contact's word at +0x18 with `lui; addiu; lw 0x18`, an address formed
     whole; `sda` on a char array or struct gives `lui; lw` with the offset folded.
   - the register roles before the loop are permuted (hero $s0 against $s1 here, the step
     vector $s6 against $s5, the steep flag $s7 against $s6).
   Tried: a contact pointer, struct views of the 0x1BF900 record (sda and not), the hero as
   D_00189E20 + 0x80 or the D_00189EA0 symbol, -fno-gcse and -frac2-gcse-unsplit-edges. */

#include "common.h"

/* A -frac2-qcopy unit: the position and contact vectors are copied with lq/sq pairs. */

typedef int Quad __attribute__((mode(TI)));

extern u8 D_00189E20[];
extern u8 D_00189EA0[];
extern char D_0018A050[];
extern char D_0018A060[];
extern int D_L01_001A9030 MACRO_ADDR;
typedef struct { char pad[0x18]; int hit; } Contact;
extern Contact D_L01_001BF900 __attribute__((sda));
extern char D_L01_001BF920[];
extern char D_L01_001BF930[];
extern char D_L01_001BF940[];

extern void func_00282C88(void *);
extern void func_L00_002D49F0(void);
extern float func_00282DB0(void *, void *);
extern void func_L00_002D38A0(void *, void *, float);
extern void func_L00_002D36E0(void *, int, float, float, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern int func_00277258(void *, int, int, float);
extern int func_L00_002E0200(float, void *, int, int, float);
extern int func_00278870(void *, float);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);

/* Moves the hero by this frame's step and resolves it against the collision up to eight
   times, taking each contact's position, normal and point. Returns 1 when the hero did not
   move much further than its radius, else -1; for mode 0xF the excess is clamped to 512 a
   side and put back along the step. */
int func_L01_002B5EA0(int mode)
{
    float old[4];
    float step[4];
    float moved[4];
    u8 *hero = D_00189E20;
    u8 *pos;
    char *contact;
    int steep;
    int hit;
    int i;
    float d;

    if (*(short *)(hero + 0x1F0) != 0)
        return 1;
    *(Quad *)old = *(Quad *)(hero + 0x80);
    func_00282C88(step);
    if (*(short *)(hero + 0x24FE) != 0) {
        func_L00_002D49F0();
        *(short *)(hero + 0x24FE) = 0;
    }
    steep = 0;
    if (func_00282DB0(hero + 0x20, hero + 0x2C0) > -0.92f)
        steep = 1;
    if (*(int *)(hero + 0x229C) != 0x11) {
        if (hero[0x22C3] != 0 || *(short *)(hero + 0x218) != 0 || steep) {
            if (D_00189E20[0x22B4] == 2)
                func_L00_002D38A0(step, step, 5.0f);
            else if (D_00189E20[0x22C3] == 1 || *(short *)(D_00189E20 + 0x218) != 0)
                func_L00_002D36E0(step, 0, 0.0f, 0.0f, 0.6f);
            else if (D_L01_001A9030 != 0)
                func_L00_002D38A0(step, step, 0.77f);
            else
                func_L00_002D36E0(step, 0, 0.0f, 0.0f, *(float *)(D_00189E20 + 0x254));
        } else {
            step[2] = *(float *)(hero + 0x254);
        }
    }
    func_00282CC0(D_00189EA0, D_00189EA0, step);
    hero = D_00189EA0 - 0x80;
    contact = D_L01_001BF930;
    for (i = 0; i < 8; i++) {
        pos = hero + 0x80;
        if (hero[0x22C3] != 0 || steep) {
            hit = func_00277258(pos, 0x324, *(int *)(hero + 0x2290), *(float *)(hero + 0x264));
        } else {
            d = *(float *)(hero + 0x250) - *(float *)(hero + 0x254);
            if (d < 0.05f)
                d = 0.05f;
            hit = func_L00_002E0200(*(float *)(hero + 0x264), pos, 0x324, *(int *)(hero + 0x2290), d);
        }
        if (*(short *)(hero + 0x1E6) == 0)
            hit |= func_00278870(pos, *(float *)(hero + 0x264));
        if (hit == 0)
            break;
        *(Quad *)D_00189EA0 = *(Quad *)contact;
        *(Quad *)D_0018A050 = *(Quad *)D_L01_001BF940;
        *(Quad *)D_0018A060 = *(Quad *)D_L01_001BF920;
        hero[0x287] = 1;
        *(int *)(hero + 0x26C) = D_L01_001BF900.hit;
    }
    pos = D_00189EA0;
    func_00282CF0(pos, pos, step);
    func_00282CF0(moved, pos, old);
    d = func_00282DF0(moved);
    if (!(*(float *)(pos + 0x1E4) * 1.5f < d))
        return 1;
    if (mode != 0xF)
        return -1;
    if (moved[0] > 512.0f)
        moved[0] = 512.0f;
    else if (moved[0] < -512.0f)
        moved[0] = -512.0f;
    if (moved[1] > 512.0f)
        moved[1] = 512.0f;
    else if (moved[1] < -512.0f)
        moved[1] = -512.0f;
    if (moved[2] > 512.0f)
        moved[2] = 512.0f;
    else if (moved[2] < -512.0f)
        moved[2] = -512.0f;
    hero = D_00189E20;
    func_00282F20(moved, moved, *(float *)(hero + 0x264));
    func_00282CC0(hero + 0x80, old, moved);
    return -1;
}
