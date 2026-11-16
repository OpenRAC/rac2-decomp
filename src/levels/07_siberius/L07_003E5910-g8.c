#include "common.h"

typedef union { u8 b[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; } Hero;

typedef struct {
    u8 pad000[0x1C8];
    f32 cam[9];
    f32 f1EC;
    u8 pad1F0[0x220 - 0x1F0];
    f32 home[4];
    u8 pad230[0x260 - 0x230];
    u8 *target;
} Vars_L07_003E5910;

typedef struct {
    u8 pad00[0x10];
    f32 pos[4];
    u8 pad20[0x68 - 0x20];
    Vars_L07_003E5910 *vars;
    u8 pad6C[0xC0 - 0x6C];
    f32 rot[4];
} Moby_L07_003E5910;

extern char g_hero_state[];
extern f32 g_group_entity_accel_step __attribute__((sda));
extern f32 g_group_entity_speed_limit __attribute__((sda));
extern f32 g_tracked_height_offset __attribute__((sda));
extern void FastVecAdd(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern float coll_probe_ground_height_below(void *, int, float);
extern void math_approach_target_with_braking(void *, float, float, float, float);
extern int moby_turn_toward_target_and_step(void *, float *, float);

/* Follow the camera height between the moby's home and the hero, never under the floor. */
float entity_move_to_tracked_height(Moby_L07_003E5910 *moby, float *goal_pos, float turn_rate)
{
    f32 home_pos[4] __attribute__((aligned(16)));
    Vars_L07_003E5910 *vars = moby->vars;
    f32 lo, hi, h, floor;

    if (vars->target != 0) {
        matrix_mul_vec3(home_pos, vars->home, moby->rot);
        FastVecAdd(home_pos, home_pos, vars->target + 0x10);
    } else {
        qcopy(home_pos, vars->home);
    }
    lo = home_pos[2] - 2.0f;
    hi = lo + 5.0f;
    h = ((Hero *)g_hero_state)->f[0x2D8 / 4] + g_tracked_height_offset;
    if (hi < h) h = hi;
    else if (h < lo) h = lo;
    floor = coll_probe_ground_height_below(moby->pos, 0, 0.5f) + g_tracked_height_offset;
    if (h < floor) h = floor;
    math_approach_target_with_braking(vars->cam, h - moby->pos[2], g_group_entity_accel_step * 0.000277777785f, g_group_entity_accel_step * 0.000277777785f,
                  g_group_entity_speed_limit * 0.0166666675f);
    moby_turn_toward_target_and_step(moby, goal_pos, turn_rate);
    return vars->f1EC;
}
