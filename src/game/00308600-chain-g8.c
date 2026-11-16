/* func_0030CCD0: beam chain update, the small cousin of the F4 family's chain loop. */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } Vector;
typedef struct {
    Vector start, end;
    void *target;
    float length;
    int unknown28, timer, light, fade;
    short segment;
} BeamState;
typedef struct { char pad[0x10]; Vector pos; } Thing;
typedef struct { char pad[0x10]; float height; } ThingInfo;
typedef struct { char pad[0x68]; BeamState *vars; } Actor;

extern int g_current_map_index;
extern int g_game_l00_mode;
extern BeamState g_beam_state_primary[], g_beam_state_secondary[];
typedef union { u8 b[0x2600]; s32 i[0x980]; void *ptr[0x980]; } Hero;
extern char g_hero_state[];
extern float g_chain_beam_length_scale __attribute__((sda));
extern float g_chain_wave_phase_step __attribute__((sda)), g_chain_amp_start __attribute__((sda)), g_chain_amp_end __attribute__((sda));
extern float g_chain_wave_phase __attribute__((sda)), g_chain_wave_phase_speed __attribute__((sda)), g_chain_swirl_phase __attribute__((sda));
extern float g_chain_swirl_phase_speed __attribute__((sda)), g_chain_swirl_phase_step __attribute__((sda)), g_chain_wave2_amp __attribute__((sda));
extern float g_chain_radial_scale __attribute__((sda)), g_chain_wave2_phase __attribute__((sda)), g_chain_wave2_phase_speed __attribute__((sda));
extern float g_chain_wave2_phase_step __attribute__((sda)), g_chain_jitter_min __attribute__((sda)), g_chain_jitter_max __attribute__((sda));
extern float g_chain_tip_scale __attribute__((sda));
extern Vector g_chain_beam_points[2][20], g_chain_beam_end[], g_chain_beam_deltas[];
extern float g_chain_wave_offsets[], g_chain_wave_values[];
extern char g_default_vector[] MACRO_ADDR;

extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void lerp_vector(void *, void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern float fast_vec_dist(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float math_fast_sin_or_cos_b(float);
extern float mat_fast_helper_a(float, float);
extern float FastAddRotations(float, float);
extern float fast_subtract_rotations(float, float);
extern float IntToFloat(int);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern ThingInfo *moby_get_private_value_0(void *);
extern float math_wrap_angle_to_pi(float);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern char *part_spawn_ground_effect(void *, int, float, float, unsigned int, int, int, void *, int, float);
extern float FastVecLength(void *);
extern float math_fast_sin_or_cos_a(float);
extern unsigned int beam_get_glow_color(void);

/* Moves the twenty points of the beam chain so they trail from the start toward the locked target. The chain waves about and sheds spark particles. */
void beam_update_chain_points(Actor *actor)
{
    Vector goal, dir, side, step, last, delta, tip;
    float angle;
    float len;
    float *wave_offset;
    int byte_offset;
    float dist;
    void *target;
    float previous_wave;
    int spin;
    float step_length;
    float weight;
    float wave;
    int i;
    float sway;
    void *hero_target;
    BeamState *beam = actor->vars;
    float zero;
    Vector *last_ptr;
    ThingInfo *info;
    float segments_left;

    if (g_current_map_index == 1 && g_game_l00_mode == 2)
        beam = g_beam_state_primary;
    if (g_current_map_index == 0x14 && g_game_l00_mode == 2)
        beam = g_beam_state_secondary;
    len = g_chain_beam_length_scale * 0.05f;
    g_chain_wave_phase = FastAddRotations(g_chain_wave_phase, g_chain_wave_phase_speed);
    g_chain_swirl_phase = fast_subtract_rotations(g_chain_swirl_phase, g_chain_swirl_phase_speed);
    g_chain_wave2_phase = FastAddRotations(g_chain_wave2_phase, g_chain_wave2_phase_speed);
    hero_target = 0;
    if (beam->target == 0)
        hero_target = ((Hero *)g_hero_state)->ptr[0x5C0 / 4];
    if (hero_target != 0) {
        if (beam->target == 0)
            beam->target = hero_target;
    }
    target = beam->target;
    if (target != 0) {
        info = 0;
        if (g_game_l00_mode != 2)
            info = moby_get_private_value_0(target);
        qcopy(&goal, &((Thing *)beam->target)->pos);
        if (info != 0)
            goal.f[2] += info->height;
        else
            goal.f[2] += 0.2f;
        len = fast_vec_dist(beam, &goal) * 0.05f;
    }
    beam->segment = 0x14;
    FastVecSub(&dir, &beam->end, beam);
    vec_scale_to_length(&dir, &dir, 1.0f);
    if (beam->target != 0) {
        FastVecCross(&side, &dir, g_hero_state + 0x2C0);
        math_apply_axis_rotation_to_quat(&dir, &dir, &side, 0.17453295f);
    }
    FastVecScale(&last, &dir, len);
    qcopy(g_chain_beam_points[0], beam);
    qcopy(g_chain_beam_points[1], beam);
    i = 1;
    do {
        float fi = i;
        byte_offset = i * 4;
        weight = IntToFloat(i) * 0.05f;
        wave = g_chain_amp_start + (g_chain_amp_end - g_chain_amp_start) * weight;
        wave = wave * math_fast_sin_or_cos_b(math_wrap_angle_to_pi(g_chain_wave_phase + fi * g_chain_wave_phase_step));
        wave = wave + math_random_signed_float_range(g_chain_jitter_min, g_chain_jitter_max);
        wave_offset = (float *)(byte_offset + (char *)g_chain_wave_offsets);
        previous_wave = *wave_offset;
        *wave_offset = wave;
        g_chain_beam_points[0][i].f[2] -= previous_wave;
        FastVecSub(&side, &g_chain_beam_points[0][i], &g_chain_beam_points[0][i - 1]);
        lerp_vector(&step, &side, &last, 0.85f);
        zero = 0.0f;
        step_length = FastVecLength(&step);
        if (step_length == zero) {
            qcopy(&g_chain_beam_points[0][i], &g_chain_beam_points[0][i - 1]);
        } else {
            FastVecScale(&step, &step, len / step_length);
            FastVecAdd(&g_chain_beam_points[0][i], &g_chain_beam_points[0][i - 1], &step);
            qcopy(&last, &step);
        }
        g_chain_beam_points[0][i].f[2] += wave;
        FastVecSub(&side, &g_chain_beam_points[0][i], &g_chain_beam_points[0][i - 1]);
        if (beam->target != 0) {
            FastVecSub(&tip, &goal, &g_chain_beam_points[0][i]);
            dist = FastVecLength(&tip);
            if (dist != zero) {
                if (i == 0x13) {
                    sway = 0.5f;
                    len = dist;
                } else if (i >= 0x10) {
                    sway = 0.5f;
                    segments_left = IntToFloat(0x13 - i);
                    len = dist / segments_left;
                } else {
                    sway = 0.1f;
                }
                /* Live across the next call: loop.c hoists this copy, which retail's preheader order shows. */
                last_ptr = &last;
                FastVecScale(&tip, &tip, len / dist);
                lerp_vector(last_ptr, last_ptr, &tip, sway);
            }
        }
        angle = math_wrap_angle_to_pi(g_chain_swirl_phase + (float)i * g_chain_swirl_phase_step);
        wave = g_chain_wave2_amp * math_fast_sin_or_cos_b(math_wrap_angle_to_pi(g_chain_wave2_phase + (float)i * g_chain_wave2_phase_step));
        qcopy(&g_chain_beam_points[1][i], &g_chain_beam_points[0][i]);
        wave = wave * math_fast_sin_or_cos_b(angle);
        g_chain_wave_values[i] = wave;
        g_chain_beam_points[1][i].f[2] += wave;
        wave = FastAddRotations(mat_fast_helper_a(side.f[0], side.f[1]), 1.5707965f);
        {
            float r2 = g_chain_radial_scale * math_fast_sin_or_cos_a(angle);
            delta.f[0] = math_fast_sin_or_cos_a(wave) * r2;
            delta.f[1] = math_fast_sin_or_cos_b(wave) * r2;
        }
        delta.f[2] = 0.0f;
        qcopy(&g_chain_beam_deltas[i], &delta);
        FastVecAdd(&g_chain_beam_points[1][i], &g_chain_beam_points[1][i], &delta);
        i++;
    } while (i < 0x14);
    qcopy(&beam->end, g_chain_beam_end);
    {
        float pitch = math_random_signed_float_range(0.52359885f, 1.0471977f);
        float yaw = math_random_float_range(-0.52359885f, 1.0471977f);
        FastVecScale(&tip, &dir, g_chain_tip_scale);
        math_apply_axis_rotation_to_quat(&tip, &tip, g_hero_state + 0x740, yaw);
        math_apply_axis_rotation_to_quat(&tip, &tip, g_hero_state + 0x750, pitch);
    }
    spin = math_random_int_range(1, 8);
    if (math_random_int_below(2))
        spin = -spin;
    wave = math_random_float_range(0.2f, 0.6f);
    part_spawn_ground_effect(beam, 0xF, wave * 0.3f, wave, beam_get_glow_color() | 0x7F000000, 0, spin, &tip, 0, 0.0f);
    part_spawn_ground_effect(beam, 0xF, wave * 0.15f, wave * 0.5f, 0x307F7F7F, 0, -spin, &tip, 0, 0.0f);
    spin = math_random_int_range(1, 8);
    if (math_random_int_below(2))
        spin = -spin;
    wave = math_random_float_range(0.15f, 3.0f);
    part_spawn_ground_effect(&beam->end, 0xC, wave * 0.1f, wave, beam_get_glow_color() | 0x7F000000, 0, spin, g_default_vector, 0, 0.0f);
}
