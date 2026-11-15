#include "common.h"

extern int func_002B38B8(char *);
extern int func_002B3868(char *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_0032DA58(char *, void *, void *, float);
extern void func_002A7750(char *, int, int);
extern int func_002E5CF8(int, int, char *);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern char *func_00273730(char *, int, int, int, void *, void *, void *, int, float, float);
extern void func_0029F338(char *);
extern void func_00273B70(char *);
extern int func_002A7820(int, int);

/* The spawn bounds: minimum vector at +0x00, maximum vector at +0x10. An incomplete `sda` array
   gives retail's mix: element 0 is a one-instruction load (GP in a call's delay slot, absolute
   elsewhere), while every other element is a `sym+offset` address, which cc1 counts as two
   instructions, keeps out of delay slots and the assembler expands absolute. */
extern float D_L07_001B0C00[] __attribute__((sda));
/* The offset vector, addressed through $gp. */
extern float D_L07_001B0C20[] SDATA(D_L07_001B0C20);
/* Two {minimum, maximum} pairs for the child's two random parameters; retail reads +0x08 $gp
   relative and the others absolute. */
extern float D_L07_001B0C30[] __attribute__((sda));
extern float D_L07_001B0C30_gp[] SDATA(D_L07_001B0C30);

/* A four-state burst: state 1 passes the rotated, offset position to func_0032DA58, state 2
   spawns nine children that run this function in state 3, where each counts down a random
   lifetime. */
void func_L07_003EE3B0(char *arg)
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
            matrix_mul_vec3(v, D_L07_001B0C20, arg + 0xC0);
            FastVecAdd(v, v, arg + 0x10);
            func_0032DA58(arg, v, arg + 0xD0, 0.0f);
            func_002A7750(arg, 2, -1);
        }
        break;
    case 2:
        if (func_002B3868(arg))
            PlayMobySound(0, 0, arg);
        for (i = 0; i < 9; i++) {
            v[0] = func_002A7878(D_L07_001B0C00[0], D_L07_001B0C00[4]) * 0.016666667f;
            v[1] = func_002A7878(D_L07_001B0C00[1], D_L07_001B0C00[5]) * 0.016666667f;
            v[2] = func_002A7878(D_L07_001B0C00[2], D_L07_001B0C00[6]) * 0.016666667f;
            matrix_mul_vec3(v, v, arg + 0xC0);
            f = func_002A78D8(D_L07_001B0C30[0], D_L07_001B0C30[1]);
            g = func_002A7878(D_L07_001B0C30_gp[2], D_L07_001B0C30[3]);
            e = func_00273730(arg, 2, *(short *)(arg + 0xAA), i, arg + 0x10, arg + 0xF0, v, 255, f, g);
            if (e) {
                *(void (**)(char *))(e + 0x64) = func_L07_003EE3B0;
                *(unsigned short *)(e + 0x34) |= 0x2000;
                func_002A7750(e, 3, -1);
            }
        }
        func_0029F338(arg);
        break;
    case 3:
        if (func_002B3868(arg))
            *(unsigned short *)(arg + 0x96) = func_002A7820(0, 60);
        func_00273B70(arg);
        if (*(unsigned short *)(arg + 0x96) == 0 || --*(unsigned short *)(arg + 0x96) == 0) {
            if (*(unsigned char *)(arg + 0x23) >= 4)
                *(unsigned char *)(arg + 0x23) -= 4;
            else
                func_0029F338(arg);
        }
        break;
    }
}
