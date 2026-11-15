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
extern float D_L02_001B3E04;
extern int D_L02_001B12A4;
extern int D_L02_001B12A8;
extern int D_L02_001B12AC;
extern char D_L02_001B1228[], D_L02_001B1328[];
extern unsigned char D_001395B8[], g_item_slot_to_record[];
extern int *D_L02_001B1190[] SDATA(D_L02_001B1190);
typedef struct { unsigned char pad[4]; unsigned char enabled; unsigned char rest[0xdb]; } MenuRecord;
extern unsigned char D_L02_00264A70[];
extern int D_L02_001B1294 __attribute__((sda));
extern int D_L02_001B1298 __attribute__((sda));
extern int D_L02_001B129C __attribute__((sda));
extern int D_L02_001B12A0 __attribute__((sda));
extern int D_L02_001B12B0 __attribute__((sda));
extern int D_L02_001B12B8 __attribute__((sda));
extern int D_L02_001B12BC __attribute__((sda));
extern int D_L02_001B12C0 __attribute__((sda));
extern int D_L02_001B12C8 __attribute__((sda));
extern int D_L02_001B12CC __attribute__((sda));
extern int D_L02_001B12D0 __attribute__((sda));
extern int D_L02_001B12D8 __attribute__((sda));
extern int D_L02_001B12DC __attribute__((sda));
extern int D_L02_001B12E0 __attribute__((sda));
extern int D_L02_001B12E8 __attribute__((sda));
extern int D_L02_001B12EC __attribute__((sda));
extern int D_L02_001B12F0 __attribute__((sda));
extern int D_L02_001B12F8 __attribute__((sda));
extern int D_L02_001B12FC __attribute__((sda));
extern int D_L02_001B1300 __attribute__((sda));
extern int D_L02_001B1308 __attribute__((sda));
extern int D_L02_001B130C __attribute__((sda));
extern int D_L02_001B1310 __attribute__((sda));
extern int D_L02_001B1318 __attribute__((sda));
extern int D_L02_001B131C __attribute__((sda));
extern int D_L02_001B1320 __attribute__((sda));
extern int D_L02_001B3E00;
#define SEL (*(short *)(state+0x118))
/* Dead-test HUD coordinate helper (owner ruling 8 November 2026, as in L05_0037A5F8-g8.c). */
static __inline__ int hud_coord(float value, float scale, float half)
{
    int mode = D_L02_001B3E00;
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
    int mode = D_L02_001B3E00;
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
    bx=hud_coord((float)D_L02_001B12A0, D_L02_001B3E04, 0.5f);
    by=hud_coord((float)D_L02_001B12A4, D_L02_001B3E04, 0.5f);
    bh=hud_coord((float)D_L02_001B129C, D_L02_001B3E04, 0.5f);
    FontSetWindow(box,bx,by,D_L02_001B12A8,D_L02_001B12AC,D_L02_001B1298,bh,D_L02_001B12B0,3);
    c1=D_L02_001B1294; text_draw_window_large(box,c1,text,func_001157AC(text));
    if(SEL==0 && !D_001395B8[arena_get_challenge_save_index(0)]) goto counts;
    {
        do {
            text=((char *)GetLocalizedString(0x2f44)); unit=((char *)GetLocalizedString(0x2f5e)); value=moby_compute_scaled_entry_value(SEL);
            if(value<10000) { sprintf(buffer,D_L02_001B1228,text,value,unit); str=buffer; goto draw1; }
            sprintf(buffer,D_L02_001B1328,text,value);
        } while(0);
        str=buffer;
    draw1:
        y2=hud_coord((float)D_L02_001B12BC, D_L02_001B3E04, 0.5f); c2=D_L02_001B12C0; text_draw_medium(D_L02_001B12B8,y2,c2,str,func_001157AC(str));
    }
counts:
    if(D_001395B8[arena_get_challenge_save_index(SEL)]) {
        text=((char *)GetLocalizedString(0x2f3e));
        sprintf(buffer,D_L02_001B1328,text,D_001395B8[arena_get_challenge_save_index(SEL)]); str=buffer;
        y3=(int)((float)D_L02_001B12EC * D_L02_001B3E04 + 0.5f); do { c3=D_L02_001B12F0; } while(0); text_draw_medium(D_L02_001B12E8,y3,c3,str,func_001157AC(str));
    }
    if(SEL!=0) { text=((char *)GetLocalizedString(0x2f40)); h=0.5f; y4=hud_coord((float)D_L02_001B12CC, D_L02_001B3E04, h); c4=D_L02_001B12D0; text_draw_small(D_L02_001B12C8,y4,c4,text,func_001157AC(text)); }
    for(i=SEL+1;i<14;i++) {
        if(!D_001395B8[arena_get_challenge_save_index(D_L02_001B1190[i][2])]) continue;
        if(i>=12 && !flag_is_byte_set()) continue;
        if(i==7 && !((MenuRecord *)(D_L02_00264A70 + g_item_slot_to_record[0x1e] * 0xe0))->enabled) continue;
        if(i==8 && !((MenuRecord *)(D_L02_00264A70 + g_item_slot_to_record[0x2a] * 0xe0))->enabled) continue;
        text=((char *)GetLocalizedString(0x2f41)); h=0.5f; y5=scaled_coord(D_L02_001B12DC, D_L02_001B3E04, h, 1); c5=D_L02_001B12E0; text_draw_small(D_L02_001B12D8,y5,c5,text,func_001157AC(text)); break;
    }
    half=0.5f;
    text=((char *)GetLocalizedString(0x2f3f)); y6=hud_coord((float)D_L02_001B12FC, D_L02_001B3E04, half); c6=D_L02_001B1300; text_draw_small(D_L02_001B12F8,y6,c6,text,func_001157AC(text));
    text=((char *)GetLocalizedString(0x2f42)); y7=hud_coord((float)D_L02_001B131C, D_L02_001B3E04, half); c7=D_L02_001B1320; text_draw_small(D_L02_001B1318,y7,c7,text,func_001157AC(text));
    text=((char *)GetLocalizedString(0x2f43)); y8=hud_coord((float)D_L02_001B130C, D_L02_001B3E04, half); c8=D_L02_001B1310; text_draw_small(D_L02_001B1308,y8,c8,text,func_001157AC(text));
}
