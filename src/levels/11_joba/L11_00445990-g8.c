#include "common.h"

extern s32 D_0018C0B4 __attribute__((nosda));
extern u8 D_001395B8[];
extern u8 g_item_slot_to_record[];
extern void moby_set_state(char *, int, int);
extern char *ref_L11_00445990_00[2] __attribute__((sda));

typedef struct {
    char pad0[4];
    u8 f4;
    char pad1[0xDB];
} L11_00445990_Rec;

extern L11_00445990_Rec D_L11_00279BA0[];

extern void hero_l11_enter_state(s32, s32);
extern s32 PadPressedWithin(s32, s32, s32 *);
extern s32 arena_get_challenge_flag_index(s32);
extern s32 flag_is_byte_set(void);
extern void arena_reset_encounter(char *);
extern void joba_menu_draw_header_count_box(char *);
extern void gfx_add_draw_callback_first(void *, void *);

/* Same shape as func_L02_003FF9A0: the selection moves to the next usable table entry (this
   table has 13 entries and only the record of entry 8 is checked). */
void joba_menu_select_next(char *moby) {
    char *state = *(char **)(moby + 0x68);
    s32 i;
    L11_00445990_Rec *record;

    if (D_0018C0B4 != 0x6F)
        hero_l11_enter_state(0x6F, 1);
    if (PadPressedWithin(0x40, 0x3C, 0) != 0) {
        moby_set_state(moby, 7, -1);
        *(s16 *)(state + 0x1E8) = *(u16 *)(state + 0x1F0);
        D_001395B8[0x49] = *(u8 *)(state + 0x1E8);
        for (i = *(s16 *)(state + 0x1E8) + 1; i < 0xD; i++) {
            if (D_001395B8[arena_get_challenge_flag_index(*(s32 *)(ref_L11_00445990_00[i] + 8))] == 0)
                continue;
            if (i >= 0xB && flag_is_byte_set() == 0)
                continue;
            if (i == 8) {
                record = &D_L11_00279BA0[g_item_slot_to_record[0x1E]];
                if (record->f4 == 0)
                    continue;
            }
            *(s16 *)(state + 0x1E8) = i;
            D_001395B8[0x49] = *(u8 *)(state + 0x1E8);
            return;
        }
    } else if (PadPressedWithin(0x10, 0x3C, 0) != 0) {
        arena_reset_encounter(moby);
    } else {
        gfx_add_draw_callback_first(joba_menu_draw_header_count_box, moby);
    }
}
