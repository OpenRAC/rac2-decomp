#include "include_asm.h"

#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
typedef struct PoolRecord64 PoolRecord64;
extern Vector D_00189EA0;
extern unsigned char D_00188660[];
extern void func_002A7750(unsigned char *, unsigned char, int);
extern unsigned char *func_0029EFD0(int);
extern void func_002B37E8(void *, void *);
extern int func_002B3868(unsigned char *);
extern int func_00282948(int *);
extern float func_00283B98(float, float);
extern int func_002E5CF8(int, int, char *);
extern void func_002E59F8(int);
extern int func_L00_00324120(int);
extern PoolRecord64 *func_PAL_L00_002D7850(int);
extern void func_L00_002D7140(unsigned char *);
extern void func_L20_0043D470(char *);
extern void func_00282CF0(void *, const void *, const void *);
extern void func_002AD6F0(void *, const void *, const void *, const void *);
extern void func_PAL_L01_00322798(void *, float *, int);
extern void func_0029F338(void *);
extern void func_00282D30(void *, const void *, float);
extern void func_00282CC0(void *, const void *, const void *);
extern void func_002A0F48(void *);
extern Vector D_L20_001B9FC0;

void func_PAL_L20_00442E80(unsigned char *object) {
    Vector oldPosition, oldRotation, delta, offset;
    unsigned char *state = *(unsigned char **)(object + 0x68);
    unsigned char *child;
    unsigned char *slot;
    int index;
    oldPosition.q = *(Quadword *)(object + 0x10);
    oldRotation.q = *(Quadword *)(object + 0xF0);
    switch (object[0x20]) {
    case 0: {
        float speed = *(float *)(state + 0x74) * 0.017453294f;
        float range = 6.2831854820251465f;
        float one = 1.0f;
        unsigned int original;
        *(int *)(state + 0x5C) |= 1;
        *(float *)(state + 0x70) = range;
        *(float *)(state + 0x74) = speed;
        original = object[0xBC];
        *(int *)(state + 0x60) = 0;
        *(int *)(state + 0x68) = 0;
        *(int *)(state + 0x80) = 0;
        *(unsigned int *)(state + 0x7C) = original;
        *(float *)(state + 0x64) = one;
        *(float *)(state + 0x6C) = one;
        func_002A7750(object, 1, -1);
        break;
    }
    case 1:
        if ((unsigned)object[0xBC] != *(unsigned int *)(state + 0x7C)) {
            if (!*(unsigned char **)(state + 0x88)) {
                if (!(*(unsigned char **)(state + 0x88) = func_0029EFD0(*(short *)(object + 0xAA))))
                    goto clone_failed;
            }
            {
                func_002B37E8(*(unsigned char **)(state + 0x88), 0);
                *(unsigned short *)(*(unsigned char **)(state + 0x88) + 0x34) |= 2;
                *(int *)(*(unsigned char **)(state + 0x88) + 0x98) = 0;
                (*(unsigned char **)(state + 0x88))[0x23] = 0;
            }
clone_failed:
            {
                float sign = -1.0f;
                if (D_00189EA0.f[1] <= *(float *)(object + 0x14)) sign = 1.0f;
                *(float *)(state + 0x64) = sign;
            }
            func_002A7750(object, 2, -1);
        }
        break;
    case 2:
        if (func_002B3868(object)) *(int *)(state + 0x78) = (int)(*(float *)(state + 0x70) / *(float *)(state + 0x74));
        if (!func_00282948((int *)(state + 0x78))) {
            *(float *)(object + 0xF8) = func_00283B98(*(float *)(object + 0xF8), *(float *)(state + 0x74));
            slot = *(int *)(state + 0x90) * 0x70 + D_00188660;
            if (*(unsigned char **)(slot + 0x88) != object || !slot[0x74])
                *(int *)(state + 0x90) = func_002E5CF8(1, 4, (char *)object);
        } else {
            object[0xBC] = *(unsigned char *)(state + 0x7C);
            func_002A7750(object, 1, -1);
            index = *(int *)(state + 0x90);
            if (index != -1) {
                unsigned char *stoppedSlot = index * 0x70 + D_00188660;
                if (*(unsigned char **)(stoppedSlot + 0x88) == object && stoppedSlot[0x74])
                    func_002E59F8(index);
            }
            *(int *)(state + 0x90) = -1;
        }
        break;
    }
    if (func_L00_00324120((int)object) && !*(int *)(state + 0x80)) {
        *(PoolRecord64 **)(state + 0x84) = func_PAL_L00_002D7850(5);
        *(int *)(state + 0x80) = 1;
        func_L20_0043D470((char *)object);
    } else if (!func_L00_00324120((int)object) && *(int *)(state + 0x80)) {
        func_L00_002D7140(*(unsigned char **)(state + 0x84));
        *(int *)(state + 0x80) = 0;
    }
    func_00282CF0(&delta, object + 0x10, &oldPosition);
    func_002AD6F0(state + 0x20, &delta, &oldRotation, object + 0xF0);
    child = *(unsigned char **)(state + 0x88);
    if (child) {
        func_PAL_L01_00322798(child, (float *)(state + 0x8C), object[0x20] == 2);
        child = *(unsigned char **)(state + 0x88);
        if (!child[0x23]) {
            func_0029F338(child);
            *(unsigned char **)(state + 0x88) = 0;
        } else {
            *(Quadword *)(child + 0xF0) = *(Quadword *)(object + 0xF0);
            func_00282CF0(&offset, &D_L20_001B9FC0, object + 0x10);
            func_00282D30(&offset, &offset, 0.01f);
            func_00282CC0(*(unsigned char **)(state + 0x88) + 0x10, &offset, object + 0x10);
            func_002A0F48(*(unsigned char **)(state + 0x88));
        }
    }
}
