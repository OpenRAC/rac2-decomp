#include "names.h"
/* func_PAL_L00_003BFBD8, the PAL copy of func_L00_003BBF48: the same C with the callee is PAL's
   func_PAL_L00_003BFEB8. */
#include "include_asm.h"
#include "names.h"
#include "common.h"

extern char g_spark_slot_records[] __attribute__((nosda));

extern void lightning_draw_curve_pal(char *a0, char *a1);

extern int math_random_int_range(int a, int b);

extern float math_random_angle(void);

extern void gfx_draw_billboard_quad(char *a, int b, unsigned int c, int d, float e, float f, float g);

/* Walks the level's table of records and draws the two sprites of the record the owner
   holds, when that record is still free. The record's own field is the owner, the one
   after it says whether it is free. Without interblock scheduling the two skips stay likely
   branches. Each sprite's colour is its own local: one shared variable dies twice, becomes a
   global pseudo, and the shifted alpha no longer ties to its saved register. */
void effect_draw_slot_sprites_pal(char *owner)
{
    unsigned int first_rgb = 0x103080;
    unsigned int second_rgb = 0xFFFFFF;
    char *base = g_spark_slot_records;
    char *p = base + 0x30;
    char *q = base;
    int i;
    int color;
    int color2;
    float angle;

    for (i = 29; i >= 0; p += 0xA0, i--, q += 0xA0) {
        if (*(int *)(p + 0x5C) == (int)owner) {
            lightning_draw_curve_pal(owner, q);
            if (*(int *)(p + 0x64) == 0) {
                color = math_random_int_range(0x50, 0x60);
                color = (int)(color << 24) | first_rgb;
                angle = math_random_angle();
                gfx_draw_billboard_quad(p, 0x31, color, 1, 0.5f, 0.15f, angle);
                color2 = math_random_int_range(0x50, 0x60);
                color2 = (int)(color2 << 24) | second_rgb;
                angle = math_random_angle();
                gfx_draw_billboard_quad(p, 0x31, color2, 1, 0.3f, 0.151f, angle);
            }
        }
    }
}
