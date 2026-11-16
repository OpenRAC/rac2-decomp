/* func_PAL_L00_002CA888, the PAL copy of func_L00_002CA4E0: the same C. */
/* func_PAL_L00_002CA888: picks a weighted idle choice for the hero.
 * Built with -fno-rerun-loop-opt: one loop pass leaves -1 inside the first loop (retail
 * keeps the origin pointer in $fp), and the count-down sum loop gives retail's order.
 * The group around `draw = value` ends cse1's block after the call, so the sampling
 * numerator stays a separate 1.0 that cse2 turns into retail's `mov.s $f13,$f21`.
 */
#include "common.h"
typedef int Vector __attribute__((mode(TI)));
typedef union { Vector q; float f[4]; } ChoiceVector;
typedef struct {
    unsigned char pad0[0xE0]; float origin[4];
    unsigned char pad1[0x1B8 - 0xF0]; int count;
    unsigned char pad2[0x208 - 0x1BC]; short gate;
    unsigned char pad3[0xC28 - 0x20A]; int flags;
    unsigned char pad4[0x2290 - 0xC2C]; void *object;
    unsigned char pad5[0x22A4 - 0x2294]; int mode;
    unsigned char pad6[0x22BB - 0x22A8]; unsigned char byte_22bb;
    unsigned char pad7[0x24CC - 0x22BC]; int state;
} HeroChoiceState;
extern HeroChoiceState g_hero_state;
extern int g_current_map_index __attribute__((sda));
extern int g_menu_choice_table __attribute__((sda));
extern unsigned char g_item_slot_to_record[];
typedef struct { unsigned char pad0[4]; unsigned char active; unsigned char pad1[0xE0 - 5]; } MappedClassEntry;
extern MappedClassEntry g_weapon_l00_table[];
typedef struct {
    unsigned char pad0[0x50]; int selector;
    unsigned char pad1[4]; float weight;
    unsigned char pad2[4]; int inactive;
    unsigned char pad3[12];
} ChoiceRecord;
extern ChoiceRecord g_hero_idle_choice_table[4];
extern int g_hero_idle_block_flag;
extern int hero_slot_item_id(int);
extern int CollLine(void *, void *, int, void *, int);
extern float math_random_float_range(float, float);

int func_PAL_L00_002CA888(int *selected)
{
    int choices[20], count = 0, index;
    ChoiceRecord *entry;
    ChoiceVector raised, origin;
    float sum, draw, value;
    if (g_hero_state.gate != 0) return 0;
    if (g_hero_state.state == 1) {
        *selected = 3;
        if (g_hero_idle_block_flag != 0) return 0;
        if ((g_hero_state.flags & 2) == 0) return 0;
        return math_random_float_range(0.0f, 1.0f) < 0.33f;
    }
    entry = g_hero_idle_choice_table;
    for (index = 0; index < 4; index++, entry++) {
        float zero = 0.0f;
        int area;
        if (entry->inactive != 0 || entry->weight == zero) continue;
        area = hero_slot_item_id(0);
        if (entry->selector != -1 && entry->selector != area) continue;
        if (index == 2) {
            if (g_current_map_index != 7 && g_current_map_index != 0x13) continue;
            if (g_hero_state.byte_22bb == 2) continue;
            qcopy(&origin, g_hero_state.origin);
            qcopy(&raised, &origin);
            raised.f[2] += 8.0f;
            if (CollLine(&origin, &raised, 2, g_hero_state.object, 0)) continue;
        }
        if (index == 3 && (g_hero_state.mode != 1 || g_hero_state.count > 42 || g_hero_state.state > 1)) continue;
        choices[count++] = index;
    }
    if (!count) return 0;
    sum = 0.0f;
    if (count > 0) {
        int size = sizeof(ChoiceRecord);
        int *p = choices;
        index = count;
        do {
            ChoiceRecord *r = (ChoiceRecord *)((char *)g_hero_idle_choice_table + *p * size);
            sum += 1.0f / (float)(int)(r->weight * 5e+01f);
            p++;
        } while (--index != 0);
    }
    value = math_random_float_range(0.0f, 1.0f);
    do { draw = value; } while (0);
    if (draw < sum) {
        float one, rate;
        ChoiceRecord *table;
        int size;
        int *cursor;
        one = 1.0f;
        table = g_hero_idle_choice_table;
        size = sizeof(ChoiceRecord);
        rate = 5e+01f;
        cursor = choices;
        for (index = 0; index < count; index++, cursor++) {
            int choice = *cursor;
            *selected = choice;
            sum -= one / (float)(int)(*(float *)((char *)table + choice * size + 0x58) * rate);
            if (sum < draw) break;
        }
        if (g_menu_choice_table == 30 && (g_weapon_l00_table + g_item_slot_to_record[30])->active == 0) {
            if (*selected == 1) *selected = 0x91;
            else if (*selected == 2) *selected = 0x92;
        }
        return 1;
    }
    return 0;
}
