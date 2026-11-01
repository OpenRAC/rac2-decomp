#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern void func_002A7A00(char *, float, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_PAL_L02_0032D5F8(char *, int, char *, char *, int, int, float *, void *, void *, float);
extern void func_0029F338(char *);
extern char D_L02_001A8F20[] __attribute__((sda));

void func_PAL_L11_0044EDC0(char *self, TI128 *pos) {
    char *state = *(char **)(self + 0x68);
    float copy[4];
    float vec[4];

    *(TI128 *)copy = *pos;
    if (*(unsigned char *)(self + 0x31) != 0) {
        func_002A7A00((char *)vec, 0.120000005f, 0.20000002f);
        func_00282CC0(vec, vec, D_L02_001A8F20);
        func_PAL_L02_0032D5F8(self, 0x9D8, *(char **)(state + 0x354) + 0x10, *(char **)(state + 0x354) + 0xF0,
                    0, 0, vec, D_L02_001A8F20, D_L02_001A8F20, 0.004f);
    }
    func_0029F338(*(char **)(state + 0x354));
    *(char **)(state + 0x354) = 0;
}


extern void func_002B60B0(char *, float, float, float, float);
extern void func_PAL_002A7E68(char *, int, int, int);
extern void func_002A7750(char *, int, int);
extern void func_PAL_002A0F68(char *);
extern void func_002A0488(char *, int, int, int);
extern int func_PAL_002B3F18(char *, char *, char *);
extern void func_L11_003973F8(char *, int, float, float);
extern void func_002A04B8(char *, int *, int *, int *);
extern u16 *D_L11_001FC420[];
extern u8 *D_L11_001B359C __attribute__((sda));

/* func_L11_00449330 is in L11_00449330.c: PAL's level 11 has other code at its place,
   so the calls to it from this unit go through its symbol. */

void func_PAL_L11_0044F150(char *object, int mode, int active) {
    char *state = *(char **)(object + 0x68);
    int colors[4];
    int green, blue;

    *(short *)(state + 0x88) = 0;
    *(short *)(state + 0x366) = 0;
    *(float *)(state + 0x20) = *(short *)(state + 0x24);
    *(short *)(state + 0x36E) = active;
    func_002B60B0(object, 0.008f, 0.124000005f,
                  0.005026549f, 0.5026549f);
    *(u8 *)(state + 0x6A) = 0;
    *(u8 *)(state + 0x2E) = 1;
    *(u8 *)(object + 0x7F) = 0;
    *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) | 0x1000) & 0xFFB9;
    *(int *)(object + 0x98) = *(int *)(*(char **)(object + 0x24) + 0x10);
    if (*(short *)(state + 0x36E) != 0) {
        func_002A7750(object, 4, 2);
        *(u16 *)(object + 0x34) |= 0x100;
        func_PAL_002A7E68(object, 0, 0, 0);
        func_PAL_002A0F68(object);
        func_L11_003973F8(object, 0, 2.0f, 2.0f);
    } else {
        if (*(u8 *)(object + 0x43) != 0)
            func_PAL_002A7E68(object, 0, 0, 8);
        func_002A7750(object, 3, 1);
        *(u8 *)(object + 0x31) = 1;
        *(u16 *)(object + 0x34) &= 0xFEFE;
    }
    func_L11_004492A0(object);
    *(short *)(state + 0x36C) = mode;
    *(int *)(state + 0x200) = 0;
    func_PAL_002B3F18(object, state + 0x1F0, state + 0x20);
    if (*(short *)(state + 0x50) != 0) {
        *(short *)(state + 0x50) = 0;
        func_002A0488(object, *(u8 *)(state + 0x54), *(u8 *)(state + 0x55),
                      *(u8 *)(state + 0x56));
        *(short *)(state + 0x52) = 1;
    }
    if (*(char **)(state + 0x354) != 0) {
        func_002A04B8(object, &colors[0], &colors[1], &colors[2]);
        green = colors[1];
        blue = colors[2];
        func_002A0488(*(char **)(state + 0x354), colors[0], green, blue);
    }
}

