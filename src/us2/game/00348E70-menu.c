#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;
extern float *object_get_first_field(void *);
extern void gfx_enable_screen_flag(void);
extern int hud_draw_widget_text(void *);
extern void text_label_draw_us2(void *);
extern void gfx_draw_screen_rectangle(int,int,int,int,int,void *);
extern int *object_get_fourth_field(u8 *);
extern void object_set_second_float4(void *,float,float,float,float);
extern void hud_set_widget_field_b(void *,int);
extern char *GetLocalizedString(int);
typedef struct {unsigned int first,second;} MenuColors;
/* func_US2_00348E70, the USA v2.00 copy of func_00348138: the same C, where the fields move 0x10 on,
   text id 0x31E4 becomes 0x307A and the call to func_0027F120 at the top is gone. */
/* Draws the option list rows: each label at its row position, with a highlight box around the selected
   row when the highlight flag is set. (USA v2.00) */
void option_list_draw_rows_us2(char *menu)
{
    float *position=object_get_first_field(menu);
    int i=0;
    MenuColors colors, first, second;
    position[0]=(*(float **)(menu+0x5c))[0];
    for(i=0;i<*(int *)(menu+0xc0);i++) {
        int offset=i*20;
        position[1]=(float)(*(int *)(menu+0xb8)+*(int *)(menu+0xbc)*i)+(*(float **)(menu+0x5c))[1];
        object_set_second_float4(menu,*(float *)(offset+*(unsigned int *)(menu+0x68)),0.0f,0.0f,0.0f);
        if(*(int *)(offset+*(unsigned int *)(menu+0x68)+4)==0x307a) position[1]+=3.0f;
        if(*(int *)(menu+0xc4)) hud_set_widget_field_b(menu,*(int *)(offset+*(unsigned int *)(menu+0x68)+4));
        else hud_set_widget_field_b(menu,GetLocalizedString(*(int *)(offset+*(unsigned int *)(menu+0x68)+4)));
        { char *entry=menu+i*4;
            if(*(int *)(entry+0x6c)) {
                if(*(int *)(menu+0xcc)==i) {
                    int x,y;
                    first.second=first.first=(*(unsigned int *)(menu+0xac)&0xffffff)|0x20000000;
                    colors=first;
                    x=(int)(position[0]-(float)(hud_draw_widget_text(menu)>>1)-2.0f-16.0f);
                    y=(int)(position[1]+2.0f);
                    gfx_draw_screen_rectangle(x,y,(int)(position[0]-(float)(hud_draw_widget_text(menu)>>1)-2.0f-16.0f+8.0f),(int)(position[1]-2.0f+16.0f),0,&colors);
                }
                if(*(int *)(menu+0x60)==i) {
                    *(int *)object_get_fourth_field((u8 *)menu)=*(int *)(menu+0xac);
                    if(*(int *)(menu+0xc8)) {
                        int x,y;
                        second.second=second.first=(*(unsigned int *)(menu+0xac)&0xffffff)|0x20000000;
                        colors=second;
                        x=(int)(position[0]-(float)(hud_draw_widget_text(menu)>>1)-8.0f);
                        y=(int)(position[1]-2.0f);
                        gfx_draw_screen_rectangle(x,y,(int)(position[0]+(float)(hud_draw_widget_text(menu)>>1)+9.0f),(int)(position[1]+2.0f+16.0f),0,&colors);
                    }
                } else *(int *)object_get_fourth_field((u8 *)menu)=*(int *)(menu+0xb0);
            } else *(int *)object_get_fourth_field((u8 *)menu)=*(int *)(menu+0xb4);
        }
        text_label_draw_us2(menu);
    }
    gfx_enable_screen_flag();
}
