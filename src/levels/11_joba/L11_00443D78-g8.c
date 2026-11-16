#include "names.h"
/* Draws the menu panel: header box, value line, count line and labels. */
#include "common.h"
extern void joba_menu_draw_help_prompts(void *,int);
extern int arena_get_challenge_title_text_id(int), arena_get_challenge_flag_index(int), func_L11_00442958(int), flag_is_byte_set(void);
extern char *GetLocalizedString(int);
extern int func_001157AC(char *);
extern int sprintf(char *,char *,...);
extern void text_draw_medium(int,int,u64,char *,int), text_draw_small(int,int,u64,char *,int);
extern void FontSetWindow(void *,int,int,int,int,int,int,int,int),text_draw_window_large(void *,u64,char *,int);
extern int g_selection_panel_header_color __attribute__((sda));
extern int g_selection_panel_window_arg_d __attribute__((sda));
extern int g_selection_panel_height __attribute__((sda));
extern int g_selection_panel_spare_a __attribute__((sda));
extern int g_selection_panel_x __attribute__((sda));
extern int g_selection_panel_y;
extern int g_selection_panel_window_arg_a;
extern int g_selection_panel_window_arg_b;
extern int g_selection_panel_window_arg_c __attribute__((sda));
extern int g_selection_panel_spare_b __attribute__((sda));
extern int g_selection_panel_value_x __attribute__((sda));
extern int g_selection_panel_value_y __attribute__((sda));
extern int g_selection_panel_value_color __attribute__((sda));
extern int g_selection_panel_spare_c __attribute__((sda));
extern int g_selection_panel_prev_hint_x __attribute__((sda));
extern int g_selection_panel_prev_hint_y __attribute__((sda));
extern int g_selection_panel_prev_hint_color __attribute__((sda));
extern int g_selection_panel_spare_d __attribute__((sda));
extern int g_selection_panel_next_hint_x __attribute__((sda));
extern int g_selection_panel_next_hint_y __attribute__((sda));
extern int g_selection_panel_next_hint_color __attribute__((sda));
extern int g_selection_panel_spare_e __attribute__((sda));
extern int g_selection_panel_count_x __attribute__((sda));
extern int g_selection_panel_count_y __attribute__((sda));
extern int g_selection_panel_count_color __attribute__((sda));
extern int g_selection_panel_spare_f __attribute__((sda));
extern int g_selection_panel_hint_a_x __attribute__((sda));
extern int g_selection_panel_hint_a_y __attribute__((sda));
extern int g_selection_panel_hint_a_color __attribute__((sda));
extern int g_selection_panel_spare_g __attribute__((sda));
extern int g_selection_panel_hint_c_x __attribute__((sda));
extern int g_selection_panel_hint_c_y __attribute__((sda));
extern int g_selection_panel_hint_c_color __attribute__((sda));
extern int g_selection_panel_spare_h __attribute__((sda));
extern int g_selection_panel_hint_b_x __attribute__((sda));
extern int g_selection_panel_hint_b_y __attribute__((sda));
extern int g_selection_panel_hint_b_color __attribute__((sda));

extern float g_hud_label_y_param;
extern char g_str_count_line_format[],g_str_challenge_label_format[];
extern unsigned char g_item_slot_to_record[],g_game_flag_table[];
typedef struct { unsigned char pad[4]; unsigned char enabled; unsigned char rest[0xdb]; } MenuRecord;
extern unsigned char g_item_l11_record_table[];
extern int *g_arena_challenge_table[] SDATA(D_L11_001B14F8);
#define TABLE D_L11_001B14F8
#define SEL (*(short *)(state+0x1e8))
extern int g_hud_coord_mode;
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

