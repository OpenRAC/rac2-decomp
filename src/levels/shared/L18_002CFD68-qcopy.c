#include "common.h"
typedef int VectorBits __attribute__((mode(TI)));
typedef struct Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner {
    unsigned char prefix_00[0x120]; void *slots_120[10]; int count_148; int active_14c;
} Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner;
extern void cancel_hero_item_animation(void);
extern void UpdateHeroSlotCallbacks(void);
extern void level_release_slot_list(Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner *);
extern void hero_set_objects_flag_bit(void);
extern void hero_clear_tracked_slots(void);
extern void attachment_reset_all(void);
extern void hero_l18_update_speed_targets(void);
extern void hero_clear_queued_anim(void);
extern void func_002A677C(void *);
extern s32 hero_l18_set_action(s32, s32);
extern void set_hero_animation(s32, s32, float);
extern u8 g_hero_state[];
/* Puts the hero under control of another object (for example a vehicle) and saves the hero position. */
void hero_attach_to_object(s32 mode, s32 index, u8 *object)
{
    u8 *base = g_hero_state;
    u8 *current;
    cancel_hero_item_animation();
    base[0x22B6] = 1;
    UpdateHeroSlotCallbacks();
    *(u8 **)(base + 0x2290) = *(u8 **)(base + 0xC18);
    level_release_slot_list((Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner *)(base + 0x18E0));
    level_release_slot_list((Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner *)(base + 0x1A30));
    *(s32 *)(*(u8 **)(base + 0x2290) + 0x9C) = -1;
    if (mode != 4 || base[0x22B4] != 4) hero_set_objects_flag_bit();
    hero_clear_tracked_slots();
    attachment_reset_all();
    g_hero_state[0x22B4] = mode;
    *(u8 **)(g_hero_state + 0xC14) = object;
    *(u8 **)(g_hero_state + 0x2290) = object;
    hero_l18_update_speed_targets();
    *(float *)(g_hero_state + 0x250) = *(float *)(g_hero_state + 0x258);
    *(float *)(g_hero_state + 0x254) = *(float *)(g_hero_state + 0x25C);
    current = *(u8 **)(g_hero_state + 0x2290);
    *(u16 *)(current + 0x34) |= 6;
    *(float *)(g_hero_state + 0xC20) = 1.0f;
    *(float *)(g_hero_state + 0xC24) = 1.0f;
    hero_clear_queued_anim();
    func_002A677C(*(u8 **)(g_hero_state + 0x2290));
    *(s16 *)(g_hero_state + 0x24F2) = index;
    if (mode == 4) {
        *(VectorBits *)(g_hero_state + 0x80) = *(VectorBits *)(object + 0x10);
        *(VectorBits *)(g_hero_state + 0x90) = *(VectorBits *)(object + 0xF0);
        *(s16 *)(g_hero_state + 0x24D4) = *(u16 *)(g_hero_state + 0x24CC);
        *(s32 *)(g_hero_state + 0x24CC) = 3;
    }
    hero_l18_set_action(index, 2);
    if (mode == 4) set_hero_animation(15, 0, 5.0f);
}

extern u8 g_hero_state[];
extern u8 g_anim_entry_table_a[], g_anim_entry_table_b[];
extern s32 g_game_l18_mode_state[] __attribute__((sda));
extern char *moby_get_private_value_0(u8 *);
extern void level_store_value_pair(s32, s32);
extern void hero_reset_speeds_and_vectors(void);
extern void attachment_reset_all(void);
extern void menu_init_panel_layout(u8 *);
extern void weapon_wheel_update_select(u8 *);
extern int weapon_wheel_draw(u8 *);
extern s32 hud_set_slot_contents(s32, s32, void (*)(u8 *), void (*)(u8 *), void (*)(u8 *), s32, s32);
extern s32 level_run_slot_callback(u32);
extern void hero_clear_tracked_slots(void);
extern void hero_clear_queued_anim(void);
extern s32 anim_copy_entry_data(char *, s32, s32, s32);
extern void cam_reset_default(void);
/* Gives control back to the hero and restores the saved position and camera state. */
void hero_detach_from_object(s32 keep)
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
        if (!keep) level_store_value_pair(0, 0);
        hero_reset_speeds_and_vectors();
        *(s16 *)(base + 0x34E) = 1;
        *(s32 *)(base + 0x3A4) &= ~1;
        *(s32 *)(base + 0x3A4) &= ~2;
        *(s32 *)(base + 0x3A0) = 0;
        base[0x22B5] = 0;
    }
    attachment_reset_all();
    g_hero_state[0x22B4] = 0;
    hud_set_slot_contents(35, 0, menu_init_panel_layout, weapon_wheel_update_select, weapon_wheel_draw, 0, 0);
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
    hero_l18_set_action(0, 1);
done:
    if (g_hero_state[0x22B4] == 4) cam_reset_default();
}
