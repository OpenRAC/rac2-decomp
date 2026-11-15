#include "names.h"
/* func_US2_L00_002D6258: the v2.00 copy of func_L00_002D5EB8 (src/levels/shared/L00_002D3798-g8.c).
 * The same C; only callees that are the release's own functions differ:
 * func_00288508 is func_US2_00288F30,
 * func_L00_0030C7F8 is func_US2_L00_0030D9F8,
 * func_002B0A18 is func_US2_002B1880.
 */
#include "common.h"

/* The hero block: the two fields the loop tests. */
typedef struct {
    char pad0000[0x340];
    int f340;                   /* 0x0340 */
    char pad0344[0xF04];
    int weapon;                 /* 0x1248 */
} Hero5940;

extern Hero5940 g_hero_state;
extern int g_frame_l00_counter[] __attribute__((sda));
extern int D_0018C350[];
extern unsigned char D_001A7A00[] __attribute__((sda));
extern int D_0018C2EC[];
extern unsigned char D_001A7A28[] MACRO_ADDR;
extern unsigned char g_item_slot_to_record[];
extern int D_L00_001A903C;
extern unsigned short g_subtitle_history __attribute__((section(".data")));
extern int D_00139868[];
extern int D_001A7398[] MACRO_ADDR;
extern unsigned char g_item_owned_flags[] MACRO_ADDR;

/* One 0xE0-byte entry of D_L00_00262570, indexed through D_00139568. */
typedef struct {
    int exists;                 /* 0x00 */
    unsigned char state;        /* 0x04 */
    char pad05[0x7];
    int index;                  /* 0x0C */
    char pad10[0x3A];
    short value;                /* 0x4A */
    char pad4C[0x20];
    int limit;                  /* 0x6C */
    char pad70[0x70];
} Entry1269;

extern Entry1269 g_weapon_l00_table[];
extern int math_sum_table_entries_under_limit(int *, int *, int *);
extern void hud_queue_hint_message(int, int);
extern void effect_controller_spawn(void);
extern void func_US2_L00_0030D9F8(int);
extern void func_US2_002B1880(int, int);
extern int snd_play_from_global_bank(int, int, void *);
extern int flag_is_byte_set(void);
extern int menu_count_chain_entries_after_head(int);
extern void gfx_set_screen_pair_run_effect(int, int);
extern void menu_advance_chain_entry(int);
extern void func_US2_00288F30(int);
extern int ref_US2_L00_002D6258_00 __attribute__((sda));

static inline int special(int i)
{
    int r = 0;

    switch (i) {
    case 12:
    case 14:
    case 17:
    case 18:
    case 53:
        r = 1;
        break;
    }
    return r;
}

static inline int unlocked(Entry1269 *e, int i)
{
    if (e->state >= 2 || (e->state == 1 && special(i)))
        return 1;
    return 0;
}

static inline int owned(int i)
{
    if (g_weapon_l00_table[g_item_slot_to_record[i]].exists) {
        int n = menu_count_chain_entries_after_head(i);
        if (n >= 2 || (n == 1 && special(i)))
            return 1;
    }
    return 0;
}

void func_US2_L00_002D6258(void)
{
    int count, i, j, ok;

    if ((g_frame_l00_counter[0] & 15) == 1 && g_frame_l00_counter[0] != 1)
        return;
    count = 4;
    {
        int *p = D_0018C350;
        math_sum_table_entries_under_limit(p, p - 1, &count);
    }
    for (j = 0; j < 10; j++)
        if (D_001A7A28[j])
            count++;
    if (*(int *)D_001A7A00 != count) {
        if (ref_US2_L00_002D6258_00 >= 11 && *(int *)D_001A7A00 < count) {
            if (!g_subtitle_history)
                hud_queue_hint_message(0x9A9, 0);
            effect_controller_spawn();
            func_US2_L00_0030D9F8(0x168);
            func_US2_002B1880(0x1235, -1);
            snd_play_from_global_bank(6, 0, 0);
        }
        D_0018C2EC[0] = count;
        *(int *)D_001A7A00 = count;
    }

    for (i = 0; i < 56; i++) {
        if ((g_weapon_l00_table + g_item_slot_to_record[i])->state) {
            if (!flag_is_byte_set())
                continue;
            if (menu_count_chain_entries_after_head(i) == 1)
                continue;
        }
        {
            Entry1269 *e = &g_weapon_l00_table[g_item_slot_to_record[i]];
            int sel = 0;
            if (e->exists)
                sel = e->state == 3;
            if (sel)
                continue;
        }
        if (menu_count_chain_entries_after_head(i) <= 0)
            continue;
        {
            Entry1269 *e = &g_weapon_l00_table[g_item_slot_to_record[i]];
            if ((D_00139868[i] >> 5) < e->limit || e->limit <= 0)
                continue;
            if (i == 31 || i == 9 || i == 45) {
                gfx_set_screen_pair_run_effect(i, g_weapon_l00_table[g_item_slot_to_record[i]].value);
                continue;
            }
            if (g_hero_state.weapon == i) {
                if (!g_hero_state.f340)
                    continue;
                if (D_001A7398[e->index] != i)
                    continue;
                gfx_set_screen_pair_run_effect(i, e->value);
                continue;
            }
        }
        if (flag_is_byte_set()) {
            Entry1269 *e = &g_weapon_l00_table[g_item_slot_to_record[i]];
            if (!e->exists)
                continue;
            if (unlocked(e, i)) {
                if (owned(i)) {
                    menu_advance_chain_entry(i);
                    func_US2_00288F30(i);
                }
            }
        } else {
            menu_advance_chain_entry(i);
            func_US2_00288F30(i);
        }
    }

    if ((g_frame_l00_counter[0] & 127) || D_001A7A00[0x7A])
        return;
    ok = 1;
    for (i = 0; i < 56; i++) {
        int ex = g_weapon_l00_table[g_item_slot_to_record[i]].exists;
        if (ex && i == 10)
            continue;
        if (ex && i == 9)
            continue;
        if (ex) {
            if (!g_item_owned_flags[i]) {
                ok = 0;
                break;
            }
            if (i == 14 || i == 12 || i == 17 || i == 18 || i == 53)
                continue;
            if (menu_count_chain_entries_after_head(i) <= 0)
                continue;
            if (!g_weapon_l00_table[g_item_slot_to_record[i]].state) {
                ok = 0;
                break;
            }
        }
    }
    if (ok && !D_001A7A00[0x7A]) {
        D_001A7A00[0x7A] = 1;
        snd_play_from_global_bank(1, 0, 0);
        func_US2_002B1880(0x1233, -1);
        D_L00_001A903C = 1;
    }
}
