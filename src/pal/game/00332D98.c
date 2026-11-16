#include "include_asm.h"


#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern f32 math_random_signed_float_range(f32 low, f32 high);
extern f32 g_default_effect_vector[] __attribute__((sda));
typedef union { TI128 quad; float v[4]; } EffectVector;
extern unsigned char *g_particle_texture_table[];
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int math_random_int_below(int);
extern unsigned char *part_spawn_gravity_fade(void *, void *, int, unsigned int, int, int, int, float, float, float, int);
extern void FastVecAdd(void *, void *, void *);
typedef int L_34730TI __attribute__((mode(TI)));
extern L_34730TI hero_copy_vector_to_out(int, L_34730TI *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
typedef int TI __attribute__((mode(TI)));
extern TI hero_copy_vector_to_out(int, TI *);
extern void FastVecAdd(void *, void *, void *);

/* func_003304D8 is defined in 0032EB28-ground-g8.c. */


/* func_00330BC0 uses small data in 0032EB28-g8.c. */

/* func_00330CA0 is in 0032EB28-damage-g8.c. */


/* func_00330E48 is in 0032EB28-g8.c. */

/* func_00330EC0 is in 0032EB28-ring-g8.c. */

/* func_00331238 is in 0032EB28-spark.c. */


/* Spawns eight pairs of coloured puffs around a point halfway along direction (PAL: same as USA v1.01). */
void part_spawn_spark_burst_2_pal(TI128 *position, void *direction)
{
    EffectVector base;
    float vel[4];
    float pos[3];
    float size = 84000.0f;
    int i;
    int rnd;
    unsigned char *p;

    qcopy(&base, position);
    FastVecScale(vel, direction, 0.5f);
    FastVecAdd(&base, &base, vel);
    i = 8;
    do {
        i--;
        pos[0] = base.v[0] + math_random_signed_float_range(0.0f, 0.1f);
        pos[1] = base.v[1] + math_random_signed_float_range(0.0f, 0.1f);
        pos[2] = base.v[2] + math_random_signed_float_range(0.0f, 0.1f);
        rnd = math_random_int_below(0xFF);
        p = part_spawn_gravity_fade(pos, g_default_effect_vector, 8, 0x407FFF, rnd, 0x7F, 0, size, size, 0.0f, 1);
        if (p != 0)
            p[2] = g_particle_texture_table[92][5];
        p = part_spawn_gravity_fade(pos, g_default_effect_vector, 8, 0x406080, rnd, 0x7F, 0, size, size, 0.0f, 1);
        if (p != 0)
            p[2] = g_particle_texture_table[53][0];
    } while (i >= 0);
}


extern s32 FastTweenColor(s32, s32, f32);
extern s32 FloatToInt(f32 value);
extern u8 *part_spawn_burst_pal(f32 *pos, f32 *sym, s32 a2, s32 a3, u32 color, s32 alpha, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);
extern u8 *g_part_tex_flash_puffs_table;

/* Spawns two flash puffs and one coloured puff near pos, sized by scale. */
void part_spawn_flash_puffs_pal(f32 *pos, f32 scale)
{
    f32 v[3];
    f32 size = scale * 6300.0f;
    u8 *effect;
    s32 i;
    for (i = 1; i >= 0; i--) {
    v[0] = pos[0] + math_random_signed_float_range(0.0f, 0.04f);
    v[1] = pos[1] + math_random_signed_float_range(0.0f, 0.04f);
    v[2] = pos[2] + math_random_signed_float_range(0.0f, 0.04f);
    part_spawn_burst_pal(v, g_default_effect_vector, 12, 0x5F, 0x7F7F7F, FloatToInt(math_random_signed_float_range(1.0f, 3.0f)), size, 500.0f, 1.0f, 0.0f, 0.0f);
    }
    effect = part_spawn_burst_pal(v, g_default_effect_vector, 12, 0x7F, 0x407FFF, FloatToInt(math_random_signed_float_range(1.0f, -1.0f)), size * 0.8f, 500.0f, 1.0f, 0.0f, 0.0f);
    if (effect != 0) {
        effect[2] = g_part_tex_flash_puffs_table[5];
    }
}

