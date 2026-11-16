#include "include_asm.h"
#include "names.h"
extern float func_002A7878_2(float a, float b);
extern unsigned int func_002A7820_1(int a, int b);
extern void VU1_addGSregister(unsigned int reg, unsigned long value);
extern float math_random_angle(void);
extern void gfx_draw_billboard_quad(char *a, int b, unsigned int c, int d, float e, float f,
                          float g);
extern void effect_draw_slot_sprites(char *a0);
extern void spark_process_owned_records(char *a0);

/* Opens the block, lays seven oriented sprites over it from two helper draws and the shared
   colour word, then runs the two slot-table passes and closes the block. */
void spark_draw_projectile_pal(char *a0)
{
    char *ctx;

    ctx = *(char **)(a0 + 0x68);
    VU1_addGSregister(0x47, 0x00053001);

    gfx_draw_billboard_quad(a0 + 0x10, 0x2C,
                  (func_002A7820_1(0x80, 0xC8) << 24) | 0x72FF, 1,
                  func_002A7878_2(0.38500002f, 0.415f) * *(float *)(ctx + 0x4C),
                  -0.01f, math_random_angle());
    gfx_draw_billboard_quad(a0 + 0x10, 0x2D,
                  (func_002A7820_1(4, 0x28) << 24) | 0x00DDB973, 1,
                  *(float *)(ctx + 0x4C) * 1.225f, 0.0f, math_random_angle());
    gfx_draw_billboard_quad(a0 + 0x10, 0x29,
                  (func_002A7820_1(4, 0x28) << 24) | 0x00DDB973, 1,
                  *(float *)(ctx + 0x4C) * 0.6f, 0.0f, math_random_angle());
    gfx_draw_billboard_quad(a0 + 0x10, 0x2A,
                  (func_002A7820_1(4, 0x2D) << 24) | 0x00DDB973, 1,
                  func_002A7878_2(0.975f, 1.025f) * *(float *)(ctx + 0x4C),
                  0.0f, math_random_angle());
    gfx_draw_billboard_quad(a0 + 0x10, 0x2A,
                  (func_002A7820_1(4, 0x2D) << 24) | 0x00DDB973, 1,
                  func_002A7878_2(0.975f, 1.025f) * *(float *)(ctx + 0x4C),
                  0.0f, math_random_angle());
    effect_draw_slot_sprites(a0);
    spark_process_owned_records(a0);
    VU1_addGSregister(0x47, 0x0005360B);
}
