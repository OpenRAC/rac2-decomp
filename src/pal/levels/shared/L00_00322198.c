#include "include_asm.h"

#include "common.h"
typedef struct { float f[4]; } BurstVector __attribute__((aligned(16)));
typedef struct { int values[6]; } BurstPalette;
typedef struct {
    float offset[4];
    unsigned char colors[16];
    float radius[3], intensity, falloff;
    int value34, value38;
    unsigned char options[4];
    unsigned short timers[4];
    unsigned char flags48, flags49;
} BurstFlashTemplate;
extern BurstPalette g_burst_palette_a[], g_burst_palette_b[];
extern BurstFlashTemplate g_burst_flash_template[] __attribute__((aligned(16)));
extern void vec_clear_128(void *);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern int gfx_swap_packed_color_channels(unsigned int, int);
extern int math_random_int_range(int, int);
extern char *part_spawn_firework_spark(void *, void *, int, int, float, int, int, int, int, float);
extern void swap_color_channel_words(int *, int *, int *, int);
extern char *part_spawn_shockwave_ring_pal(char *, char *, char *, float, int,
                          unsigned char, unsigned char, unsigned char, unsigned char);
extern char *moby_spawn_template_effect(char *, void *, int, void *);

/* Spawns a burst of firework sparks and, when there is a parent, two glows, then an optional flash (PAL). */
void part_l00_spawn_explosion_burst_pal(char *parent, char *position, float scale, float flash)
{
    BurstVector zero;
    BurstPalette first, second;
    int rgb[3];
    int i;
    float speed, size, glow;
    vec_clear_128(&zero);
    for (i = 2; i >= 0; i--) {
        int firstColor, secondColor, life, fadeLife;
        speed = math_random_float_range(8.0f, 10.0f) * 0.020000001f;
        size = scale * 500000.0f;
        first = g_burst_palette_a[0];
        second = g_burst_palette_b[0];
        firstColor = gfx_swap_packed_color_channels(first.values[math_random_int_below(6)], 1);
        secondColor = gfx_swap_packed_color_channels(second.values[math_random_int_below(6)], 1);
        life = math_random_int_range(12, 17);
        fadeLife = math_random_int_range(21, 25);
        part_spawn_firework_spark(position, &zero, firstColor, secondColor,
                      size, life, fadeLife, 0, 0, speed * scale);
    }
    if (parent) {
        rgb[0] = 127; rgb[1] = 64; rgb[2] = 0;
        swap_color_channel_words(rgb, rgb + 1, rgb + 2, 1);
        glow = scale * 4.0f;
        part_spawn_shockwave_ring_pal(parent, position, (char *)&zero, glow, 17,
                      *(unsigned char *)&rgb[0], *(unsigned char *)&rgb[1],
                      *(unsigned char *)&rgb[2], 48);
        rgb[0] = 96; rgb[1] = 32; rgb[2] = 0;
        swap_color_channel_words(rgb, rgb + 1, rgb + 2, 1);
        glow = scale * 3.0f;
        part_spawn_shockwave_ring_pal(parent, position, (char *)&zero, glow, 24,
                      *(unsigned char *)&rgb[0], *(unsigned char *)&rgb[1],
                      *(unsigned char *)&rgb[2], 32);
    }
    if (flash != 0.0f) {
        if (flash > 0.0f) {
            g_burst_flash_template[0].radius[1] = flash;
            g_burst_flash_template[0].radius[2] = flash;
            g_burst_flash_template[0].radius[0] = flash;
        } else {
            g_burst_flash_template[0].radius[1] = 13.0f;
            g_burst_flash_template[0].radius[2] = 13.0f;
            g_burst_flash_template[0].radius[0] = 13.0f;
        }
        moby_spawn_template_effect((char *)g_burst_flash_template, position, 0, 0);
    }
}

