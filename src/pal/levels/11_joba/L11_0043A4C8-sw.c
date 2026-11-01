#include "include_asm.h"

#include "common.h"
extern char D_00188660[];
extern void func_002E59F8(int);
extern int func_002E5CF8(int, int, char *);
extern int D_L11_001B359C __attribute__((sda));
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00282E80(void *, void *);
extern char D_00189EA0[];
/* Stops the object's sound if its slot still belongs to it, then forgets the slot. */
static inline void stop_owned_sound(char *state, char *p)
{
    int slot = *(int *)(state + 0x14);

    if (slot != -1) {
        char *e = D_00188660 + slot * 0x70;

        if (*(char **)(e + 0x88) == p && *(unsigned char *)(e + 0x74))
            func_002E59F8(slot);
    }
    *(int *)(state + 0x14) = -1;
}
extern void func_002E59F8(int a);
extern char D_00188660[];
extern int func_002E5CF8(int index, int a1, char *a2);

/* Five-stage mover driven by the parent's state byte: when the parent reaches 2 it starts its
   sound and moves out along its +0xE0 direction over half a turn (pi/120 a frame); when the
   parent leaves 2 it does the same back, only while D_00189EA0 is more than 6 away, and at a
   full turn returns to its saved position and waits again. */
void func_PAL_L11_0043A7A8(char *p)
{
    char *state = *(char **)(p + 0x68);
    char *parent = (char *)(D_L11_001B359C + (*(int *)(state + 8) << 8));
    float offset[4];

    switch (*(unsigned char *)(p + 0x20)) {
    case 0:
        *(unsigned char *)(p + 0x20) = 1;
        *(float *)(state + 0xC) = 3.1415927f;
        *(float *)(state + 0x10) = 0;
        qcopy(state + 0x20, p + 0x10);
        *(unsigned short *)(p + 0x34) |= 0x800;
    case 1:
        if (*(unsigned char *)(parent + 0x20) == 2) {
            char *e = D_00188660 + *(int *)(state + 0x14) * 0x70;

            if (*(char **)(e + 0x88) != p || !*(unsigned char *)(e + 0x74))
                *(int *)(state + 0x14) = func_002E5CF8(0, 4, p);
            *(unsigned char *)(p + 0x20) = 2;
            *(float *)(state + 0xC) = 3.1415927f;
            *(float *)(state + 0x10) = 0;
        } else {
            stop_owned_sound(state, p);
        }
        break;
    case 2:
        *(float *)(state + 0x10) += 0.031415932f;
        *(float *)(state + 0xC) = func_00283B98(*(float *)(state + 0xC), 0.031415932f);
        if (*(float *)(state + 0x10) >= 3.1415927f) {
            stop_owned_sound(state, p);
            *(unsigned char *)(p + 0x20) = 3;
        } else {
            func_00282F20((char *)offset, p + 0xE0, (func_00283180(*(float *)(state + 0xC)) + 1.0f) * 5.0f);
            func_00282CC0(p + 0x10, (char *)offset, state + 0x20);
        }
        break;
    case 3:
        if (*(unsigned char *)(parent + 0x20) != 2) {
            char *e = D_00188660 + *(int *)(state + 0x14) * 0x70;

            if (*(char **)(e + 0x88) != p || !*(unsigned char *)(e + 0x74))
                *(int *)(state + 0x14) = func_002E5CF8(0, 4, p);
            *(unsigned char *)(p + 0x20) = 4;
        } else {
            stop_owned_sound(state, p);
        }
        break;
    case 4:
        if (func_00282E80(p + 0x10, D_00189EA0) > 6.0f) {
            *(float *)(state + 0x10) += 0.031415932f;
            *(float *)(state + 0xC) = func_00283B98(*(float *)(state + 0xC), 0.031415932f);
            if (*(float *)(state + 0x10) >= 6.2831855f) {
                stop_owned_sound(state, p);
                *(unsigned char *)(p + 0x20) = 1;
                *(float *)(state + 0xC) = 3.1415927f;
                *(float *)(state + 0x10) = 0;
                qcopy(p + 0x10, state + 0x20);
            } else {
                func_00282F20((char *)offset, p + 0xE0, (func_00283180(*(float *)(state + 0xC)) + 1.0f) * 5.0f);
                func_00282CC0(p + 0x10, (char *)offset, state + 0x20);
            }
        }
        break;
    }
}
