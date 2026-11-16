#include "common.h"

/* func_PAL_L11_004495E8: the PAL copy of v2.00's func_US2_L11_004455E0
 * (src/us2/levels/11_joba/L11_004455E0-g8.c), the Joba copy of the v2.00 menu panel. The same C,
 * flags and helpers, with PAL's text ids. The v2.00 notes follow.
 * Its loop label differs from the twin's in two ways. The label's y goes through hud_coord1, the
 * display-mode test of hud_coord alone, and its colour is read in a one-pass group like the count
 * line's. With the full hud_coord the loop is three insns longer, loop.c keeps the constant 8 of
 * `i == 8` inside it, and the colour load is scheduled into the label's y. */
extern void joba_menu_draw_help_prompts(char *,int);
extern int arena_get_challenge_title_text_id(int), arena_get_challenge_flag_index(int), func_L11_00442958(int);
extern char *GetLocalizedString(int);
extern int func_001157AC(char *);
extern int sprintf(char *,char *,...);
extern void FontSetWindow(void *,int,int,int,int,int,int,int,int);
extern void text_draw_window_large(void *,u64,char *,int);
extern void text_draw_window_small(void *,u64,char *,int);
extern int pal_language_at_least_two(void);
extern unsigned char g_language MACRO_ADDR;
extern void text_draw_small(int,int,u64,char *,int);
extern void text_draw_medium(int,int,u64,char *,int);
extern int flag_is_byte_set(void);
extern float g_hud_label_y_param;
extern int g_selection_panel_y;
extern int g_selection_panel_window_arg_a;
extern int g_selection_panel_window_arg_b;
extern char g_str_count_line_format[], g_str_challenge_label_format[];
extern unsigned char g_game_flag_table[], g_item_slot_to_record[];
extern int *g_arena_challenge_table[] SDATA(D_L11_001B14F8);
typedef struct { unsigned char pad[4]; unsigned char enabled; unsigned char rest[0xdb]; } MenuRecord;
extern unsigned char g_item_l11_record_table[];
extern int g_selection_panel_header_color __attribute__((sda));
extern int g_selection_panel_window_arg_d __attribute__((sda));
extern int g_selection_panel_height __attribute__((sda));
extern int g_selection_panel_x __attribute__((sda));
extern int g_selection_panel_window_arg_c __attribute__((sda));
extern int g_selection_panel_value_x __attribute__((sda));
extern int g_selection_panel_value_y __attribute__((sda));
extern int g_selection_panel_value_color __attribute__((sda));
extern int g_selection_panel_prev_hint_x __attribute__((sda));
extern int g_selection_panel_prev_hint_y __attribute__((sda));
extern int g_selection_panel_prev_hint_color __attribute__((sda));
extern int g_selection_panel_next_hint_x[] SDATA(D_L11_001B1698);
extern int g_selection_panel_next_hint_y __attribute__((sda));
extern int g_selection_panel_next_hint_color __attribute__((sda));
extern int g_selection_panel_count_x __attribute__((sda));
extern int g_selection_panel_count_y __attribute__((sda));
extern int g_selection_panel_count_color __attribute__((sda));
extern int g_selection_panel_hint_a_x __attribute__((sda));
extern int g_selection_panel_hint_a_y __attribute__((sda));
extern int g_selection_panel_hint_a_color __attribute__((sda));
extern int g_selection_panel_hint_c_x[] SDATA(D_L11_001B16C8);
extern int g_selection_panel_hint_c_y __attribute__((sda));
extern int g_selection_panel_hint_c_color __attribute__((sda));
extern int g_selection_panel_hint_b_x[] SDATA(D_L11_001B16D8);
extern int g_selection_panel_hint_b_y __attribute__((sda));
extern int g_selection_panel_hint_b_color __attribute__((sda));
extern int g_hud_coord_mode;
#define SEL (*(short *)(state+0x1e8))
/* Dead-test HUD coordinate helper (owner ruling 8 November 2026, as in L05_0037A5F8-g8.c). */
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = g_hud_coord_mode;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;

    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = scale;
    copy = handle;
    if (copy != 0)
        scaled = half;
    return result;
}
static __inline__ int hud_coord(float value, float scale, float half)
{
    int mode = g_hud_coord_mode;
    float scaled = value * scale + half;
    int result = (int)scaled;
    int copy;

    if (mode == 1)
        scaled = scale;
    if (result != 0)
        scaled = scale;
    copy = result;
    if (copy != 0)
        scaled = half;
    return result;
}
/* hud_coord1: hud_coord with its display-mode test only (the same kind of dead test). */
static __inline__ int hud_coord1(float value, float scale, float half)
{
    int mode = g_hud_coord_mode;
    float scaled = value * scale + half;
    int result = (int)scaled;

    if (mode == 1)
        scaled = scale;
    return result;
}

/* Draws the Joba challenge selection panel: the challenge title, its best score and counts, and
   the previous/next/confirm hints (PAL copy of joba_menu_draw_selection_panel). */
