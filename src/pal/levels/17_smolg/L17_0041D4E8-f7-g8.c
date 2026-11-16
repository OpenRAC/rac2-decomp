/* func_PAL_L17_0041D4E8, the PAL copy of func_L00_0040EAA0: the same C, where func_002F5CC8
   becomes func_PAL_002F6C18; func_L00_002B9D60 becomes func_PAL_L00_002B9CD8; func_002AF0A8
   becomes func_PAL_002AFC10. */
#include "common.h"

typedef struct {
    int msg;          /* 0x0 */
    int link;         /* 0x4 */
    unsigned char idx;   /* 0x8 */
    signed char item;    /* 0x9 */
    unsigned char on;    /* 0xA */
    signed char count;   /* 0xB */
    union { int word; signed char low; struct { char pad[1]; unsigned char quiet; char pad2; unsigned char had; } b; } tail; /* 0xC */
} TriggerVars;

extern void STUB_printf(const char *, ...);
extern int req_push_queue(void *, int);
extern int req_launch_queued(void *);  /* its result is tested elsewhere */
extern void data_set_small_value_and_refresh(int, int);
extern int MemcardSave(int, int);
extern void moby_mark_spawned(void *);
extern void moby_mark_table_entry_flagged(int);
extern void moby_set_state(void *, int, int);
extern int IsPointInCuboid(void *, int);
extern void moby_mark_flag_and_append_to_list(int);
extern void snd_play_indexed_pal(int);
extern int flag_is_third_pending_set(void *);
extern void level_capture_checkpoint_state(void *, void *);
extern void game_set_slowdown_factor_pal(void);
extern int game_is_either_mode_two(void);
extern void hero_reset_position_and_direction_pal(void *, void *, int, int);

extern unsigned int g_request_flag_table[];
typedef struct {
    char pad0[0x80]; char body[0x2294 - 0x80];
    int mode; char pad2298[0x24CC - 0x2298];
    int health;
} HeroView;
extern HeroView g_hero_state;
extern char g_hero_position[];
extern unsigned char g_moby_group_flags[];
extern int g_current_map_index;
extern unsigned char g_map_visited_flags[] MACRO_ADDR;
extern int g_coin_door_state;
extern char g_str_l06_item_trigger_debug[];
extern int g_game_l06_frame_counter;
extern char *g_region_table;
extern char g_request_l06_queue[];
extern short **g_item_trigger_entry_lists[];
extern char g_str_l06_item_trigger_debug_2[];

typedef struct {
    char pad00[0x10]; char pos[0x10];
    unsigned char state; char pad21[0x47];
    TriggerVars *vars; char pad6C[0x3E];
    short id; char padAC[4];
    unsigned char group; char padB1; short oclass; char padB4[8];
    unsigned char hit; char padBD[0x33];
    char dir[0x10];
} Thing;

