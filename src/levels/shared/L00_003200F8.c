/* Adapted from RAC1 spawn_color_swapped_explosion_burst at 8bbc6b38,
 * src/overlays/shared/moby_ground_collision.c (GPL-3.0). RAC2 callee returns,
 * argument widths, palette locations and flash-template fields are verified
 * independently; no donor assembler aliases or false void returns retained. */
#include "common.h"

typedef struct { float f[4]; } BurstVector __attribute__((aligned(16)));
typedef struct { int values[6]; } BurstPalette;
/* Every template byte consumed by 312B70 is represented, through +0x49.
 * This is a measured record view, not a bound on its external allocation. */
typedef struct {
    float offset[4];
    unsigned char colors[16];
    float radius[3], intensity, falloff;
    int value34, value38;
    unsigned char options[4];
    unsigned short timers[4];
    unsigned char flags48, flags49;
} BurstFlashTemplate;
extern BurstPalette D_L00_001AA260[], D_L00_001AA278[];
/* 312B70 reads the full external template through byte 0x49, including its
 * first 16-byte vector. Its complete owner remains incompletely bounded. */
extern BurstFlashTemplate D_L00_00281760[] __attribute__((aligned(16)));
extern void vec_clear_128(void *);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern int gfx_swap_packed_color_channels(unsigned int, int);
extern int math_random_int_range(int, int);
/* Bank-preserving views: BBCB0 has eight GPR/two FP arguments; 308408 has
 * eight GPR/one FP, with its four color/alpha arguments genuinely unsigned 8-bit. */
extern char *part_spawn_firework_spark(void *, void *, int, int, float, int, int, int, int, float);
extern void swap_color_channel_words(int *, int *, int *, int);
extern char *part_spawn_shockwave_ring(char *, char *, char *, float, int,
                          unsigned char, unsigned char, unsigned char, unsigned char);
extern char *moby_spawn_template_effect(char *, void *, int, void *);

/* Spawns an orange explosion burst of sparks at a position, with glow lights and an optional flash. */
void part_l00_spawn_explosion_burst(char *parentObj, char *position, float scale, float flashRadius)
{
    BurstVector zero;
    BurstPalette first, second;
    int rgb[3];
    int burstIdx;
    float speed, size, glow;
    vec_clear_128(&zero);
    for (burstIdx = 2; burstIdx >= 0; burstIdx--) {
        int firstColor, secondColor, life, fadeLife;
        speed = math_random_float_range(8.0f, 10.0f) * 0.01666666753590107f;
        size = scale * 500000.0f;
        first = D_L00_001AA260[0];
        second = D_L00_001AA278[0];
        firstColor = gfx_swap_packed_color_channels(first.values[math_random_int_below(6)], 1);
        secondColor = gfx_swap_packed_color_channels(second.values[math_random_int_below(6)], 1);
        life = math_random_int_range(15, 20);
        fadeLife = math_random_int_range(25, 30);
        part_spawn_firework_spark(position, &zero, firstColor, secondColor,
                      size, life, fadeLife, 0, 0, speed * scale);
    }
    if (parentObj) {
        rgb[0] = 127; rgb[1] = 64; rgb[2] = 0;
        swap_color_channel_words(rgb, rgb + 1, rgb + 2, 1);
        glow = scale * 4.0f;
        part_spawn_shockwave_ring(parentObj, position, (char *)&zero, glow, 20,
                      *(unsigned char *)&rgb[0], *(unsigned char *)&rgb[1],
                      *(unsigned char *)&rgb[2], 48);
        rgb[0] = 96; rgb[1] = 32; rgb[2] = 0;
        swap_color_channel_words(rgb, rgb + 1, rgb + 2, 1);
        glow = scale * 3.0f;
        part_spawn_shockwave_ring(parentObj, position, (char *)&zero, glow, 29,
                      *(unsigned char *)&rgb[0], *(unsigned char *)&rgb[1],
                      *(unsigned char *)&rgb[2], 32);
    }
    if (flashRadius != 0.0f) {
        if (flashRadius > 0.0f) {
            D_L00_00281760[0].radius[1] = flashRadius;
            D_L00_00281760[0].radius[2] = flashRadius;
            D_L00_00281760[0].radius[0] = flashRadius;
        } else {
            D_L00_00281760[0].radius[1] = 13.0f;
            D_L00_00281760[0].radius[2] = 13.0f;
            D_L00_00281760[0].radius[0] = 13.0f;
        }
        moby_spawn_template_effect((char *)D_L00_00281760, position, 0, 0);
    }
}
