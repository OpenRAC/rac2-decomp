#include "include_asm.h"

#include "common.h"
typedef int Vec128_L11 __attribute__((mode(TI)));
extern int g_current_map_index;
extern char g_hero_position[];
extern int g_lightning_point_count __attribute__((sda));
extern char *g_path_l11_table[];
extern char g_ribbon_row_table[];
extern int math_random_int_below(int);
extern void FastVecAdd(void *, void *, void *);
extern void ResetBoltPointsToLine(void *);
extern void lightning_rebuild_bolt_points(char *);
extern void draw_object_ribbon_pair_pal(char *);
extern void gfx_add_draw_callback_third(void (*)(char *), void *);
extern int gfx_add_point_light(void *, int, float, float);

/* Advances the object's state and refreshes the last four points of its row in the level's
 * table of 640-byte entries, then registers the callback that draws them. */
void UpdateRibbonTrailPoints_pal(char *object)
{
    float position[4] __attribute__((aligned(16)));
    char *state = *(char **)(object + 0x68);
    char *source;
    int count;
    int i;

    if (*(int *)(state + 0x38) >= 20) *(int *)(state + 0x3c) = 1;
    if (*(int *)(state + 0x3c) || g_current_map_index == 4 || g_current_map_index == 11) {
        if (*(int *)(state + 0x38) >= 20 && 85.0f < *(float *)(g_hero_position + 8)) return;
        qcopy(state, object + 0x10);
        qcopy(state + 0x10, state);
        *(float *)(state + 0x20) += (6.0f - *(float *)(state + 0x20)) * 0.08400001f + 12.0f;
        position[0] = 0.0f;
        position[1] = *(float *)(state + 0x20);
        position[2] = 0.0f;
        FastVecAdd(state + 0x10, state, position);
        qcopy(position, state + 0x10);
        if (g_current_map_index != 4 && g_current_map_index != 11) g_lightning_point_count = math_random_int_below(20);
        else g_lightning_point_count = 20;
        ResetBoltPointsToLine(object);
        lightning_rebuild_bolt_points(object);
        source = g_path_l11_table[*(int *)(state + 0x34)];
        count = g_lightning_point_count;
        /* The table is not read back here, so the row's base can stay out of the loop. */
        for (i = count - 4; i < count; i++) {
            qcopy_nc(&((Vec128_L11 *)(g_ribbon_row_table + *(int *)(state + 0x38) * 640))[i], &((Vec128_L11 *)source)[i + 1]);
        }
        gfx_add_draw_callback_third(draw_object_ribbon_pair_pal, object);
        if (!*(unsigned char *)(object + 0x20)) {
            *(int *)(state + 0x24) = gfx_add_point_light(state, 0, 0.0f, 0.0f);
            object[0x20] = 1;
            *(int *)(state + 0x2c) = g_lightning_point_count;
            *(int *)(state + 0x30) = -1;
        }
    }
}
