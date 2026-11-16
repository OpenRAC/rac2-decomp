/* func_PAL_L05_004495C8, the PAL copy of func_L05_004432E0: the same C. */
#include "common.h"

/* func_PAL_L05_004495C8 needs -g -frac2-qcopy -frac2-qcopy-barrier besides -G8, so it has a unit
   of its own (config/cflags.txt). */

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector_L05_004432E0;

extern char *g_ship_encounter_table, *g_feltzin_target_mobys;
extern int g_current_map_index;
/* Retail splits this address: its lui fills a branch delay slot on its own. */
extern char *g_chase_target __attribute__((nosda));
extern char *g_feltzin_enemy_table __attribute__((sda));
/* The output vector. As an incomplete sda array its address stays one `la` (an adjacent
   lui/addiu pair), which reorg does not copy into the early exits' delay slots. */
extern char g_ship_saved_position[] __attribute__((sda));
extern float g_cam_chase_goal_rate __attribute__((sda));
extern float g_cam_goal_rate_normal __attribute__((sda)), g_cam_goal_rate_alt __attribute__((sda));
extern float g_cam_chase_spring_rate_a __attribute__((sda)), g_cam_chase_spring_rate_b __attribute__((sda));
extern float g_cam_rise_rate_end __attribute__((sda)), g_cam_rise_rate_start __attribute__((sda));
extern float g_cam_side_high __attribute__((sda)), g_cam_side_low __attribute__((sda));
extern float g_cam_roll_amount_scale __attribute__((sda)), g_cam_climb_rate_end_a __attribute__((sda));
extern float g_cam_climb_rate_end_b __attribute__((sda)), g_cam_climb_rate_start __attribute__((sda));
extern float g_ship_forward_offset __attribute__((sda));
extern int hero_get_state_value_b(void);
extern float math_step_spring_damper_clamped(float *velocity, float current, float goal, float a, float b, float c);
extern float IntToFloat(int);
extern float math_fast_sin_or_cos_b(float);
extern float FastVecLength(void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);

#define FRAME_TIME 0.020000001f /* 1/60 s */
#define DEG_TO_RAD 0.017453294f

static inline float Lerp_L05_004432E0(float from, float to, float t)
{
    return from + (to - from) * t;
}

/* Moves the camera position at camera+0x30 along its moby's +0xC0 direction by the moby
   state's speed, which outside level 20 first approaches a goal (func_002702C8). Level 20 adds
   a height and a side step interpolated from the record's +0x50 block; level 15 adds an
   interpolated climb (written per arm, so jump2 cross-jumps the common tail) and clamps the
   height to 400..650. A sway along camera+0x10 driven by the record's +0xD4 block follows, then
   the [5, 1000] box clamp and a pull back towards entry `index` of D_L05_001B2614. The frame's
   motion is accumulated at record+0x30; the position is copied to D_L05_001B3600. */
