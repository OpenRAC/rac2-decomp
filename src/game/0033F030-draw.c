#include "names.h"
/* Draws the active menu, including eight widgets of each virtual-draw layout.
 * This unit disables GCSE to retain the two loops' separate cursor setup. */
extern int g_menu_input_flags[];
extern char *g_resident_data_base[] __attribute__((sda));
extern int math_ping_pong_blend_values(int, int, int, int, int);
extern int *object_get_fourth_field(void *);
extern float *object_get_second_field(void *);
extern void gfx_draw_screen_element_stored(void *);
extern void text_label_draw(void *);
extern void object_set_flag_value(void *, int);
extern void radial_menu_draw_info_second(void *);
extern void radial_menu_draw_info_left(void *);
extern void radial_menu_layout_items(void *, int, int, int);
typedef struct {
    char reserved00[8];
    short adjustment;
    short reserved0A;
    void (*draw)(void *);
} DrawMethod;
/* Draws the radial menu with its eight item slots and eight icons, when the menu is open. */
void radial_menu_draw(char *self)
{
    char *widget214, *widget2A8, *widget2F4, *recordCursor, *iconCursor, *cursorWidget, *recordMethodSlot, *iconMethodSlot;
    int i, j;
    float *pos;
    int *color;
    if (*(int *)(self+0xA58)) {
        if (g_menu_input_flags[0]&0xF000) math_ping_pong_blend_values(0,0,1,1,1);
        widget214=self+0x214; widget2A8=self+0x2A8; widget2F4=self+0x2F4;
        color=object_get_fourth_field(widget214);
        cursorWidget=self+0x5A0;
        *color=math_ping_pong_blend_values(0x60442D00,0x70FFFEED,20,1,0);
        recordCursor=self+0x340;
        gfx_draw_screen_element_stored(self);
        recordMethodSlot=self+0x370;
        gfx_draw_screen_element_stored(self+0x4C);
        gfx_draw_screen_element_stored(self+0xE4);
        gfx_draw_screen_element_stored(self+0x130);
        text_label_draw(self+0x828);
        text_label_draw(self+0x8B8);
        text_label_draw(self+0x900);
        text_label_draw(self+0x948);
        text_label_draw(self+0x990);
        object_set_flag_value(self+0x870,0);
        radial_menu_draw_info_second(self);
        radial_menu_draw_info_left(self);
        gfx_draw_screen_element_stored(widget214);gfx_draw_screen_element_stored(widget2A8);gfx_draw_screen_element_stored(widget2F4);
        pos=object_get_second_field(widget2A8); *pos=-*pos;
        pos=object_get_second_field(widget2F4); *pos=-*pos;
        gfx_draw_screen_element_stored(widget2A8);gfx_draw_screen_element_stored(widget2F4);
        pos=object_get_second_field(widget2A8); *pos=-*pos;
        pos=object_get_second_field(widget2F4); *pos=-*pos;
        for(i=7;i>=0;i--,recordCursor+=0x4C,recordMethodSlot+=0x4C) {
            DrawMethod *method=*(DrawMethod **)recordMethodSlot;
            method->draw(recordCursor+method->adjustment);
        }
        iconCursor=self+0x5EC;iconMethodSlot=self+0x61C;
        for(j=7;j>=0;j--,iconCursor+=0x3C,iconMethodSlot+=0x3C) {
            DrawMethod *method=*(DrawMethod **)iconMethodSlot;
            method->draw(iconCursor+method->adjustment);
        }
        gfx_draw_screen_element_stored(cursorWidget);
        *object_get_fourth_field(cursorWidget)=0x80FFDE8D;
        radial_menu_layout_items(g_resident_data_base[0]+0x36F28,0xF3,0x2B,0x70);
    }
}
