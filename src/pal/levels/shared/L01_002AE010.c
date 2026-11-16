#include "include_asm.h"



#include "common.h"
extern void cancel_hero_item_animation_pal(void);
extern void UpdateHeroSlotCallbacks_pal(void);
extern void hero_set_objects_flag_bit(void);
extern void hero_clear_tracked_slots(void);
extern void attachment_reset_all(void);
extern void hero_clear_queued_anim(void);
extern void func_002A677C(int);
extern char g_hero_state[];
extern void cancel_hero_item_animation_pal(void);
extern void UpdateHeroSlotCallbacks_pal(void);
extern void level_release_slot_list(char *a0);
extern void hero_set_objects_flag_bit(void);
extern void hero_clear_tracked_slots(void);
extern void attachment_reset_all(void);
extern void hero_clear_queued_anim(void);
extern void func_002A677C(int a0);
extern s32 func_PAL_L01_002BEC60(int a0, int a1);
extern void func_PAL_L01_002B3C40(void);
extern char g_hero_state[];

void hero_switch_mode_and_moby_pal(int a0, int a1, int a2) {
    char *s0 = g_hero_state;

    cancel_hero_item_animation_pal();
    s0[0x22B6] = 1;
    UpdateHeroSlotCallbacks_pal();
    *(int *)(s0 + 0x2290) = *(int *)(s0 + 0xC18);
    level_release_slot_list(s0 + 0x18E0);
    level_release_slot_list(s0 + 0x1A30);
    *(int *)(*(int *)(s0 + 0x2290) + 0x9C) = -1;
    if (a0 != 4 || *(unsigned char *)(s0 + 0x22B4) != a0)
        hero_set_objects_flag_bit();
    hero_clear_tracked_slots();
    attachment_reset_all();
    {
        char *s1 = g_hero_state;

        *(unsigned char *)(s1 + 0x22B4) = a0;
        *(int *)(s1 + 0xC14) = a2;
        *(int *)(s1 + 0x2290) = a2;
    }
    func_PAL_L01_002B3C40();
    {
        char *s2 = g_hero_state;

        *(float *)(s2 + 0x250) = *(float *)(s2 + 0x258);
        *(float *)(s2 + 0x254) = *(float *)(s2 + 0x25C);
        *(unsigned short *)(*(int *)(s2 + 0x2290) + 0x34) |= 6;
        *(float *)(s2 + 0xC20) = 1.0f;
        *(float *)(s2 + 0xC24) = 1.0f;
        hero_clear_queued_anim();
        func_002A677C(*(int *)(s2 + 0x2290));
        *(unsigned short *)(s2 + 0x24F2) = a1;
    }
    func_PAL_L01_002BEC60(a1, 2);
}

