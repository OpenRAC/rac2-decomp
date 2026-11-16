#include "include_asm.h"
#include "names.h"

extern int g_menu_input_flags[];
extern char *g_resident_data_base[] __attribute__((sda));
extern int math_ping_pong_blend_values(int, int, int, int, int);
extern int *object_get_fourth_field(void *);
extern float *object_get_second_field(void *);
extern void gfx_draw_screen_element_stored(void *);
extern void text_label_draw_us2(void *);
extern void object_set_flag_value(void *, int);
extern void radial_menu_draw_info_second(void *);
extern void radial_menu_draw_info_left_us2(void *);
extern void radial_menu_layout_items(void *, int, int, int);
typedef struct {
    char reserved00[8];
    short adjustment;
    short reserved0A;
    void (*draw)(void *);
} DrawMethod;

/* Draws the radial menu with its eight item slots and eight icons, when the menu is open (USA v2.00 layout). */
void radial_menu_draw_us2(char *self)
{
    char *highlight, *arrow_left, *arrow_right, *entry, *icon, *cursor, *slot, *icon_slot;
    int i, j;
    float *scale;
    int *color;
    if (*(int *)(self+0xAB8)) {
        if (g_menu_input_flags[0]&0xF000) math_ping_pong_blend_values(0,0,1,1,1);
        highlight=self+0x214; arrow_left=self+0x2A8; arrow_right=self+0x2F4;
        color=object_get_fourth_field(highlight);
        cursor=self+0x5A0;
        *color=math_ping_pong_blend_values(0x60442D00,0x70FFFEED,20,1,0);
        entry=self+0x340;
        gfx_draw_screen_element_stored(self);
        slot=self+0x370;
        gfx_draw_screen_element_stored(self+0x4C);
        gfx_draw_screen_element_stored(self+0xE4);
        gfx_draw_screen_element_stored(self+0x130);
        text_label_draw_us2(self+0x828);
        text_label_draw_us2(self+0x8D8);
        text_label_draw_us2(self+0x930);
        text_label_draw_us2(self+0x988);
        text_label_draw_us2(self+0x9E0);
        object_set_flag_value(self+0x880,0);
        radial_menu_draw_info_second(self);
        radial_menu_draw_info_left_us2(self);
        gfx_draw_screen_element_stored(highlight);gfx_draw_screen_element_stored(arrow_left);gfx_draw_screen_element_stored(arrow_right);
        scale=object_get_second_field(arrow_left); *scale=-*scale;
        scale=object_get_second_field(arrow_right); *scale=-*scale;
        gfx_draw_screen_element_stored(arrow_left);gfx_draw_screen_element_stored(arrow_right);
        scale=object_get_second_field(arrow_left); *scale=-*scale;
        scale=object_get_second_field(arrow_right); *scale=-*scale;
        for(i=7;i>=0;i--,entry+=0x4C,slot+=0x4C) {
            DrawMethod *m=*(DrawMethod **)slot;
            m->draw(entry+m->adjustment);
        }
        icon=self+0x5EC;icon_slot=self+0x61C;
        for(j=7;j>=0;j--,icon+=0x3C,icon_slot+=0x3C) {
            DrawMethod *m=*(DrawMethod **)icon_slot;
            m->draw(icon+m->adjustment);
        }
        gfx_draw_screen_element_stored(cursor);
        *object_get_fourth_field(cursor)=0x80FFDE8D;
        radial_menu_layout_items(g_resident_data_base[0]+0x36F28,0xF3,0x2B,0x70);
    }
}
