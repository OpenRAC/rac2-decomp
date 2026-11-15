#include "include_asm.h"
#include "names.h"
extern float IntToFloat(int);
extern float math_fast_sin_or_cos_a(float);
extern int FloatToInt(float);
extern float math_ease_out_quad(float);
extern int math_random_int_range(int, int);
extern void DrawParticleGlows(char *);
extern void gfx_draw_facing_sprite(char *, int, int, float, char *, int, char *, float);
extern void gfx_draw_facing_sprite_near_cam(char *, int, int, float, float, int, int, float);
extern void DrawAndReleaseObjectParticles(char *);
extern char g_spark_records[];

/* Draws the glow, sparkle and particle effects of the object. */
void DrawObjectSpriteEffects(char *obj)
{
    char *data;
    float fadeRatio;
    char *pos;

    data = *(char **)(obj + 0x68);
    if ((unsigned char)(*(unsigned char *)(obj + 0x20) - 2) < 2) {
        pos = data + 0x30;
        fadeRatio = IntToFloat(*(int *)(data + 0x44)) / IntToFloat(0x14);
        gfx_draw_facing_sprite(pos, 0x204080, *(int *)(data + 0x58),
                       math_ease_out_quad(1.0f - fadeRatio) * 0.75f, (char *)0x2E, 1,
                       data + 0x20, 0.0f);
    }
    DrawParticleGlows(obj);
    gfx_draw_facing_sprite_near_cam(obj + 0x10, 0x7F7F7F, math_random_int_range(0x20, 0x40), 0.125f, 0.0f, 0xB, 2, 0.3f);
    gfx_draw_facing_sprite_near_cam(obj + 0x10, 0x103080, math_random_int_range(0x20, 0x40), 0.225f, 0.0f, 0xB, 2, 0.31f);
    DrawAndReleaseObjectParticles(obj);
}

/* Draws the glow of every particle record (100 x 0x40 bytes at D_0022B0A0) owned by obj:
 * the record's +0x30 angle, shifted by pi, gives a 0..1 sine level; 128 times that
 * becomes the shared intensity of two func_00328F18 quads. */
void DrawParticleGlows(char *obj)
{
    int i;
    float s;
    int n;

    for (i = 0; i < 100; i++) {
        char *e = g_spark_records + i * 0x40;
        if (*(char **)(e + 0x34) == obj) {
            s = (math_fast_sin_or_cos_a(*(float *)(e + 0x30) - 3.1415927f) + 1.0f) * 0.5f;
            n = FloatToInt(s * 128.0f);
            gfx_draw_facing_sprite_near_cam(e + 0x10, 0x103080, n, 0.125f, 0.0f, 0x2E, 2, 0.011f);
            gfx_draw_facing_sprite_near_cam(e + 0x10, 0x7F7F7F, n, 0.0625f, 0.0f, 0x2E, 2, 0.011f);
        }
    }
}
