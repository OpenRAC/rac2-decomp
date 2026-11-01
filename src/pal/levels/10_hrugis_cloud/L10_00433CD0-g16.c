#include "include_asm.h"

#include "common.h"
extern int func_002A77E0(int);
extern float func_002A7878(float, float);
extern int func_00282948(void *);
extern char D_L10_002BAC40[];
extern char D_L10_001B1790[16] __attribute__((sda));
extern void func_002AA458(void *, void *, void *, float, float, float);
extern float func_00282E48(void *, void *);
extern void func_002A7750(void *, int, int);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern float func_00283B98(float, float);
extern int func_L10_0042E590(void *);
extern void func_PAL_L05_0039BD90(void *, int, int, int, int, int, int, int, float);
extern void func_PAL_L05_0042A240(void *, int, int, int, int, int, int, int, int, int, int, float);
extern void func_0029F338(void *);
extern void func_PAL_L10_004342B0(void *);
extern void func_L10_0042E660(char *, int);
extern char *func_PAL_L10_00433CD0(int);

/* Update of a cloud object spawned by func_PAL_L10_00433CD0. State 0 waits for the timer at
   work+0x1C; state 1 steers to its point in D_L10_002BAC40 (state 2 within 2 units); state 2
   steers to the 16-byte target D_L10_001B1790 and bursts there. Then the velocity at work+0
   moves the object and decays, the angles spin, and leaving the 2..1021 box (or
   func_L10_0042E590) bursts it as well; otherwise func_PAL_L10_004342B0 runs on a random half of the frames.
   -G16 for the $gp target; -frac2-gcse-unsplit-edges keeps the object+0x10 PRE copy in the
   dispatch block, as retail (the split edge of the state-0 timer test would get its own). */
void func_PAL_L10_00433EE0(char *object)
{
    char *st = *(char **)(object + 0x68);

    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        if (func_00282948(st + 0x1C))
            func_002A7750(object, 1, -1);
        break;
    case 1: {
        float speed = func_002A7878(2.0f, 4.0f) * 0.020000001f;
        func_002AA458(object + 0x10, D_L10_002BAC40 + *(int *)(st + 0x28) * 16, st + 0x18,
                      0.0012f, 0.040000003f, speed);
        if (func_00282E48(object + 0x10, D_L10_002BAC40 + *(int *)(st + 0x28) * 16) < 2.0f)
            func_002A7750(object, 2, -1);
        break;
    }
    case 2:
        func_002AA458(object + 0x10, D_L10_001B1790, st + 0x18, 0.0048f, 0.0048f,
                      0.16000001f);
        if (func_00282E48(object + 0x10, D_L10_001B1790) < 0.5f) {
            if (*(short *)(object + 0xAA) == 0x1315)
                func_PAL_L05_0039BD90(object + 0x10, 0, 0, 0, 0, 15, 0, 1, 0.7f);
            else
                func_PAL_L05_0042A240(object + 0x10, 0, 0, 0, 0, 10, 20, 1, 1, 0, 0, 0.7f);
            func_PAL_L10_00433CD0(*(int *)(st + 0x14));
            func_0029F338(object);
            return;
        }
        break;
    }
    func_00282CC0(object + 0x10, object + 0x10, st);
    func_00282F20(st, st, func_00282DF0(st) * 0.9875f);
    *(float *)(object + 0xF8) = func_00283B98(*(float *)(object + 0xF8), 0.03f);
    *(float *)(object + 0xF0) = func_00283B98(*(float *)(object + 0xF0), 0.01f);
    *(float *)(object + 0xF4) = func_00283B98(*(float *)(object + 0xF4), -0.02f);
    if (func_L10_0042E590(object) || *(float *)(object + 0x10) < 2.0f || *(float *)(object + 0x10) > 1021.0f ||
        *(float *)(object + 0x14) < 2.0f || *(float *)(object + 0x14) > 1021.0f ||
        *(float *)(object + 0x18) < 2.0f || *(float *)(object + 0x18) > 1021.0f) {
        func_L10_0042E660(object, 0);
        if (*(short *)(object + 0xAA) == 0x1315)
            func_PAL_L05_0039BD90(object + 0x10, 0, 0, 0, 0, 30, 0, 1, 0.7f);
        else
            func_PAL_L05_0042A240(object + 0x10, 0, 0, 0, 0, 20, 40, 1, 1, 0, 0, 0.7f);
        func_PAL_L10_00433CD0(*(int *)(st + 0x14));
        func_0029F338(object);
    } else if (func_002A77E0(2)) {
        func_PAL_L10_004342B0(object);
    }
}
