#include "common.h"

typedef struct { int id, kind, spare[3], owned; } ItemRow;
typedef struct {
    int state, tick;
    char pad08[0x64];
    int scroll;
    char pad70[0x10];
    int selected;
    char pad84[0xbc];
    ItemRow rows[64];
    int count;
} ListState;
typedef struct { char pad00[4]; unsigned char color; char pad05[0x37]; unsigned short icon; char pad3e[0xa2]; } IconInfo;
extern ListState g_vendor_menu_state;
extern unsigned char g_item_slot_to_record[];
extern IconInfo g_weapon_table[];
extern float D_001B2280[] MACRO_ADDR;
extern int g_is_pal_video MACRO_ADDR;
extern int g_screen_width MACRO_ADDR, g_screen_height MACRO_ADDR;
extern void gfx_set_scissor_clamped(int,int,int,int);
extern int subtract_integer_with_clamp(int);
extern void DrawFramebufferRect(int,int,int,int,int,int,unsigned int);
extern int GetIconFrame(int,int);
extern unsigned int ui_get_item_color(int);
extern void hud_draw_sprite_gradient(int,int,int,int,int,unsigned int *);
extern char *GetLocalizedString(int);
extern int text_measure_width_small_scaled(char *,int,float);
extern void draw_large_text_edge_faded(float,float,unsigned long,float,char *,int);

#define screen_y(y) ((int)(D_001B2280[0] * (y) + 0.5f) + (D_001A7B90 ? 4 : 0))

/* Draws the scrolling row of item icons in the vendor menu, with a pulsing frame around the
   selected one and a label under items already owned or for sale. */
void DrawVendorItemSelectList(void)
{
    int pulse;
    int i, index, y, icon, kind, special, alpha0, alpha1;
    unsigned int color, colors[4];
    double distance;
    gfx_set_scissor_clamped(58,456,(int)(D_001B2280[0]*320.0f+0.5f),screen_y(382));
    if (g_vendor_menu_state.scroll < 0) g_vendor_menu_state.scroll += 4;
    else if (g_vendor_menu_state.scroll > 0) g_vendor_menu_state.scroll -= 4;
    i = -5;
    pulse = ((subtract_integer_with_clamp(((g_vendor_menu_state.tick*4)&63)-32)+64)*0x10202)|0x80000000;
    DrawFramebufferRect(229,screen_y(325),285,screen_y(381),g_screen_width,g_screen_height,
        pulse);
    DrawFramebufferRect(231,screen_y(327),283,screen_y(379),g_screen_width,g_screen_height,0x80442d00);
    y = g_vendor_menu_state.scroll - 47;
    do {
        index = i + g_vendor_menu_state.selected;
        if (index >= 0 && index < g_vendor_menu_state.count) {
            icon = GetIconFrame((g_weapon_table + g_item_slot_to_record[g_vendor_menu_state.rows[index].id])->icon,0);
            if (g_vendor_menu_state.rows[index].owned) kind = 2;
            else {
                special = 0;
                kind = g_weapon_table[g_item_slot_to_record[g_vendor_menu_state.rows[index].id]].color;
                switch (g_vendor_menu_state.rows[index].id) {
                case 12: case 14: case 17: case 18: case 53: special = 1; break;
                }
                kind = special && kind == 1 ? 2 : kind;
            }
            color = ui_get_item_color(kind) & 0xffffff;
            distance = (double)(256.0f - (float)(y+2));
            if (distance < 0.0) distance = -distance;
            alpha0 = 128 - (int)(distance * 0.75);
            distance = (double)(256.0f - (float)(y+40));
            if (distance < 0.0) distance = -distance;
            alpha1 = 128 - (int)(distance * 0.75);
            alpha0 = alpha0 < 0 ? 0 : alpha0;
            alpha1 = alpha1 < 0 ? 0 : alpha1;
            alpha0 <<= 24;
            alpha1 <<= 24;
            colors[2] = colors[0] = alpha0 | color;
            colors[3] = colors[1] = alpha1 | color;
            hud_draw_sprite_gradient(icon,y+4,screen_y(329),40,(int)(D_001B2280[0]*40.0f+0.5f),colors);
            if (g_vendor_menu_state.rows[index].owned) {
                char *text = GetLocalizedString(0x325f);
                int tx = (text_measure_width_small_scaled(text,-1,0.75f) >> 1) - 25;
                draw_large_text_edge_faded((float)(y - tx),(float)screen_y(366),0x80f0f0f0UL,0.75f,text,-1);
            } else if (g_vendor_menu_state.rows[index].kind == 1) {
                char *text = GetLocalizedString(0x2dc9);
                int tx = (text_measure_width_small_scaled(text,-1,0.75f) >> 1) - 25;
                draw_large_text_edge_faded((float)(y - tx),(float)screen_y(366),0x80f0f0f0UL,0.75f,text,-1);
            }
        }
        i++;
        y += 56;
    } while (i < 7);
}
