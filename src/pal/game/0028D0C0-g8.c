#include "common.h"

/* func_PAL_0028D0C0, the PAL copy of func_0028C6D0: the same C, where the text draws take a scale.
 * The ammo line is drawn at 0.9f and the weapon's name at 0.8f; a name split in two lines is fitted
 * to 80 wide by func_PAL_00280358, line by line, never below 0.8f.
 * One scratch int holds the colour and then the name's length: the reassignment is why cprop leaves
 * retail's copy into the colour register. */
#define F(p,t,o) (*(t *)((char *)(p)+(o)))
extern float IntToFloat(int);
extern int FloatToInt(float);
extern float FastAddRotations(float,float);
extern void menu_show_colored_label_pal(void *,int,float);
extern int hud_is_open_done(void);
extern int hud_screen_position(void *,int *,int *);
extern int sprintf(char *,char *,...);
extern unsigned int FastTweenColor(unsigned int,unsigned int,float);
extern void text_draw_centered_small_scaled(int,int,unsigned int,char *,int,float);
extern float text_calc_fit_scale(char *,int,int,float);
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
/* Draws the round weapon-select menu: the selected weapon's ammo count and its name, fitted to 80 wide (PAL: scaled text). */
int weapon_wheel_draw_pal(char *menu)
{
    float fade_in,fade_out;
    int alpha,x,y,i,selected,split,pos,text_length,text_y;
    unsigned int scratch;
    char buffer[80], *text,*second_line;
    WheelWeaponRecord *record;
    unsigned char *fade=(unsigned char *)menu+0x70;
    fade_in=IntToFloat(fade[0])/IntToFloat(8);
    if(fade_in>1.0f) fade_in=1.0f; else if(fade_in<0.0f) fade_in=0.0f;
    fade_out=IntToFloat(fade[1])/IntToFloat(8);
    if(fade_out>1.0f) fade_out=1.0f; else if(fade_out<0.0f) fade_out=0.0f;
    alpha=FloatToInt(fade_in*128.0f);
    i=0;
    x=F(menu,int,0x50); y=F(menu,int,0x54);
    hud_screen_position(menu,&x,&y);
    for(;i<g_radial_slot_count;i++) {
        FastAddRotations(((float)i*2.0f*3.1415927f)/(float)g_radial_slot_count-3.1415927f,1.5707964f);
        if(F(menu,int,0x74)==i && F(g_radial_menu_pages[g_radial_menu_page_index]+i*28,int,0) && g_resident_data_base) {
            float phase=(float)(i+7);
            if(phase>7.0f) phase-=8.0f;
            menu_show_colored_label_pal(g_resident_data_base+0x376c8,1,phase);
        }
        if(F(g_radial_menu_pages[g_radial_menu_page_index]+i*28,int,0) && g_resident_data_base) {
            char *data=g_resident_data_base+0x38000;
            F(data,int,0x7a8c)=hud_is_open_done()?FloatToInt((float)alpha*0.5f):0;
        }
    }
    selected=F(menu,int,0x74);
    if(selected>=0 && F(g_radial_menu_pages[g_radial_menu_page_index]+selected*28,int,0) && !g_notice_owner) {
        int weapon_id=g_weapon_menu_slots[selected], value;
        float opacity;
        record=&g_weapon_l00_table[g_item_slot_to_record[weapon_id]];
        opacity=fade_in*fade_out;

        if(record->active && record->sellsAmmo) {
            value=g_item_ammo_counts[weapon_id];
            sprintf(buffer,g_str_ammo_format,value,record->ammoCapacity);
            {
                unsigned int ammo_color;
                if (value) ammo_color=FastTweenColor(0x00f0f0f0,0x80f0f0f0,opacity);
                else ammo_color=FastTweenColor(0x004040ff,0x804040ff,opacity);
                text_draw_centered_small_scaled(x+105,y+112,ammo_color,buffer,-1,0.9f);
            }
        }
        scratch=FastTweenColor(0x00f0f0f0,0x80f0f0f0,opacity);
        split=0;
        text=GetLocalizedString(g_weapon_l00_table[g_item_slot_to_record[F(g_radial_menu_pages[g_radial_menu_page_index]+selected*28,int,0x18)]].localizedName);
        if(text && func_001157AC(text)) {
            unsigned int color=scratch;
            scratch=func_001157AC(text);
            text_length=scratch;
            second_line=text;
            for(pos=0;pos<text_length;pos++) {
                second_line++;
                if(*(unsigned char *)second_line=='-') {second_line++;split=pos+2;break;}
            }
            if(!split) {
                second_line=text;
                for(pos=0;pos<text_length;pos++) {
                    second_line++;
                    if(*(unsigned char *)second_line==' ') {second_line++;split=pos+1;break;}
                }
            }
            text_y=y+100;
            if(g_weapon_l00_table[g_item_slot_to_record[g_weapon_menu_slots[selected]]].sellsAmmo) text_y=y+75;
            else { int split_y=y+85; text_y=split ? split_y : text_y; }
            if(split) {
                float min_scale=0.8f;
                float scale=text_calc_fit_scale(text,split,80,min_scale);
                text_draw_centered_small_scaled(x+105,text_y,color,text,split,scale);
                text_y+=16;
                scale=text_calc_fit_scale(second_line,-1,80,min_scale);
                text_draw_centered_small_scaled(x+105,text_y,color,second_line,-1,scale);
            } else text_draw_centered_small_scaled(x+105,text_y,color,text,-1,0.8f);
        }
    }
    return F(menu,int,0x58);
}
