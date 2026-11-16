#include "common.h"
typedef struct { int word[4]; } BeamDamageData __attribute__((aligned(16)));
typedef struct {
    float position[4][4];
    u32 color[4];
    float uv[4][2];
    unsigned long packet[4];
} BeamBatch __attribute__((aligned(16)));
extern float g_snivelak_muzzle_offset[4] __attribute__((sda));
extern float g_laser_beam_side_offsets[2] __attribute__((sda));
extern int g_laser_beam_texture_table[2] __attribute__((sda));
extern float g_laser_beam_uv_table[4][2] MACRO_ADDR;
extern float D_L16_001B1800_GP[4][2] SDATA(D_L16_001B1800);
extern u32 g_laser_beam_color_table[2] __attribute__((sda));
extern int g_laser_spark_count __attribute__((sda));
extern u32 g_laser_spark_color __attribute__((sda));
extern float g_laser_spark_speed_table[4] MACRO_ADDR;
extern float D_L16_001B1830_GP SDATA(D_L16_001B1830);
extern int g_snivelak_beam_texture_range[2];
extern int D_L16_001B1840_GP SDATA(D_L16_001B1840);
extern float g_snivelak_beam_size_range[2];
extern float D_L16_001B1848_GP SDATA(D_L16_001B1848);
extern float g_scene_origin_transform[4], g_aim_target_position[4];
extern BeamDamageData g_particle_template MACRO_ADDR;
extern int g_frame_l16_counter;
extern void moby_transform_joint_point(void *, int, void *), transform_vector(void *, void *, void *);
extern float turret_get_horizontal_speed(char *);
extern void FastVecSub(void *, void *, void *), FastVecAdd(void *, void *, void *);
extern void vec_fast_normalize_helper(void *, void *, float), vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *), FastVecScale(void *, void *, float);
extern void make_hit_descriptor(char *, int, int, float, BeamDamageData *);
extern int CollLine(void *, void *, int, void *, void *);
extern u32 FastTweenColor(u32, u32, float);
extern unsigned long GetEffectTextureDescriptor(int);
extern void draw_world_quad(void *, int, int);
extern int math_random_int_range(int, int), FloatToInt(float);
extern float math_random_signed_float_range(float, float), math_random_float_range(float, float);
extern void lerp_vector(void *, void *, void *, float);
/* Particle calls consume six/three GPR inputs and five/one FP inputs.
 * Both return their allocated pointer or null; this caller ignores those results. */
extern void *part_spawn_burst(void *, void *, int, int, int, int, float, float, float, float, float);
extern void *part_spawn_trail_2(void *, void *, int, float);
extern void vec_random_direction(void *, float, float);

