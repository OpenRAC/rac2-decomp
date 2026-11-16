#include "common.h"

/* func_PAL_L02_004029E0: the PAL copy of v2.00's func_US2_L02_003FF808
 * (src/us2/levels/02_maktar_nebula/L02_003FF808-g8.c), itself the v2.00 copy of func_L02_003FE250, the
 * Maktar Nebula menu panel. The same C, flags and helpers, with PAL's text ids. As in v2.00, the
 * header text is drawn with func_00280190 when func_PAL_L02_00402928 returns nonzero, and three
 * label x positions come from per-language tables indexed by D_001A7BB4. */
extern void arena_draw_menu_help_prompts(char *,int);
extern int arena_get_challenge_name_text(int), arena_get_challenge_save_index(int), moby_compute_scaled_entry_value(int);
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
extern float g_hud_label_scale;
extern int g_arena_panel_box_y;
extern int g_arena_panel_window_left;
extern int g_arena_panel_window_top;
extern char g_str_arena_panel_format[], g_str_arena_value_format[];
extern unsigned char g_game_flag_table[], g_item_slot_to_record[];
extern int *g_arena_challenge_table_2[] SDATA(D_L02_001B1190);
typedef struct { unsigned char pad[4]; unsigned char enabled; unsigned char rest[0xdb]; } MenuRecord;
extern unsigned char g_material_l02_table[];
extern int g_arena_panel_title_color __attribute__((sda));
extern int g_arena_panel_window_height __attribute__((sda));
extern int g_arena_panel_box_height __attribute__((sda));
extern int g_arena_panel_box_x __attribute__((sda));
extern int g_arena_panel_window_flags __attribute__((sda));
extern int g_arena_panel_line_x __attribute__((sda));
extern int g_arena_panel_line_y __attribute__((sda));
extern int g_arena_panel_line_color __attribute__((sda));
extern int g_arena_panel_hint_x __attribute__((sda));
extern int g_arena_panel_hint_y __attribute__((sda));
extern int g_arena_panel_hint_color __attribute__((sda));
extern int g_arena_panel_note_x[] SDATA(D_L02_001B12D8);
extern int g_arena_panel_note_y __attribute__((sda));
extern int g_arena_panel_note_color __attribute__((sda));
extern int g_arena_panel_value_x __attribute__((sda));
extern int g_arena_panel_value_y __attribute__((sda));
extern int g_arena_panel_value_color __attribute__((sda));
extern int g_arena_panel_label_x __attribute__((sda));
extern int g_arena_panel_label_y __attribute__((sda));
extern int g_arena_panel_label_color __attribute__((sda));
extern int g_arena_panel_extra_x[] SDATA(D_L02_001B1308);
extern int g_arena_panel_extra_y __attribute__((sda));
extern int g_arena_panel_extra_color __attribute__((sda));
extern int g_arena_panel_footer_x[] SDATA(D_L02_001B1318);
extern int g_arena_panel_footer_y __attribute__((sda));
extern int g_arena_panel_footer_color __attribute__((sda));
extern int g_hud_l02_mode;
#define SEL (*(short *)(state+0x118))
/* Dead-test HUD coordinate helper (owner ruling 8 November 2026, as in L05_0037A5F8-g8.c). */
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = g_hud_l02_mode;
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
    int mode = g_hud_l02_mode;
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

/* Draws the challenge menu panel: the challenge name, its bolt reward, how often it was done,
   and the hints for moving to the next or previous entry (PAL text ids and per-language positions). */
