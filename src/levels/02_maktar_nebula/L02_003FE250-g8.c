#include "names.h"
/* Draws the menu panel: header box, value line, count line and labels. */
#include "common.h"
extern void arena_draw_menu_help_prompts(char *,int);
extern int arena_get_challenge_name_text(int), arena_get_challenge_save_index(int), moby_compute_scaled_entry_value(int);
extern char *GetLocalizedString(int);
extern int func_001157AC(char *);
extern int sprintf(char *,char *,...);
extern void FontSetWindow(void *,int,int,int,int,int,int,int,int);
extern void text_draw_window_large(void *,u64,char *,int);
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
extern int g_arena_panel_note_x __attribute__((sda));
extern int g_arena_panel_note_y __attribute__((sda));
extern int g_arena_panel_note_color __attribute__((sda));
extern int g_arena_panel_value_x __attribute__((sda));
extern int g_arena_panel_value_y __attribute__((sda));
extern int g_arena_panel_value_color __attribute__((sda));
extern int g_arena_panel_label_x __attribute__((sda));
extern int g_arena_panel_label_y __attribute__((sda));
extern int g_arena_panel_label_color __attribute__((sda));
extern int g_arena_panel_extra_x __attribute__((sda));
extern int g_arena_panel_extra_y __attribute__((sda));
extern int g_arena_panel_extra_color __attribute__((sda));
extern int g_arena_panel_footer_x __attribute__((sda));
extern int g_arena_panel_footer_y __attribute__((sda));
extern int g_arena_panel_footer_color __attribute__((sda));
extern int g_hud_l02_mode;
#define SEL (*(short *)(state+0x118))
/* Dead-test HUD coordinate helper (owner ruling 8 November 2026, as in L05_0037A5F8-g8.c). */
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

static __inline__ int scaled_coord(int value, float scale, float half, int active)
{
    int mode = g_hud_l02_mode;
    float scaled = (float)value * scale + half;
    int result = (int)scaled;

    if (result != 0 && mode == active)
        scaled = 1.0f;
    return result;
}

void arena_draw_menu_panel(unsigned char *object) {
    unsigned char box[32]; char buffer[64];
    unsigned char *state; char *text,*unit,*str; int i,value,y2,y3,y4,y5,y6,y7,y8,bx,by,bh; u64 c1,c2,c3,c4,c5,c6,c7,c8; float half,h;
    arena_draw_menu_help_prompts(object,1);
    state=*(unsigned char **)(object+0x68);
    text=((char *)GetLocalizedString(arena_get_challenge_name_text(SEL)));
    bx=hud_coord((float)g_arena_panel_box_x, g_hud_label_scale, 0.5f);
    by=hud_coord((float)g_arena_panel_box_y, g_hud_label_scale, 0.5f);
    bh=hud_coord((float)g_arena_panel_box_height, g_hud_label_scale, 0.5f);
    FontSetWindow(box,bx,by,g_arena_panel_window_left,g_arena_panel_window_top,g_arena_panel_window_height,bh,g_arena_panel_window_flags,3);
    c1=g_arena_panel_title_color; text_draw_window_large(box,c1,text,func_001157AC(text));
    if(SEL==0 && !g_game_flag_table[arena_get_challenge_save_index(0)]) goto counts;
    {
        do {
            text=((char *)GetLocalizedString(0x2f44)); unit=((char *)GetLocalizedString(0x2f5e)); value=moby_compute_scaled_entry_value(SEL);
            if(value<10000) { sprintf(buffer,g_str_arena_panel_format,text,value,unit); str=buffer; goto draw1; }
            sprintf(buffer,g_str_arena_value_format,text,value);
        } while(0);
        str=buffer;
    draw1:
        y2=hud_coord((float)g_arena_panel_line_y, g_hud_label_scale, 0.5f); c2=g_arena_panel_line_color; text_draw_medium(g_arena_panel_line_x,y2,c2,str,func_001157AC(str));
    }
counts:
    if(g_game_flag_table[arena_get_challenge_save_index(SEL)]) {
        text=((char *)GetLocalizedString(0x2f3e));
        sprintf(buffer,g_str_arena_value_format,text,g_game_flag_table[arena_get_challenge_save_index(SEL)]); str=buffer;
        y3=(int)((float)g_arena_panel_value_y * g_hud_label_scale + 0.5f); do { c3=g_arena_panel_value_color; } while(0); text_draw_medium(g_arena_panel_value_x,y3,c3,str,func_001157AC(str));
    }
    if(SEL!=0) { text=((char *)GetLocalizedString(0x2f40)); h=0.5f; y4=hud_coord((float)g_arena_panel_hint_y, g_hud_label_scale, h); c4=g_arena_panel_hint_color; text_draw_small(g_arena_panel_hint_x,y4,c4,text,func_001157AC(text)); }
    for(i=SEL+1;i<14;i++) {
        if(!g_game_flag_table[arena_get_challenge_save_index(g_arena_challenge_table_2[i][2])]) continue;
        if(i>=12 && !flag_is_byte_set()) continue;
        if(i==7 && !((MenuRecord *)(g_material_l02_table + g_item_slot_to_record[0x1e] * 0xe0))->enabled) continue;
        if(i==8 && !((MenuRecord *)(g_material_l02_table + g_item_slot_to_record[0x2a] * 0xe0))->enabled) continue;
        text=((char *)GetLocalizedString(0x2f41)); h=0.5f; y5=scaled_coord(g_arena_panel_note_y, g_hud_label_scale, h, 1); c5=g_arena_panel_note_color; text_draw_small(g_arena_panel_note_x,y5,c5,text,func_001157AC(text)); break;
    }
    half=0.5f;
    text=((char *)GetLocalizedString(0x2f3f)); y6=hud_coord((float)g_arena_panel_label_y, g_hud_label_scale, half); c6=g_arena_panel_label_color; text_draw_small(g_arena_panel_label_x,y6,c6,text,func_001157AC(text));
    text=((char *)GetLocalizedString(0x2f42)); y7=hud_coord((float)g_arena_panel_footer_y, g_hud_label_scale, half); c7=g_arena_panel_footer_color; text_draw_small(g_arena_panel_footer_x,y7,c7,text,func_001157AC(text));
    text=((char *)GetLocalizedString(0x2f43)); y8=hud_coord((float)g_arena_panel_extra_y, g_hud_label_scale, half); c8=g_arena_panel_extra_color; text_draw_small(g_arena_panel_extra_x,y8,c8,text,func_001157AC(text));
}
