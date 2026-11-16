#include "include_asm.h"

#include "common.h"
typedef unsigned int u128 __attribute__((mode(TI)));
extern int g_blast_burst_first_indices[6] __attribute__((sda));
extern int g_blast_burst_last_indices[6] __attribute__((sda));
extern u8 g_blast_burst_ring_param_a __attribute__((sda));
extern u8 g_blast_burst_ring_param_b __attribute__((sda));
extern u8 g_blast_burst_ring_param_c __attribute__((sda));
extern u8 D_L11_001B12F0_4[] MACRO_ADDR;
extern u8 D_L11_001B12F8_4[] MACRO_ADDR;
extern u8 D_L11_001B1300_4[] MACRO_ADDR;
typedef struct {
    char pad[0x20];
    float scale[3];
} BurstSphere;
extern BurstSphere g_blast_burst_template;
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern char *part_spawn_firework_spark(void *, void *, int, int, float, int, int, int, int, float);
extern char *part_spawn_shockwave_ring_pal(char *, char *, char *, int, float, u8, u8, u8, u8);
extern int math_fast_helper_a(void *, float);
extern char *moby_spawn_template_effect(void *, void *, int, int);
extern int snd_play_from_class_bank(int, int, char *, int);
/* Called with a constant radius: each ring loads it afresh instead of sharing one register. */
static __inline__ void spawn_ring(char *obj, char *pos, char *velocity, float radius, int type,
                                  u8 r, u8 g, u8 b, u8 a)
{
    part_spawn_shockwave_ring_pal(obj, pos, velocity, type, radius, r, g, b, a);
}

/* Bursts at pos: twelve sparks, three coloured rings, a damage ring for an owner, then the
   blast sphere and its sound. */
void part_spawn_blast_burst_pal(char *obj, char *pos)
{
    float velocity[4], sphere[4];
    float size, scale, damage;
    float speed;
    int i, index, first, last, life;
    char *spark;

    *(u128 *)velocity = 0;
    velocity[2] = 0.16000001f;
    damage = 4.0f;
    size = 5.0f;
    scale = 2.0f;
    for (i = 11; i >= 0; i--) {
        speed = math_random_float_range(8.0f, 10.0f) * (0.020000001f);
        index = math_random_int_below(6);
        first = g_blast_burst_first_indices[index];
        last = g_blast_burst_last_indices[index];
        life = math_random_int_range(12, 17);
        spark = part_spawn_firework_spark(pos, velocity, first, last, scale * 400000.0f, life,
                              math_random_int_range(25, 37), 0, 0, speed * scale);
        if (spark)
            spark[3] = 0x44;
    }
    spawn_ring(obj, pos, (char *)velocity, 8.0f, 13, g_blast_burst_ring_param_a,
               D_L11_001B12F0_4[1], D_L11_001B12F0_4[2], D_L11_001B12F0_4[3]);
    spawn_ring(obj, pos, (char *)velocity, 8.0f, 18, g_blast_burst_ring_param_b,
               D_L11_001B12F8_4[1], D_L11_001B12F8_4[2], D_L11_001B12F8_4[3]);
    spawn_ring(obj, pos, (char *)velocity, 8.0f, 25, g_blast_burst_ring_param_c,
               D_L11_001B1300_4[1], D_L11_001B1300_4[2], D_L11_001B1300_4[3]);
    if (obj && damage > 0.0f)
        spawn_ring(obj, pos, (char *)velocity, damage, 22, 80, 50, 50, 20);
    if (size != 0.0f) {
        qcopy(sphere, pos);
        sphere[3] = size;
        if (math_fast_helper_a(sphere, 100.0f) != -1) {
            if (size > 0.0f)
                g_blast_burst_template.scale[0] = g_blast_burst_template.scale[2] = g_blast_burst_template.scale[1] = size;
            else
                g_blast_burst_template.scale[0] = g_blast_burst_template.scale[2] = g_blast_burst_template.scale[1] = 15;
            moby_spawn_template_effect(&g_blast_burst_template, pos, 0, 0);
        }
    }
    snd_play_from_class_bank(0, 0, obj, 0xDF7);
}
