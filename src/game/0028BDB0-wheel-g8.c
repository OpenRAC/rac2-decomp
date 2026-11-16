#include "common.h"

/* Weapon wheel. One scratch int holds the colour and then the name's length: the reassignment is why cprop leaves retail's copy into the colour register. */
#define F(p,t,o) (*(t *)((char *)(p)+(o)))
extern float IntToFloat(int);
extern int FloatToInt(float);
extern float FastAddRotations(float,float);
extern void menu_show_colored_label(void *,int,float);
extern int hud_is_open_done(void);
extern int hud_screen_position(void *,int *,int *);
extern int sprintf(char *,char *,...);
extern unsigned int FastTweenColor(unsigned int,unsigned int,float);
extern int text_draw_centered_small(int,int,unsigned int,char *,int);
extern char *GetLocalizedString(int);
extern unsigned int func_001157AC(const char *);
extern int g_radial_slot_count;
extern char **g_radial_menu_pages;
extern int g_radial_menu_page_index __attribute__((sda));
extern int g_notice_owner __attribute__((sda));
extern char *g_resident_data_base __attribute__((sda));
extern unsigned char g_item_slot_to_record[];
extern int g_weapon_menu_slots[] MACRO_ADDR;
extern int g_item_ammo_counts[];
typedef struct { int active; char reserved04[0x44]; short localizedName; char reserved4A[0x3E]; unsigned short sellsAmmo; char reserved8A[4]; unsigned short ammoCapacity; char reserved90[0x50]; } WheelWeaponRecord;
extern WheelWeaponRecord g_weapon_l00_table[];
extern char g_str_ammo_format[];
/* Draws the weapon wheel: highlights the selected slot and prints its ammo count and name. */
int weapon_wheel_draw(char *menu)
{
    float menu_fade,selection_fade;
    int alpha,x,y,i,selected,split,j,len,text_y;
    unsigned int scratch;
    char buffer[80], *text,*tail;
    WheelWeaponRecord *record;
    unsigned char *fade=(unsigned char *)menu+0x70;
    menu_fade=IntToFloat(fade[0])/IntToFloat(8);
    if(menu_fade>1.0f) menu_fade=1.0f; else if(menu_fade<0.0f) menu_fade=0.0f;
    selection_fade=IntToFloat(fade[1])/IntToFloat(8);
    if(selection_fade>1.0f) selection_fade=1.0f; else if(selection_fade<0.0f) selection_fade=0.0f;
    alpha=FloatToInt(menu_fade*128.0f);
    i=0;
    x=F(menu,int,0x50); y=F(menu,int,0x54);
    hud_screen_position(menu,&x,&y);
    for(;i<g_radial_slot_count;i++) {
        FastAddRotations(((float)i*2.0f*3.1415927f)/(float)g_radial_slot_count-3.1415927f,1.5707964f);
        if(F(menu,int,0x74)==i && F(g_radial_menu_pages[g_radial_menu_page_index]+i*28,int,0) && g_resident_data_base) {
            float f=(float)(i+7);
            if(f>7.0f) f-=8.0f;
            menu_show_colored_label(g_resident_data_base+0x376c8,1,f);
        }
        if(F(g_radial_menu_pages[g_radial_menu_page_index]+i*28,int,0) && g_resident_data_base) {
            char *p=g_resident_data_base+0x38000;
            F(p,int,0x7354)=hud_is_open_done()?FloatToInt((float)alpha*0.5f):0;
        }
    }
    selected=F(menu,int,0x74);
    if(selected>=0 && F(g_radial_menu_pages[g_radial_menu_page_index]+selected*28,int,0) && !g_notice_owner) {
        int n=g_weapon_menu_slots[selected], value;
        float opacity;
        record=&g_weapon_l00_table[g_item_slot_to_record[n]];
        opacity=menu_fade*selection_fade;

        if(record->active && record->sellsAmmo) {
            value=g_item_ammo_counts[n];
            sprintf(buffer,g_str_ammo_format,value,record->ammoCapacity);
            {
                unsigned int c;
                if (value) c=FastTweenColor(0x00f0f0f0,0x80f0f0f0,opacity);
                else c=FastTweenColor(0x004040ff,0x804040ff,opacity);
                text_draw_centered_small(x+105,y+112,c,buffer,-1);
            }
        }
        scratch=FastTweenColor(0x00f0f0f0,0x80f0f0f0,opacity);
        split=0;
        text=GetLocalizedString(g_weapon_l00_table[g_item_slot_to_record[F(g_radial_menu_pages[g_radial_menu_page_index]+selected*28,int,0x18)]].localizedName);
        if(text && func_001157AC(text)) {
            unsigned int color=scratch;
            scratch=func_001157AC(text);
            len=scratch;
            tail=text;
            for(j=0;j<len;j++) {
                tail++;
                if(*(unsigned char *)tail=='-') {tail++;split=j+2;break;}
            }
            if(!split) {
                tail=text;
                for(j=0;j<len;j++) {
                    tail++;
                    if(*(unsigned char *)tail==' ') {tail++;split=j+1;break;}
                }
            }
            text_y=y+100;
            if(g_weapon_l00_table[g_item_slot_to_record[g_weapon_menu_slots[selected]]].sellsAmmo) text_y=y+75;
            else { int splitY=y+85; text_y=split ? splitY : text_y; }
            if(split) {
                text_draw_centered_small(x+105,text_y,color,text,split);
                text_draw_centered_small(x+105,text_y+16,color,tail,-1);
            } else text_draw_centered_small(x+105,text_y,color,text,-1);
        }
    }
    return F(menu,int,0x58);
}
