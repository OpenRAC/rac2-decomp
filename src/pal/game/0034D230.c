#include "include_asm.h"
#include "names.h"


extern int *object_get_fourth_field(unsigned char *field);

/* Returns the alpha byte (top 8 bits) of a menu label's color. (PAL) */
unsigned int menu_get_label_color_alpha_pal(unsigned char *owner)
{
    unsigned int address = (unsigned int)object_get_fourth_field(owner + 0x378);
    return *(unsigned int *)address & 0xff000000u;
}


extern void hud_set_widget_value_pair(char *, int, int);

/* Stores the screen mode and sets the widget icon to match it. (PAL) */
void menu_set_screen_mode_and_sound_pal(char *self, int mode)
{
    *(int *)(self + 0x15A4) = mode;
    switch (mode) {
    case 0:
        hud_set_widget_value_pair(self + 0x2A0, 0x7567, 0);
        break;
    case 1:
        hud_set_widget_value_pair(self + 0x2A0, 0xEAA2, 0);
        break;
    }
}


extern void F72a1dff5_FUN_00349AB8(char *p, int a);
extern void F72a1dff5_FUN_00349630(char *p, int a);
extern void F72a1dff5_FUN_00336920(char *p, void *b, int c);

/* Stores a value and, if its flag is set, clears it and resets the screen widgets. (PAL) */
void menu_set_screen_value_restart_fades_pal(char *menu, void *data, int value)
{
    *(int *)(menu + 0x1584) = value;
    if (*(int *)(menu + 0x1588) != 0) {
        *(int *)(menu + 0x1588) = 0;
        F72a1dff5_FUN_00349AB8(menu + 0xF3C, 0);
        F72a1dff5_FUN_00349AB8(menu + 0xFD0, 0);
        F72a1dff5_FUN_00349AB8(menu + 0x1064, 0);
        F72a1dff5_FUN_00349630(menu + 0x10F8, 1);
        F72a1dff5_FUN_00349AB8(menu + 0x1180, 0);
        F72a1dff5_FUN_00336920(menu + 0x158, data, 0);
    }
    if (*(int *)(menu + 0x159C) != 0) {
        F72a1dff5_FUN_00336920(menu + 0x158, data, 0);
    }
}


typedef int s32;
extern void F01bd4546_FUN_00335E68(char *p, int v);
extern void F01bd4546_FUN_00349630(char *p, int v);
extern void F01bd4546_FUN_00349678(char *p, float v);

/* Stores a value and, if its flag is set, clears it and restarts the six slot fades (PAL timings). (PAL) */
void menu_set_screen_value_restart_six_fades_pal(char *menu, int value)
{
    char *slot_1, *slot_2, *slot_3, *slot_4, *slot_5, *slot_6;

    *(s32 *)(menu + 5524) = value;
    if (*(s32 *)(menu + 5528) != 0) {
        *(s32 *)(menu + 5528) = 0;
        F01bd4546_FUN_00335E68(menu + 1496, 0);
        slot_1 = menu + 3084;
        slot_2 = menu + 3220;
        slot_3 = menu + 3356;
        slot_4 = menu + 3492;
        slot_5 = menu + 3628;
        slot_6 = menu + 3764;
        F01bd4546_FUN_00349630(slot_1, 1);
        F01bd4546_FUN_00349630(slot_2, 1);
        F01bd4546_FUN_00349630(slot_3, 1);
        F01bd4546_FUN_00349630(slot_4, 1);
        F01bd4546_FUN_00349630(slot_5, 1);
        F01bd4546_FUN_00349630(slot_6, 1);
        F01bd4546_FUN_00349678(slot_1, *(s32 *)0x1A7C18 ? 0.14f : 0.116666675f);
        F01bd4546_FUN_00349678(slot_2, *(s32 *)0x1A7C18 ? 0.14f : 0.116666675f);
        F01bd4546_FUN_00349678(slot_3, *(s32 *)0x1A7C18 ? 0.14f : 0.116666675f);
        F01bd4546_FUN_00349678(slot_4, *(s32 *)0x1A7C18 ? 0.14f : 0.116666675f);
        F01bd4546_FUN_00349678(slot_5, *(s32 *)0x1A7C18 ? 0.14f : 0.116666675f);
        F01bd4546_FUN_00349678(slot_6, *(s32 *)0x1A7C18 ? 0.14f : 0.116666675f);
    }
}


extern int math_ping_pong_blend_values_pal(int, int, int, int, int);
extern void object_set_flag_value(void *, int);
extern int g_menu_input_flags;
extern int math_ping_pong_blend_values_pal(int, int, int, int, int);
extern float *object_get_field_a(void *);
extern void object_set_flag_value(void *, int);

/* Sets a label widget's pulsing color, value and visibility. */
void menu_show_colored_label_pal(char *object, int enabled, float value)
{
    int *result;
    char *child;
    if (g_menu_input_flags & 0xF000)
        math_ping_pong_blend_values_pal(0, 0, 1, 0, 1);
    child = object + 0x5D8;
    result = (int *)object_get_fourth_field((unsigned char *)child);
    *result = math_ping_pong_blend_values_pal(0x60442D00, 0x70FFFEED, 20, 0, 0);
    *object_get_field_a(child) = value;
    object_set_flag_value(child, enabled);
}


extern void F076896f4_FUN_00349AB8(void *, int);

/* Stores a value and, if its flag is set, clears it and restarts four widgets' fades. (PAL) */
void menu_set_screen_value_restart_four_fades_pal(int *self, int value)
{
    self[1379] = value;
    if (self[1380] != 0) {
        self[1380] = 0;
        F076896f4_FUN_00349AB8((char *)self + 4628, 0);
        F076896f4_FUN_00349AB8((char *)self + 4776, 0);
        F076896f4_FUN_00349AB8((char *)self + 4924, 0);
        F076896f4_FUN_00349AB8((char *)self + 5072, 0);
    }
}



extern void *object_construct_derived_b(void *p);
extern s32 hud_construct_pal(void *p);
extern void *object_construct_derived_c(void *p);
extern void *text_panel_shutdown(void *p);

/* walks 26 consecutive 72-byte records calling one leaf per record, then calls four more leaves on fixed offsets of the same object and returns the object pointer */
unsigned char *menu_init_level_parts_pal(unsigned char *menu)
{
    unsigned char *slot;
    int i;

    for (i = 25, slot = menu; i != -1; i--) {
        object_construct_derived_b(slot);
        slot += 72;
    }
    object_construct_derived_b(menu + 1872);
    hud_construct_pal(menu + 1952);
    object_construct_derived_c(menu + 7504);
    text_panel_shutdown(menu + 7564);
    text_panel_shutdown(menu + 8156);
    return menu;
}

