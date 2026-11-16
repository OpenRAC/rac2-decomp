/* func_PAL_L16_003ADB58, the PAL copy of func_L16_003AA3F0: the same C, at 50 Hz. */
#include "common.h"
typedef struct { float x, y, z, w; } __attribute__((aligned(16))) Vector;
typedef Vector Row[4];
typedef struct {
    int index;
    char pad4[0xe];
    short lifetime;
    int pad14;
    u8 selected[8];
    Vector positions[32], velocities[32];
    Vector branches[4][4], branchVelocities[4][4];
    int duration;
    char pad624[0x2c];
    float rotation[3];
} Beam;
typedef struct {
    char pad0[0x10];
    Vector position;
    char pad20[0x48];
    Beam *vars;
} BeamMoby;
extern int g_current_map_index;
extern int g_beam_lifetime_min __attribute__((sda)), g_vendor_beam_lifetime_max __attribute__((sda));
extern float g_beam_spark_spread_angle __attribute__((sda)), g_beam_velocity_spread __attribute__((sda)), g_beam_jitter_w __attribute__((sda));
extern int g_beam_trail_param_a __attribute__((sda)), g_beam_trail_param_b __attribute__((sda));
extern int g_beam_color_a __attribute__((sda)), g_beam_l16_color_b __attribute__((sda));
extern char *g_beam_definition_table __attribute__((sda));
extern float g_scene_origin_transform[4];
extern int math_random_int_range(int,int);
extern float math_random_float_range(float,float);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern void vec_random_direction(void *,float,float);
extern void vec_clear_128(void *);
extern void FastVecAdd(void *,void *,void *);
extern void FastVecScale(void *,void *,float);
extern float vec_distance_xy(void *,void *);
extern float math_random_angle(void);
extern void euler_to_matrix(void *,void *);
extern void transform_vector(void *,void *,void *);
extern int math_random_int_below(int);
extern void *part_spawn_trail(void *,void *,void *,int,int,int,int,int,int);

/* The second particle loop draws this coin and never reads it. The test still has to be there at
   gcse: it splits the block, so the call's &jitter takes the reaching register as in the first loop.
   Storing the value it already holds, not a constant, is one RTL insn fewer, which sets gcse's table
   to the 207 buckets that give the spilled addresses retail's stack slots. */
static inline void flipCoin(int *heads)
{
    int coin = math_random_int_below(2);
    if (coin)
        *heads = coin;
    else
        *heads = 0;
}

