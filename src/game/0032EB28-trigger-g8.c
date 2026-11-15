/* func_003334B0, in a unit of its own because it needs -G8 and owns its switch's jump table. */
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
extern void snd_play_indexed(int);
extern int flag_is_third_pending_set(void *);
extern void level_capture_checkpoint_state(void *, void *);
extern void game_set_slowdown_factor(void);
extern int game_is_either_mode_two(void);
extern void stub_empty_14(void *, void *, int, int);

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
extern int g_current_game_mode;
extern char D_001B0ED0[];
extern int g_game_time;
extern char *D_001B1C4C;
extern char D_001BAD40[];
extern short **D_0026C320[];
extern char D_0026E6A0[];

typedef struct {
    char pad00[0x10]; char pos[0x10];
    unsigned char state; char pad21[0x47];
    TriggerVars *vars; char pad6C[0x3E];
    short id; char padAC[4];
    unsigned char group; char padB1; short oclass; char padB4[8];
    unsigned char hit; char padBD[0x33];
    char dir[0x10];
} Thing;

/* Runs a trigger that waits for the player, checks for needed items and then gives rewards or messages. It removes itself when done. */
void item_reward_trigger_update(Thing *m)
{
    TriggerVars *p = m->vars;
    int notify, i, missing, fail;
    int played;

    switch (m->state) {
    case 0:
        if ((p->item != -1 && D_001A7BC8[p->item] != 0)
            || (m->group != 0xFF && (D_0019B2E8[m->group + g_current_map_index * 16] & 0x80))) {
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
        if (g_current_game_mode != 0)
            break;
        if (p->msg != -1 && IsPointInCuboid(g_hero_state.body, p->msg) == 0)
            break;
        fail = 1;
        missing = 1;
        if (D_0026C320[g_current_map_index] != 0 && D_0026C320[g_current_map_index][p->idx] != 0) {
            for (i = 0; D_0026C320[g_current_map_index][p->idx][i] != -1; i++) {
                int e = D_0026C320[g_current_map_index][p->idx][i];

                missing = 0;
                if (p->tail.b.quiet == 0) {
                    int bit = 1 << (e & 0x1F);
                    if (D_00139768[(unsigned int)e >> 2] & bit)
                        continue;
                }
                if (req_push_queue(D_001BAD40, e) == 0 && i == 0) {
                    STUB_printf(D_0026E6A0, m->id, m->oclass, g_current_map_index, p->idx, e);
                    return;
                }
                fail = 0;
            }
            /* Retail allocates missing ahead of fail, which takes a fourth reference to it.
               This test supplies one and leaves no word: played is dead on this path, so
               flow deletes the arm and jump2 deletes the emptied test. It is not `!= 0`
               because thread_jumps would then send it past the test below and keep it. */
            if (missing > 0)
                played = p->item + 1;
        }
        if (missing != 0)
            STUB_printf(D_001B0ED0, g_current_map_index, p->idx);
        if (fail != 0) {
            p->tail.b.had = 0;
            moby_set_state(m, 4, -1);
            break;
        }
        p->tail.b.had = 1;
        req_launch_queued(D_001BAD40);
        if (g_game_time < 5 || (g_current_map_index == 6 && p->idx == 0))
            game_set_slowdown_factor();
        moby_set_state(m, 3, -1);
        break;
    case 3:
        if (game_is_either_mode_two() == 0) {
            if (p->link != -1) {
                char *o = D_001B1C4C + (p->link << 7);
                stub_empty_14(o + 0x30, o + 0x70, 0, 1);
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
                snd_play_indexed(p->item);
            notify = 1;
        }
        if (m->group != 0xFF && !(D_0019B2E8[m->group + g_current_map_index * 16] & 0x80)) {
            moby_mark_table_entry_flagged(m->group);
            notify = 1;
        }
        if (p->count != 0 && (p->tail.word & 0xFFFF0000)) {
            if (p->link != -1) {
                char *o = D_001B1C4C + (p->link << 7);
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
                snd_play_indexed(p->item);
            played = 1;
        }
        if (m->group != 0xFF && !(D_0019B2E8[m->group + g_current_map_index * 16] & 0x80)) {
            moby_mark_table_entry_flagged(m->group);
            played = 1;
        }
        if (p->count > 0 && (p->tail.word & 0xFFFF0000)) {
            if (p->link != -1) {
                char *o = D_001B1C4C + (p->link << 7);
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
