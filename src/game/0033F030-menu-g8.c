#include "include_asm.h"
#include "names.h"

typedef struct { float x, y; } Pair;
typedef struct { int value; } MenuColor;
extern Pair D_001AE048[], D_001AE050[], D_001AE058[], D_001AE060[], D_001AE068[], D_001AE070[];
typedef struct { int value; char pad[20]; int id; } Item;
typedef struct { Item *items; } Items;
extern Items *g_radial_menu_pages;
extern char *D_001A8CFC;
extern unsigned char g_item_slot_to_record[];
extern int D_00139868[];
extern char g_weapon_table[];
extern struct { char pad[0x1C4]; int buttons; } g_pad_state;
extern void *memset(void *, int, unsigned int);
extern void object_set_first_float4(void *, float, float, float, float);
extern void object_set_flag_value(void *, int);
extern void hud_set_widget_value_pair(void *, int, int);
extern char *menu_return_object_unchanged(void *);
extern void shop_choose_item_colors(int, int *, int *, int *);
extern int *object_get_fourth_field(void *);
extern void object_set_first_pair(void *, int, int);
extern void meter_set_max(void *, int);
extern void meter_set_value(void *, int);
extern int snd_play_from_global_bank(int, int, void *);
extern void radial_menu_move_grid_selection(void *, int);
extern void radial_menu_move_item_selection(void *, int);
extern unsigned int math_ping_pong_blend_values(unsigned int, unsigned int, int, int, int);
extern void object_set_value_float(void *, float);
/* Updates the eight item rows, their colors and the current menu selection. */
int func_0033FB98(char *self, int buttons)
{
    Pair offset0, offsetE4, offset130, offset4C, offset828, offset900, offset8B8, offset948, offset990, offsetCursor;
    MenuColor firstColor, secondColor, textColor;
    int i;
    char *child;
    memset(&offset0,0,8);
    memset(&offsetE4,0,8);
    memset(&offset130,0,8);
    memset(&offset4C,0,8);
    offset828 = D_001AE048[0];
    offset900 = D_001AE050[0];
    offset8B8 = D_001AE058[0];
    offset948 = D_001AE060[0];
    offset990 = D_001AE068[0];
    object_set_first_float4(self + 0x0, offset0.x + (*(Pair **)(self+0x80C))->x, offset0.y + (*(Pair **)(self+0x80C))->y, 0.0f, 0.0f);
    object_set_first_float4(self + 0x4C, offset4C.x + (*(Pair **)(self+0x80C))->x, offset4C.y + (*(Pair **)(self+0x80C))->y, 0.0f, 0.0f);
    object_set_first_float4(self + 0xE4, offsetE4.x + (*(Pair **)(self+0x80C))->x, offsetE4.y + (*(Pair **)(self+0x80C))->y, 0.0f, 0.0f);
    object_set_first_float4(self + 0x130, offset130.x + (*(Pair **)(self+0x80C))->x, offset130.y + (*(Pair **)(self+0x80C))->y, 0.0f, 0.0f);
    object_set_first_float4(self + 0x828, offset828.x + (*(Pair **)(self+0x80C))->x, offset828.y + (*(Pair **)(self+0x80C))->y, 0.0f, 0.0f);
    object_set_first_float4(self + 0x8B8, offset8B8.x + (*(Pair **)(self+0x80C))->x, offset8B8.y + (*(Pair **)(self+0x80C))->y, 0.0f, 0.0f);
    object_set_first_float4(self + 0x900, offset900.x + (*(Pair **)(self+0x80C))->x, offset900.y + (*(Pair **)(self+0x80C))->y, 0.0f, 0.0f);
    object_set_first_float4(self + 0x948, offset948.x + (*(Pair **)(self+0x80C))->x, offset948.y + (*(Pair **)(self+0x80C))->y, 0.0f, 0.0f);
    object_set_first_float4(self + 0x990, offset990.x + (*(Pair **)(self+0x80C))->x, offset990.y + (*(Pair **)(self+0x80C))->y, 0.0f, 0.0f);
    offsetCursor=D_001AE070[0];
    object_set_first_float4(self + 0x2A8, offsetCursor.x + (*(Pair **)(self+0x80C))->x, offsetCursor.y + (*(Pair **)(self+0x80C))->y, 0.0f, 0.0f);
    object_set_first_float4(self + 0x2F4, offsetCursor.x + (*(Pair **)(self+0x80C))->x, offsetCursor.y + (*(Pair **)(self+0x80C))->y, 0.0f, 0.0f);
    object_set_first_float4(self + 0x5A0, offsetCursor.x + (*(Pair **)(self+0x80C))->x, offsetCursor.y + (*(Pair **)(self+0x80C))->y, 0.0f, 0.0f);
    if (g_radial_menu_pages) {
        int resourceOffset;
        i=0;
        resourceOffset = 0x36F28;
        for (child = self + 0x5EC; i < 8; child += 0x3C, i++) {
            char *bar, *row;
            if (!g_radial_menu_pages->items[i].value) object_set_flag_value(child,0);
            else {
                object_set_flag_value(child,1);
                hud_set_widget_value_pair(child,g_radial_menu_pages->items[i].value,0);
            }
            bar=menu_return_object_unchanged(D_001A8CFC+resourceOffset)+i*0x48;
            object_set_flag_value(bar,0);
            firstColor.value = 0;
            secondColor.value = 0;
            textColor.value = 0;
            shop_choose_item_colors(g_radial_menu_pages->items[i].id,&firstColor.value,&secondColor.value,&textColor.value);
            {
                int *primary = object_get_fourth_field(child);
                *primary = (*primary & 0xFF000000) | (textColor.value & 0xFFFFFF);
            }
            bar=menu_return_object_unchanged(D_001A8CFC+resourceOffset)+i*0x48;
            object_set_flag_value(bar,1);
            object_set_first_pair(bar,firstColor.value,secondColor.value);
            meter_set_max(bar,100);
            meter_set_value(bar,100);
            row=g_weapon_table+g_item_slot_to_record[g_radial_menu_pages->items[i].id]*224;
            if (*(int *)row) {
                int active = (unsigned char)row[4] != 0;
                if (*(int *)(row+0x6C) || active) {
                    meter_set_max(bar,*(int *)(row+0x6C));
                    {
                        int *secondary = object_get_fourth_field(child);
                        *secondary = (*secondary & 0xFF000000) | (textColor.value & 0xFFFFFF);
                    }
                    if (*(int *)(g_weapon_table+g_item_slot_to_record[g_radial_menu_pages->items[i].id]*224+0x6C)>0)
                        meter_set_value(bar,D_00139868[g_radial_menu_pages->items[i].id]>>5);
                }
            }
        }
    }
    if (buttons&4) {
        int v,lower;
        snd_play_from_global_bank(3,0,0);
        lower=-1;
        v=*(int *)(self+0x7CC)-1;
        *(int *)(self+0x7CC)=v>lower?v:7;
    } else if (buttons&8) {
        int v;
        snd_play_from_global_bank(3,0,0);
        v=*(int *)(self+0x7CC)+1;
        *(int *)(self+0x7CC)=v>7?0:v;
    } else {
        switch (*(int *)(self+0x81C)) {
        case 0: radial_menu_move_grid_selection(self,buttons); break;
        case 1: radial_menu_move_item_selection(self,buttons); break;
        }
    }
    if (g_pad_state.buttons&12) math_ping_pong_blend_values(0,0,1,0,1);
    {
        int *p=object_get_fourth_field(self+0x5A0);
        *p=math_ping_pong_blend_values(0x60442D00,0x70FFFEED,20,0,0);
    }
    object_set_value_float(self+0x5A0,(float)*(int *)(self+0x7CC));
    return 0;
}
