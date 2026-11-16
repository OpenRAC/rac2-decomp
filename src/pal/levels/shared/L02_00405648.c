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
void moby_update_effect_by_class_pal(char *moby) {
    char *moby_ref = moby;
    char *vars = *(char **)(moby + 0x68);
    float scaled_vec[4];
    short kind = *(short *)(moby + 0xAA);

    switch (kind) {
    case 0xB1B:
        break;
    case 0xB5A:
        ref_L02_004012A0_01(moby + 0x10, 0, 0, 0, 0, 20, 45, 1, 1, 0, 0, 0, 0.3f, 20.0f);
        return;
    }
    ref_L02_004012A0_02(scaled_vec, (const float *)ref_L02_004012A0_00, moby + 0x10);
    ref_L02_004012A0_03(scaled_vec, scaled_vec, 1.0f);
    ref_L02_004012A0_04(moby, moby + 0x10, 0x10001, 0, 1, 0, 0.25f, *(float *)(vars + 0x6C), 1.0f);
    ref_L02_004012A0_05(moby, moby + 0x10, scaled_vec, 0.0f);
}

