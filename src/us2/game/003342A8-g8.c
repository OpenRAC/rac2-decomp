/* func_US2_003342A8, the v2.00 copy of func_003334B0: the same C, where func_0026F778 becomes
 * func_0026F780 and func_002AF0A8 becomes func_US2_002AFF10. */
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
extern void stub_empty_14(void *, void *, int, int);

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
extern int g_current_game_mode;
extern char g_str_item_reward_trigger_debug[];
extern int g_game_time;
extern char *g_vec_record_table;
extern char g_loader_movie[];
extern short **g_item_reward_tables[];
extern char g_str_reward_trigger_debug[];

typedef struct {
    char pad00[0x10]; char pos[0x10];
    unsigned char state; char pad21[0x47];
    TriggerVars *vars; char pad6C[0x3E];
    short id; char padAC[4];
    unsigned char group; char padB1; short oclass; char padB4[8];
    unsigned char hit; char padBD[0x33];
    char dir[0x10];
} Thing;

/* Runs a reward trigger: when the hero enters its box it queues the item rewards, sets off the movie, marks the item and group as collected and saves the game (v2.00 copy). */
void item_reward_trigger_update_us2(Thing *moby)
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
        if (g_current_game_mode != 0)
            break;
        if (vars->msg != -1 && IsPointInCuboid(g_hero_state.body, vars->msg) == 0)
            break;
        fail = 1;
        missing = 1;
        if (g_item_reward_tables[g_current_map_index] != 0 && g_item_reward_tables[g_current_map_index][vars->idx] != 0) {
            for (i = 0; g_item_reward_tables[g_current_map_index][vars->idx][i] != -1; i++) {
                int reward_item = g_item_reward_tables[g_current_map_index][vars->idx][i];

                missing = 0;
                if (vars->tail.b.quiet == 0) {
                    int bit = 1 << (reward_item & 0x1F);
                    if (g_request_flag_table[(unsigned int)reward_item >> 2] & bit)
                        continue;
                }
                if (req_push_queue(g_loader_movie, reward_item) == 0 && i == 0) {
                    STUB_printf(g_str_reward_trigger_debug, moby->id, moby->oclass, g_current_map_index, vars->idx, reward_item);
                    return;
                }
                fail = 0;
            }
            /* Retail allocates missing ahead of fail, which takes a fourth reference to it.
               This test supplies one and leaves no word: played is dead on this path, so
               flow deletes the arm and jump2 deletes the emptied test. It is not `!= 0`
               because thread_jumps would then send it past the test below and keep it. */
            if (missing > 0)
                played = vars->item + 1;
        }
        if (missing != 0)
            STUB_printf(g_str_item_reward_trigger_debug, g_current_map_index, vars->idx);
        if (fail != 0) {
            vars->tail.b.had = 0;
            moby_set_state(moby, 4, -1);
            break;
        }
        vars->tail.b.had = 1;
        req_launch_queued(g_loader_movie);
        if (g_game_time < 5 || (g_current_map_index == 6 && vars->idx == 0))
            game_set_slowdown_factor();
        moby_set_state(moby, 3, -1);
        break;
    case 3:
        if (game_is_either_mode_two() == 0) {
            if (vars->link != -1) {
                char *record = g_vec_record_table + (vars->link << 7);
                stub_empty_14(record + 0x30, record + 0x70, 0, 1);
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
                char *record = g_vec_record_table + (vars->link << 7);
                level_capture_checkpoint_state(record + 0x30, record + 0x70);
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
                char *record = g_vec_record_table + (vars->link << 7);
                level_capture_checkpoint_state(record + 0x30, record + 0x70);
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
