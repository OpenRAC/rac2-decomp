#include "include_asm.h"

#include "common.h"
extern void moby_set_state(void *, int, int);
extern void gfx_add_draw_callback_first(void (*)(void *), void *);
extern void spark_burst_draw_glows(void *);
extern float ApproachValue(void *, float, float);
extern void *SpawnExplosion_pal(void *, int, float, int, int, int, int, int, int, int, int, int, int, float);
extern void set_moby_color(void *, int, int, int);
extern void moby_mark_spawned(void *);
extern void moby_apply_fade_color_to_linked(void *);
extern int moby_transform_point_and_rotation_by_parent(void *, void *, void *, void *, void *, void *);
extern float g_spark_burst_fade_rate SDATA(D_L04_001B1394);
extern float g_spark_burst_explosion_a SDATA(D_L04_001B1398);
extern int g_spark_burst_explosion_b SDATA(D_L04_001B139C);
extern int g_spark_burst_explosion_c SDATA(D_L04_001B13A0);
extern int g_spark_burst_explosion_d SDATA(D_L04_001B13A4);
extern int g_spark_burst_explosion_e SDATA(D_L04_001B13A8);
extern int g_spark_burst_explosion_f SDATA(D_L04_001B13AC);
extern int g_spark_burst_explosion_g SDATA(D_L04_001B13B0);
extern int g_spark_burst_explosion_h SDATA(D_L04_001B13B4);
extern int g_spark_burst_explosion_i SDATA(D_L04_001B13B8);
extern int g_spark_burst_explosion_j SDATA(D_L04_001B13BC);

void spark_l04_burst_update_pal(unsigned char *m)
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
            SpawnExplosion_pal(p + 0x20, 0, g_spark_burst_explosion_a, g_spark_burst_explosion_b, g_spark_burst_explosion_c, g_spark_burst_explosion_d, g_spark_burst_explosion_e, g_spark_burst_explosion_f, g_spark_burst_explosion_g, g_spark_burst_explosion_h, g_spark_burst_explosion_i, g_spark_burst_explosion_j, *(int *)(p + 0x44), 20.0f);
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
        ApproachValue(p + 0x58, 1.0f, g_spark_burst_fade_rate * 0.020000001f);
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