void func_PAL_L17_0041D4E8(Thing *m)
{
    TriggerVars *p = m->vars;
    int notify, i, missing, fail;
    int played;

    switch (m->state) {
    case 0:
        if ((p->item != -1 && g_map_visited_flags[p->item] != 0)
            || (m->group != 0xFF && (g_moby_group_flags[m->group + g_current_map_index * 16] & 0x80))) {
            moby_mark_spawned(m);
            break;
        }
        moby_set_state(m, 1, -1);
    case 1:
        if (p->on == 0 && flag_is_third_pending_set(m) == 0 && m->hit == 0)
            break;
        p->on = 1;
        moby_set_state(m, 2, -1);
    case 2:
        if (p->on == 0) {
            moby_set_state(m, 1, -1);
            break;
        }
        if (g_hero_state.mode == 0x1C)
            break;
        if (g_hero_state.health <= 0)
            break;
        if (g_coin_door_state != 0)
            break;
        if (p->msg != -1 && IsPointInCuboid(g_hero_state.body, p->msg) == 0)
            break;
        fail = 1;
        missing = 1;
        if (g_item_trigger_entry_lists[g_current_map_index] != 0 && g_item_trigger_entry_lists[g_current_map_index][p->idx] != 0) {
            for (i = 0; g_item_trigger_entry_lists[g_current_map_index][p->idx][i] != -1; i++) {
                int e = g_item_trigger_entry_lists[g_current_map_index][p->idx][i];

                missing = 0;
                if (p->tail.b.quiet == 0) {
                    int bit = 1 << (e & 0x1F);
                    if (g_request_flag_table[(unsigned int)e >> 2] & bit)
                        continue;
                }
                if (req_push_queue(g_request_l06_queue, e) == 0 && i == 0) {
                    STUB_printf(g_str_l06_item_trigger_debug_2, m->id, m->oclass, g_current_map_index, p->idx, e);
                    return;
                }
                fail = 0;
            }
        }
        /* Retail keeps missing in $s5 above fail: the test's do-while (a debug-print macro's
           shape) counts it at loop depth, its fourth reference. Its loop label is not aligned
           in retail, so the unit turns loop alignment off; the other loop's label is already
           on an 8-byte boundary. */
        do {
            if (missing != 0)
                STUB_printf(g_str_l06_item_trigger_debug, g_current_map_index, p->idx);
        } while (0);
        if (fail != 0) {
            p->tail.b.had = 0;
            moby_set_state(m, 4, -1);
            break;
        }
        p->tail.b.had = 1;
        req_launch_queued(g_request_l06_queue);
        if (g_game_l06_frame_counter < 5 || (g_current_map_index == 6 && p->idx == 0))
            game_set_slowdown_factor_pal();
        moby_set_state(m, 3, -1);
        break;
    case 3:
        if (game_is_either_mode_two() == 0) {
            if (p->link != -1) {
                char *o = g_region_table + (p->link << 7);
                hero_reset_position_and_direction_pal(o + 0x30, o + 0x70, 0, 1);
            }
            moby_set_state(m, 4, -1);
        }
        if (g_current_map_index != 0)
            break;
        if (p->item == -1)
            break;
        if (game_is_either_mode_two() != 0)
            break;
        notify = 0;
        if (p->item != -1) {
            moby_mark_flag_and_append_to_list(p->item);
            if (p->item != 0x18)
                snd_play_indexed_pal(p->item);
            notify = 1;
        }
        if (m->group != 0xFF && !(g_moby_group_flags[m->group + g_current_map_index * 16] & 0x80)) {
            moby_mark_table_entry_flagged(m->group);
            notify = 1;
        }
        if (p->count != 0 && (p->tail.word & 0xFFFF0000)) {
            if (p->link != -1) {
                char *o = g_region_table + (p->link << 7);
                level_capture_checkpoint_state(o + 0x30, o + 0x70);
            } else
                level_capture_checkpoint_state(m->pos, m->dir);
        }
        if (p->tail.low != -1)
            data_set_small_value_and_refresh(p->tail.low, 1);
        else if (notify != 0 || p->tail.b.had != 0)
            MemcardSave(0, -1);
        break;
    case 4:
        played = 0;
        if (p->item != -1) {
            moby_mark_flag_and_append_to_list(p->item);
            if (p->item != 0x18)
                snd_play_indexed_pal(p->item);
            played = 1;
        }
        if (m->group != 0xFF && !(g_moby_group_flags[m->group + g_current_map_index * 16] & 0x80)) {
            moby_mark_table_entry_flagged(m->group);
            played = 1;
        }
        if (p->count > 0 && (p->tail.word & 0xFFFF0000)) {
            if (p->link != -1) {
                char *o = g_region_table + (p->link << 7);
                level_capture_checkpoint_state(o + 0x30, o + 0x70);
            } else
                level_capture_checkpoint_state(g_hero_position, g_hero_position + 0x10);
        }
        if (p->tail.low != -1)
            data_set_small_value_and_refresh(p->tail.low, 1);
        else if ((played != 0 || p->tail.b.had != 0) && p->count != p->tail.low)
            MemcardSave(0, -1);
        moby_mark_spawned(m);
        break;
    }
}
