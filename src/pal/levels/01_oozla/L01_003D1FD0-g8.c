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
extern float level_get_water_height_pal(void);
extern float math_random_angle(void);
extern void moby_set_state(void *,int,int);
extern void moby_scale_owner_words_by_angles(void *,void *,void *,float,float,float);
extern float math_step_damped_spring_pal(float *,float *,float,float,float,float);
extern float vec_distance_xy(void *,void *);
extern void FastVecSub(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);

/* Initializes a floating object and keeps its motion above the water surface. */
void water_floater_update_pal(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    float snapshots[2][4] __attribute__((aligned(16)));
    float push[4] __attribute__((aligned(16)));
    float water_height, dist, delta;

    if (!vars) {
        STUB_printf(g_str_water_floater_debug, *(s16 *)(moby + 0xAA), *(s16 *)(moby + 0xB2));
        return;
    }
    switch (moby[0x20]) {
    case 0:
        if (level_get_water_height_pal() > 0.0f) {
            *(float *)(vars + 0x20) = math_random_angle();
            *(float *)(vars + 0x24) = math_random_angle();
            *(float *)(vars + 0x28) = 0.02f;
            qcopy(vars, moby + 0x10);
            moby_set_state(moby, 1, -1);
        }
        break;
    case 1:
        /* Retail takes two position snapshots before updating movement. */
        *(Snapshot128 *)snapshots[0] = *(Snapshot128 *)(moby + 0x10);
        *(Snapshot128 *)snapshots[1] = *(Snapshot128 *)snapshots[0];
        water_height = level_get_water_height_pal();
        moby_scale_owner_words_by_angles(moby, vars + 0x20, vars + 0x24, g_water_floater_scale,
                      g_water_floater_angle_a * 0.0003490659f,
                      g_water_floater_angle_b * 0.0003490659f);
        math_step_damped_spring_pal((float *)(moby + 0x10), (float *)(vars + 0x10), *(float *)vars,
                          g_water_floater_speed * 0.00040000002f, g_water_floater_limit, 3.0f);
        math_step_damped_spring_pal((float *)(moby + 0x14), (float *)(vars + 0x14), *(float *)(vars + 4),
                          g_water_floater_speed * 0.00040000002f, g_water_floater_limit, 3.0f);
        dist = vec_distance_xy(moby + 0x10, g_hero_position);
        if (dist < g_water_floater_push_radius &&
            *(float *)(g_hero_position + 8) < *(float *)(moby + 0x18) + 0.8f) {
            FastVecSub(push, moby + 0x10, g_hero_position);
            push[2] = 0;
            vec_scale_to_length(push, push, (g_water_floater_push_radius - dist) * 0.08f);
            FastVecAdd(moby + 0x10, moby + 0x10, push);
        }
        delta = water_height + *(float *)(vars + 0x28) - *(float *)(moby + 0x18);
        if (delta > 0.060000002f)
            delta = 0.060000002f;
        else if (delta < -0.060000002f)
            delta = -0.060000002f;
        *(float *)(moby + 0x18) += delta;
        break;
    }
}
