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

extern s8 g_meter_vtable_a[];
extern s8 g_meter_vtable_b[];
/* Constructs all of the HUD's sub widgets (labels, icons, fades, meters), clears the effect tables and returns
   the HUD. (USA v2.00) */
s32 hud_construct_us2(s32 hud) {
    s32 effect_1214;
    s32 effect_133c;
    s32 vtable_slot_a;
    s32 words_e2c;
    s32 vtable_slot_b;
    s32 effect_fd0;
    s32 words_146c;
    s32 words_10f8;
    s32 words_eb4;
    s32 words_14f4;
    s32 effect_1180;
    s32 effect_12a8;
    s32 effect_13d0;
    s32 effect_f3c;
    s32 effect_1064;
    s32 label_ptr;
    s32 icon_ptr;
    s32 label_count;
    s32 icon_count;

    label_count = 7;
    label_ptr = hud + 0x378;
    object_construct_derived_a(hud);
    object_construct_derived_a(hud + 0x4C);
    object_construct_derived_a(hud + 0x98);
    hud_construct_widget_base(hud + 0x100);
    object_construct_derived_c(hud + 0x158);
    object_construct_derived_a(hud + 0x194);
    object_construct_derived_a(hud + 0x1E0);
    hud_construct_widget_base(hud + 0x248);
    object_construct_derived_c(hud + 0x2A0);
    object_construct_derived_a(hud + 0x2E0);
    object_construct_derived_a(hud + 0x32C);
    do {
        label_count -= 1;
        object_construct_derived_a(label_ptr);
        label_ptr += 0x4C;
    } while (label_count != -1);
    icon_ptr = hud + 0x624;
    object_construct_derived_a(hud + 0x5D8);
    icon_count = 7;
    words_e2c = hud + 0xE2C;
    words_eb4 = hud + 0xEB4;
    effect_f3c = hud + 0xF3C;
    effect_fd0 = hud + 0xFD0;
    effect_1064 = hud + 0x1064;
    words_10f8 = hud + 0x10F8;
    effect_1180 = hud + 0x1180;
    effect_1214 = hud + 0x1214;
    effect_12a8 = hud + 0x12A8;
    effect_133c = hud + 0x133C;
    effect_13d0 = hud + 0x13D0;
    vtable_slot_a = hud + 0x1464;
    vtable_slot_b = hud + 0x1468;
    words_146c = hud + 0x146C;
    words_14f4 = hud + 0x14F4;
    do {
        icon_count -= 1;
        object_construct_derived_c(icon_ptr);
        icon_ptr += 0x3C;
    } while (icon_count != -1);
    meter_screen_init_parts(hud + 0x808);
    menu_clear_sixteen_words(hud + 0xC0C);
    menu_clear_sixteen_words(hud + 0xC94);
    menu_clear_sixteen_words(hud + 0xD1C);
    menu_clear_sixteen_words(hud + 0xDA4);
    menu_clear_sixteen_words(words_e2c);
    menu_clear_sixteen_words(words_eb4);
    effect_clear_row_groups(effect_f3c);
    effect_clear_row_groups(effect_fd0);
    effect_clear_row_groups(effect_1064);
    menu_clear_sixteen_words(words_10f8);
    effect_clear_row_groups(effect_1180);
    effect_clear_row_groups(effect_1214);
    effect_clear_row_groups(effect_12a8);
    effect_clear_row_groups(effect_133c);
    effect_clear_row_groups(effect_13d0);
    object_init_type_pointer(vtable_slot_a);
    (*(s32 *)((s8 *)(hud) + (0x1464))) = ((s32)g_meter_vtable_a);
    object_init_type_pointer(vtable_slot_b);
    (*(s32 *)((s8 *)(hud) + (0x1468))) = ((s32)g_meter_vtable_b);
    menu_clear_sixteen_words(words_146c);
    menu_clear_sixteen_words(words_14f4);
    return hud;
}
