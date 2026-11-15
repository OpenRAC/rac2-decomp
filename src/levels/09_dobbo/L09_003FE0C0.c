#include "common.h"

extern int func_00283DB8(void *, float);
extern float func_00282E80(void *, void *);
extern void func_00282CF0(float *, const float *, const float *);
extern float func_00282E20(void *);
extern float func_00283248(float, float);
extern float func_00283BE0(float, float);
extern int func_00277F48(void *, int, void *, void *, float);
extern void func_0029FC20(char *, int, void *);
extern void func_L00_002E6EF8(void (*)(void *), void *);
extern void func_L09_003FD7D0(void *);
extern unsigned char *D_L09_001C3EC0[];

/* Unit of its own for -fno-gcse: with gcse, cprop carries the copy's destination into the
   ray call's argument and keeps it in a saved register (548 bytes).

   When the object is within twice its 0x32 range of the sub-object's 0x140 point: refreshes
   the sub-object's 0x340 block, aims its 0x278/0x3DC and 0x274/0x3E0 angles along the
   0x370 to 0x390 direction, copies 0x390 to 0x330, optionally registers func_L09_003FD7D0
   when the 1.4 * 0x434 sphere test hits, and records in 0x3AC/0x44C the last hit whose
   type is 0xCB, 0x76C or 0xEB0. Returns whether it was in range. */
int func_L09_003FE0C0(unsigned char *a0, int a1) {
    unsigned char *s1 = *(unsigned char **)(a0 + 0x68);
    float v[8] __attribute__((aligned(16)));
    int done = 0;
    int n;
    int i;
    unsigned char *e;

    if (vec_distance_xy(a0 + 0x10, s1 + 0x140) <
        (float)*(short *)(a0 + 0x32) * 2.0f) {
        unsigned char *blk;
        unsigned char *copy;
        float x;
        float y;
        float r;

        func_0029FC20((char *)a0, 1, s1 + 0x340);
        done = 1;
        blk = s1 + 0x390;
        FastVecSub(v, (float *)blk, (float *)(s1 + 0x370));
        x = func_00283248(v[0], v[1]);
        y = -func_00283248(vec_length_xy(v), v[2]);
        r = fast_subtract_rotations(x, *(float *)(a0 + 0xF8));
        *(float *)(s1 + 0x278) = r;
        *(float *)(s1 + 0x3DC) = r;
        r = fast_subtract_rotations(y, *(float *)(a0 + 0xF4));
        *(float *)(s1 + 0x274) = r;
        *(float *)(s1 + 0x3E0) = r;
        qcopy(s1 + 0x330, blk);
        copy = s1 + 0x330;
        if (a1 != 0) {
            qcopy(v + 4, copy);
            v[7] = *(float *)(s1 + 0x434) * 1.4f;
            if (func_00283DB8(v + 4, (float)*(short *)(a0 + 0x32)) != -1) {
                func_L00_002E6EF8(func_L09_003FD7D0, a0);
            }
        }
        n = func_00277F48(copy, 0, 0, 0, *(float *)(s1 + 0x434) * 0.9f);
        if (n > 0) {
            for (i = 0; i < n; i++) {
                if (D_L09_001C3EC0[i] != 0) {
                    if (*(short *)(D_L09_001C3EC0[i] + 0xAA) == 0xCB ||
                        *(short *)(D_L09_001C3EC0[i] + 0xAA) == 0x76C ||
                        *(short *)(D_L09_001C3EC0[i] + 0xAA) == 0xEB0) {
                        e = D_L09_001C3EC0[i];
                        *(unsigned char **)(s1 + 0x3AC) = e;
                        *(int *)(s1 + 0x44C) = *(short *)(e + 0xAA);
                    }
                }
            }
        }
        if (a1 != 0) {
            *(int *)(s1 + 0x42C) |= 2;
        }
    }
    return done;
}
