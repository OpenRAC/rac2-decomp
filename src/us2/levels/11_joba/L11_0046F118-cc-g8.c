/* func_US2_L11_0046F118, the USA v2.00 copy of func_L11_0046D660: the same C, where rename func_002AF0A8 becomes func_US2_002AFF10. */
/* Family F7: one body per level (L02, L05, L06, L10, L11, L12, L13, L15, L18, L22, L23), the
   same opcodes in each. Built with -malign-loops=2 (config/cflags.txt): see the print below. */
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
extern void snd_play_indexed_us2(int);
extern int flag_is_third_pending_set(void *);
extern void level_capture_checkpoint_state(void *, void *);
extern void game_set_slowdown_factor(void);
extern int game_is_either_mode_two(void);
extern void hero_reset_position_and_direction(void *, void *, int, int);

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
extern int g_arena_state;
extern char g_str_l11_item_trigger_debug[];
extern int g_arena_progress_level;
extern char *g_arena_camera_table;
extern char g_request_l11_queue[];
extern short **g_trigger_entry_lists_by_map[];
extern char g_str_debug_trigger[];

typedef struct {
    char pad00[0x10]; char pos[0x10];
    unsigned char state; char pad21[0x47];
    TriggerVars *vars; char pad6C[0x3E];
    short id; char padAC[4];
    unsigned char group; char padB1; short oclass; char padB4[8];
    unsigned char hit; char padBD[0x33];
    char dir[0x10];
} Thing;

/* Updates a trigger moby: it waits for the hero to step in, checks the needed items, plays the message, gives the reward item and then removes itself. (USA v2.00) */
void item_l11_trigger_update_us2(Thing *moby)
{
    TriggerVars *vars = moby->vars;
    int notify, i, missing, fail;
    int played;

    switch (moby->state) {
    case 0:
        if ((vars->item != -1 && g_map_visited_flags[vars->item] != 0)
            || (moby->group != 0xFF && (g_moby_group_flags[moby->group + g_current_map_index * 16] & 0x80))) {
            moby_mark_spawned(moby);
            break;
        }
        moby_set_state(moby, 1, -1);
    case 1:
        if (vars->on == 0 && flag_is_third_pending_set(moby) == 0 && moby->hit == 0)
            break;
        vars->on = 1;
        moby_set_state(moby, 2, -1);
    case 2:
        if (vars->on == 0) {
            moby_set_state(moby, 1, -1);
            break;
        }
        if (g_hero_state.mode == 0x1C)
            break;
        if (g_hero_state.health <= 0)
            break;
        if (g_arena_state != 0)
            break;
        if (vars->msg != -1 && IsPointInCuboid(g_hero_state.body, vars->msg) == 0)
            break;
        fail = 1;
        missing = 1;
        if (g_trigger_entry_lists_by_map[g_current_map_index] != 0 && g_trigger_entry_lists_by_map[g_current_map_index][vars->idx] != 0) {
            for (i = 0; g_trigger_entry_lists_by_map[g_current_map_index][vars->idx][i] != -1; i++) {
                int e = g_trigger_entry_lists_by_map[g_current_map_index][vars->idx][i];

                missing = 0;
                if (vars->tail.b.quiet == 0) {
                    int bit = 1 << (e & 0x1F);
                    if (g_request_flag_table[(unsigned int)e >> 2] & bit)
                        continue;
                }
                if (req_push_queue(g_request_l11_queue, e) == 0 && i == 0) {
                    STUB_printf(g_str_debug_trigger, moby->id, moby->oclass, g_current_map_index, vars->idx, e);
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
                STUB_printf(g_str_l11_item_trigger_debug, g_current_map_index, vars->idx);
        } while (0);
        if (fail != 0) {
            vars->tail.b.had = 0;
            moby_set_state(moby, 4, -1);
            break;
        }
        vars->tail.b.had = 1;
        req_launch_queued(g_request_l11_queue);
        if (g_arena_progress_level < 5 || (g_current_map_index == 6 && vars->idx == 0))
            game_set_slowdown_factor();
        moby_set_state(moby, 3, -1);
        break;
    case 3:
        if (game_is_either_mode_two() == 0) {
            if (vars->link != -1) {
                char *o = g_arena_camera_table + (vars->link << 7);
                hero_reset_position_and_direction(o + 0x30, o + 0x70, 0, 1);
            }
            moby_set_state(moby, 4, -1);
        }
        if (g_current_map_index != 0)
            break;
        if (vars->item == -1)
            break;
        if (game_is_either_mode_two() != 0)
            break;
        notify = 0;
        if (vars->item != -1) {
            moby_mark_flag_and_append_to_list(vars->item);
            if (vars->item != 0x18)
                snd_play_indexed_us2(vars->item);
            notify = 1;
        }
        if (moby->group != 0xFF && !(g_moby_group_flags[moby->group + g_current_map_index * 16] & 0x80)) {
            moby_mark_table_entry_flagged(moby->group);
            notify = 1;
        }
        if (vars->count != 0 && (vars->tail.word & 0xFFFF0000)) {
            if (vars->link != -1) {
                char *o = g_arena_camera_table + (vars->link << 7);
                level_capture_checkpoint_state(o + 0x30, o + 0x70);
            } else
                level_capture_checkpoint_state(moby->pos, moby->dir);
        }
        if (vars->tail.low != -1)
            data_set_small_value_and_refresh(vars->tail.low, 1);
        else if (notify != 0 || vars->tail.b.had != 0)
            MemcardSave(0, -1);
        break;
    case 4:
        played = 0;
        if (vars->item != -1) {
            moby_mark_flag_and_append_to_list(vars->item);
            if (vars->item != 0x18)
                snd_play_indexed_us2(vars->item);
            played = 1;
        }
        if (moby->group != 0xFF && !(g_moby_group_flags[moby->group + g_current_map_index * 16] & 0x80)) {
            moby_mark_table_entry_flagged(moby->group);
            played = 1;
        }
        if (vars->count > 0 && (vars->tail.word & 0xFFFF0000)) {
            if (vars->link != -1) {
                char *o = g_arena_camera_table + (vars->link << 7);
                level_capture_checkpoint_state(o + 0x30, o + 0x70);
            } else
                level_capture_checkpoint_state(g_hero_position, g_hero_position + 0x10);
        }
        if (vars->tail.low != -1)
            data_set_small_value_and_refresh(vars->tail.low, 1);
        else if ((played != 0 || vars->tail.b.had != 0) && vars->count != vars->tail.low)
            MemcardSave(0, -1);
        moby_mark_spawned(moby);
        break;
    }
}
