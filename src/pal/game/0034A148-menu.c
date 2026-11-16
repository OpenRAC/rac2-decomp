#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
extern float *object_get_first_field(void *);
extern void gfx_disable_screen_flag(void),gfx_enable_screen_flag(void);
extern int hud_draw_widget_text(void *);
extern void func_PAL_00338770(void *);
extern void gfx_draw_screen_rectangle(int,int,int,int,int,void *);
extern int *object_get_fourth_field(u8 *);
extern void object_set_second_float4(void *,float,float,float,float);
extern void hud_set_widget_field_b(void *,int);
extern char *GetLocalizedString(int);
typedef struct {unsigned int first,second;} MenuColors;

void option_list_draw_rows_pal(char *o)
{
    float *pos=object_get_first_field(o);
    int i=0;
    MenuColors colors, first, second;
    gfx_disable_screen_flag();
    pos[0]=(*(float **)(o+0x5C))[0];
    for(i=0;i<*(int *)(o+0xC0);i++) {
        int offset=i*20;
        pos[1]=(float)(*(int *)(o+0xB8)+*(int *)(o+0xBC)*i)+(*(float **)(o+0x5C))[1];
        object_set_second_float4(o,*(float *)(offset+*(unsigned int *)(o+0x68)),0.0f,0.0f,0.0f);
        if(*(int *)(offset+*(unsigned int *)(o+0x68)+4)==0x10FC) pos[1]+=3.0f;
        if(*(int *)(o+0xC4)) hud_set_widget_field_b(o,*(int *)(offset+*(unsigned int *)(o+0x68)+4));
        else hud_set_widget_field_b(o,GetLocalizedString(*(int *)(offset+*(unsigned int *)(o+0x68)+4)));
        { char *entry=o+i*4;
            if(*(int *)(entry+0x6C)) {
                if(*(int *)(o+0xCC)==i) {
                    int x,y;
                    first.second=first.first=(*(unsigned int *)(o+0xAC)&0xffffff)|0x20000000;
                    colors=first;
                    x=(int)(pos[0]-(float)(hud_draw_widget_text(o)>>1)-2.0f-16.0f);
                    y=(int)(pos[1]+2.0f);
                    gfx_draw_screen_rectangle(x,y,(int)(pos[0]-(float)(hud_draw_widget_text(o)>>1)-2.0f-16.0f+8.0f),(int)(pos[1]-2.0f+16.0f),0,&colors);
                }
                if(*(int *)(o+0x60)==i) {
                    *(int *)object_get_fourth_field((u8 *)o)=*(int *)(o+0xAC);
                    if(*(int *)(o+0xC8)) {
                        int x,y;
                        second.second=second.first=(*(unsigned int *)(o+0xAC)&0xffffff)|0x20000000;
                        colors=second;
                        x=(int)(pos[0]-(float)(hud_draw_widget_text(o)>>1)-8.0f);
                        y=(int)(pos[1]-2.0f);
                        gfx_draw_screen_rectangle(x,y,(int)(pos[0]+(float)(hud_draw_widget_text(o)>>1)+9.0f),(int)(pos[1]+2.0f+16.0f),0,&colors);
                    }
                } else *(int *)object_get_fourth_field((u8 *)o)=*(int *)(o+0xB0);
            } else *(int *)object_get_fourth_field((u8 *)o)=*(int *)(o+0xB4);
        }
        func_PAL_00338770(o);
    }
    gfx_enable_screen_flag();
}
