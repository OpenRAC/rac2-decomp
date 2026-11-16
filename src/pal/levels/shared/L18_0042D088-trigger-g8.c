#include "common.h"
typedef struct { float v[4]; } TriggerPoint __attribute__((aligned(16)));
typedef u8 TriggerActor[0x100];
extern TriggerActor *g_moby_l18_table __attribute__((sda));
extern u8 g_hero_state[], g_hero_position[], g_moby_nibble_table[], g_moby_group_flags[];
typedef struct { u8 p[0x464]; u8 x[1]; } Hist;
extern u8 g_trigger_l18_flags[];
extern int g_current_map_index;
extern float FastAddRotations(float, float), vec_distance_xy(void *, void *), math_fast_sin_or_cos_b(float);
extern int FloatToInt(float);
extern void moby_mark_table_entry_flagged(int), moby_set_flag_bit(void *, int);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void hero_detach_from_object(int), moby_set_group_enabled(int, int), moby_set_byte_on_group(int, int);
extern void level_capture_checkpoint_state(void *, void *);
extern int snd_play_from_class_bank(int, int, void *, int);

/* Activate the tagged linkage when the hero touches this rotating trigger. */
void rotating_trigger_update_pal(u8 *moby)
{
    TriggerPoint point;
    u8 *vars = *(u8 **)(moby + 0x68);
    int touched, value;
    float distance;
    unsigned short id;
    u8 *counter; u8 *hero_state;
    if (!vars) return;
    *(float *)(vars + 4) = FastAddRotations(*(float *)(vars + 4), 0.12566372752189636f);
    if (moby[0x20] == 0) {
        moby_transform_joint_to_world(moby, 0, &point);
        touched = 0;
        distance = vec_distance_xy(g_hero_state + 0x80, &point);
        vars[8] = 0;
        hero_state = g_hero_state;
        if (*(u8 **)(hero_state + 0x33C) == moby && *(int *)(hero_state + 0x340) &&
            distance < (*(float *)(moby + 0x2C) * 0.5f) / *(float *)(*(u8 **)(moby + 0x24) + 0x24)) {
            touched = 1;
            if (!vars[0x10]) {
                unsigned short id2 = *(u16 *)(moby + 0xB2);
                if (id2 & 1) {
                    u8 *h = &g_moby_nibble_table[((short)id2 >> 1) + (g_current_map_index << 10)];
                    if (((*h >> 4) & 7) != 7) *h += 16;
                } else {
                    u8 *h = &g_moby_nibble_table[((short)id2 >> 1) + (g_current_map_index << 10)];
                    if ((*h & 7) != 7) (*h)++;
                }
            }
            if (vars[0x12]) moby_mark_table_entry_flagged(moby[0xB0]);
        }
        if (moby[0xB0] != 255 && !vars[0x11]) {
            id = *(u16 *)(moby + 0xB2);
            if (((Hist *)g_trigger_l18_flags)->x[(short)id]) goto activate;
            { int n = g_moby_nibble_table[((short)id >> 1) + (g_current_map_index << 10)];
            if (id & 1) { if ((n >> 4) & 7) goto activate; }
            else if (n & 7) goto activate; }
        }
        if ((vars[0x13] && (g_moby_group_flags[moby[0xB0] + (g_current_map_index << 4)] & 0x80)) || touched) {
activate:
            moby[0x20] = 1;
            moby[0xBC] = 1;
            if (*(int *)vars != -1) moby_set_flag_bit(g_moby_l18_table[*(int *)vars], 1);
            if (vars[9]) hero_detach_from_object(0);
            if (*(int *)(vars + 0xC) != -1) {
                if (vars[0xB]) moby_set_group_enabled(*(int *)(vars + 0xC), vars[0xB]);
                if (vars[0xA] != 255) moby_set_byte_on_group(*(int *)(vars + 0xC), vars[0xA]);
            }
            if (vars[0x12] && touched) {
                if (g_hero_state[0x22B4]) {
                    u8 saved = g_hero_state[0x22B4];
                    u8 *hero = *(u8 **)(g_hero_state + 0xC18);
                    u8 *previous = *(u8 **)(g_hero_state + 0x2290);
                    g_hero_state[0x22B4] = 0;
                    *(u8 **)(g_hero_state + 0x2290) = hero;
                    level_capture_checkpoint_state(hero + 0x10, hero + 0xF0);
                    g_hero_state[0x22B4] = saved;
                    *(u8 **)(g_hero_state + 0x2290) = previous;
                } else level_capture_checkpoint_state(g_hero_state + 0x80, g_hero_state + 0x90);
            }
        }
        value = FloatToInt((math_fast_sin_or_cos_b(*(float *)(vars + 4)) * 4.0f - 3.0f) * 128.0f);
        if (value > 128) value = 128;
        else if (value < 32) value = 32;
        { u32 color = ((u32)value << 8) | 0x80000000U;
        *(u32 *)(moby + 0x78) = (((u32)value << 16) | color) | value; }
    } else {
        if (!vars[8]) {
            snd_play_from_class_bank(0, 0, moby, 0x8A1);
            vars[8] = 1;
        }
        *(u32 *)(moby + 0x78) = 0x80208010;
    }
}
