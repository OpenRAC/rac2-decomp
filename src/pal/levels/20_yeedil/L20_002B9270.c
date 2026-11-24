#include "include_asm.h"

#include "common.h"
extern char g_hero_state[];
extern u8 g_item_slot_to_record[];
extern s32 hero_slot_item_id(s32 index);
extern void weapon_wheel_init_pal(void);
extern void UpdateRadialMenuSelection_pal(void);
extern int DrawRadialSelectorPanel_pal(void);
extern s32 hud_set_slot_contents(s32, s32, void *, void *, void *, s32, s32);
extern void cancel_hero_item_animation_pal(void);
extern void UpdateHeroSlotCallbacks_pal(void);
extern void level_release_slot_list(char *);
extern void hero_set_objects_flag_bit(void);
extern void hero_clear_tracked_slots(void);
extern void attachment_reset_all(void);
extern int level_run_slot_callback(s32);
extern void hero_clear_queued_anim(void);
extern void func_002A677C(s32);
extern s32 hero_l20_set_move_state_pal(s32, s32);
extern void set_hero_animation_pal(f32, s32, s32);
extern s32 g_pad_pressed_flags[];
extern void UpdateYeedilHeroCollisionCapsule_pal(void);

/* func_L20_002B7A48 is defined in L20_002B7A48-selector.c. */

/*W23E*/

/* func_L20_002B93E0 is defined in L20_002B7A48-g8.c (it reaches data through $gp). */

/* Puts the hero into a new mode (on foot or riding) and attaches it to the given object. (PAL version) */
void SetYeedilHeroVehicleMode_pal(s32 new_mode_arg, s32 animation_arg, char *attach_object_arg)
{
    char *hero = g_hero_state;
    s32 new_mode = new_mode_arg;
    char *attach_object = attach_object_arg;
    s32 animation = animation_arg;
    char *block;

    cancel_hero_item_animation_pal();
    *(u8 *)(hero + 0x22B6) = 1;
    UpdateHeroSlotCallbacks_pal();
    *(s32 *)(hero + 0x2290) = *(s32 *)(hero + 0xC18);
    level_release_slot_list(hero + 0x18E0);
    level_release_slot_list(hero + 0x1A30);
    *(s32 *)(*(s32 *)(hero + 0x2290) + 0x9C) = -1;
    if (new_mode != 4 || *(u8 *)(hero + 0x22B4) != new_mode)
        hero_set_objects_flag_bit();
    hero_clear_tracked_slots();
    attachment_reset_all();
    block = g_hero_state;
    *(u8 *)(block + 0x22B4) = new_mode;
    *(s32 *)(block + 0xC14) = (s32)attach_object;
    *(s32 *)(block + 0x2290) = (s32)attach_object;
    if ((new_mode & 0xFF) == 1) {
        if (g_pad_pressed_flags[0] & 0x10) {
            hud_set_slot_contents(0x23, 0, (void *)weapon_wheel_init_pal, (void *)UpdateRadialMenuSelection_pal,
                          (void *)DrawRadialSelectorPanel_pal, 0, 0);
            level_run_slot_callback(3);
        }
    }
    UpdateYeedilHeroCollisionCapsule_pal();
    hero = g_hero_state;
    *(f32 *)(hero + 0x250) = *(f32 *)(hero + 0x258);
    *(f32 *)(hero + 0x254) = *(f32 *)(hero + 0x25C);
    *(u16 *)(*(s32 *)(hero + 0x2290) + 0x34) |= 6;
    *(f32 *)(hero + 0xC20) = 1.0f;
    *(f32 *)(hero + 0xC24) = 1.0f;
    hero_clear_queued_anim();
    func_002A677C(*(s32 *)(hero + 0x2290));
    *(u16 *)(hero + 0x24F2) = animation;
    switch (new_mode) {
    case 1:
        *(u16 *)(hero + 0x24D4) = *(u16 *)(hero + 0x24CC);
        *(s32 *)(hero + 0x24CC) = *(s32 *)(hero + 0x24D0);
        if (*(s32 *)(hero + 0x24CC) >= 5)
            *(s32 *)(hero + 0x24CC) = 4;
        break;
    case 4:
        qcopy(hero + 0x80, attach_object + 0x10);
        qcopy(hero + 0x90, attach_object + 0xF0);
        *(u16 *)(hero + 0x24D4) = *(u16 *)(hero + 0x24CC);
        *(s32 *)(hero + 0x24CC) = 3;
    }
    hero_l20_set_move_state_pal(animation, 2);
    if (new_mode == 4)
        set_hero_animation_pal(4.0f, 0xF, 0);
}

