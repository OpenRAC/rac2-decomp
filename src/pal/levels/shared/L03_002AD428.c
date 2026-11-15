#include "include_asm.h"

#include "common.h"
extern char g_hero_state[];
extern int D_L03_001A8F00 MACRO_ADDR;
extern char g_hero_position[];
extern void ref_L03_002AD540_00(void);
extern void func_PAL_L00_002D29E8(void);
extern void ref_L03_002AD540_01(void);
extern void ref_L03_002AD540_02(void);
extern void ref_L03_002AD540_03(char *a0, char *a1, char *a2);
extern void ref_L03_002AD540_04(void);
extern void ref_L03_002AD540_05(void);
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
extern void part_spawn_effect_from_record(int a0);
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
extern void coll_clear_map_bits_around_pos(void *a0);
extern void func_002A677C(int a0);
extern void ref_L03_002AD540_06(void);
extern void UpdateHeroMobyProbedHeightBounds(void);

void func_PAL_L03_002AD428(void) {
    char *p;

    p = g_hero_state;
    *(short *)(p + 0x2162) = 0;
    *(short *)(p + 0x2160) = 0;
    if (*(unsigned char *)(p + 0x22B4) != 0) {
        ref_L03_002AD540_00();
        return;
    }
    func_PAL_L00_002D29E8();
    ref_L03_002AD540_01();
    ref_L03_002AD540_02();
    ref_L03_002AD540_03(p + 0x80, p + 0x90, p + 0x550);
    ref_L03_002AD540_04();
    ref_L03_002AD540_05();
    if (D_L03_001A8F00 == 2 || D_L03_001A8F00 == 6) {
        if (*(unsigned char *)(p + 0x22B5) != 0)
            hero_set_objects_flag_bit();
        else
            hero_clear_objects_flag_bit();
        return;
    }
    RebuildRegionObjectMembership();
    if (*(unsigned char *)(p + 0x22B4) != 0)
        return;
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
    if (*(unsigned char *)(p + 0x22B5) != 0 || hero_is_action_allowed() != 0)
        hero_set_objects_flag_bit();
    else
        hero_clear_objects_flag_bit();
    gfx_fade_screen_effect();
    ApplyHeroAxisScales();
    func_PAL_L00_002A6688();
    func_PAL_L00_002D6408();
    func_PAL_L00_002A62B0();
    func_PAL_L00_002D5680();
    {
        char *q = g_hero_state;
        if ((*(int *)(q + 0x229C) != 0x16 && *(int *)(q + 0x229C) != 0x1F
             && *(int *)(q + 0x2294) != 0x31) || hero_is_in_swing_or_grind_mode() != 0)
            coll_clear_map_bits_around_pos(g_hero_position);
    }
    {
        char *q = g_hero_state;
        func_002A677C(*(int *)(q + 0x2290));
    }
    ref_L03_002AD540_06();
    UpdateHeroMobyProbedHeightBounds();
}

