#include "include_asm.h"
#include "names.h"

extern int g_current_map_index;
extern float fast_vec_dist(void *, void *);
extern float vec_spring_to_target(void *, void *, void *, float, float, float);
extern float FastAddRotations(float, float);
extern int table_find_last_used_entry(int);
extern int math_random_int_below(int);
extern char *GetLocalizedString(int);
extern int level_l00_call_module_handler_with_arg_9_pal(int, int);
typedef struct L05Slot40 {
    int state;
    int next;
    int pad08[2];
    int limit;
    int value;
    int pad18[4];
} L05Slot40;
extern L05Slot40 g_slot_value_table[];
extern int snd_play_from_class_bank(int, int, char *, int);
extern void moby_mark_spawned(void *);
extern int g_active_effect_moby __attribute__((sda));
extern void func_PAL_L05_003D1248(char *);

void func_PAL_L05_003D0F1C(char *object)
{
    char *state = *(char **)(object + 0x68);
    float scale;

    if (g_active_effect_moby != 0) {
        scale = fast_vec_dist((void *)(g_active_effect_moby + 0x10), object + 0x10);

        if (g_current_map_index == 0x14) {
            vec_spring_to_target(object + 0x10, (void *)(g_active_effect_moby + 0x10), state + 0x40,
                         0.012800001f, 0.0048f, 1.2800001f);
            goto check_scale;
        }
        if (scale < 6e+01f) {
            float *p = *(float **)(object + 0x24);
            float v = p[9] * 0.02222222276031971f * scale;

            *(float *)(object + 0x2C) = v;
            {
                float cap = p[9] * 0.3f;

                if (v < cap)
                    *(float *)(object + 0x2C) = cap;
            }
            vec_spring_to_target(object + 0x10, (void *)(g_active_effect_moby + 0x10), state + 0x40,
                         0.008f, 0.0024f, 0.6f);
        }
    check_scale:
        if (scale < 0.5f) {
            int slot = table_find_last_used_entry(6);
            int add = g_slot_value_table[slot].limit;

            if (math_random_int_below(4) != 0) {
                level_l00_call_module_handler_with_arg_9_pal(GetLocalizedString(0x1283), -1);
                add = 0x21;
            } else {
                level_l00_call_module_handler_with_arg_9_pal(GetLocalizedString(0x1284), -1);
            }
            snd_play_from_class_bank(0xC, 0, object, 0xFBF);
            g_slot_value_table[slot].value += add;
            if (g_slot_value_table[slot].limit < g_slot_value_table[slot].value)
                g_slot_value_table[slot].value = g_slot_value_table[slot].limit;
            moby_mark_spawned(object);
            return;
        }
    }
    *(float *)(object + 0xF8) = FastAddRotations(*(float *)(object + 0xF8), 0.03f);
    func_PAL_L05_003D1248(object);
}