/* Builds the beam's random zigzag path and its four side branches, and spawns trail particles along it (PAL: 50 Hz timings). */
void start_vendor_beam_pulse_pal(BeamMoby *object)
{
    Beam *beam = object->vars;
    Vector positions[32], velocities[32], scratch, jitter;
    Vector transform[4];
    const float frame_time = 0.020000001f;
    float half;
    float time_step;
    float unit;
    float spread;
    int i, smooth_index, branch_index, particle_index, j, k;
    int selected;
    object->position.w = 1.0f;
    beam->lifetime = math_random_int_range((((int)(g_beam_lifetime_min) * 5 + 2) / 6),(((int)(g_vendor_beam_lifetime_max) * 5 + 2) / 6));
    beam->duration = beam->lifetime;
    if (g_current_map_index == 0xd5 || g_current_map_index == 16)
        spread = math_random_float_range(40.0f, 45.0f);
    else spread = math_random_float_range(4.0f, 8.0f);
    half = 0.5f;
    time_step = frame_time;
    unit = 1.0f;
    for (i = 0; i < 32; i++) {
        float height = IntToFloat(i);
        float last = IntToFloat(31);
        height = height / last;
        height = (half - height) * spread;
        if ((unsigned)(i - 3) >= 26) {
            vec_clear_128(&positions[i]);
            vec_clear_128(&velocities[i]);
        } else {
            vec_random_direction(&positions[i], 0.0f, g_beam_spark_spread_angle);
            if (g_current_map_index == 16 || g_current_map_index == 0xd5)
                vec_random_direction(&velocities[i], 0.0f, 0.24000001f);
            else vec_random_direction(&velocities[i], 0.0f, g_beam_velocity_spread * time_step);
        }
        {
            float y = positions[i].y;
            positions[i].w = unit;
            positions[i].y = y + height;
        }
    }
    for (smooth_index = 0; smooth_index < 32; smooth_index++) {
        if (smooth_index == 0 || smooth_index == 31) {
            qcopy(&beam->positions[smooth_index], &positions[smooth_index]);
            qcopy(&beam->velocities[smooth_index], &velocities[smooth_index]);
        } else {
            FastVecAdd(&scratch, &positions[smooth_index-1], &positions[smooth_index]);
            FastVecAdd(&scratch, &scratch, &positions[smooth_index+1]);
            FastVecScale(&beam->positions[smooth_index], &scratch, 0.333f);
            FastVecAdd(&scratch, &velocities[smooth_index-1], &velocities[smooth_index]);
            FastVecAdd(&scratch, &scratch, &velocities[smooth_index+1]);
            FastVecScale(&beam->velocities[smooth_index], &scratch, 0.333f);
        }
    }
    for (branch_index = 0; branch_index < 4; branch_index++) {
        if (g_current_map_index == 0xd5 || g_current_map_index == 16)
            vec_random_direction(&scratch, 1.0f, 1.0f);
        else vec_random_direction(&scratch, g_beam_spark_spread_angle, g_beam_spark_spread_angle);
        selected = FloatToInt(math_random_float_range((float)branch_index * 6.0f, (float)(branch_index + 1) * 6.0f)) + 4;
        beam->selected[branch_index] = selected;
        qcopy(&beam->branches[0][branch_index], &beam->positions[selected]);
        qcopy(&beam->branchVelocities[0][branch_index], &beam->velocities[selected]);
        {
            int vel_offset = (int)&((Beam *)0)->branchVelocities[0][branch_index];
            int cur_offset = (int)&((Beam *)0)->branches[0][branch_index];
            for (j = 1; j < 4; j++) {
                Beam *column = (Beam *)(branch_index * 16);
                column = (Beam *)((int)column + (int)beam);
                vec_random_direction(&jitter, 0.1f, 0.1f);
                if (g_current_map_index == 0xd5 || g_current_map_index == 16)
                    vec_random_direction(((Row *)((char *)beam + vel_offset))[j], 0.0f, 0.24000001f);
                else vec_random_direction(((Row *)((char *)beam + vel_offset))[j], 0.0f, g_beam_velocity_spread * frame_time);
                FastVecAdd(((Row *)((char *)beam + cur_offset))[j], column->branches[j-1], &scratch);
                FastVecAdd(((Row *)((char *)beam + cur_offset))[j], ((Row *)((char *)beam + cur_offset))[j], &jitter);
            }
        }
    }
    if (vec_distance_xy(&object->position, g_scene_origin_transform) >= 4.0f) {
        char *definition = (char *)(beam->index * 128 + (int)g_beam_definition_table);
        beam->rotation[2] = *(float *)(definition + 0x78);
        beam->rotation[1] = *(float *)(definition + 0x74);
        beam->rotation[0] = math_random_angle();
        euler_to_matrix(transform, beam->rotation);
        qcopy(&transform[3], &object->position);
        for (particle_index = 0; particle_index < 32; particle_index += 8) {
            int color, duration;
            transform_vector(&scratch, &beam->positions[particle_index], transform);
            qcopy(&jitter, &beam->velocities[particle_index]);
            jitter.w = g_beam_jitter_w;
            color = math_random_int_below(2) ? g_beam_color_a : g_beam_l16_color_b;
            duration = math_random_int_below(10);
            part_spawn_trail(&scratch, &jitter, &jitter, g_beam_trail_param_a, g_beam_trail_param_b, particle_index >> 1, 15, (((int)(duration + 20) * 5 + 2) / 6), color);
        }
        for (k = 0; k < 2; k++) {
            int duration, heads;
            transform_vector(&scratch, &beam->branches[3][k], transform);
            qcopy(&jitter, &beam->branchVelocities[3][k]);
            jitter.w = g_beam_jitter_w;
            flipCoin(&heads);
            duration = math_random_int_below(10);
            part_spawn_trail(&scratch, &jitter, &jitter, g_beam_trail_param_a, g_beam_trail_param_b, beam->selected[k] >> 1, 15, (((int)(duration + 20) * 5 + 2) / 6), g_beam_l16_color_b);
        }
    }
}
