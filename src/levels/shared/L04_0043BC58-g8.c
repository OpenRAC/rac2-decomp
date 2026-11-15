#include "common.h"
extern void moby_set_state(void *, int, int);
extern void gfx_add_draw_callback_first(void (*)(void *), void *);
extern void spark_burst_draw_glows(void *);
extern float ApproachValue(void *, float, float);
extern void *SpawnExplosion(void *, int, float, int, int, int, int, int, int, int, int, int, int, float);
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
/* Updates a spark burst: waits, grows along its path with sparkles, then explodes and fades out. */
void spark_l04_burst_update(unsigned char *moby)
{
    float temporary[4];
    unsigned char *vars = *(unsigned char **)(moby + 0x68);
    switch (moby[0x20]) {
    case 0:
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        gfx_add_draw_callback_first(spark_burst_draw_glows, moby);
        ApproachValue(vars + 0x4c, 1.0f, *(float *)(vars + 0x5c));
        if (*(float *)(vars + 0x4c) >= 1.0f) {
            moby_set_state(moby, 2, -1);
            SpawnExplosion(vars + 0x20, 0, D_L04_001B1398, D_L04_001B139C, D_L04_001B13A0, D_L04_001B13A4, D_L04_001B13A8, D_L04_001B13AC, D_L04_001B13B0, D_L04_001B13B4, D_L04_001B13B8, D_L04_001B13BC, *(int *)(vars + 0x44), 20.0f);
        }
        break;
    case 2:
        if (!(*(float *)(vars + 0x58) < 1.0f)) {
            *(unsigned short *)(*(unsigned char **)(vars + 0x48) + 0x34) = *(unsigned short *)(vars + 0x50);
            set_moby_color(*(void **)(vars + 0x48), vars[0x54], vars[0x55], vars[0x56]);
            moby_mark_spawned(moby);
            return;
        }
        moby_apply_fade_color_to_linked(moby);
        ApproachValue(vars + 0x58, 1.0f, D_L04_001B1394 * 0.016666668f);
        break;
    }
    if (*(int *)(vars + 0x40))
        moby_transform_point_and_rotation_by_parent(moby, *(void **)(vars + 0x40), vars, temporary, vars, temporary);
    if (*(int *)(vars + 0x44)) {
        unsigned char *other = *(unsigned char **)(vars + 0x48);
        moby_transform_point_and_rotation_by_parent(other, *(void **)(vars + 0x44), other + 0x10, other + 0xf0, other + 0x10, other + 0xf0);
        qcopy(vars + 0x20, other + 0x10);
    }
}
