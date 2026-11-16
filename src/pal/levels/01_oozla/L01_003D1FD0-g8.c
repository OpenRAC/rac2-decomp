#include "include_asm.h"

#include "common.h"
typedef int Snapshot128 __attribute__((mode(TI)));
extern u8 g_str_water_floater_debug[],g_hero_position[];
extern float g_water_floater_scale __attribute__((sda));
extern float g_water_floater_angle_a __attribute__((sda));
extern float g_water_floater_angle_b __attribute__((sda));
extern float g_water_floater_speed __attribute__((sda));
extern float g_water_floater_limit __attribute__((sda));
extern float g_water_floater_push_radius __attribute__((sda));
extern void STUB_printf(void *,int,int);
extern float func_PAL_L01_003BEB40(void);
extern float math_random_angle(void);
extern void moby_set_state(void *,int,int);
extern void moby_scale_owner_words_by_angles(void *,void *,void *,float,float,float);
extern float func_PAL_L01_003D2900(float *,float *,float,float,float,float);
extern float vec_distance_xy(void *,void *);
extern void FastVecSub(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);

/* Initializes a floating object and keeps its motion above the water surface. */
void func_PAL_L01_003D29A0(u8 *a0)
{
    u8 *p = *(u8 **)(a0 + 0x68);
    float snapshots[2][4] __attribute__((aligned(16)));
    float d[4] __attribute__((aligned(16)));
    float h, dist, delta;

    if (!p) {
        STUB_printf(g_str_water_floater_debug, *(s16 *)(a0 + 0xAA), *(s16 *)(a0 + 0xB2));
        return;
    }
    switch (a0[0x20]) {
    case 0:
        if (func_PAL_L01_003BEB40() > 0.0f) {
            *(float *)(p + 0x20) = math_random_angle();
            *(float *)(p + 0x24) = math_random_angle();
            *(float *)(p + 0x28) = 0.02f;
            qcopy(p, a0 + 0x10);
            moby_set_state(a0, 1, -1);
        }
        break;
    case 1:
        /* Retail takes two position snapshots before updating movement. */
        *(Snapshot128 *)snapshots[0] = *(Snapshot128 *)(a0 + 0x10);
        *(Snapshot128 *)snapshots[1] = *(Snapshot128 *)snapshots[0];
        h = func_PAL_L01_003BEB40();
        moby_scale_owner_words_by_angles(a0, p + 0x20, p + 0x24, g_water_floater_scale,
                      g_water_floater_angle_a * 0.0003490659f,
                      g_water_floater_angle_b * 0.0003490659f);
        func_PAL_L01_003D2900((float *)(a0 + 0x10), (float *)(p + 0x10), *(float *)p,
                          g_water_floater_speed * 0.00040000002f, g_water_floater_limit, 3.0f);
        func_PAL_L01_003D2900((float *)(a0 + 0x14), (float *)(p + 0x14), *(float *)(p + 4),
                          g_water_floater_speed * 0.00040000002f, g_water_floater_limit, 3.0f);
        dist = vec_distance_xy(a0 + 0x10, g_hero_position);
        if (dist < g_water_floater_push_radius &&
            *(float *)(g_hero_position + 8) < *(float *)(a0 + 0x18) + 0.8f) {
            FastVecSub(d, a0 + 0x10, g_hero_position);
            d[2] = 0;
            vec_scale_to_length(d, d, (g_water_floater_push_radius - dist) * 0.08f);
            FastVecAdd(a0 + 0x10, a0 + 0x10, d);
        }
        delta = h + *(float *)(p + 0x28) - *(float *)(a0 + 0x18);
        if (delta > 0.060000002f)
            delta = 0.060000002f;
        else if (delta < -0.060000002f)
            delta = -0.060000002f;
        *(float *)(a0 + 0x18) += delta;
        break;
    }
}
