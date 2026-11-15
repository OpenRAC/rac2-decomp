#include "include_asm.h"

#include "common.h"
extern void moby_set_state(void *, int, int);
extern void gfx_add_draw_callback_first(void (*)(void *), void *);
extern void spark_burst_draw_glows(void *);
extern float ApproachValue(void *, float, float);
extern void *func_PAL_L00_003FB330(void *, int, float, int, int, int, int, int, int, int, int, int, int, float);
extern void set_moby_color(void *, int, int, int);
extern void moby_mark_spawned(void *);
extern void moby_apply_fade_color_to_linked(void *);
extern int moby_transform_point_and_rotation_by_parent(void *, void *, void *, void *, void *, void *);
extern float D_L04_001B1394 SDATA(D_L04_001B1394);
extern float D_L04_001B1398 SDATA(D_L04_001B1398);
extern int D_L04_001B139C SDATA(D_L04_001B139C);
extern int D_L04_001B13A0 SDATA(D_L04_001B13A0);
extern int D_L04_001B13A4 SDATA(D_L04_001B13A4);
extern int D_L04_001B13A8 SDATA(D_L04_001B13A8);
extern int D_L04_001B13AC SDATA(D_L04_001B13AC);
extern int D_L04_001B13B0 SDATA(D_L04_001B13B0);
extern int D_L04_001B13B4 SDATA(D_L04_001B13B4);
extern int D_L04_001B13B8 SDATA(D_L04_001B13B8);
extern int D_L04_001B13BC SDATA(D_L04_001B13BC);

void func_PAL_L04_004410A8(unsigned char *m)
{
    float temporary[4];
    unsigned char *p = *(unsigned char **)(m + 0x68);
    switch (m[0x20]) {
    case 0:
        moby_set_state(m, 1, -1);
        break;
    case 1:
        gfx_add_draw_callback_first(spark_burst_draw_glows, m);
        ApproachValue(p + 0x4c, 1.0f, *(float *)(p + 0x5c));
        if (*(float *)(p + 0x4c) >= 1.0f) {
            moby_set_state(m, 2, -1);
            func_PAL_L00_003FB330(p + 0x20, 0, D_L04_001B1398, D_L04_001B139C, D_L04_001B13A0, D_L04_001B13A4, D_L04_001B13A8, D_L04_001B13AC, D_L04_001B13B0, D_L04_001B13B4, D_L04_001B13B8, D_L04_001B13BC, *(int *)(p + 0x44), 20.0f);
        }
        break;
    case 2:
        if (!(*(float *)(p + 0x58) < 1.0f)) {
            *(unsigned short *)(*(unsigned char **)(p + 0x48) + 0x34) = *(unsigned short *)(p + 0x50);
            set_moby_color(*(void **)(p + 0x48), p[0x54], p[0x55], p[0x56]);
            moby_mark_spawned(m);
            return;
        }
        moby_apply_fade_color_to_linked(m);
        ApproachValue(p + 0x58, 1.0f, D_L04_001B1394 * 0.020000001f);
        break;
    }
    if (*(int *)(p + 0x40))
        moby_transform_point_and_rotation_by_parent(m, *(void **)(p + 0x40), p, temporary, p, temporary);
    if (*(int *)(p + 0x44)) {
        unsigned char *other = *(unsigned char **)(p + 0x48);
        moby_transform_point_and_rotation_by_parent(other, *(void **)(p + 0x44), other + 0x10, other + 0xf0, other + 0x10, other + 0xf0);
        qcopy(p + 0x20, other + 0x10);
    }
}
