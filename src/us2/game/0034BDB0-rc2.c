#include "names.h"
/* func_US2_0034BDB0, the USA v2.00 copy of func_0034B070: the same C, where the
 * object's fields sit 0x10 and 0x20 further along. */
#include "common.h"

extern void *object_init_type_pointer();
extern void *object_construct_derived_a();
extern void *object_construct_derived_c();
extern char *hud_construct_widget_base();
extern u8 *menu_clear_sixteen_words();
extern u8 *effect_clear_row_groups();
extern char *meter_screen_init_parts();

extern s8 D_001AD928[];
extern s8 D_001AD908[];
s32 func_US2_0034BDB0(s32 arg0) {
    s32 sp0;
    s32 sp4;
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    s32 sp38;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s2;
    s32 var_s2_2;

    var_s2 = 7;
    var_s1 = arg0 + 0x378;
    object_construct_derived_a(arg0);
    object_construct_derived_a(arg0 + 0x4C);
    object_construct_derived_a(arg0 + 0x98);
    hud_construct_widget_base(arg0 + 0x100);
    object_construct_derived_c(arg0 + 0x158);
    object_construct_derived_a(arg0 + 0x194);
    object_construct_derived_a(arg0 + 0x1E0);
    hud_construct_widget_base(arg0 + 0x248);
    object_construct_derived_c(arg0 + 0x2A0);
    object_construct_derived_a(arg0 + 0x2E0);
    object_construct_derived_a(arg0 + 0x32C);
    do {
        var_s2 -= 1;
        object_construct_derived_a(var_s1);
        var_s1 += 0x4C;
    } while (var_s2 != -1);
    var_s1_2 = arg0 + 0x624;
    object_construct_derived_a(arg0 + 0x5D8);
    var_s2_2 = 7;
    spC = arg0 + 0xE2C;
    sp20 = arg0 + 0xEB4;
    sp34 = arg0 + 0xF3C;
    sp14 = arg0 + 0xFD0;
    sp38 = arg0 + 0x1064;
    sp1C = arg0 + 0x10F8;
    sp28 = arg0 + 0x1180;
    sp0 = arg0 + 0x1214;
    sp2C = arg0 + 0x12A8;
    sp4 = arg0 + 0x133C;
    sp30 = arg0 + 0x13D0;
    sp8 = arg0 + 0x1464;
    sp10 = arg0 + 0x1468;
    sp18 = arg0 + 0x146C;
    sp24 = arg0 + 0x14F4;
    do {
        var_s2_2 -= 1;
        object_construct_derived_c(var_s1_2);
        var_s1_2 += 0x3C;
    } while (var_s2_2 != -1);
    meter_screen_init_parts(arg0 + 0x808);
    menu_clear_sixteen_words(arg0 + 0xC0C);
    menu_clear_sixteen_words(arg0 + 0xC94);
    menu_clear_sixteen_words(arg0 + 0xD1C);
    menu_clear_sixteen_words(arg0 + 0xDA4);
    menu_clear_sixteen_words(spC);
    menu_clear_sixteen_words(sp20);
    effect_clear_row_groups(sp34);
    effect_clear_row_groups(sp14);
    effect_clear_row_groups(sp38);
    menu_clear_sixteen_words(sp1C);
    effect_clear_row_groups(sp28);
    effect_clear_row_groups(sp0);
    effect_clear_row_groups(sp2C);
    effect_clear_row_groups(sp4);
    effect_clear_row_groups(sp30);
    object_init_type_pointer(sp8);
    (*(s32 *)((s8 *)(arg0) + (0x1464))) = ((s32)D_001AD928);
    object_init_type_pointer(sp10);
    (*(s32 *)((s8 *)(arg0) + (0x1468))) = ((s32)D_001AD908);
    menu_clear_sixteen_words(sp18);
    menu_clear_sixteen_words(sp24);
    return arg0;
}
