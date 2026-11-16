#include "include_asm.h"
#include "names.h"


extern int *object_get_fourth_field(unsigned char *field);

/* Returns the alpha byte of the HUD label's color (the label at +0x378). */
unsigned int menu_get_label_color_alpha_us2(unsigned char *owner)
{
    unsigned int color_address = (unsigned int)object_get_fourth_field(owner + 0x378);
    return *(unsigned int *)color_address & 0xff000000u;
}


extern void hud_set_widget_value_pair(char *, int, int);

/* Stores the screen mode and shows the matching icon on the second widget. */
void menu_set_screen_mode_and_sound_us2(char *self, int mode)
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

/* Stores a value and, if the fade flag is set, clears it and restarts the HUD fades. */
void menu_set_screen_value_restart_fades_us2(char *hud, void *item, int value)
{
    *(int *)(hud + 0x1584) = value;
    if (*(int *)(hud + 0x1588) != 0) {
        *(int *)(hud + 0x1588) = 0;
        F72a1dff5_FUN_00349AB8(hud + 0xF3C, 0);
        F72a1dff5_FUN_00349AB8(hud + 0xFD0, 0);
        F72a1dff5_FUN_00349AB8(hud + 0x1064, 0);
        F72a1dff5_FUN_00349630(hud + 0x10F8, 1);
        F72a1dff5_FUN_00349AB8(hud + 0x1180, 0);
        F72a1dff5_FUN_00336920(hud + 0x158, item, 0);
    }
    if (*(int *)(hud + 0x159C) != 0) {
        F72a1dff5_FUN_00336920(hud + 0x158, item, 0);
    }
}


typedef int s32;
extern void F01bd4546_FUN_00335E68(char *p, int v);
extern void F01bd4546_FUN_00349630(char *p, int v);
extern void F01bd4546_FUN_00349678(char *p, float v);

/* Stores a value and, if the fade flag is set, clears it and restarts six fading widgets at the PAL/NTSC speed. */
void menu_set_screen_value_restart_six_fades_us2(char *hud, int value)
{
    char *widget_0, *widget_1, *widget_2, *widget_3, *widget_4, *widget_5;

    *(s32 *)(hud + 5524) = value;
    if (*(s32 *)(hud + 5528) != 0) {
        *(s32 *)(hud + 5528) = 0;
        F01bd4546_FUN_00335E68(hud + 1496, 0);
        widget_0 = hud + 3084;
        widget_1 = hud + 3220;
        widget_2 = hud + 3356;
        widget_3 = hud + 3492;
        widget_4 = hud + 3628;
        widget_5 = hud + 3764;
        F01bd4546_FUN_00349630(widget_0, 1);
        F01bd4546_FUN_00349630(widget_1, 1);
        F01bd4546_FUN_00349630(widget_2, 1);
        F01bd4546_FUN_00349630(widget_3, 1);
        F01bd4546_FUN_00349630(widget_4, 1);
        F01bd4546_FUN_00349630(widget_5, 1);
        F01bd4546_FUN_00349678(widget_0, *(s32 *)0x1A7B98 ? 0.14f : 0.116666675f);
        F01bd4546_FUN_00349678(widget_1, *(s32 *)0x1A7B98 ? 0.14f : 0.116666675f);
        F01bd4546_FUN_00349678(widget_2, *(s32 *)0x1A7B98 ? 0.14f : 0.116666675f);
        F01bd4546_FUN_00349678(widget_3, *(s32 *)0x1A7B98 ? 0.14f : 0.116666675f);
        F01bd4546_FUN_00349678(widget_4, *(s32 *)0x1A7B98 ? 0.14f : 0.116666675f);
        F01bd4546_FUN_00349678(widget_5, *(s32 *)0x1A7B98 ? 0.14f : 0.116666675f);
    }
}


extern int math_ping_pong_blend_values(int, int, int, int, int);
extern void object_set_flag_value(void *, int);
extern int g_menu_input_flags;
extern int math_ping_pong_blend_values(int, int, int, int, int);
extern float *object_get_field_a(void *);
extern void object_set_flag_value(void *, int);

/* Shows the colored label with a pulsing color and the given value; any d-pad input restarts the pulse. */
void menu_show_colored_label_us2(char *object, int visible, float value)
{
    int *color;
    char *label;
    if (g_menu_input_flags & 0xF000)
        math_ping_pong_blend_values(0, 0, 1, 0, 1);
    label = object + 0x5D8;
    color = (int *)object_get_fourth_field((unsigned char *)label);
    *color = math_ping_pong_blend_values(0x60442D00, 0x70FFFEED, 20, 0, 0);
    *object_get_field_a(label) = value;
    object_set_flag_value(label, visible);
}


extern void F076896f4_FUN_00349AB8(void *, int);

/* Stores a value and, if the fade flag is set, clears it and restarts four fading widgets. */
void menu_set_screen_value_restart_four_fades_us2(int *hud, int value)
{
    hud[1379] = value;
    if (hud[1380] != 0) {
        hud[1380] = 0;
        F076896f4_FUN_00349AB8((char *)hud + 4628, 0);
        F076896f4_FUN_00349AB8((char *)hud + 4776, 0);
        F076896f4_FUN_00349AB8((char *)hud + 4924, 0);
        F076896f4_FUN_00349AB8((char *)hud + 5072, 0);
    }
}




extern void *object_construct_derived_b(void *p);
extern s32 hud_construct_us2(void *p);
extern void *object_construct_derived_c(void *p);
extern void *text_panel_shutdown(void *p);

/* walks 26 consecutive 72-byte records calling one leaf per record, then calls four more leaves on fixed offsets of the same object and returns the object pointer */
/* Constructs the HUD's 26 widget records and its other parts, and returns the HUD. */
unsigned char *hud_item_panel_construct_us2(unsigned char *hud)
{
    unsigned char *widget;
    int i;

    for (i = 25, widget = hud; i != -1; i--) {
        object_construct_derived_b(widget);
        widget += 72;
    }
    object_construct_derived_b(hud + 1872);
    hud_construct_us2(hud + 1952);
    object_construct_derived_c(hud + 7504);
    text_panel_shutdown(hud + 7564);
    text_panel_shutdown(hud + 8156);
    return hud;
}

