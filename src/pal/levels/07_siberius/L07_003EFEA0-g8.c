#include "include_asm.h"

#include "common.h"
extern int func_002B38B8(char *);
extern int func_002B3868(char *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_PAL_0032F3B8(char *, void *, void *, float);
extern void func_002A7750(char *, int, int);
extern int func_002E5CF8(int, int, char *);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern char *func_PAL_002735D0(char *, int, int, int, void *, void *, void *, int, float, float);
extern void func_0029F338(char *);
extern void func_PAL_00273A10(char *);
extern int func_002A7820(int, int);
extern float D_L07_001B0C00[] __attribute__((sda));
extern float D_L07_001B0C20[] SDATA(D_L07_001B0C20);
extern float D_L07_001B0C30[] __attribute__((sda));
extern float D_L07_001B0C30_gp[] SDATA(D_L07_001B0C30);

/* A four-state burst: state 1 passes the rotated, offset position to func_PAL_0032F3B8, state 2
   spawns nine children that run this function in state 3, where each counts down a random
   lifetime. */
void func_PAL_L07_003F27F8(char *arg)
{
    float v[4] __attribute__((aligned(16)));
    int i;
    float f, g;
    char *e;

    switch (*(unsigned char *)(arg + 0x20)) {
    case 0:
        func_002A7750(arg, 1, -1);
        break;
    case 1:
        if (func_002B38B8(arg)) {
            func_00283098(v, D_L07_001B0C20, arg + 0xC0);
            func_00282CC0(v, v, arg + 0x10);
            func_PAL_0032F3B8(arg, v, arg + 0xD0, 0.0f);
            func_002A7750(arg, 2, -1);
        }
        break;
    case 2:
        if (func_002B3868(arg))
            func_002E5CF8(0, 0, arg);
        for (i = 0; i < 9; i++) {
            v[0] = func_002A7878(D_L07_001B0C00[0], D_L07_001B0C00[4]) * 0.020000001f;
            v[1] = func_002A7878(D_L07_001B0C00[1], D_L07_001B0C00[5]) * 0.020000001f;
            v[2] = func_002A7878(D_L07_001B0C00[2], D_L07_001B0C00[6]) * 0.020000001f;
            func_00283098(v, v, arg + 0xC0);
            f = func_002A78D8(D_L07_001B0C30[0], D_L07_001B0C30[1]);
            g = func_002A7878(D_L07_001B0C30_gp[2], D_L07_001B0C30[3]);
            e = func_PAL_002735D0(arg, 2, *(short *)(arg + 0xAA), i, arg + 0x10, arg + 0xF0, v, 255, f, g);
            if (e) {
                *(void (**)(char *))(e + 0x64) = func_PAL_L07_003F27F8;
                *(unsigned short *)(e + 0x34) |= 0x2000;
                func_002A7750(e, 3, -1);
            }
        }
        func_0029F338(arg);
        break;
    case 3:
        if (func_002B3868(arg))
            *(unsigned short *)(arg + 0x96) = ((s32)(func_002A7820(0, 60)) * 5 + 2) / 6;
        func_PAL_00273A10(arg);
        if (*(unsigned short *)(arg + 0x96) == 0 || --*(unsigned short *)(arg + 0x96) == 0) {
            if (*(unsigned char *)(arg + 0x23) >= 4)
                *(unsigned char *)(arg + 0x23) -= 4;
            else
                func_0029F338(arg);
        }
        break;
    }
}
