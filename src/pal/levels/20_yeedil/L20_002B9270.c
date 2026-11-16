#include "include_asm.h"

#include "common.h"
extern char g_hero_state[];
extern u8 g_item_slot_to_record[];
extern s32 hero_slot_item_id(s32 index);
extern void func_PAL_0028D6F0(void);
extern void func_PAL_0028D738(void);
extern int func_PAL_0028DC40(void);
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
extern s32 func_PAL_L20_002D7920(s32, s32);
extern void set_hero_animation_pal(f32, s32, s32);
extern s32 g_pad_pressed_flags[];
extern void func_PAL_L20_002C6358(void);

/* func_L20_002B7A48 is defined in L20_002B7A48-selector.c. */

/*W23E*/

/* func_L20_002B93E0 is defined in L20_002B7A48-g8.c (it reaches data through $gp). */

void func_PAL_L20_002C5738(s32 a0, s32 a1, char *a2)
{
    char *D = g_hero_state;
    s32 p0 = a0;
    char *p2 = a2;
    s32 p1 = a1;
    char *block;

    cancel_hero_item_animation_pal();
    *(u8 *)(D + 0x22B6) = 1;
    UpdateHeroSlotCallbacks_pal();
    *(s32 *)(D + 0x2290) = *(s32 *)(D + 0xC18);
    level_release_slot_list(D + 0x18E0);
    level_release_slot_list(D + 0x1A30);
    *(s32 *)(*(s32 *)(D + 0x2290) + 0x9C) = -1;
    if (p0 != 4 || *(u8 *)(D + 0x22B4) != p0)
        hero_set_objects_flag_bit();
    hero_clear_tracked_slots();
    attachment_reset_all();
    block = g_hero_state;
    *(u8 *)(block + 0x22B4) = p0;
    *(s32 *)(block + 0xC14) = (s32)p2;
    *(s32 *)(block + 0x2290) = (s32)p2;
    if ((p0 & 0xFF) == 1) {
        if (g_pad_pressed_flags[0] & 0x10) {
            hud_set_slot_contents(0x23, 0, (void *)func_PAL_0028D6F0, (void *)func_PAL_0028D738,
                          (void *)func_PAL_0028DC40, 0, 0);
            level_run_slot_callback(3);
        }
    }
    func_PAL_L20_002C6358();
    D = g_hero_state;
    *(f32 *)(D + 0x250) = *(f32 *)(D + 0x258);
    *(f32 *)(D + 0x254) = *(f32 *)(D + 0x25C);
    *(u16 *)(*(s32 *)(D + 0x2290) + 0x34) |= 6;
    *(f32 *)(D + 0xC20) = 1.0f;
    *(f32 *)(D + 0xC24) = 1.0f;
    hero_clear_queued_anim();
    func_002A677C(*(s32 *)(D + 0x2290));
    *(u16 *)(D + 0x24F2) = p1;
    switch (p0) {
    case 1:
        *(u16 *)(D + 0x24D4) = *(u16 *)(D + 0x24CC);
        *(s32 *)(D + 0x24CC) = *(s32 *)(D + 0x24D0);
        if (*(s32 *)(D + 0x24CC) >= 5)
            *(s32 *)(D + 0x24CC) = 4;
        break;
    case 4:
        qcopy(D + 0x80, p2 + 0x10);
        qcopy(D + 0x90, p2 + 0xF0);
        *(u16 *)(D + 0x24D4) = *(u16 *)(D + 0x24CC);
        *(s32 *)(D + 0x24CC) = 3;
    }
    func_PAL_L20_002D7920(p1, 2);
    if (p0 == 4)
        set_hero_animation_pal(4.0f, 0xF, 0);
}

