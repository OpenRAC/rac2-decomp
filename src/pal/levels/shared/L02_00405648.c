#include "include_asm.h"


#include "common.h"
extern char ref_L02_004012A0_00[] __attribute__((nosda));
extern void ref_L02_004012A0_01(void *, int, int, int, int, int, int, int, int, int, int,
                                int, float, float);
extern void ref_L02_004012A0_02(float *, const float *, const float *);
extern void ref_L02_004012A0_03(void *, void *, float);
extern void ref_L02_004012A0_04(void *, void *, int, int, int, int, float, float, float);
extern void ref_L02_004012A0_05(void *, void *, void *, float);

/* The kind at +0xAA decides the work: the second kind reports itself and leaves, every
   other kind turns the object's own basis, scales it and hands it on. */
void func_PAL_L02_00405BE0(char *a0) {
    char *s1 = a0;
    char *s2 = *(char **)(a0 + 0x68);
    float v[4];
    short kind = *(short *)(a0 + 0xAA);

    switch (kind) {
    case 0xB1B:
        break;
    case 0xB5A:
        ref_L02_004012A0_01(a0 + 0x10, 0, 0, 0, 0, 20, 45, 1, 1, 0, 0, 0, 0.3f, 20.0f);
        return;
    }
    ref_L02_004012A0_02(v, (const float *)ref_L02_004012A0_00, a0 + 0x10);
    ref_L02_004012A0_03(v, v, 1.0f);
    ref_L02_004012A0_04(a0, a0 + 0x10, 0x10001, 0, 1, 0, 0.25f, *(float *)(s2 + 0x6C), 1.0f);
    ref_L02_004012A0_05(a0, a0 + 0x10, v, 0.0f);
}

