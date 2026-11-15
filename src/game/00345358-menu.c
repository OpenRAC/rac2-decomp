#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;
extern float *object_get_first_field(void *);
extern void gfx_disable_screen_flag(void),gfx_enable_screen_flag(void);
extern int hud_draw_widget_text(void *);
extern void text_label_draw(void *);
extern void gfx_draw_screen_rectangle(int,int,int,int,int,void *);
extern int *object_get_fourth_field(u8 *);
extern void object_set_second_float4(void *,float,float,float,float);
extern void hud_set_widget_field_b(void *,int);
extern char *func_00288FB8_2(int);
typedef struct {unsigned int first,second;} MenuColors;
/* Draws the rows of an option list and marks the highlighted row with boxes behind its text. */
void option_list_draw_rows(char *menu)
{
    float *pos=object_get_first_field(menu);
    int i=0;
    MenuColors colors, first, second;
    gfx_disable_screen_flag();
    pos[0]=(*(float **)(menu+0x4c))[0];
    for(i=0;i<*(int *)(menu+0xb0);i++) {
        int offset=i*20;
        pos[1]=(float)(*(int *)(menu+0xa8)+*(int *)(menu+0xac)*i)+(*(float **)(menu+0x4c))[1];
        object_set_second_float4(menu,*(float *)(offset+*(unsigned int *)(menu+0x58)),0.0f,0.0f,0.0f);
        if(*(int *)(offset+*(unsigned int *)(menu+0x58)+4)==0x31e4) pos[1]+=3.0f;
        if(*(int *)(menu+0xb4)) hud_set_widget_field_b(menu,*(int *)(offset+*(unsigned int *)(menu+0x58)+4));
        else hud_set_widget_field_b(menu,func_00288FB8_2(*(int *)(offset+*(unsigned int *)(menu+0x58)+4)));
        { char *entry=menu+i*4;
            if(*(int *)(entry+0x5c)) {
                if(*(int *)(menu+0xbc)==i) {
                    int x,y;
                    first.second=first.first=(*(unsigned int *)(menu+0x9c)&0xffffff)|0x20000000;
                    colors=first;
                    x=(int)(pos[0]-(float)(hud_draw_widget_text(menu)>>1)-2.0f-16.0f);
                    y=(int)(pos[1]+2.0f);
                    gfx_draw_screen_rectangle(x,y,(int)(pos[0]-(float)(hud_draw_widget_text(menu)>>1)-2.0f-16.0f+8.0f),(int)(pos[1]-2.0f+16.0f),0,&colors);
                }
                if(*(int *)(menu+0x50)==i) {
                    *(int *)object_get_fourth_field((u8 *)menu)=*(int *)(menu+0x9c);
                    if(*(int *)(menu+0xb8)) {
                        int x,y;
                        second.second=second.first=(*(unsigned int *)(menu+0x9c)&0xffffff)|0x20000000;
                        colors=second;
                        x=(int)(pos[0]-(float)(hud_draw_widget_text(menu)>>1)-8.0f);
                        y=(int)(pos[1]-2.0f);
                        gfx_draw_screen_rectangle(x,y,(int)(pos[0]+(float)(hud_draw_widget_text(menu)>>1)+9.0f),(int)(pos[1]+2.0f+16.0f),0,&colors);
                    }
                } else *(int *)object_get_fourth_field((u8 *)menu)=*(int *)(menu+0xa0);
            } else *(int *)object_get_fourth_field((u8 *)menu)=*(int *)(menu+0xa4);
        }
        text_label_draw(menu);
    }
    gfx_enable_screen_flag();
}
