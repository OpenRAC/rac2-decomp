#include "common.h"

/* One entity of the group: the kind word is at 0xAA. */
typedef struct L19Thing {
    u8 pad[0xAA];
    s16 kind;
} L19Thing;

/* The group: the count is at 0x44, the list of entities at 0x18C. */
typedef struct L19Group {
    u8 pad0[0x44];
    s16 count;
    u8 pad1[0x18C - 0x46];
    L19Thing *items[1];     /* bounded by count */
} L19Group;

extern L19Group D_L19_001BD740;
extern s32 D_L19_001A8F00[] __attribute__((sda));
extern u8 D_001A7A40[] __attribute__((sda));
extern u8 D_L19_001B22E0[] __attribute__((sda));
extern f32 D_L19_001B2300[] __attribute__((sda));

extern void AttachManipulator(u8 *, u32, u8 *);
extern int text_sum_subtitle_lengths(void);
extern int game_is_either_mode_two(void);
extern void moby_set_state(void *, int, int);
extern void moby_reset_vars_defaults(void *);
extern int hero_is_reachable_for_count(void *, int, float);
extern void text_print_localized_formatted(int, ...);
extern void level_apply_index_for_key(void *);
extern int req_push_queue(void *, int);
extern int req_launch_queued(void *);
extern void moby_set_byte_on_group(int, int);
extern void moby_mark_spawned(void *);
extern int MemcardSave(int, int);
extern void value_set_entry_by_index(int, int);
extern int subtitle_request_voice_line(int, int);
extern int flag_is_byte_set(void);
extern void func_L00_0030C710(int);
extern int math_random_int_range(int, int);
extern int snd_play_from_class_bank(int, int, char *, int);
extern void moby_update_eased_node(void *, void *, void *, float, float);

extern int g_frame_l19_counter[] __attribute__((sda));
extern int D_L19_001B2724[] __attribute__((sda));
extern u8 *g_moby_l19_array __attribute__((sda));
extern int D_L19_001B1FB8[] __attribute__((sda));
extern int g_player_bolts[] __attribute__((sda));
extern u8 D_L19_001A7C80[] __attribute__((sda));
extern u8 D_001395B8[];
extern u32 D_00139800, D_00138324;
extern int D_L19_0028E950[];
extern u8 D_L19_001BFC40[];

/* While the glow effect is on, finds every Mystic in the level and makes it glow brightly. */
void mystic_glow_all(void)
{
    L19Thing *mystic;
    s32 i;

    if (D_L19_001A8F00[0] != 2)
        return;
    if (D_001A7A40[0] == 0)
        return;
    for (i = 0; i < D_L19_001BD740.count; i++) {
        mystic = D_L19_001BD740.items[i];
        if (mystic->kind != 0xE3E /* The Mystic */)
            continue;
        if (D_L19_001B22E0[1] != 0)
            continue;
        AttachManipulator((u8 *)mystic, 0, D_L19_001B22E0);
        D_L19_001B2300[0] = 1.9f;
        D_L19_001B2300[1] = 1.9f;
        D_L19_001B2300[2] = 1.9f;
    }
}

/* func_L19_0042A9A0 is in L19_0042A9A0.c. */

/* Makes every object of the same kind as the given one glow brightly while the glow effect is on. */
void moby_glow_all_same_class(L19Thing *refMoby)
{
    L19Thing *other;
    s32 i;

    if (D_L19_001A8F00[0] != 2)
        return;
    if (D_001A7A40[0] == 0)
        return;
    for (i = 0; i < D_L19_001BD740.count; i++) {
        other = D_L19_001BD740.items[i];
        if (other->kind != refMoby->kind)
            continue;
        if (D_L19_001B22E0[1] != 0)
            continue;
        AttachManipulator((u8 *)other, 0, D_L19_001B22E0);
        D_L19_001B2300[0] = 1.9f;
        D_L19_001B2300[1] = 1.9f;
        D_L19_001B2300[2] = 1.9f;
    }
}

#define H(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define I(p, o) (*(int *)((u8 *)(p) + (o)))
#define QUANTITY D_001A79F8[9]
/* The two prices in the level's table, each with a second value used when the flag is set. */
#define PRICE_A (D_L19_001A7C80[0xF] ? D_L19_0028E950[15] : D_L19_0028E950[14])
#define PRICE_B (D_L19_001A7C80[0xF] ? D_L19_0028E950[17] : D_L19_0028E950[16])

