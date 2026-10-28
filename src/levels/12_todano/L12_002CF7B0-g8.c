#include "include_asm.h"

extern int D_L12_001A8F00 __attribute__((nosda));

extern int D_L12_001BDB30 __attribute__((nosda));

extern char *D_L12_001B2EA8 __attribute__((sda));

/* Clear the two flag bits on every object of the chain while a mode gate holds.
   Near miss: nonmatching/levels/func_L12_00388038.c */

extern int D_001A79F0;

extern void *func_L01_002F1FD0(float, float, float);

extern void func_00283098(void *, void *, void *);

extern void func_00282D30(void *, void *, float);

extern void func_00282CC0(void *, void *, void *);

extern char D_L12_0027F710[];

extern int D_L12_001A9410 __attribute__((sda));

typedef struct {
    char pad0[0x30];
    unsigned int mode;
    int count;
    char pad1[0x18];
    int mesh;
    char pad2[0x138];
    int *entries[4];
} L12_002FFF88_STATE;

extern L12_002FFF88_STATE D_L12_001BDB00;

/* Builds the level's four trail slices for the mesh its state points at. */
void func_L12_002FFF88(void)
{
    int index;
    void *obj;
    float scale;
    char *q;
    int i;
    int off;

    if (D_001A79F0 != 12)
        return;

    obj = 0;
    index = -1;
    if (D_L12_001BDB00.mode < 2) {
        obj = func_L01_002F1FD0(0.0f, 0.0f, 0.0f);
        index = 2;
    }
    if (index != -1 && obj != 0) {
        if (D_L12_001BDB00.entries[index] != 0) {
            char *d = obj + 0x10;
            char *c = obj + 0xC0;
            D_L12_001BDB00.mesh = (int)D_L12_0027F710;
            q = (char *)&D_L12_001A9410;
            off = 0x20;
            i = 3;
            scale = *(float *)(obj + 0x2C) / *(float *)(*(int *)(obj + 0x24) + 0x24);
            for (; i >= 0; i--) {
                func_00283098((char *)(D_L12_001BDB00.mesh + off), q, c);
                func_00282D30((char *)(D_L12_001BDB00.mesh + off),
                              (char *)(D_L12_001BDB00.mesh + off), scale);
                func_00282CC0((char *)(D_L12_001BDB00.mesh + off),
                              (char *)(D_L12_001BDB00.mesh + off), d);
                off += 0x10;
                q += 0x10;
            }
            *(int *)(D_L12_001BDB00.mesh + 0x68) = D_L12_001BDB00.entries[index];
        }
    }
    if (D_L12_001BDB00.mode == 0 && D_L12_001BDB00.count >= 0x925)
        D_L12_001BDB00.mesh = 0;
    if (D_L12_001BDB00.mode == 1 && D_L12_001BDB00.count < 0x3C)
        D_L12_001BDB00.mesh = 0;
}

typedef int Quadword89F80 __attribute__((mode(TI)));

extern float func_00282DB0(void *, void *);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002A7750(void *, int, int);
extern int func_002AD0E0(void *, void *, void *, void *, void *, void *);
extern void func_002AD6F0(void *, void *, void *, void *);
extern int func_L02_004127F8(char *);
extern char *ref_L12_00389F80_00 __attribute__((sda));
extern char *ref_L12_00389F80_01;
extern float ref_L12_00389F80_02 __attribute__((sda));
extern float ref_L12_00389F80_03 __attribute__((sda));

/* Per-state step of a homing object: state 0 starts it, state 1 steers it by the thing it
   follows (or just turns it) and then spins a short delay loop. */
void func_L12_00389F80(char *object) {
    char *state = *(char **)(object + 0x68);
    float a[4];
    float b[4];
    float c[4];
    float dot;
    int i;

    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        *(unsigned int *)(state + 0x5C) |= 4;
        *(short *)(object + 0x7C) = 3;
        func_002A7750(object, 1, -1);
        break;
    case 1:
        if (*(int *)(state + 0xE0) == -1 ||
            func_L02_004127F8(ref_L12_00389F80_00 + (*(int *)(state + 0xE0) << 8)) == 0) {
            func_00282F20(state + 0x30, object + 0xD0, -(ref_L12_00389F80_02 * 0.016666668f));
            *(float *)(object + 0x48) = ref_L12_00389F80_03;
        } else {
            func_002AD0E0(object, ref_L12_00389F80_01 + (*(int *)(state + 0xE0) << 8), object + 0x10,
                          object + 0xF0, a, b);
            a[2] = 0.0f;
            func_00282CF0(c, a, object + 0x10);
            *(Quadword89F80 *)a = *(Quadword89F80 *)c;
            a[2] = 0.0f;
            b[0] = func_00283180(*(float *)(object + 0xF8) + 4.7123895f);
            b[1] = func_00283198(*(float *)(object + 0xF8) + 4.7123895f);
            b[2] = 0.0f;
            dot = func_00282DB0(a, b);
            c[0] = func_00283180(*(float *)(object + 0xF8)) * dot * 0.1f;
            c[1] = func_00283198(*(float *)(object + 0xF8)) * dot * 0.1f;
            c[2] = 0.0f;
            func_002AD6F0(state + 0x20, c, object + 0xF0, object + 0xF0);
            *(float *)(object + 0x48) = dot * 59.999996f;
        }
        i = 6;
        while (--i >= 0)
            ;
        break;
    }
}
