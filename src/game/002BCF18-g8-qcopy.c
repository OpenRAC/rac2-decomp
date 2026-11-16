#include "names.h"
/* func_002BCF18 in its own unit: small data at -G8 and lq/sq quadword copies (-frac2-qcopy -frac2-qcopy-barrier). */
#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));

extern float g_frame_time_scale;
/* Read through lui/lw with a separate address register: not small data, so an
   incomplete array indexed [0]. */
extern unsigned char *g_part_tex_falling_drop_table[];
extern int math_random_int_below(int);
extern char *part_alloc(int);
extern int FloatToInt(float);
extern char func_001163B0(void);

/* Creates a falling drop particle at a point with a velocity. It does nothing if there is no life or the screen is too busy. */
char *part_spawn_falling_drop(char *position, char *velocity, int color, int endColor, int life, int type, float size)
{
    char *particle;

    if (life == 0)
        return 0;
    if (g_frame_time_scale > 0.9f && math_random_int_below(3) == 0)
        return 0;
    if (g_frame_time_scale > 0.95f && math_random_int_below(2) == 0)
        return 0;
    if (g_frame_time_scale > 1.0f && math_random_int_below(1) == 0)
        return 0;
    particle = part_alloc(0x10);
    if (particle != 0) {
        char *motion;
        unsigned char *textureTable;
        int alphaRand;

        *(TI128 *)(particle + 0x10) = *(TI128 *)position;
        *(int *)(particle + 4) = color;
        alphaRand = FloatToInt(4.0f) + 0x40;
        particle[1] = 0;
        *(float *)(particle + 0xC) = size;
        particle[3] = 0x44;
        particle[9] = alphaRand;
        particle[8] = func_001163B0();
        motion = particle + 0x20;
        textureTable = g_part_tex_falling_drop_table[0];
        particle[2] = *((type != 3) ? textureTable + type : textureTable);
        *(short *)(particle + 0xA) = life;
        *(short *)(motion + 0x18) = life;
        *(float *)(motion + 0x1C) = size;
        *(int *)(motion + 0x10) = color;
        *(int *)(motion + 0x14) = endColor;
        *(short *)(motion + 0x1A) = type;
        *(TI128 *)motion = *(TI128 *)velocity;
        *(float *)(motion + 0xC) = *(float *)(position + 8) - 0.5f;
    }
    return particle;
}
