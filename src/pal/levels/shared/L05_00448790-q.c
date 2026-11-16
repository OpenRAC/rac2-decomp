#include "include_asm.h"

#include "common.h"
extern char *g_path_l05_entry_table MACRO_ADDR;
extern char *g_feltzin_target_mobys MACRO_ADDR;
extern char *g_linked_point_table MACRO_ADDR;
extern char g_ship_saved_position[] MACRO_ADDR;
extern float fast_vec_dist(char *, char *);
extern void vec_scale_to_length(char *, char *, float);
extern s32 math_random_int_below(s32);
extern void UpdateDrivenMobyTransform_pal(char *);
extern void ship_restore_settings(void);

/* Picks the best-scoring of the entity's nine slots (or the runner-up on a random draw), copies
   its transform to the object and to the entity, and resets the object. */
void ship_respawn_at_best_saved_slot_pal(char *obj)
{
    char *entry = *(char **)(g_path_l05_entry_table + *(short *)(obj + 0x84) * 32 + 0x1C);
    char *self = g_feltzin_target_mobys + (*(s32 *)(entry + 0x20) << 8);
    char *state = *(char **)(self + 0x68);
    s32 best = -1;
    s32 second = -1;
    float next = 0.0f;
    float top = 0.0f;
    s32 i;
    s32 pick;
    char *rec;

    for (i = 0; i < 9; i++) {
        s32 *slot = (s32 *)(state + 0x21C) + i;
        if (*slot >= 0) {
            float score = fast_vec_dist(self + 0x10, g_linked_point_table + (*slot << 7) + 0x30);
            if (top < score) {
                next = top;
                second = best;
                top = score;
                best = *slot;
            } else if (next < score) {
                second = *slot;
                next = score;
            }
        }
    }
    pick = best;
    if (math_random_int_below(2) != 0)
        pick = second >= 0 ? second : pick;
    rec = g_linked_point_table + (pick << 7);
    qcopy(obj + 0x30, rec + 0x30);
    qcopy(g_ship_saved_position, obj + 0x30);
    qcopy(self + 0x10, obj + 0x30);
    vec_scale_to_length(obj, rec, 1.0f);
    vec_scale_to_length(obj + 0x10, rec + 0x10, 1.0f);
    vec_scale_to_length(obj + 0x20, rec + 0x20, 1.0f);
    qzero(*(char **)(obj + 0x70) + 0xB0);
    UpdateDrivenMobyTransform_pal(obj);
    ship_restore_settings();
}
