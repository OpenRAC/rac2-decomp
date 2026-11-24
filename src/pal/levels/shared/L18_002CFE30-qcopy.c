#include "include_asm.h"

#include "common.h"
extern void hero_clear_tracked_slots(void);
extern void attachment_reset_all(void);
extern void hero_clear_queued_anim(void);
extern s32 hero_l18_set_move_state_pal(s32, s32);
extern u8 g_hero_state[];
extern u8 g_hero_state[];
extern u8 g_anim_entry_table_a[], g_anim_entry_table_b[];
extern s32 g_game_l18_mode_state[] __attribute__((sda));
extern char *moby_get_private_value_0(u8 *);
extern void level_store_value_pair_pal(s32, s32);
extern void hero_reset_speeds_and_vectors(void);
extern void attachment_reset_all(void);
extern void menu_init_panel_layout_pal(u8 *);
extern void weapon_wheel_update_select_pal(u8 *);
extern int weapon_wheel_draw_pal(u8 *);
extern s32 hud_set_slot_contents(s32, s32, void (*)(u8 *), void (*)(u8 *), void (*)(u8 *), s32, s32);
extern s32 level_run_slot_callback(u32);
extern void hero_clear_tracked_slots(void);
extern void hero_clear_queued_anim(void);
extern s32 anim_copy_entry_data(char *, s32, s32, s32);
extern void cam_reset_default(void);

/* Gives control back to the hero and restores the saved position and camera state. */
void hero_detach_from_object_pal(s32 keep)
{
    u8 *base = g_hero_state;
    u8 *object;
    float *record;
    s32 value;
    s32 mode;
    u8 *attached;
    u8 *restored;
    u8 *current;
    if (base[0x22B4] == 4) {
        record = (float *)moby_get_private_value_0(*(u8 **)(base + 0x2290));
        if (record) *record = (float)*(s32 *)(base + 0x24CC);
        object = *(u8 **)(base + 0xC18);
        qcopy((base + 0x80), (object + 0x10));
        qcopy((base + 0x90), (object + 0xF0));
        *(s32 *)(base + 0x24CC) = *(s16 *)(base + 0x24D4);
        if (!keep) level_store_value_pair_pal(0, 0);
        hero_reset_speeds_and_vectors();
        *(s16 *)(base + 0x34E) = 1;
        *(s32 *)(base + 0x3A4) &= ~1;
        *(s32 *)(base + 0x3A4) &= ~2;
        *(s32 *)(base + 0x3A0) = 0;
        base[0x22B5] = 0;
    }
    attachment_reset_all();
    g_hero_state[0x22B4] = 0;
    hud_set_slot_contents(35, 0, menu_init_panel_layout_pal, weapon_wheel_update_select_pal, weapon_wheel_draw_pal, 0, 0);
    level_run_slot_callback(3);
    attached = *(u8 **)(g_hero_state + 0xC14);
    if (attached) *(u16 *)(attached + 0x34) &= ~6;
    *(u8 **)(g_hero_state + 0xC14) = 0;
    hero_clear_tracked_slots();
    restored = *(u8 **)(g_hero_state + 0xC18);
    *(u8 **)(g_hero_state + 0x2290) = restored;
    qcopy((restored + 0x10), (g_hero_state + 0x80));
    *(s32 *)(restored + 0x9C) = 0;
    *(float *)(g_hero_state + 0xC24) = 1.0f;
    hero_clear_queued_anim();
    current = *(u8 **)(g_hero_state + 0x2290);
    if (current[0x42] != 255) {
        value = anim_copy_entry_data((char *)current, current[0x42], current[0x40], (s32)g_anim_entry_table_a);
        *(s32 *)(*(u8 **)(g_hero_state + 0x2290) + 0x58) = value;
    }
    current = *(u8 **)(g_hero_state + 0x2290);
    value = anim_copy_entry_data((char *)current, current[0x43], current[0x41], (s32)g_anim_entry_table_b);
    *(s32 *)(*(u8 **)(g_hero_state + 0x2290) + 0x5C) = value;
    if (*(s32 *)(g_hero_state + 0x2294) != 0x61) goto reset;
    switch (g_game_l18_mode_state[0]) {
    case 2:
    case 6:
        goto done;
    }
reset:
    hero_l18_set_move_state_pal(0, 1);
done:
    if (g_hero_state[0x22B4] == 4) cam_reset_default();
}
