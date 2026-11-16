#include "include_asm.h"
#include "moby_classes.h"
#include "names.h"

extern unsigned char g_extras_unlocked_flag;

extern int g_current_map_index __attribute__((sda));

extern int math_sum_weighted_table_taps(int, int);

/* Works out a level from the current difficulty and the given value, giving 3 when the mode flag is set. */
int level_get_difficulty_scaled(int amount)
{
    int mode = g_extras_unlocked_flag;
    int steps;
    int v;

    if (mode == 0) {
        steps = math_sum_weighted_table_taps(g_current_map_index, amount) / 100;
        v = 3 - steps;
        return mode < v ? v : 1;
    }
    return 3;
}

extern int D_001A79F0_1;
extern float ref_L00_002E3BA0_00[][3];

extern char *func_L00_0031E7A8(char *);

/* Scales the health and glow of a spawned object by a per-level factor, except for crates. */
void moby_scale_by_difficulty(char *object)
{
    char *glow;

    if (g_extras_unlocked_flag == 0)
        return;
    {
        short classId = *(short *)(object + 0xAA);

        if (classId == MOBY_CLASS_CRATE || classId == 0x1F6 /* moby class 502 */ || classId == MOBY_CLASS_EXPLOSIVE_CRATE || classId == MOBY_CLASS_PURPLE_NANOTECH_CRATE)
            return;
    }
    if (g_current_map_index >= 0x1C)
        return;
    *(short *)(object + 0xB6) = (int)(*(short *)(object + 0xB6) * ref_L00_002E3BA0_00[g_current_map_index][0]);
    if (*(short *)(object + 0xB6) < 0)
        *(short *)(object + 0xB6) = 0x7FFF;
    glow = func_L00_0031E7A8(object);
    if (glow != 0) {
        int i = g_current_map_index;
        float size = *(short *)(glow + 4);
        float red = (unsigned char)glow[0x14];
        float green = (unsigned char)glow[0x15];
        float blue = (unsigned char)glow[0x16];
        int v;

        *(short *)(glow + 4) = (int)(ref_L00_002E3BA0_00[i][0] * size);
        *(float *)glow = *(short *)(glow + 4);
        v = (int)(ref_L00_002E3BA0_00[i][2] * red);
        if (v > 0xFF)
            v = 0xFF;
        glow[0x14] = v;
        v = (int)(ref_L00_002E3BA0_00[D_001A79F0_1][2] * green);
        if (v > 0xFF)
            v = 0xFF;
        glow[0x15] = v;
        v = (int)(ref_L00_002E3BA0_00[D_001A79F0_1][2] * blue);
        if (v > 0xFF)
            v = 0xFF;
        glow[0x16] = v;
    }
}



/* func_L00_002E54E0 is matched in its own unit, src/levels/shared/L00_002E54E0-g8.c (-O2 -G8 -ffunction-sections). */
