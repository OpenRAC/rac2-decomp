#include "include_asm.h"



#include "common.h"
typedef struct {
    unsigned char pad0[0x160]; float velocity[4];
    float field_170, elapsed_174, speed_178;
    unsigned char pad1[0x1B4 - 0x17C]; float animation_time; int count_1b8;
    unsigned char pad2[4]; int count_1c0;
    unsigned char pad3[0x1E0 - 0x1C4]; short flag_1e0;
    unsigned char pad4[2]; short flag_1e4;
    unsigned char pad5[0x278 - 0x1E6]; float distance_278;
    unsigned char pad6[4]; float angle_280; unsigned char flag_284;
    unsigned char pad7[0x40E - 0x285]; unsigned char flag_40e;
    unsigned char pad8[0x49C - 0x40F]; unsigned char level_49c;
    unsigned char pad9[0xC20 - 0x49D]; float animation_scale;
    unsigned char pad10[4]; int flags_c28;
    unsigned char pad11[0x1454 - 0xC2C]; short flag_1454; unsigned char flag_1456;
    unsigned char pad12[0x1492 - 0x1457]; unsigned char flag_1492;
    unsigned char pad13[0x2290 - 0x1493]; void *object; int mode, frame;
    unsigned char pad14[0x22B4 - 0x229C]; unsigned char mode_22b4;
    unsigned char pad15[4]; unsigned char flag_22b9;
    unsigned char pad16[0x24A0 - 0x22BA]; int reset_24a0;
    unsigned char pad17[0x24B8 - 0x24A4]; float timer;
    unsigned char pad18[0x24FC - 0x24BC]; short flag_24fc;
} HeroActionState;
extern HeroActionState g_hero_state;
extern unsigned int g_pad_pressed_flags[];
extern int ref_L00_002CAB08_00(int, int);
extern int hero_get_step_offset_from_direction_pal(void);
extern int pad_presses_within_frames(int, int, int, int);
extern int PadPressedWithin(int, int, int *);
extern int hero_slot_item_id(int);
extern unsigned char g_item_owned_flags[] MACRO_ADDR;

int func_PAL_L00_002CAEB0(void)
{
    int offset;
    if (g_hero_state.mode == 14) return 0;
    offset = hero_get_step_offset_from_direction_pal();
    if ((g_pad_pressed_flags[0] & 8) && offset > 0 && pad_presses_within_frames(0x40, 0x1F000, offset + 4, offset)) {
        ref_L00_002CAB08_00(11, 1);
        return 1;
    }
    if (g_hero_state.count_1b8 < 6) goto fail;
    if (!PadPressedWithin(0x40, 7, 0)) goto fail;
    if (hero_slot_item_id(3) == 2 && g_item_owned_flags[2] != 0 && g_hero_state.flag_24fc == 0 &&
        (2.5f < g_hero_state.distance_278 || g_hero_state.angle_280 < 0.785398244857788086f) &&
        0.7f < g_hero_state.timer && 0.018000001f < g_hero_state.speed_178)
        ref_L00_002CAB08_00(10, 1);
    else if (hero_slot_item_id(3) == 3 && g_hero_state.flag_24fc == 0 && 0.7f < g_hero_state.timer &&
             (2.5f < g_hero_state.distance_278 || g_hero_state.flag_284 != 0) &&
             0.018000001f < g_hero_state.speed_178) {
        if (g_hero_state.flag_1e4 != 0) return 1;
        ref_L00_002CAB08_00(16, 1);
    } else if (hero_slot_item_id(3) == 3 && g_hero_state.flag_24fc == 0)
        ref_L00_002CAB08_00(13, 1);
    else if (hero_slot_item_id(3) == 2 && g_hero_state.flag_24fc == 0 && g_item_owned_flags[2] != 0)
        ref_L00_002CAB08_00(15, 1);
    else
        ref_L00_002CAB08_00(7, 1);
    return 1;
fail:
    return 0;
}