void arena_draw_menu_panel_pal(unsigned char *object) {
    unsigned char box[32]; char text_buf[64];
    unsigned char *state; char *text,*unit,*line; int *note_x,*footer_x,*extra_x; int i,value,line_y,value_y,hint_y,note_y,label_text_y,footer_y,extra_y,box_x,box_y,box_height; u64 title_color,line_color,value_color,hint_color,note_color,label_color,footer_color,extra_color; float half,h;
    arena_draw_menu_help_prompts(object,1);
    state=*(unsigned char **)(object+0x68);
    text=((char *)GetLocalizedString(arena_get_challenge_name_text(SEL)));
    box_x=hud_coord((float)g_arena_panel_box_x, g_hud_label_scale, 0.5f);
    box_y=hud_coord((float)g_arena_panel_box_y, g_hud_label_scale, 0.5f);
    box_height=hud_coord((float)g_arena_panel_box_height, g_hud_label_scale, 0.5f);
    FontSetWindow(box,box_x,box_y,g_arena_panel_window_left,g_arena_panel_window_top,g_arena_panel_window_height,box_height,g_arena_panel_window_flags,3);
    if(pal_language_at_least_two()) { title_color=g_arena_panel_title_color; text_draw_window_small(box,title_color,text,func_001157AC(text)); }
    else { title_color=g_arena_panel_title_color; text_draw_window_large(box,title_color,text,func_001157AC(text)); }
    if(SEL==0 && !g_game_flag_table[arena_get_challenge_save_index(0)]) goto counts;
    {
        text=((char *)GetLocalizedString(0xE69)); unit=((char *)GetLocalizedString(0xE83)); value=moby_compute_scaled_entry_value(SEL);
        if(value<10000) { sprintf(text_buf,g_str_arena_panel_format,text,(u64)value,unit); line=text_buf; }
        else { sprintf(text_buf,g_str_arena_value_format,text,(u64)value); line=text_buf; }
        line_y=hud_coord((float)g_arena_panel_line_y, g_hud_label_scale, 0.5f); line_color=g_arena_panel_line_color; text_draw_medium(g_arena_panel_line_x,line_y,line_color,line,func_001157AC(line));
    }
counts:
    if(g_game_flag_table[arena_get_challenge_save_index(SEL)]) {
        text=((char *)GetLocalizedString(0xE63));
        sprintf(text_buf,g_str_arena_value_format,text,g_game_flag_table[arena_get_challenge_save_index(SEL)]); line=text_buf;
        value_y=(int)((float)g_arena_panel_value_y * g_hud_label_scale + 0.5f); do { value_color=g_arena_panel_value_color; } while(0); text_draw_medium(g_arena_panel_value_x,value_y,value_color,line,func_001157AC(line));
    }
    if(SEL!=0) { text=((char *)GetLocalizedString(0xE65)); h=0.5f; hint_y=hud_coord((float)g_arena_panel_hint_y, g_hud_label_scale, h); hint_color=g_arena_panel_hint_color; text_draw_small(g_arena_panel_hint_x,hint_y,hint_color,text,func_001157AC(text)); }
    for(i=SEL+1;i<14;i++) {
        if(!g_game_flag_table[arena_get_challenge_save_index(g_arena_challenge_table_2[i][2])]) continue;
        if(i>=12 && !flag_is_byte_set()) continue;
        if(i==7 && !((MenuRecord *)(g_material_l02_table + g_item_slot_to_record[0x1e] * 0xe0))->enabled) continue;
        if(i==8 && !((MenuRecord *)(g_material_l02_table + g_item_slot_to_record[0x2a] * 0xe0))->enabled) continue;
        text=((char *)GetLocalizedString(0xE66)); note_x=&g_arena_panel_note_x[g_language]; h=0.5f; note_y=hud_coord((float)g_arena_panel_note_y, g_hud_label_scale, h); note_color=g_arena_panel_note_color; text_draw_small(*note_x,note_y,note_color,text,func_001157AC(text)); break;
    }
    half=0.5f;
    text=((char *)GetLocalizedString(0xE64)); label_text_y=hud_coord((float)g_arena_panel_label_y, g_hud_label_scale, half); label_color=g_arena_panel_label_color; text_draw_small(g_arena_panel_label_x,label_text_y,label_color,text,func_001157AC(text));
    text=((char *)GetLocalizedString(0xE67)); footer_x=&g_arena_panel_footer_x[g_language]; footer_y=label_y(footer_x, (float)g_arena_panel_footer_y, g_hud_label_scale, half, 1); footer_color=g_arena_panel_footer_color; text_draw_small(*footer_x,footer_y,footer_color,text,func_001157AC(text));
    text=((char *)GetLocalizedString(0xE68)); extra_x=&g_arena_panel_extra_x[g_language]; extra_y=hud_coord((float)g_arena_panel_extra_y, g_hud_label_scale, half); extra_color=g_arena_panel_extra_color; text_draw_small(*extra_x,extra_y,extra_color,text,func_001157AC(text));
}