void cam_update_chase_position_pal(char *camera)
{
    Vector_L05_004432E0 motion;
    Vector_L05_004432E0 delta;
    char *record = *(char **)(camera + 0x70);
    char *moby = g_feltzin_target_mobys
        + (*(int *)(*(char **)(g_ship_encounter_table + *(short *)(camera + 0x84) * 32 + 0x1C) + 0x20) << 8);
    char *state = *(char **)(moby + 0x68);

    if (g_current_map_index != 20) {
        float goal;
        if (*(int *)(state + 0x34)) {
            goal = (hero_get_state_value_b() ? g_cam_goal_rate_alt : g_cam_goal_rate_normal) * FRAME_TIME;
            *(float *)(state + 0x38) = math_step_spring_damper_clamped((float *)(state + 0x3C),
                *(float *)(state + 0x38), goal, g_cam_chase_spring_rate_a, 0.2f, 0.0f);
        } else {
            goal = g_cam_chase_goal_rate * FRAME_TIME;
            *(float *)(state + 0x38) = math_step_spring_damper_clamped((float *)(state + 0x3C),
                *(float *)(state + 0x38), goal, g_cam_chase_spring_rate_b, 0.2f, 0.0f);
        }
    }
    FastVecScale(&motion, moby + 0xC0, *(float *)(state + 0x38));
    FastVecAdd(camera + 0x30, camera + 0x30, &motion);
    qzero_nc(record + 0x30);

    if (g_current_map_index == 20) {
        char *input = *(char **)(camera + 0x70) + 0x50;
        float t = -*(float *)(input + 0x64) / (*(float *)(input + 0x74) * DEG_TO_RAD);
        float rise = (g_cam_rise_rate_start + (g_cam_rise_rate_end - g_cam_rise_rate_start) * t) * FRAME_TIME;
        float side_low = g_cam_side_low, side_high = g_cam_side_high;
        float side;
        *(float *)(camera + 0x38) += rise;
        *(float *)(record + 0x38) = rise;
        t = *(float *)(input + 0x68) / (*(float *)(input + 0x78) * DEG_TO_RAD);
        side = (side_low + (side_high - side_low) * t) * FRAME_TIME;
        FastVecScale(&delta, camera + 0x10, side);
        FastVecAdd(camera + 0x30, camera + 0x30, &delta);
        FastVecAdd(record + 0x30, record + 0x30, &delta);
    }

    if (g_current_map_index == 15) {
        float old_height = *(float *)(camera + 0x38);
        float t = *(float *)(record + 0x40);
        float climb;
        if (hero_get_state_value_b())
            climb = Lerp_L05_004432E0(g_cam_climb_rate_start, g_cam_climb_rate_end_b, t) * FRAME_TIME;
        else
            climb = Lerp_L05_004432E0(g_cam_climb_rate_start, g_cam_climb_rate_end_a, t) * FRAME_TIME;
        *(float *)(camera + 0x38) += climb;
        if (*(float *)(camera + 0x38) < 400.0f)
            *(float *)(camera + 0x38) = 400.0f;
        else if (*(float *)(camera + 0x38) > 650.0f)
            *(float *)(camera + 0x38) = 650.0f;
        *(float *)(record + 0x38) = *(float *)(camera + 0x38) - old_height;
    }

    {
        char *roll = *(char **)(camera + 0x70) + 0xD4;
        if (*(short *)(roll + 4)) {
            float amount = IntToFloat(*(short *)(roll + 6));
            amount = g_cam_roll_amount_scale * math_fast_sin_or_cos_b(amount * *(float *)(roll + 8) * 3.1415927f);
            if (*(short *)(roll + 4) == 1)
                amount = -amount;
            FastVecScale(&delta, camera + 0x10, amount);
            FastVecAdd(camera + 0x30, camera + 0x30, &delta);
            FastVecAdd(record + 0x30, record + 0x30, &delta);
        }
    }

    if (*(float *)(camera + 0x30) < 5.0f) *(float *)(camera + 0x30) = 5.0f;
    if (*(float *)(camera + 0x34) < 5.0f) *(float *)(camera + 0x34) = 5.0f;
    if (*(float *)(camera + 0x38) < 5.0f) *(float *)(camera + 0x38) = 5.0f;
    if (*(float *)(camera + 0x30) > 1000.0f) *(float *)(camera + 0x30) = 1000.0f;
    if (*(float *)(camera + 0x34) > 1000.0f) *(float *)(camera + 0x34) = 1000.0f;
    if (*(float *)(camera + 0x38) > 1000.0f) *(float *)(camera + 0x38) = 1000.0f;

    if (!hero_get_state_value_b() && g_chase_target) {
        int index = **(int **)(g_chase_target + 0x68);
        if (index >= 0) {
            char *sphere = g_feltzin_enemy_table + index * 128;
            float radius = FastVecLength(sphere) - g_ship_forward_offset;
            float distance;
            FastVecSub(&delta, sphere + 0x30, camera + 0x30);
            distance = FastVecLength(&delta);
            if (radius < distance) {
                vec_scale_to_length(&delta, &delta, distance - radius);
                FastVecAdd(camera + 0x30, camera + 0x30, &delta);
            }
        }
    }
    *(Quad *)g_ship_saved_position = *(Quad *)(camera + 0x30);
}
