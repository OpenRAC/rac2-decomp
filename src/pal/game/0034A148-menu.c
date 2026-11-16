#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
extern float *object_get_first_field(void *);
extern void gfx_disable_screen_flag(void),gfx_enable_screen_flag(void);
extern int hud_draw_widget_text(void *);
extern void text_label_draw_pal(void *);
extern void gfx_draw_screen_rectangle(int,int,int,int,int,void *);
extern int *object_get_fourth_field(u8 *);
extern void object_set_second_float4(void *,float,float,float,float);
extern void hud_set_widget_field_b(void *,int);
extern char *GetLocalizedString(int);
typedef struct {unsigned int first,second;} MenuColors;

/* Draws the option list rows with their text, highlight boxes and selection colors. (PAL) */
void option_list_draw_rows_pal(char *menu)
{
    float *pos=object_get_first_field(menu);
    int i=0;
    MenuColors colors, first, second;
    gfx_disable_screen_flag();
    pos[0]=(*(float **)(menu+0x5C))[0];
    for(i=0;i<*(int *)(menu+0xC0);i++) {
        int offset=i*20;
        pos[1]=(float)(*(int *)(menu+0xB8)+*(int *)(menu+0xBC)*i)+(*(float **)(menu+0x5C))[1];
        object_set_second_float4(menu,*(float *)(offset+*(unsigned int *)(menu+0x68)),0.0f,0.0f,0.0f);
        if(*(int *)(offset+*(unsigned int *)(menu+0x68)+4)==0x10FC) pos[1]+=3.0f;
        if(*(int *)(menu+0xC4)) hud_set_widget_field_b(menu,*(int *)(offset+*(unsigned int *)(menu+0x68)+4));
        else hud_set_widget_field_b(menu,GetLocalizedString(*(int *)(offset+*(unsigned int *)(menu+0x68)+4)));
        { char *entry=menu+i*4;
            if(*(int *)(entry+0x6C)) {
                if(*(int *)(menu+0xCC)==i) {
                    int x,y;
                    first.second=first.first=(*(unsigned int *)(menu+0xAC)&0xffffff)|0x20000000;
                    colors=first;
                    x=(int)(pos[0]-(float)(hud_draw_widget_text(menu)>>1)-2.0f-16.0f);
                    y=(int)(pos[1]+2.0f);
                    gfx_draw_screen_rectangle(x,y,(int)(pos[0]-(float)(hud_draw_widget_text(menu)>>1)-2.0f-16.0f+8.0f),(int)(pos[1]-2.0f+16.0f),0,&colors);
                }
                if(*(int *)(menu+0x60)==i) {
                    *(int *)object_get_fourth_field((u8 *)menu)=*(int *)(menu+0xAC);
                    if(*(int *)(menu+0xC8)) {
                        int x,y;
                        second.second=second.first=(*(unsigned int *)(menu+0xAC)&0xffffff)|0x20000000;
                        colors=second;
                        x=(int)(pos[0]-(float)(hud_draw_widget_text(menu)>>1)-8.0f);
                        y=(int)(pos[1]-2.0f);
                        gfx_draw_screen_rectangle(x,y,(int)(pos[0]+(float)(hud_draw_widget_text(menu)>>1)+9.0f),(int)(pos[1]+2.0f+16.0f),0,&colors);
                    }
                } else *(int *)object_get_fourth_field((u8 *)menu)=*(int *)(menu+0xB0);
            } else *(int *)object_get_fourth_field((u8 *)menu)=*(int *)(menu+0xB4);
        }
        text_label_draw_pal(menu);
    }
    gfx_enable_screen_flag();
}