void joba_menu_draw_selection_panel(unsigned char *moby) {
    unsigned char box[32]; char buffer[64];
    unsigned char *state; char *text,*label,*unit,*line_text,*label_text,*next_hint_text,*t3,*t4,*t5; int i,value,value_y,count_y,prev_hint_y,next_hint_y,hint_y1,hint_y2,hint_y3,one,bx,by,bh; u64 header_color,value_color,count_color,prev_hint_color,next_hint_color,hint_color1,hint_color2,hint_color3; float half;
    one=1;
    joba_menu_draw_help_prompts(moby,1);
    state=*(unsigned char **)(moby+0x68);
    text=((char *)GetLocalizedString(arena_get_challenge_title_text_id(SEL)));
    bx=hud_coord((float)g_selection_panel_x, g_hud_label_y_param, 0.5f);
    by=hud_coord((float)g_selection_panel_y, g_hud_label_y_param, 0.5f);
    bh=hud_coord((float)g_selection_panel_height, g_hud_label_y_param, 0.5f);
    FontSetWindow(box,bx,by,g_selection_panel_window_arg_a,g_selection_panel_window_arg_b,g_selection_panel_window_arg_d,bh,g_selection_panel_window_arg_c,3);
    header_color=g_selection_panel_header_color; text_draw_window_large(box,header_color,text,func_001157AC(text));
    if(SEL==0 && !g_game_flag_table[arena_get_challenge_flag_index(0)]) goto counts;
    if(SEL==one && !g_game_flag_table[arena_get_challenge_flag_index(one)]) goto counts;
    {
        do {
            text=((char *)GetLocalizedString(0x2f44)); unit=((char *)GetLocalizedString(0x2f5e)); value=func_L11_00442958(SEL);
            if(value<10000) { sprintf(buffer,g_str_count_line_format,text,value,unit); line_text=buffer; goto draw1; }
            sprintf(buffer,g_str_challenge_label_format,text,value);
        } while(0);
        line_text=buffer;
    draw1:
        value_y=hud_coord((float)g_selection_panel_value_y, g_hud_label_y_param, 0.5f); value_color=g_selection_panel_value_color; text_draw_medium(g_selection_panel_value_x,value_y,value_color,line_text,func_001157AC(line_text));
    }
counts:
    if(g_game_flag_table[arena_get_challenge_flag_index(SEL)]) {
        label_text=((char *)GetLocalizedString(0x2f3e));
        sprintf(buffer,g_str_challenge_label_format,label_text,g_game_flag_table[arena_get_challenge_flag_index(SEL)]); line_text=buffer;
        count_y=(int)((float)g_selection_panel_count_y * g_hud_label_y_param + 0.5f); do { count_color=g_selection_panel_count_color; } while(0); text_draw_medium(g_selection_panel_count_x,count_y,count_color,line_text,func_001157AC(line_text));
    }
    if(SEL!=0) { label_text=((char *)GetLocalizedString(0x2f40)); prev_hint_y=hud_coord((float)g_selection_panel_prev_hint_y, g_hud_label_y_param, 0.5f); prev_hint_color=g_selection_panel_prev_hint_color; text_draw_small(g_selection_panel_prev_hint_x,prev_hint_y,prev_hint_color,label_text,func_001157AC(label_text)); }
    for(i=SEL+1;i<13;i++) {
        half=0.5f;
        if(!g_game_flag_table[arena_get_challenge_flag_index(TABLE[i][2])]) continue;
        if(i>=11 && !flag_is_byte_set()) continue;
        if(i==8 && !((MenuRecord *)(g_item_l11_record_table + g_item_slot_to_record[0x1e] * 0xe0))->enabled) continue;
        next_hint_text=((char *)GetLocalizedString(0x2f41)); next_hint_y=hud_coord((float)g_selection_panel_next_hint_y, g_hud_label_y_param, half); next_hint_color=g_selection_panel_next_hint_color; text_draw_small(g_selection_panel_next_hint_x,next_hint_y,next_hint_color,next_hint_text,func_001157AC(next_hint_text)); break;
    }
    half=0.5f;
    text=((char *)GetLocalizedString(0x2f3f)); hint_y1=hud_coord((float)g_selection_panel_hint_a_y, g_hud_label_y_param, half); hint_color1=g_selection_panel_hint_a_color; text_draw_small(g_selection_panel_hint_a_x,hint_y1,hint_color1,text,func_001157AC(text));
    text=((char *)GetLocalizedString(0x2f42)); hint_y2=hud_coord((float)g_selection_panel_hint_b_y, g_hud_label_y_param, half); hint_color2=g_selection_panel_hint_b_color; text_draw_small(g_selection_panel_hint_b_x,hint_y2,hint_color2,text,func_001157AC(text));
    text=((char *)GetLocalizedString(0x2f43)); hint_y3=hud_coord((float)g_selection_panel_hint_c_y, g_hud_label_y_param, half); hint_color3=g_selection_panel_hint_c_color; text_draw_small(g_selection_panel_hint_c_x,hint_y3,hint_color3,text,func_001157AC(text));
}
