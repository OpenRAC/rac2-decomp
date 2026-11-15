#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;
extern float *func_00335E10(void *);
extern void func_0027F120(void),func_0027F110(void);
extern int func_00336A40(void *);
extern void func_00336A78(void *);
extern void func_0027EAE8(int,int,int,int,int,void *);
extern int func_00335E20(u8 *);
extern void func_00335F88(void *,float,float,float,float);
extern void func_00336A38(void *,int);
extern int func_00288FB8_2(int);
typedef struct {unsigned int first,second;} MenuColors;
/* Draws the rows of an option list and marks the highlighted row with boxes behind its text. */
void func_00348138(char *menu)
{
    float *pos=GetFirstField(menu);
    int i=0;
    MenuColors colors, first, second;
    DisableScreenFlag();
    pos[0]=(*(float **)(menu+0x4c))[0];
    for(i=0;i<*(int *)(menu+0xb0);i++) {
        int offset=i*20;
        pos[1]=(float)(*(int *)(menu+0xa8)+*(int *)(menu+0xac)*i)+(*(float **)(menu+0x4c))[1];
        SetSecondFloat4(menu,*(float *)(offset+*(unsigned int *)(menu+0x58)),0.0f,0.0f,0.0f);
        if(*(int *)(offset+*(unsigned int *)(menu+0x58)+4)==0x31e4) pos[1]+=3.0f;
        if(*(int *)(menu+0xb4)) SetWidgetField40(menu,*(int *)(offset+*(unsigned int *)(menu+0x58)+4));
        else SetWidgetField40(menu,func_00288FB8_2(*(int *)(offset+*(unsigned int *)(menu+0x58)+4)));
        { char *entry=menu+i*4;
            if(*(int *)(entry+0x5c)) {
                if(*(int *)(menu+0xbc)==i) {
                    int x,y;
                    first.second=first.first=(*(unsigned int *)(menu+0x9c)&0xffffff)|0x20000000;
                    colors=first;
                    x=(int)(pos[0]-(float)(DrawWidgetText(menu)>>1)-2.0f-16.0f);
                    y=(int)(pos[1]+2.0f);
                    DrawScreenRectangle(x,y,(int)(pos[0]-(float)(DrawWidgetText(menu)>>1)-2.0f-16.0f+8.0f),(int)(pos[1]-2.0f+16.0f),0,&colors);
                }
                if(*(int *)(menu+0x50)==i) {
                    *(int *)GetFieldC((u8 *)menu)=*(int *)(menu+0x9c);
                    if(*(int *)(menu+0xb8)) {
                        int x,y;
                        second.second=second.first=(*(unsigned int *)(menu+0x9c)&0xffffff)|0x20000000;
                        colors=second;
                        x=(int)(pos[0]-(float)(DrawWidgetText(menu)>>1)-8.0f);
                        y=(int)(pos[1]-2.0f);
                        DrawScreenRectangle(x,y,(int)(pos[0]+(float)(DrawWidgetText(menu)>>1)+9.0f),(int)(pos[1]+2.0f+16.0f),0,&colors);
                    }
                } else *(int *)GetFieldC((u8 *)menu)=*(int *)(menu+0xa0);
            } else *(int *)GetFieldC((u8 *)menu)=*(int *)(menu+0xa4);
        }
        DrawAlignedTextLabel(menu);
    }
    EnableScreenFlag();
}
