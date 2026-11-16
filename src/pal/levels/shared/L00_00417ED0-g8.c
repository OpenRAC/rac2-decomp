#include "include_asm.h"
#include "common.h"

/* func_PAL_L00_00417ED0, the PAL copy of func_L00_00412FF8: the same C, except that D_L00_001B13DC
 * is read as a word, held in a local across the -1 store, and scaled to 50 Hz. */

extern int g_lightning_arc_counter __attribute__((sda));
extern int g_lightning_arc_value __attribute__((sda));
extern int g_lightning_arc_flags __attribute__((sda));
extern char g_hero_turn_rotation[];
extern char g_lightning_arc_point_buffers[];
extern char g_lightning_arc_state_buffers[];
extern char *CreateMoby(int id);
extern void euler_rotation_basis(char *dst, char *src);
extern void FastVecScale(float *dst, char *src, float scale);
extern void FastVecAdd(char *dst, char *src, float *local);
extern void func_PAL_L00_00418190(char *object);

char *func_PAL_L00_00417ED0(char *owner)
{
    char *object = CreateMoby(0x1195);
    char *state;
    int timer;
    int counter;
    float local[4];

    if (object != 0) {
        *(unsigned char *)(object + 0x20) = 1;
        *(unsigned char *)(object + 0x30) = 0xFF;
        state = *(char **)(object + 0x68);
        timer = g_lightning_arc_flags;
        *(int *)(state + 0x18) = -1;
        *(unsigned short *)(state + 0x1E) = ((s32)(timer) * 5 + 2) / 6;
        euler_rotation_basis(object + 0xC0, g_hero_turn_rotation);
        counter = g_lightning_arc_counter;
        *(char **)(state + 0) = g_lightning_arc_point_buffers + counter * 0xA0;
        *(char **)(state + 4) = g_lightning_arc_state_buffers + counter * 0x140;
        if ((unsigned int)counter >= 4)
            g_lightning_arc_counter = 0;
        g_lightning_arc_counter = (g_lightning_arc_counter + 1) % 4;
        *(int *)(state + 0x24) = g_lightning_arc_value;
        *(char **)(state + 0x20) = owner;
        FastVecScale(local, *(char **)(g_hero_turn_rotation + 0x2200) + 0xE0, 0.75f);
        FastVecAdd(object + 0x10, g_hero_turn_rotation - 0x10, local);
        func_PAL_L00_00418190(object);
    }
    return object;
}
