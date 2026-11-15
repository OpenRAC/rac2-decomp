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
extern void MemcardSave(int, int);
extern void moby_mark_spawned(void *);
extern void moby_mark_table_entry_flagged(int);
extern void moby_set_state(void *, int, int);
extern int IsPointInCuboid(void *, int);
extern void moby_mark_flag_and_append_to_list(int);
extern void snd_play_indexed(int);
extern int flag_is_third_pending_set(void *);
extern void level_capture_checkpoint_state(void *, void *);
extern void game_set_slowdown_factor(void);
extern int game_is_either_mode_two(void);
extern void hero_reset_position_and_direction(void *, void *, int, int);

extern unsigned int D_00139768[];
typedef struct {
    char pad0[0x80]; char body[0x2294 - 0x80];
    int mode; char pad2298[0x24CC - 0x2298];
    int health;
} HeroView;
extern HeroView g_hero_state;
extern char g_hero_position[];
extern unsigned char D_0019B2E8[];
extern int g_current_map_index;
extern unsigned char D_001A7BC8[] MACRO_ADDR;
extern int D_L22_001A8F00;
extern char D_L22_001B13D0[];
extern int D_L22_001B1C48;
extern char *D_L22_001B220C;
extern char D_L22_001BFE80[];
extern short **D_L22_002A3E20[];
extern char D_L22_002A6DB0[];

typedef struct {
    char pad00[0x10]; char pos[0x10];
    unsigned char state; char pad21[0x47];
    TriggerVars *vars; char pad6C[0x3E];
    short id; char padAC[4];
    unsigned char group; char padB1; short oclass; char padB4[8];
    unsigned char hit; char padBD[0x33];
    char dir[0x10];
} Thing;

/* Update for a trigger object that waits for the hero, checks the needed items, then plays a message and hands out its item or event. */
void item_l22_give_trigger_update(Thing *trigger)
{
    TriggerVars *vars = trigger->vars;
    int notify, i, missing, fail;
    int played;

    switch (trigger->state) {
    case 0:
        if ((vars->item != -1 && D_001A7BC8[vars->item] != 0)
            || (trigger->group != 0xFF && (D_0019B2E8[trigger->group + g_current_map_index * 16] & 0x80))) {
            moby_mark_spawned(trigger);
            break;
        }
        moby_set_state(trigger, 1, -1);
    case 1:
        if (vars->on == 0 && flag_is_third_pending_set(trigger) == 0 && trigger->hit == 0)
            break;
        vars->on = 1;
        moby_set_state(trigger, 2, -1);
    case 2:
        if (vars->on == 0) {
            moby_set_state(trigger, 1, -1);
            break;
        }
        if (g_hero_state.mode == 0x1C)
            break;
        if (g_hero_state.health <= 0)
            break;
        if (D_L22_001A8F00 != 0)
            break;
        if (vars->msg != -1 && IsPointInCuboid(g_hero_state.body, vars->msg) == 0)
            break;
        fail = 1;
        missing = 1;
        if (D_L22_002A3E20[g_current_map_index] != 0 && D_L22_002A3E20[g_current_map_index][vars->idx] != 0) {
            for (i = 0; D_L22_002A3E20[g_current_map_index][vars->idx][i] != -1; i++) {
                int e = D_L22_002A3E20[g_current_map_index][vars->idx][i];

                missing = 0;
                if (vars->tail.b.quiet == 0) {
                    int bit = 1 << (e & 0x1F);
                    if (D_00139768[(unsigned int)e >> 2] & bit)
                        continue;
                }
                if (req_push_queue(D_L22_001BFE80, e) == 0 && i == 0) {
                    STUB_printf(D_L22_002A6DB0, trigger->id, trigger->oclass, g_current_map_index, vars->idx, e);
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
                STUB_printf(D_L22_001B13D0, g_current_map_index, vars->idx);
        } while (0);
        if (fail != 0) {
            vars->tail.b.had = 0;
            moby_set_state(trigger, 4, -1);
            break;
        }
        vars->tail.b.had = 1;
        req_launch_queued(D_L22_001BFE80);
        if (D_L22_001B1C48 < 5 || (g_current_map_index == 6 && vars->idx == 0))
            game_set_slowdown_factor();
        moby_set_state(trigger, 3, -1);
        break;
    case 3:
        if (game_is_either_mode_two() == 0) {
            if (vars->link != -1) {
                char *o = D_L22_001B220C + (vars->link << 7);
                hero_reset_position_and_direction(o + 0x30, o + 0x70, 0, 1);
            }
            moby_set_state(trigger, 4, -1);
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
                snd_play_indexed(vars->item);
            notify = 1;
        }
        if (trigger->group != 0xFF && !(D_0019B2E8[trigger->group + g_current_map_index * 16] & 0x80)) {
            moby_mark_table_entry_flagged(trigger->group);
            notify = 1;
        }
        if (vars->count != 0 && (vars->tail.word & 0xFFFF0000)) {
            if (vars->link != -1) {
                char *o = D_L22_001B220C + (vars->link << 7);
                level_capture_checkpoint_state(o + 0x30, o + 0x70);
            } else
                level_capture_checkpoint_state(trigger->pos, trigger->dir);
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
                snd_play_indexed(vars->item);
            played = 1;
        }
        if (trigger->group != 0xFF && !(D_0019B2E8[trigger->group + g_current_map_index * 16] & 0x80)) {
            moby_mark_table_entry_flagged(trigger->group);
            played = 1;
        }
        if (vars->count > 0 && (vars->tail.word & 0xFFFF0000)) {
            if (vars->link != -1) {
                char *o = D_L22_001B220C + (vars->link << 7);
                level_capture_checkpoint_state(o + 0x30, o + 0x70);
            } else
                level_capture_checkpoint_state(g_hero_position, g_hero_position + 0x10);
        }
        if (vars->tail.low != -1)
            data_set_small_value_and_refresh(vars->tail.low, 1);
        else if ((played != 0 || vars->tail.b.had != 0) && vars->count != vars->tail.low)
            MemcardSave(0, -1);
        moby_mark_spawned(trigger);
        break;
    }
}
