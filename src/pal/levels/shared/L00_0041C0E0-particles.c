#include "include_asm.h"
#include "names.h"

extern char g_spark_l00_records[];
extern void ref_L00_00417700_00(void *, void *);
extern float math_random_float_range(float, float);
extern void gfx_draw_billboard_quad(void *, int, int, int, float, float, float);

void beam_glow_sprites_update_owned_pal(char *object)
{
    int address = (int)g_spark_l00_records;
    char *pos = (char *)(address + 0x30);
    char *base = (char *)address;
    int i;
    for (i = 0; i < 24; i++, base += 0xB0, pos += 0xB0) {
        if (*(char **)(pos + 0x6C) == object) {
            ref_L00_00417700_00(object, base);
            if (*(int *)(pos + 0x70) == 0) {
                gfx_draw_billboard_quad(pos, 0x31, 0x3F7F0000, 1, math_random_float_range(0.125f, 0.25f) * 5.0f, 1.25f, 0.0f);
                gfx_draw_billboard_quad(pos, 0x31, 0x5F7F7F7F, 1, math_random_float_range(0.0625f, 0.125f) * 5.0f, 1.24f, 0.0f);
                gfx_draw_billboard_quad(pos, 0xB, 0x103F0000, 1, math_random_float_range(0.15f, 0.35f) * 5.0f, 1.23f, 0.0f);
            }
        }
    }
}
