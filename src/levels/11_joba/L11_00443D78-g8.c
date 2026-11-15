#include "names.h"
/* Draws the menu panel: header box, value line, count line and labels. */
#include "common.h"
extern void joba_menu_draw_help_prompts(void *,int);
extern int arena_get_challenge_title_text_id(int), arena_get_challenge_flag_index(int), func_L11_00442958(int), flag_is_byte_set(void);
extern int GetLocalizedString(int);
extern int func_001157AC(char *);
extern int sprintf(char *,char *,...);
extern void text_draw_medium(int,int,u64,char *,int), text_draw_small(int,int,u64,char *,int);
extern void FontSetWindow(void *,int,int,int,int,int,int,int,int),text_draw_window_large(void *,u64,char *,int);
extern int D_L11_001B1650 __attribute__((sda));
extern int D_L11_001B1654 __attribute__((sda));
extern int D_L11_001B1658 __attribute__((sda));
extern int D_L11_001B165C __attribute__((sda));
extern int D_L11_001B1660 __attribute__((sda));
extern int D_L11_001B1664;
extern int D_L11_001B1668;
extern int D_L11_001B166C;
extern int D_L11_001B1670 __attribute__((sda));
extern int D_L11_001B1674 __attribute__((sda));
extern int D_L11_001B1678 __attribute__((sda));
extern int D_L11_001B167C __attribute__((sda));
extern int D_L11_001B1680 __attribute__((sda));
extern int D_L11_001B1684 __attribute__((sda));
extern int D_L11_001B1688 __attribute__((sda));
extern int D_L11_001B168C __attribute__((sda));
extern int D_L11_001B1690 __attribute__((sda));
extern int D_L11_001B1694 __attribute__((sda));
extern int D_L11_001B1698 __attribute__((sda));
extern int D_L11_001B169C __attribute__((sda));
extern int D_L11_001B16A0 __attribute__((sda));
extern int D_L11_001B16A4 __attribute__((sda));
extern int D_L11_001B16A8 __attribute__((sda));
extern int D_L11_001B16AC __attribute__((sda));
extern int D_L11_001B16B0 __attribute__((sda));
extern int D_L11_001B16B4 __attribute__((sda));
extern int D_L11_001B16B8 __attribute__((sda));
extern int D_L11_001B16BC __attribute__((sda));
extern int D_L11_001B16C0 __attribute__((sda));
extern int D_L11_001B16C4 __attribute__((sda));
extern int D_L11_001B16C8 __attribute__((sda));
extern int D_L11_001B16CC __attribute__((sda));
extern int D_L11_001B16D0 __attribute__((sda));
extern int D_L11_001B16D4 __attribute__((sda));
extern int D_L11_001B16D8 __attribute__((sda));
extern int D_L11_001B16DC __attribute__((sda));
extern int D_L11_001B16E0 __attribute__((sda));