/* Draws the boss's laser beam from its body to its target, hurts whatever it hits and sprays sparks along the beam. */
void snivelak_draw_laser_beam(u8 *moby)
{
    BeamBatch batch[2];
    float bone[16] __attribute__((aligned(16)));
    float side[4] __attribute__((aligned(16)));
    float camera[4] __attribute__((aligned(16)));
    float ray[4] __attribute__((aligned(16)));
    float start[4] __attribute__((aligned(16)));
    float end[4] __attribute__((aligned(16)));
    float target[4] __attribute__((aligned(16)));
    char effect[48] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float sample[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(moby + 0x68);
    u8 *object;
    int j, k, texture, seed;
    float size, speed;
    float *pos;
    /* These named values are what retail's slot order measures: gcse's reaching registers
       take spill slots in hash-bucket order, with 157 buckets (312 insns when gcse starts)
       and the counter's pseudo at 145 or above. The block around the counter's loop serves
       the same purpose. Removing or adding one moves the spill slots. */
    int joint = 2;
    float drop = -0.1f;
    int layers = 0x90001;
    int ignore = 0;
    int lowerRow = 2;
    int drawFirst = 0;
    int drawCount = 1;
    void *body;
    float *muzzle;
    float *eye;
    BeamDamageData *damage;
    int shift = 24;
    float length;

    body = *(void **)(state + 0x1f0);
    moby_transform_joint_point(body, joint, bone);
    muzzle = g_snivelak_muzzle_offset;
    transform_vector(start, muzzle, bone);
    object = *(u8 **)(state + 0x24c);
    if (object) {
        qcopy(target, (object + 0x10));
        target[2] = turret_get_horizontal_speed((char *)object);
    } else qcopy(target, (state + 0x210));
    FastVecSub(end, moby + 0x10, target);
    end[2] = drop;
    length = *(float *)(state + 0x250);
    vec_fast_normalize_helper(end, end, length);
    FastVecAdd(end, end, target);
    damage = &g_particle_template;
    make_hit_descriptor(effect, (int)moby, layers, (float)state[0x36], damage);
    if (CollLine(start, end, ignore, moby, effect))
        qcopy_nc(end, g_aim_target_position);
    eye = g_scene_origin_transform;
    FastVecSub(camera, eye, start);
    FastVecSub(ray, end, start);
    FastVecCross(side, ray, camera);
    vec_scale_to_length(side, side, 1.0f);
    {
        int i;
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 4; j++) {
                batch[i].color[j] = FastTweenColor(g_laser_beam_color_table[i] & 0xff000000,
                    g_laser_beam_color_table[i], *(float *)(state + 0x254));
                batch[i].uv[j][0] = D_L16_001B1800_GP[j][0];
                batch[i].uv[j][1] = g_laser_beam_uv_table[j][1];
                pos = batch[i].position[j];
                if (j & 1)
                    FastVecScale(pos, side, g_laser_beam_side_offsets[i]);
                else FastVecScale(pos, side, -g_laser_beam_side_offsets[i]);
                if (j < lowerRow) FastVecAdd(pos, pos, start);
                else FastVecAdd(pos, pos, end);
                pos[3] = 1.0f;
            }
            batch[i].packet[1] = GetEffectTextureDescriptor(g_laser_beam_texture_table[i]);
            batch[i].packet[0] = 0;
            batch[i].packet[2] = 0xff9000000260UL;
            batch[i].packet[3] = 0x8000000048UL;
        }
    }
    draw_world_quad(&batch[0], drawFirst, drawCount);
    draw_world_quad(&batch[1], drawFirst, drawCount);
    if (*(int *)(state + 0x258) != g_frame_l16_counter) {
        *(int *)(state + 0x258) = g_frame_l16_counter;
        FastVecSub(delta, end, start);
        for (k = 0; k < g_laser_spark_count; k++) {
            texture = math_random_int_range(D_L16_001B1840_GP, g_snivelak_beam_texture_range[1]);
            seed = FloatToInt(math_random_signed_float_range(1.0f, 2.0f));
            size = math_random_float_range(D_L16_001B1848_GP, g_snivelak_beam_size_range[1]) * 210000.0f;
            speed = math_random_float_range(g_laser_spark_speed_table[2], g_laser_spark_speed_table[3]);
            vec_scale_to_length(velocity, delta, speed * 0.016666668f);
            lerp_vector(sample, end, start, math_random_float_range(0.0f, 1.0f));
            part_spawn_burst(sample, velocity, texture, (int)g_laser_spark_color >> shift,
                g_laser_spark_color & 0xffffff, seed, size,
                500.0f, 1.0f, 0.0f, 1.0f);
            size = math_random_float_range(10.0f, 20.0f);
            part_spawn_trail_2(sample, velocity, texture, size * 0.00027777778f);
            vec_random_direction(velocity, D_L16_001B1830_GP * 0.016666668f,
                g_laser_spark_speed_table[1] * 0.016666668f);
            velocity[2] += math_random_float_range(g_laser_spark_speed_table[2], g_laser_spark_speed_table[3]) * 0.016666668f;
            part_spawn_trail_2(end, velocity, texture, 0.0040555559f);
        }
    }
}