void joba_menu_draw_selection_panel_pal(unsigned char *object) {
    unsigned char box[32]; char buffer[64];
    unsigned char *state; char *text,*unit,*str; int *x5,*x7,*x8; int i,value,y2,y3,y4,y5,y6,y7,y8,bx,by,bh; u64 c1,c2,c3,c4,c5,c6,c7,c8; float half,h;
    joba_menu_draw_help_prompts(object,1);
    state=*(unsigned char **)(object+0x68);
    text=((char *)GetLocalizedString(arena_get_challenge_title_text_id(SEL)));
    bx=hud_coord((float)g_selection_panel_x, g_hud_label_y_param, 0.5f);
    by=hud_coord((float)g_selection_panel_y, g_hud_label_y_param, 0.5f);
    bh=hud_coord((float)g_selection_panel_height, g_hud_label_y_param, 0.5f);
    FontSetWindow(box,bx,by,g_selection_panel_window_arg_a,g_selection_panel_window_arg_b,g_selection_panel_window_arg_d,bh,g_selection_panel_window_arg_c,3);
    if(pal_language_at_least_two()) { c1=g_selection_panel_header_color; text_draw_window_small(box,c1,text,func_001157AC(text)); }
    else { c1=g_selection_panel_header_color; text_draw_window_large(box,c1,text,func_001157AC(text)); }
    if(SEL==0 && !g_game_flag_table[arena_get_challenge_flag_index(0)]) goto counts;
    if(SEL==1 && !g_game_flag_table[arena_get_challenge_flag_index(1)]) goto counts;
    {
        text=((char *)GetLocalizedString(0xE69)); unit=((char *)GetLocalizedString(0xE83)); value=func_L11_00442958(SEL);
        if(value<10000) { sprintf(buffer,g_str_count_line_format,text,(u64)value,unit); str=buffer; }
        else { sprintf(buffer,g_str_challenge_label_format,text,(u64)value); str=buffer; }
        y2=hud_coord((float)g_selection_panel_value_y, g_hud_label_y_param, 0.5f); c2=g_selection_panel_value_color; text_draw_medium(g_selection_panel_value_x,y2,c2,str,func_001157AC(str));
    }
counts:
    if(g_game_flag_table[arena_get_challenge_flag_index(SEL)]) {
        text=((char *)GetLocalizedString(0xE63));
        sprintf(buffer,g_str_challenge_label_format,text,g_game_flag_table[arena_get_challenge_flag_index(SEL)]); str=buffer;
        y3=(int)((float)g_selection_panel_count_y * g_hud_label_y_param + 0.5f); do { c3=g_selection_panel_count_color; } while(0); text_draw_medium(g_selection_panel_count_x,y3,c3,str,func_001157AC(str));
    }
    if(SEL!=0) { text=((char *)GetLocalizedString(0xE65)); h=0.5f; y4=hud_coord((float)g_selection_panel_prev_hint_y, g_hud_label_y_param, h); c4=g_selection_panel_prev_hint_color; text_draw_small(g_selection_panel_prev_hint_x,y4,c4,text,func_001157AC(text)); }
    for(i=SEL+1;i<13;i++) {
        if(!g_game_flag_table[arena_get_challenge_flag_index(g_arena_challenge_table[i][2])]) continue;
        if(i>=11 && !flag_is_byte_set()) continue;
        if(i==8 && !((MenuRecord *)(g_item_l11_record_table + g_item_slot_to_record[0x1e] * 0xe0))->enabled) continue;
        text=((char *)GetLocalizedString(0xE66)); x5=&g_selection_panel_next_hint_x[g_language]; h=0.5f; y5=hud_coord1((float)g_selection_panel_next_hint_y, g_hud_label_y_param, h); do { c5=g_selection_panel_next_hint_color; } while(0); text_draw_small(*x5,y5,c5,text,func_001157AC(text)); break;
    }
    half=0.5f;
    text=((char *)GetLocalizedString(0xE64)); y6=hud_coord((float)g_selection_panel_hint_a_y, g_hud_label_y_param, half); c6=g_selection_panel_hint_a_color; text_draw_small(g_selection_panel_hint_a_x,y6,c6,text,func_001157AC(text));
    text=((char *)GetLocalizedString(0xE67)); x7=&g_selection_panel_hint_b_x[g_language]; y7=label_y(x7, (float)g_selection_panel_hint_b_y, g_hud_label_y_param, half, 1); c7=g_selection_panel_hint_b_color; text_draw_small(*x7,y7,c7,text,func_001157AC(text));
    text=((char *)GetLocalizedString(0xE68)); x8=&g_selection_panel_hint_c_x[g_language]; y8=hud_coord((float)g_selection_panel_hint_c_y, g_hud_label_y_param, half); c8=g_selection_panel_hint_c_color; text_draw_small(*x8,y8,c8,text,func_001157AC(text));
}