extern float D_L11_001B3E04;
extern char D_L11_001B15A0[],D_L11_001B16E8[];
extern unsigned char g_item_slot_to_record[],D_001395B8[];
typedef struct { unsigned char pad[4]; unsigned char enabled; unsigned char rest[0xdb]; } MenuRecord;
extern unsigned char D_L11_00279BA0[];
extern int *g_arena_challenge_table[] SDATA(D_L11_001B14F8);
#define TABLE D_L11_001B14F8
#define SEL (*(short *)(state+0x1e8))
extern int D_L11_001B3E00;
static __inline__ int hud_coord(float value, float scale, float half)
{
    int mode = D_L11_001B3E00;
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
    unsigned char *state; char *text,*label,*unit,*lineText,*labelText,*nextHintText,*t3,*t4,*t5; int i,value,valueY,countY,prevHintY,nextHintY,hintY1,hintY2,hintY3,one,bx,by,bh; u64 headerColor,valueColor,countColor,prevHintColor,nextHintColor,hintColor1,hintColor2,hintColor3; float half;
    one=1;
    joba_menu_draw_help_prompts(moby,1);
    state=*(unsigned char **)(moby+0x68);
    text=((char *)GetLocalizedString(arena_get_challenge_title_text_id(SEL)));
    bx=hud_coord((float)D_L11_001B1660, D_L11_001B3E04, 0.5f);
    by=hud_coord((float)D_L11_001B1664, D_L11_001B3E04, 0.5f);
    bh=hud_coord((float)D_L11_001B1658, D_L11_001B3E04, 0.5f);
    FontSetWindow(box,bx,by,D_L11_001B1668,D_L11_001B166C,D_L11_001B1654,bh,D_L11_001B1670,3);
    headerColor=D_L11_001B1650; text_draw_window_large(box,headerColor,text,func_001157AC(text));
    if(SEL==0 && !D_001395B8[arena_get_challenge_flag_index(0)]) goto counts;
    if(SEL==one && !D_001395B8[arena_get_challenge_flag_index(one)]) goto counts;
    {
        do {
            text=((char *)GetLocalizedString(0x2f44)); unit=((char *)GetLocalizedString(0x2f5e)); value=func_L11_00442958(SEL);
            if(value<10000) { sprintf(buffer,D_L11_001B15A0,text,value,unit); lineText=buffer; goto draw1; }
            sprintf(buffer,D_L11_001B16E8,text,value);
        } while(0);
        lineText=buffer;
    draw1:
        valueY=hud_coord((float)D_L11_001B167C, D_L11_001B3E04, 0.5f); valueColor=D_L11_001B1680; text_draw_medium(D_L11_001B1678,valueY,valueColor,lineText,func_001157AC(lineText));
    }
counts:
    if(D_001395B8[arena_get_challenge_flag_index(SEL)]) {
        labelText=((char *)GetLocalizedString(0x2f3e));
        sprintf(buffer,D_L11_001B16E8,labelText,D_001395B8[arena_get_challenge_flag_index(SEL)]); lineText=buffer;
        countY=(int)((float)D_L11_001B16AC * D_L11_001B3E04 + 0.5f); do { countColor=D_L11_001B16B0; } while(0); text_draw_medium(D_L11_001B16A8,countY,countColor,lineText,func_001157AC(lineText));
    }
    if(SEL!=0) { labelText=((char *)GetLocalizedString(0x2f40)); prevHintY=hud_coord((float)D_L11_001B168C, D_L11_001B3E04, 0.5f); prevHintColor=D_L11_001B1690; text_draw_small(D_L11_001B1688,prevHintY,prevHintColor,labelText,func_001157AC(labelText)); }
    for(i=SEL+1;i<13;i++) {
        half=0.5f;
        if(!D_001395B8[arena_get_challenge_flag_index(TABLE[i][2])]) continue;
        if(i>=11 && !flag_is_byte_set()) continue;
        if(i==8 && !((MenuRecord *)(D_L11_00279BA0 + g_item_slot_to_record[0x1e] * 0xe0))->enabled) continue;
        nextHintText=((char *)GetLocalizedString(0x2f41)); nextHintY=hud_coord((float)D_L11_001B169C, D_L11_001B3E04, half); nextHintColor=D_L11_001B16A0; text_draw_small(D_L11_001B1698,nextHintY,nextHintColor,nextHintText,func_001157AC(nextHintText)); break;
    }
    half=0.5f;
    text=((char *)GetLocalizedString(0x2f3f)); hintY1=hud_coord((float)D_L11_001B16BC, D_L11_001B3E04, half); hintColor1=D_L11_001B16C0; text_draw_small(D_L11_001B16B8,hintY1,hintColor1,text,func_001157AC(text));
    text=((char *)GetLocalizedString(0x2f42)); hintY2=hud_coord((float)D_L11_001B16DC, D_L11_001B3E04, half); hintColor2=D_L11_001B16E0; text_draw_small(D_L11_001B16D8,hintY2,hintColor2,text,func_001157AC(text));
    text=((char *)GetLocalizedString(0x2f43)); hintY3=hud_coord((float)D_L11_001B16CC, D_L11_001B3E04, half); hintColor3=D_L11_001B16D0; text_draw_small(D_L11_001B16C8,hintY3,hintColor3,text,func_001157AC(text));
}
