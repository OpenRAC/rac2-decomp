#include "include_asm.h"

#include "common.h"
extern void func_0029F338(void *);
extern float func_002A7940(void);
extern void func_002A7750(void *, int, int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern int D_L02_001A8FF0 __attribute__((sda));
extern char D_L02_001BA500[];
extern float func_002A7878_range(float, float) __asm__("func_002A7878");
extern float func_002A78D8(float, float);
extern int func_00283CF0(float);
extern float func_00282E48(void *, void *);
extern int D_001A79F0[] __attribute__((sda));
extern char *D_L02_001B3200 __attribute__((sda));
extern char D_L02_001B3210[] __attribute__((sda));
extern void func_002B0178(void *, void *, void *);
extern void func_002A93B0(void *);
extern int func_PAL_002B1A50(void *, void *, int);
extern void func_L02_003CE9A8(void *);
extern int func_002B3BA8(void *, int, float, float, int, int);
extern void func_002AFFD8(void *, void *, int);

void func_PAL_L02_003D24B8(char *obj) {
    char *d = *(char **)(obj + 0x68);
    char *entry;
    int hit;
    if (*(unsigned char *)(obj + 0x20) == 0) {
        if (D_001A79F0[0] == 26) {
            if (D_L02_001A8FF0 == 0) return;
            func_002B0178(obj + 0x10, obj, obj + 0x10);
            *(short *)(d + 0x338) = 1;
            *(int *)(obj + 0x9c) = 3;
            *(unsigned short *)(obj + 0x34) |= 0x100;
            *(float *)(d + 0x90) = func_00282E48(obj + 0x10, D_L02_001B3210) - 1.5f;
        } else {
            *(int *)(obj + 0x9c) = 12;
            *(float *)(d + 0x90) = *(float *)(obj + 0x18) - 1.0f;
        }
        if (*(int *)(d + 0x210) == -1) {
            func_0029F338(obj);
            return;
        }
        entry = D_L02_001B3200 + *(int *)(d + 0x210) * 0x30;
        if (*(short *)(entry + 0x30)) {
            *(int *)(d + 0x13c) = *(int *)(d + 0x218) = **(int **)(entry + 0x3c);
        } else *(int *)(d + 0x218) = -1;
        *(float *)(d + 0x324) = func_002A7878_range(1.0f, 1.332999945f);
        *(float *)(obj + 0x2c) = *(float *)(*(char **)(obj + 0x24) + 0x24) * *(float *)(d + 0x324);
        *(char *)(d + 0x48) = func_00283CF0(15.0f);
        *(char *)(d + 0x4a) = func_00283CF0(6.4f);
        *(int *)(d + 0x98) = 3;
        *(float *)(d + 0x80) = 0.2f;
        *(float *)(d + 0x84) = 0.2f;
        *(float *)(d + 0x8c) = 0.4f;
        *(float *)(d + 0x108) = 0.4f;
        *(float *)(d + 0x134) = 0.05f;
        *(char *)(d + 0x60) = 11;
        *(char *)(d + 0x28) = 3;
        *(float *)(d + 0x30) = 0.3330000043f;
        *(float *)(d + 0x104) = *(float *)(d + 0x324) * 0.2f;
        *(float *)(d + 0x100) = *(float *)(d + 0x324) * 0.3f;
        *(float *)(d + 0x10c) = 0.4f;
        *(float *)(d + 0x110) = 1.57079649f;
        *(float *)(d + 0x130) = 0.52359885f;
        *(int *)(d + 0x138) |= 0x280;
        *(float *)(d + 0x1dc) = func_002A78D8(18.0f, 22.0f) * 0.01745329425f;
        *(short *)(d + 0x1e2) = 100;
        *(short *)(d + 0x1e4) = 150;
        *(char *)(d + 0x1e8) = 7;
        *(char *)(d + 0x1e9) = 6;
        *(float *)(d + 0x1d4) = 3.0f;
        *(float *)(d + 0x1d0) = 0.080000006f;
        *(float *)(d + 0x328) = func_002A7940();
        if (*(int *)(d + 0x214)) {
            *(int *)(obj + 0x98) = 0;
            *(unsigned short *)(obj + 0x34) = (*(unsigned short *)(obj + 0x34) | 0x41) & 0xefff;
            func_002A7750(obj, 13, 4);
            if (*(unsigned char *)(obj + 0x43) != 10) func_PAL_002A7E68(obj, 10, 0, 0);
        } else {
            func_002A7750(obj, 1, 0);
            if (*(unsigned char *)(obj + 0x43)) func_PAL_002A7E68(obj, 0, 0, 0);
        }
        qcopy(d + 0x2e0, obj + 0x10);
    }
    if (*(unsigned char *)(obj + 0x31) && func_00282E48(obj + 0x10, D_L02_001BA500) < 24.0f) {
        func_002A93B0(obj);
        *(char *)(obj + 0x6f) = 22;
    }
    hit = func_PAL_002B1A50(obj, d + 0x50, 0);
    if (hit) {
        func_L02_003CE9A8(obj);
        if (hit >= 4) func_002A7750(obj, 12, -1);
    }
    if ((unsigned int)(*(unsigned char *)(obj + 0x95) - 3) >= 2)
        *(short *)(d + 0x314) = func_002B3BA8(obj, *(int *)(d + 0x210), 16.0f, 0.0f, 0, 0);
    if (*(short *)(d + 0x338)) func_002AFFD8(obj + 0x10, d + 0x300, 0);
}

extern void func_00282978(void *);
extern void func_002AEC48(void *, void *, int, float, float);
extern void func_PAL_002B14F8(void *, void *, int, float, int);

/* Clears the two angle words at +0x310 and +0x312 and counts up the +0x96 word, then runs the
   two placement helpers on the sub-object at +0x260. */
void func_PAL_L02_003D28F0(char *a0) {
    char *p = *(char **)(a0 + 0x68);
    char *q;
    unsigned short n;

    func_00282978(p + 0x310);
    func_00282978(p + 0x312);
    n = *(unsigned short *)(a0 + 0x96);
    if (n <= 0xFFFE)
        *(unsigned short *)(a0 + 0x96) = n + 1;
    q = p + 0x260;
    func_002AEC48(a0, q, 0, 0.0432f, 0.43200004f);
    func_PAL_002B14F8(a0, q, 0, 1.79999995231628417968750f, 1);
}
