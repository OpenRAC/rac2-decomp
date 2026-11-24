#include "include_asm.h"

#include "common.h"
extern u8 g_hero_state[];
extern u8 g_anim_entry_buffer_low[], g_anim_entry_buffer_high[];
extern s32 g_hero_vehicle_mode[] __attribute__((sda));
extern void moby_mark_spawned(void *);
extern char *moby_get_private_value_0(u8 *);
extern void level_store_value_pair_us2(s32, s32);
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
extern s32 hero_l20_set_move_state_us2(s32, s32);

/* Apart from the leading state-1 block this is the same code as func_L18_002CFF48
   (src/levels/shared/L18_002CFD68-qcopy.c), and it needs the same grouped-copy profile.
   The state-1 block and the rest each take the hero block's address on their own: retail
   rebuilds it from the %hi kept in $s2.  D_L20_001A8F00 is declared as an sda array, as in
   the sibling, which gives retail's lui + lw into the same register. */
/* Takes the hero out of vehicle or ride mode and puts it back on foot (USA v2.00). */
void hero_exit_vehicle_mode_us2(s32 keep)
{
    u8 *hero = g_hero_state;
    u8 *base;
    u8 *vehicle_moby;
    float *saved_value;
    s32 value;
    u8 *attached;
    u8 *hero_moby;
    u8 *current;

    if (hero[0x22B4] == 1) {
        *(s32 *)(hero + 0x24D0) = *(s32 *)(hero + 0x24CC);
        *(s32 *)(hero + 0x24CC) = *(s16 *)(hero + 0x24D4);
        if (*(void **)(hero + 0x1860)) {
            moby_mark_spawned(*(void **)(hero + 0x1860));
            *(void **)(hero + 0x1860) = 0;
        }
        if (*(void **)(hero + 0x1864)) {
            moby_mark_spawned(*(void **)(hero + 0x1864));
            *(void **)(hero + 0x1864) = 0;
        }
    }
    base = g_hero_state;
    if (base[0x22B4] == 4) {
        saved_value = (float *)moby_get_private_value_0(*(u8 **)(base + 0x2290));
        if (saved_value) *saved_value = (float)*(s32 *)(base + 0x24CC);
        vehicle_moby = *(u8 **)(base + 0xC18);
        qcopy((base + 0x80), (vehicle_moby + 0x10));
        qcopy((base + 0x90), (vehicle_moby + 0xF0));
        *(s32 *)(base + 0x24CC) = *(s16 *)(base + 0x24D4);
        if (!keep) level_store_value_pair_us2(0, 0);
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
    hero_moby = *(u8 **)(g_hero_state + 0xC18);
    *(u8 **)(g_hero_state + 0x2290) = hero_moby;
    qcopy((hero_moby + 0x10), (g_hero_state + 0x80));
    *(s32 *)(hero_moby + 0x9C) = 0;
    *(float *)(g_hero_state + 0xC24) = 1.0f;
    hero_clear_queued_anim();
    current = *(u8 **)(g_hero_state + 0x2290);
    if (current[0x42] != 255) {
        value = anim_copy_entry_data((char *)current, current[0x42], current[0x40], (s32)g_anim_entry_buffer_low);
        *(s32 *)(*(u8 **)(g_hero_state + 0x2290) + 0x58) = value;
    }
    current = *(u8 **)(g_hero_state + 0x2290);
    value = anim_copy_entry_data((char *)current, current[0x43], current[0x41], (s32)g_anim_entry_buffer_high);
    *(s32 *)(*(u8 **)(g_hero_state + 0x2290) + 0x5C) = value;
    if (*(s32 *)(g_hero_state + 0x2294) != 0x61) goto reset;
    switch (g_hero_vehicle_mode[0]) {
    case 2:
    case 6:
        goto done;
    }
reset:
    hero_l20_set_move_state_us2(0, 1);
done:
    if (g_hero_state[0x22B4] == 4) cam_reset_default();
}
