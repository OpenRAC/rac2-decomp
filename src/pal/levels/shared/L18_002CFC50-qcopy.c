#include "include_asm.h"

#include "common.h"
typedef int VectorBits __attribute__((mode(TI)));
typedef struct Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner {
    unsigned char prefix_00[0x120]; void *slots_120[10]; int count_148; int active_14c;
} Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner;
extern void cancel_hero_item_animation_pal(void);
extern void UpdateHeroSlotCallbacks_pal(void);
extern void level_release_slot_list(Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner *);
extern void hero_set_objects_flag_bit(void);
extern void hero_clear_tracked_slots(void);
extern void attachment_reset_all(void);
extern void func_PAL_L18_002D0738(void);
extern void hero_clear_queued_anim(void);
extern void func_002A677C(void *);
extern s32 func_PAL_L18_002E01E0(s32, s32);
extern void set_hero_animation_pal(s32, s32, float);
extern u8 g_hero_state[];
extern u8 g_hero_state[];
extern u8 g_anim_entry_table_a[], g_anim_entry_table_b[];
extern s32 g_game_l18_mode_state[] __attribute__((sda));
extern char *moby_get_private_value_0(u8 *);
extern void attachment_reset_all(void);
extern s32 hud_set_slot_contents(s32, s32, void (*)(u8 *), void (*)(u8 *), void (*)(u8 *), s32, s32);
extern s32 level_run_slot_callback(u32);
extern void hero_clear_tracked_slots(void);
extern void hero_clear_queued_anim(void);
extern s32 anim_copy_entry_data(char *, s32, s32, s32);

void func_PAL_L18_002CFC50(s32 mode, s32 index, u8 *object)
{
    u8 *base = g_hero_state;
    u8 *current;
    cancel_hero_item_animation_pal();
    base[0x22B6] = 1;
    UpdateHeroSlotCallbacks_pal();
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
    func_PAL_L18_002D0738();
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
    func_PAL_L18_002E01E0(index, 2);
    if (mode == 4) set_hero_animation_pal(15, 0, 4.0f);
}
