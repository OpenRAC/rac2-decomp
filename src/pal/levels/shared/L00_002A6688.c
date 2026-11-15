#include "include_asm.h"

#include "common.h"
extern unsigned char g_hero_state[];
extern unsigned char g_hero_position[];
extern int D_L00_001A8F00 MACRO_ADDR;
extern void func_PAL_L00_002A6468(void);
extern void func_PAL_L00_002D29E8(void);
extern void func_PAL_L00_002B3608(void);
extern void hero_process_action_command(void);
extern int func_PAL_L00_002ACE70(void *, void *, void *);
extern void FindGrindRail(void);
extern void hero_find_ledge_candidate(void);
extern void func_PAL_L00_002CB7A0(void);
extern void hero_set_objects_flag_bit(void);
extern void hero_clear_objects_flag_bit(void);
extern void RebuildRegionObjectMembership(void);
extern void func_PAL_L00_002B9C20(void);
extern void func_PAL_L00_002AC088(void);
extern void func_PAL_L00_002AB0C0(void);
extern void func_PAL_L00_002AB308(void);
extern void func_PAL_L00_002ABA88(void);
extern void func_PAL_L00_002AB830(void);
extern void func_PAL_L00_002A53A8(void);
extern void func_PAL_L00_002A56D0(void);
extern void func_PAL_L00_002B7688(void);
extern void attachment_update_all(void);
extern void update_hero_moby(void);
extern void part_spawn_effect_from_record(int);
extern void func_PAL_L00_002B2018(void);
extern void func_PAL_L00_002B2230(void);
extern void func_PAL_L00_002B20F8(void);
extern void hero_update_items_frame(void);
extern int hero_is_action_allowed(void);
extern void gfx_fade_screen_effect(void);
extern void ApplyHeroAxisScales(void);
extern void func_PAL_L00_002A6688(void);
extern void func_PAL_L00_002D6408(void);
extern void func_PAL_L00_002A62B0(void);
extern void func_PAL_L00_002D5680(void);
extern int hero_is_in_swing_or_grind_mode(void);
extern void coll_clear_map_bits_around_pos(void *);
extern void func_002A677C(void *);
extern void func_PAL_L00_002A7390(void);
extern void UpdateHeroMobyProbedHeightBounds(void);

/* Run the frame's ordered resident-player updates while its control mode is active. */
void func_PAL_L00_002A6CB8(void) {
    unsigned char *player = g_hero_state;
    unsigned char *hero;
    *(short *)(player + 0x2162) = 0;
    *(short *)(player + 0x2160) = 0;
    if (player[0x22B4]) { func_PAL_L00_002A6468(); return; }
    func_PAL_L00_002D29E8();
    func_PAL_L00_002B3608();
    hero_process_action_command();
    func_PAL_L00_002ACE70(player + 0x80, player + 0x90, player + 0x550);
    FindGrindRail();
    hero_find_ledge_candidate();
    func_PAL_L00_002CB7A0();
    if (D_L00_001A8F00 == 2 || D_L00_001A8F00 == 6) {
        if (player[0x22B5]) hero_set_objects_flag_bit();
        else hero_clear_objects_flag_bit();
        return;
    }
    RebuildRegionObjectMembership();
    if (player[0x22B4]) return;
    func_PAL_L00_002B9C20();
    func_PAL_L00_002AC088();
    func_PAL_L00_002AB0C0();
    func_PAL_L00_002AB308();
    func_PAL_L00_002ABA88();
    func_PAL_L00_002AB830();
    func_PAL_L00_002A53A8();
    func_PAL_L00_002A56D0();
    func_PAL_L00_002B7688();
    attachment_update_all();
    update_hero_moby();
    part_spawn_effect_from_record(0);
    func_PAL_L00_002B2018();
    func_PAL_L00_002B2230();
    func_PAL_L00_002B20F8();
    hero_update_items_frame();
    if (player[0x22B5] || hero_is_action_allowed()) hero_set_objects_flag_bit();
    else hero_clear_objects_flag_bit();
    gfx_fade_screen_effect();
    ApplyHeroAxisScales();
    func_PAL_L00_002A6688();
    func_PAL_L00_002D6408();
    func_PAL_L00_002A62B0();
    func_PAL_L00_002D5680();
    hero = g_hero_state;
    if ((*(int *)(hero + 0x229C) != 0x16 && *(int *)(hero + 0x229C) != 0x1F && *(int *)(hero + 0x2294) != 0x31) || hero_is_in_swing_or_grind_mode())
        coll_clear_map_bits_around_pos(g_hero_position);
    { unsigned char *base = g_hero_state; func_002A677C(*(void **)(base + 0x2290)); }
    func_PAL_L00_002A7390();
    UpdateHeroMobyProbedHeightBounds();
}

