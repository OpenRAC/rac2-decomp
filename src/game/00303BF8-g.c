#include "include_asm.h"
#include "names.h"

extern float D_002222E0[];
extern int g_game_time;

extern float FloatFraction(float);
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_sin_or_cos_a(float);

/* Fills three columns of the 64-entry, 32-byte-stride table at D_002222E0 from the state's
   parameters, one column for each flag bit (0x10, 0x40, 0x20) the state's word at +0x4C has
   clear: a sine of the wrapped phase 8 x 8 grid position, a cosine, and a sine again. */
/* Calculates the wave noise tables that make the surface ripple over time. */
void surface_grid_update_wave_tables(char *object)
{
    char *state = *(char **)(object + 0x68);
    int i;

    if (~*(int *)(state + 0x4C) & 0x10) {
        for (i = 0; i < 64; i++) {
            int col = i % 8;
            int row = i / 8;

            D_002222E0[i * 8] = math_fast_sin_or_cos_b(FloatFraction(*(float *)(state + 0x38) * (float)col + *(float *)(state + 0x3C) * (float)row + (float)g_game_time * *(float *)(state + 0x30)) * 6.2831855f);
        }
    }
    if (~*(int *)(state + 0x4C) & 0x40) {
        for (i = 0; i < 64; i++)
            D_002222E0[i * 8 + 1] = math_fast_sin_or_cos_a(FloatFraction((float)g_game_time * D_002222E0[i * 8 + 2] / *(float *)(state + 0x24)) * 6.2831855f);
    }
    if (~*(int *)(state + 0x4C) & 0x20) {
        for (i = 0; i < 64; i++)
            D_002222E0[i * 8 + 4] = math_fast_sin_or_cos_b(FloatFraction((float)g_game_time * D_002222E0[i * 8 + 3]) * 6.2831855f);
    }
}
