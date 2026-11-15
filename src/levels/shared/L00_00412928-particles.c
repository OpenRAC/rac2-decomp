#include "include_asm.h"
#include "names.h"

extern char g_spark_l00_records[];
extern void ref_L00_00417700_00(void *, void *);
extern float math_random_float_range(float, float);
extern void gfx_draw_billboard_quad(void *, int, int, int, float, float, float);

/* Redraws each lightning arc owned by this object and adds glow sprites while the arc is idle. */
void beam_glow_sprites_update_owned(char *moby)
{
    int tableAddress = (int)g_spark_l00_records;
    char *glowPos = (char *)(tableAddress + 0x30);
    char *entry = (char *)tableAddress;
    int i;
    for (i = 0; i < 24; i++, entry += 0xB0, glowPos += 0xB0) {
        if (*(char **)(glowPos + 0x6C) == moby) {
            ref_L00_00417700_00(moby, entry);
            if (*(int *)(glowPos + 0x70) == 0) {
                gfx_draw_billboard_quad(glowPos, 0x31, 0x3F7F0000, 1, math_random_float_range(0.125f, 0.25f) * 5.0f, 1.25f, 0.0f);
                gfx_draw_billboard_quad(glowPos, 0x31, 0x5F7F7F7F, 1, math_random_float_range(0.0625f, 0.125f) * 5.0f, 1.24f, 0.0f);
                gfx_draw_billboard_quad(glowPos, 0xB, 0x103F0000, 1, math_random_float_range(0.15f, 0.35f) * 5.0f, 1.23f, 0.0f);
            }
        }
    }
}
