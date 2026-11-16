#include "include_asm.h"
#include "common.h"

/* func_PAL_L00_00417ED0, the PAL copy of func_L00_00412FF8: the same C, except that D_L00_001B13DC
 * is read as a word, held in a offset across the -1 store, and scaled to 50 Hz. */

extern int g_lightning_arc_counter __attribute__((sda));
extern int g_lightning_arc_value __attribute__((sda));
extern int g_lightning_arc_flags __attribute__((sda));
extern char g_hero_turn_rotation[];
extern char g_lightning_arc_point_buffers[];
extern char g_lightning_arc_state_buffers[];
extern char *CreateMoby(int id);
extern void euler_rotation_basis(char *dst, char *src);
extern void FastVecScale(float *dst, char *src, float scale);
extern void FastVecAdd(char *dst, char *src, float *offset);
extern void wave_line_reset_effect_pal(char *moby);

/* Creates a lightning arc object for an owner and gives it one of four reusable sets of points (PAL: 50 Hz timer). */
char *lightning_arc_spawn_pal(char *owner)
{
    char *moby = CreateMoby(0x1195);
    char *vars;
    int arc_flags;
    int counter;
    float offset[4];

    if (moby != 0) {
        *(unsigned char *)(moby + 0x20) = 1;
        *(unsigned char *)(moby + 0x30) = 0xFF;
        vars = *(char **)(moby + 0x68);
        arc_flags = g_lightning_arc_flags;
        *(int *)(vars + 0x18) = -1;
        *(unsigned short *)(vars + 0x1E) = ((s32)(arc_flags) * 5 + 2) / 6;
        euler_rotation_basis(moby + 0xC0, g_hero_turn_rotation);
        counter = g_lightning_arc_counter;
        *(char **)(vars + 0) = g_lightning_arc_point_buffers + counter * 0xA0;
        *(char **)(vars + 4) = g_lightning_arc_state_buffers + counter * 0x140;
        if ((unsigned int)counter >= 4)
            g_lightning_arc_counter = 0;
        g_lightning_arc_counter = (g_lightning_arc_counter + 1) % 4;
        *(int *)(vars + 0x24) = g_lightning_arc_value;
        *(char **)(vars + 0x20) = owner;
        FastVecScale(offset, *(char **)(g_hero_turn_rotation + 0x2200) + 0xE0, 0.75f);
        FastVecAdd(moby + 0x10, g_hero_turn_rotation - 0x10, offset);
        wave_line_reset_effect_pal(moby);
    }
    return moby;
}
