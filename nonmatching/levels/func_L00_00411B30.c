/* func_L00_00411B30: near miss, 1044/1044 bytes, 0 of 27 places (USA v1.01, 31 October 2026).

   Profile: its own unit, `-O2 -G0 -ffunction-sections -frac2-qcopy -fno-gcse`.

   Same size as retail; what still differs:
   - the table address: retail keeps only `lui %hi(D_L00_00256BC0)` in $s6 outside the loop and
     forms `addiu %lo` inside each iteration. Here `base` holds the whole address. Without
     `base`, -fno-gcse leaves both halves in the loop; with gcse on, PRE hoists the `lui` as in
     retail, but also reuses the first `slot + 0x20` through a copy ($s4) instead of retail's
     recomputed `addiu $s1,$s0,0x20` before the lerp, one saved register too many.
   - the second lq/sq copy: retail computes the destination in $a0 and the source in $v1;
     here they swap.
   - the hit setup: retail loads +0xCC, then f12 from +0xC8, then stores the owner's +0xB8 in
     the call's delay slot; here the store comes first.
   -fno-gcse is what gives retail's other copies (the `$s2 = $a0` after the second quad copy). */

#include "common.h"

/* A -frac2-qcopy unit: the record's 16-byte vectors are copied with lq/sq pairs. */

typedef int Quad __attribute__((mode(TI)));

typedef struct {
    char pad[0x18];
    unsigned char kind;
    unsigned char mode;
    unsigned short owner;
    char pad1C[0x14];
} Hit00411B30;

