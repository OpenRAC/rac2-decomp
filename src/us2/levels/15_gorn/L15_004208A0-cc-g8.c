/* func_US2_L15_004208A0, the USA v2.00 copy of func_L15_0041F2F8: the same C, where rename func_002AF0A8 becomes func_US2_002AFF10. */
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
extern void func_US2_002AFF10(int);
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
extern int D_L15_001A8F00;
extern char D_L15_001B0FD0[];
extern int D_L15_001B2148;
extern char *D_L15_001B270C;
extern char D_L15_001BF9C0[];
extern short **D_L15_002B6840[];
extern char D_L15_002BBCB0[];

typedef struct {
    char pad00[0x10]; char pos[0x10];
    unsigned char state; char pad21[0x47];
    TriggerVars *vars; char pad6C[0x3E];
    short id; char padAC[4];
    unsigned char group; char padB1; short oclass; char padB4[8];
    unsigned char hit; char padBD[0x33];
    char dir[0x10];
} Thing;

void func_US2_L15_004208A0(Thing *m)
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
        if (D_L15_001A8F00 != 0)
            break;
        if (p->msg != -1 && IsPointInCuboid(g_hero_state.body, p->msg) == 0)
            break;
        fail = 1;
        missing = 1;
        if (D_L15_002B6840[g_current_map_index] != 0 && D_L15_002B6840[g_current_map_index][p->idx] != 0) {
            for (i = 0; D_L15_002B6840[g_current_map_index][p->idx][i] != -1; i++) {
                int e = D_L15_002B6840[g_current_map_index][p->idx][i];

                missing = 0;
                if (p->tail.b.quiet == 0) {
                    int bit = 1 << (e & 0x1F);
                    if (D_00139768[(unsigned int)e >> 2] & bit)
                        continue;
                }
                if (req_push_queue(D_L15_001BF9C0, e) == 0 && i == 0) {
                    STUB_printf(D_L15_002BBCB0, m->id, m->oclass, g_current_map_index, p->idx, e);
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
                STUB_printf(D_L15_001B0FD0, g_current_map_index, p->idx);
        } while (0);
        if (fail != 0) {
            p->tail.b.had = 0;
            moby_set_state(m, 4, -1);
            break;
        }
        p->tail.b.had = 1;
        req_launch_queued(D_L15_001BF9C0);
        if (D_L15_001B2148 < 5 || (g_current_map_index == 6 && p->idx == 0))
            game_set_slowdown_factor();
        moby_set_state(m, 3, -1);
        break;
    case 3:
        if (game_is_either_mode_two() == 0) {
            if (p->link != -1) {
                char *o = D_L15_001B270C + (p->link << 7);
                hero_reset_position_and_direction(o + 0x30, o + 0x70, 0, 1);
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
                func_US2_002AFF10(p->item);
            notify = 1;
        }
        if (m->group != 0xFF && !(D_0019B2E8[m->group + g_current_map_index * 16] & 0x80)) {
            moby_mark_table_entry_flagged(m->group);
            notify = 1;
        }
        if (p->count != 0 && (p->tail.word & 0xFFFF0000)) {
            if (p->link != -1) {
                char *o = D_L15_001B270C + (p->link << 7);
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
                func_US2_002AFF10(p->item);
            played = 1;
        }
        if (m->group != 0xFF && !(D_0019B2E8[m->group + g_current_map_index * 16] & 0x80)) {
            moby_mark_table_entry_flagged(m->group);
            played = 1;
        }
        if (p->count > 0 && (p->tail.word & 0xFFFF0000)) {
            if (p->link != -1) {
                char *o = D_L15_001B270C + (p->link << 7);
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
