#include "include_asm.h"

#include "common.h"
extern void vec_scale_to_length(float *, float *, float);
extern char g_spark_records[];
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);

void func_PAL_0032A0E0(char *owner)
{
    int address = (int)g_spark_records;
    char *position = (char *)(address + 0x10);
    char *other = (char *)(address + 0x20);
    int remaining = 99;
    char *base = (char *)address;
    char *data = *(char **)(owner + 0x68);
    do {
        if (*(char **)(position + 0x24) == owner) {
            matrix_mul_vec3(position, base, owner + 0xC0);
            vec_scale_to_length((float *)other, (float *)position, 1.0f);
            FastVecAdd(position, position, owner + 0x10);
            *(float *)(position + 0x20) += 0.75398237f;
            if (*(float *)(position + 0x20) >= 6.2831854820251465f) {
                *(int *)(position + 0x24) = 0;
                --*(int *)(data + 0x48);
            }
        }
        base += 0x40;
        other += 0x40;
        position += 0x40;
    } while (--remaining >= 0);
}


extern float IntToFloat(int);
extern float math_ease_out_quad(float);
extern int math_random_int_range(int, int);
extern void DrawParticleGlows(char *);
extern void gfx_draw_facing_sprite(char *, int, int, float, char *, int, char *, float);
extern void gfx_draw_facing_sprite_near_cam(char *, int, int, float, float, int, int, float);
extern void DrawAndReleaseObjectParticles(char *);

void func_PAL_0032A1E8(char *obj)
{
    char *data;
    float f;
    char *pos;

    data = *(char **)(obj + 0x68);
    if ((unsigned char)(*(unsigned char *)(obj + 0x20) - 2) < 2) {
        pos = data + 0x30;
        f = IntToFloat(*(int *)(data + 0x44)) / IntToFloat(0x11);
        gfx_draw_facing_sprite(pos, 0x204080, *(int *)(data + 0x58),
                       math_ease_out_quad(1.0f - f) * 0.75f, (char *)0x2E, 1,
                       data + 0x20, 0.0f);
    }
    DrawParticleGlows(obj);
    gfx_draw_facing_sprite_near_cam(obj + 0x10, 0x7F7F7F, math_random_int_range(0x20, 0x40), 0.125f, 0.0f, 0xB, 2, 0.3f);
    gfx_draw_facing_sprite_near_cam(obj + 0x10, 0x103080, math_random_int_range(0x20, 0x40), 0.225f, 0.0f, 0xB, 2, 0.31f);
    DrawAndReleaseObjectParticles(obj);
}

