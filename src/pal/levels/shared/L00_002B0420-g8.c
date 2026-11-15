#include "include_asm.h"
#include "names.h"

typedef float Row[4];
typedef struct {
    unsigned char pad0[472];
    int f1d8;
    unsigned char pad1dc[0x1530 - 0x1dc];
    Row history[16][3];
    unsigned char pad1830[0x2294 - 0x1830];
    int f2294;
    unsigned char pad2298[32];
    unsigned char f22b8;
    unsigned char pad22b9[275];
    int history_index;
    int history_count;
    int filter_count;
} Root;
extern Root g_hero_state;
extern int ref_L00_002B0528_0 __attribute__((sda));
extern void copy_matrix3x4(void *, void *);
extern void mat_normalize_columns(void *);
extern void vec_clear_128(void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void mat_get_euler_angles(void *, void *);
extern float mat_measure_difference(Row *, Row *);

void func_PAL_L00_002B0420(char *object, void *matrix, int filter)
{
    Row sum[4];
    /* Retail accumulates into this scratch array without clearing it. */
    float scores[16];
    int i, j, n, rejected, accepted;
    Row *cursor;
    float max;
    int index = g_hero_state.history_index;

    {
        Row *history = g_hero_state.history[0];
        copy_matrix3x4(history + index * 3, matrix);
        mat_normalize_columns(history + g_hero_state.history_index * 3);
    }
    g_hero_state.history_index = (g_hero_state.history_index + 1) % 16;
    g_hero_state.history_count++;
    if (g_hero_state.history_count > 16)
        g_hero_state.history_count = 16;
    if (!filter)
        return;
    for (cursor = sum, j = 2; j >= 0; j--, cursor++)
        vec_clear_128(cursor);
    if (g_hero_state.f2294 == 2)
        ref_L00_002B0528_0 = 5;
    else
        ref_L00_002B0528_0 = 11;
    if (g_hero_state.filter_count < ref_L00_002B0528_0)
        g_hero_state.filter_count++;
    else if (g_hero_state.filter_count > ref_L00_002B0528_0)
        g_hero_state.filter_count--;
    n = g_hero_state.filter_count;
    if (n < 2)
        n = 2;
    if (g_hero_state.f22b8 && g_hero_state.f1d8 < 8) {
        if (n > 3)
            n = 3;
    }
    if (g_hero_state.history_count < n)
        return;
    rejected = 0;
    for (i = 0; i < n; i++) {
        int a = (g_hero_state.history_index + 15 - i) % 16;
        for (j = 0; j < n; j++) {
            if (i != j) {
                int b = (g_hero_state.history_index + 15 - j) % 16;
                scores[i] += mat_measure_difference(g_hero_state.history[0] + a * 3,
                                              g_hero_state.history[0] + b * 3);
            }
        }
    }
    max = 0.0f;
    for (i = 0; i < n; i++) {
        if (max < scores[i])
            max = scores[i];
    }
    for (i = 0; i < n; i++) {
        if (max * 0.2f < scores[i])
            rejected++;
    }
    accepted = 0;
    for (i = 0; i < n; i++) {
        if (max * 0.2f < scores[i] && rejected > 0 && rejected < 3)
            continue;
        accepted++;
        {
            int sample = (g_hero_state.history_index + 15 - i) % 16;
            {
                Row *p = g_hero_state.history[0] + sample * 3;
                Row *out;
                for (out = sum, j = 2; j >= 0; out++, j--, p++)
                    FastVecAdd(out, out, p);
            }
        }
    }
    for (cursor = sum, j = 2; j >= 0; j--, cursor++)
        FastVecScale(cursor, cursor, 1.0f / (float)accepted);
    mat_get_euler_angles(sum, object + 0xf0);
}