/* An interaction state machine at byte 0x20, a larger cousin of func_L08_00435A78: offers two
   purchases for the quantity at D_001A79F8[9] (states 1-2 and 4-5, each followed by a movie in
   state 3 or 6), then buys the remaining quantity back at 30000 or 3000 each (states 7-8). */
/* Runs a trader's talk. It offers two purchases, plays a short movie after each, then buys the player's leftover items for bolts. */
void UpdateTwoItemTraderNpc(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *companion;
    int remaining;

    moby_glow_all_same_class((L19Thing *)moby);
    if (g_frame_l19_counter[0] == 5)
        text_sum_subtitle_lengths();
    switch (moby[0x20]) {
    case 0:
        if (game_is_either_mode_two())
            break;
        if (D_00139800 & 0x4000000) {
            H(moby, 0x34) = (H(moby, 0x34) & 0xFFBE) | 0x1000;
            I(moby, 0x98) = I(*(u8 **)(moby + 0x24), 0x10);
            if (D_001395B8[0x89]) {
                text_sum_subtitle_lengths();
                if (QUANTITY < 1)
                    moby_set_state(moby, 7, -1);
                else
                    moby_set_state(moby, 8, -1);
            } else if (QUANTITY < PRICE_B)
                moby_set_state(moby, 4, -1);
            else
                moby_set_state(moby, 5, -1);
            moby_reset_vars_defaults(moby);
        } else if (D_00139800 & 0x1000000) {
            text_sum_subtitle_lengths();
            H(moby, 0x34) = (H(moby, 0x34) & 0xFFBE) | 0x1000;
            I(moby, 0x98) = I(*(u8 **)(moby + 0x24), 0x10);
            if (QUANTITY < PRICE_A)
                moby_set_state(moby, 1, -1);
            else
                moby_set_state(moby, 2, -1);
        } else {
            I(moby, 0x98) = 0;
            H(moby, 0x34) = (H(moby, 0x34) | 0x41) & 0xEFFF;
        }
        break;
    case 1:
        if (QUANTITY >= PRICE_A)
            moby_set_state(moby, 2, -1);
        else if (hero_is_reachable_for_count(moby, 10, 2.5f)) {
            text_print_localized_formatted(0x27DC, PRICE_A, -1);
            level_apply_index_for_key(moby);
        }
        break;
    case 2:
        if (QUANTITY < PRICE_A)
            moby_set_state(moby, 1, -1);
        else if (hero_is_reachable_for_count(moby, 10, 2.5f)) {
            text_print_localized_formatted(0x27DD, PRICE_A, -1);
            level_apply_index_for_key(moby);
            if (D_00138324 & 0x10) {
                req_push_queue(D_L19_001BFC40, 0x9A);
                QUANTITY -= PRICE_A;
                req_launch_queued(D_L19_001BFC40);
                moby_set_state(moby, 3, -1);
            }
        }
        break;
    case 3:
        D_L19_001B2724[1] = 1;
        if (D_L19_001A8F00[0] == 2) {
            moby[0x31] = 0;
            H(moby, 0x34) |= 1;
        }
        if (I(vars, 0x80) != -1 && D_L19_001A8F00[0] == 2) {
            companion = g_moby_l19_array;
            H(companion + I(vars, 0x80) * 0x100, 0x34) |= 1;
            (companion + I(vars, 0x80) * 0x100)[0x31] = 0;
        }
        if (!game_is_either_mode_two()) {
            D_L19_001B2724[1] = 0;
            moby[0x31] = 1;
            H(moby, 0x34) &= 0xFFFE;
            if (moby[0x21] != 0xFF)
                moby_set_byte_on_group(moby[0x21], 1);
            if (I(vars, 0x80) != -1) {
                moby_mark_spawned(g_moby_l19_array + I(vars, 0x80) * 0x100);
                I(vars, 0x80) = -1;
            }
            MemcardSave(0, -1);
            if ((u32)QUANTITY <= PRICE_B)
                moby_set_state(moby, 4, -1);
            else
                moby_set_state(moby, 5, -1);
        }
        break;
    case 4:
        if (QUANTITY >= PRICE_B)
            moby_set_state(moby, 5, -1);
        else if (hero_is_reachable_for_count(moby, 10, 2.5f)) {
            text_print_localized_formatted(0x27DE, PRICE_B, -1);
            level_apply_index_for_key(moby);
        }
        break;
    case 5:
        if (QUANTITY < PRICE_B)
            moby_set_state(moby, 4, -1);
        else if (hero_is_reachable_for_count(moby, 10, 2.5f)) {
            text_print_localized_formatted(0x27DF, PRICE_B, -1);
            level_apply_index_for_key(moby);
            if (D_00138324 & 0x10) {
                req_push_queue(D_L19_001BFC40, 0x99);
                QUANTITY -= PRICE_B;
                req_launch_queued(D_L19_001BFC40);
                moby_set_state(moby, 6, -1);
            }
        }
        break;
    case 6:
        D_L19_001B2724[1] = 1;
        if (D_L19_001A8F00[0] == 2) {
            moby[0x31] = 0;
            H(moby, 0x34) |= 1;
        }
        if (!game_is_either_mode_two()) {
            D_L19_001B2724[1] = 0;
            moby[0x31] = 1;
            H(moby, 0x34) &= 0xFFFE;
            if (moby[0x21] != 0xFF)
                moby_set_byte_on_group(moby[0x21], 1);
            D_001395B8[0x89] = 1;
            value_set_entry_by_index(0x1294, -1);
            remaining = 2;
            if (D_001395B8[0x84])
                remaining--;
            if (D_001395B8[0x86])
                remaining--;
            if (remaining > 0)
                subtitle_request_voice_line(0xA0F, 0x66);
            else
                subtitle_request_voice_line(0xA10, 0x67);
            MemcardSave(0, -1);
            if (QUANTITY < 1)
                moby_set_state(moby, 7, -1);
            else
                moby_set_state(moby, 8, -1);
        }
        break;
    case 7:
        if (QUANTITY > 0)
            moby_set_state(moby, 8, -1);
        else if (hero_is_reachable_for_count(moby, 10, 2.5f)) {
            if (!D_L19_001B1FB8[0])
                text_print_localized_formatted(0x27E2, 0, -1);
            else
                text_print_localized_formatted(0x27E0, -1);
            level_apply_index_for_key(moby);
        }
        break;
    case 8:
        if (QUANTITY < 1)
            moby_set_state(moby, 7, -1);
        else if (hero_is_reachable_for_count(moby, 10, 2.5f)) {
            if (flag_is_byte_set()) {
                text_print_localized_formatted(0x27E1, QUANTITY, QUANTITY * 30000, -1);
                level_apply_index_for_key(moby);
                if (D_00138324 & 0x10) {
                    text_sum_subtitle_lengths();
                    g_player_bolts[0] += QUANTITY * 30000;
                    QUANTITY = 0;
                    func_L00_0030C710(180);
                    snd_play_from_class_bank(0, 0, (char *)moby, math_random_int_range(13, 17));
                    moby_set_state(moby, 9, -1);
                }
            } else {
                text_print_localized_formatted(0x27E1, QUANTITY, QUANTITY * 3000, -1);
                level_apply_index_for_key(moby);
                if (D_00138324 & 0x10) {
                    text_sum_subtitle_lengths();
                    g_player_bolts[0] += QUANTITY * 3000;
                    QUANTITY = 0;
                    func_L00_0030C710(180);
                    moby_set_state(moby, 9, -1);
                }
            }
        }
        break;
    case 9:
        H(moby, 0x96)++;
        if (H(moby, 0x96) > 0x7FF8)
            H(moby, 0x96) = 0x7FF8;
        if (H(moby, 0x96) > 40 && H(moby, 0x96) < 90 && H(moby, 0x96) % 4 == 0)
            snd_play_from_class_bank(0, 0, (char *)moby, math_random_int_range(13, 17));
        if (hero_is_reachable_for_count(moby, 10, 2.5f))
            text_print_localized_formatted(0x27E2, D_L19_001B1FB8[0], -1);
        else
            moby_set_state(moby, 7, -1);
        break;
    }
    if (D_001A7A40[0])
        *(float *)(vars + 0x70) = 2.75f;
    moby_update_eased_node(moby, vars, 0, 0.02f, 0.3f);
}