extern char *func_002AB1F0(char *);
extern void func_002AFFD8(void *, void *, int);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283CE0(int);
extern void func_00282D08(void *, void *, void *, float);
extern int func_00282948(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002A8C00(void *, char *, int, float, void *);
extern void func_002A8E20(char *, void *);
extern void func_L00_00412928(char *, int, int);
extern char D_L00_00256BC0[];

/* Moves the owner's records among the forty-eight at D_L00_00256BC0: each end follows its
   anchor object, the six angles turn, and the point between the ends travels from one to the
   other as the timer at +0xB8 runs down; when it expires the hit is applied once, and the
   record is freed when the timer at +0xA8 expires. */
void func_L00_00411B30(char *owner)
{
    float v[4];
    Hit00411B30 hit;
    char *slot;
    char *base;
    char *m;
    char *a;
    float f;
    int i;

    base = D_L00_00256BC0;
    for (i = 0; i < 48; i++) {
        slot = base + i * 0xD0;
        if (*(char **)(slot + 0xAC) != owner)
            continue;
        a = slot + 0x20;
        *(Quad *)a = *(Quad *)(slot + 0x40);
        if (*(char **)(slot + 0xB4) != 0) {
            m = func_002AB1F0(*(char **)(slot + 0xB4));
            if (m != 0) {
                func_002AFFD8(*(char **)(slot + 0xB4) + 0x10, v, 1);
                func_00282D30(v, v, *(float *)(m + 0x10));
                func_00282CC0(v, v, *(char **)(slot + 0xB4) + 0x10);
                func_00282CC0(a, v, a);
            } else {
                *(Quad *)a = *(Quad *)(*(char **)(slot + 0xB4) + 0x10);
            }
        }
        if (*(int *)(slot + 0xB8) != 0) {
            *(float *)(slot + 0x60) = func_00283B98(*(float *)(slot + 0x60), *(float *)(slot + 0x6C) * 100.0f);
            *(float *)(slot + 0x64) = func_00283B98(*(float *)(slot + 0x64), *(float *)(slot + 0x70) * 100.0f);
            *(float *)(slot + 0x68) = func_00283B98(*(float *)(slot + 0x68), *(float *)(slot + 0x74) * 100.0f);
            *(float *)(slot + 0x84) = func_00283B98(*(float *)(slot + 0x84), *(float *)(slot + 0x90) * 100.0f);
            *(float *)(slot + 0x88) = func_00283B98(*(float *)(slot + 0x88), *(float *)(slot + 0x94) * 100.0f);
            *(float *)(slot + 0x8C) = func_00283B98(*(float *)(slot + 0x8C), *(float *)(slot + 0x98) * 100.0f);
        } else {
            *(float *)(slot + 0x60) = func_00283B98(*(float *)(slot + 0x60), *(float *)(slot + 0x6C));
            *(float *)(slot + 0x64) = func_00283B98(*(float *)(slot + 0x64), *(float *)(slot + 0x70));
            *(float *)(slot + 0x68) = func_00283B98(*(float *)(slot + 0x68), *(float *)(slot + 0x74));
            *(float *)(slot + 0x84) = func_00283B98(*(float *)(slot + 0x84), *(float *)(slot + 0x90));
            *(float *)(slot + 0x88) = func_00283B98(*(float *)(slot + 0x88), *(float *)(slot + 0x94));
            *(float *)(slot + 0x8C) = func_00283B98(*(float *)(slot + 0x8C), *(float *)(slot + 0x98));
        }
        *(float *)(slot + 0x0) = func_00283180(*(float *)(slot + 0x60)) * *(float *)(slot + 0x78);
        *(float *)(slot + 0x4) = func_00283198(*(float *)(slot + 0x64)) * *(float *)(slot + 0x7C);
        *(float *)(slot + 0x8) = -func_00283198(*(float *)(slot + 0x68)) * *(float *)(slot + 0x80);
        *(float *)(slot + 0x10) = func_00283180(*(float *)(slot + 0x84)) * *(float *)(slot + 0x9C);
        *(float *)(slot + 0x14) = func_00283198(*(float *)(slot + 0x88)) * *(float *)(slot + 0xA0);
        *(float *)(slot + 0x18) = -func_00283198(*(float *)(slot + 0x8C)) * *(float *)(slot + 0xA4);
        *(Quad *)(slot + 0x30) = *(Quad *)(slot + 0x50);
        a = slot + 0x30;
        if (*(char **)(slot + 0xB0) != 0) {
            m = func_002AB1F0(*(char **)(slot + 0xB0));
            if (m != 0) {
                func_002AFFD8(*(char **)(slot + 0xB0) + 0x10, v, 1);
                func_00282D30(v, v, *(float *)(m + 0x10));
                func_00282CC0(v, v, *(char **)(slot + 0xB0) + 0x10);
                func_00282CC0(a, v, a);
            } else {
                *(Quad *)a = *(Quad *)(*(char **)(slot + 0xB0) + 0x10);
            }
        }
        f = func_00283CE0(*(int *)(slot + 0xB8));
        f = f / func_00283CE0(*(int *)(slot + 0xBC));
        func_00282D08(a, slot + 0x20, a, 1.0f - f);
        if (!func_00282948(slot + 0xB8))
            continue;
        if (*(int *)(*(char **)(slot + 0xB0) + 0x98) != 0 && *(int *)(slot + 0xC0) == 0 &&
            *(int *)(slot + 0xC4) != 0) {
            func_00282CF0(v, a, slot + 0x20);
            func_00282F20(v, v, 1.0f / 30.0f);
            *(int *)(owner + 0xB8) = *(int *)(*(char **)(slot + 0xCC) + 0x20);
            func_002A8C00(&hit, owner, 0x210000, *(float *)(slot + 0xC8), v);
            hit.kind = 5;
            hit.mode = 3;
            hit.owner = *(unsigned short *)(owner + 0xAA);
            func_002A8E20(*(char **)(slot + 0xB0), &hit);
            *(int *)(slot + 0xC0) = 1;
            func_L00_00412928(a, 10, 1);
        }
        if (func_00282948(slot + 0xA8))
            *(char **)(slot + 0xAC) = 0;
    }
}
