#include "include_asm.h"

typedef unsigned char u8;
extern float *func_00335E10(void *);
extern void func_0027F120(void),func_0027F110(void);
extern int func_00336A40(void *);
extern void func_PAL_00338770(void *);
extern void func_0027EAE8(int,int,int,int,int,void *);
extern int func_00335E20(u8 *);
extern void func_00335F88(void *,float,float,float,float);
extern void func_00336A38(void *,int);
extern int func_00288FB8(int);
typedef struct {unsigned int first,second;} MenuColors;

void func_PAL_0034A300(char *o)
{
    float *pos=func_00335E10(o);
    int i=0;
    MenuColors colors, first, second;
    func_0027F120();
    pos[0]=(*(float **)(o+0x5C))[0];
    for(i=0;i<*(int *)(o+0xC0);i++) {
        int offset=i*20;
        pos[1]=(float)(*(int *)(o+0xB8)+*(int *)(o+0xBC)*i)+(*(float **)(o+0x5C))[1];
        func_00335F88(o,*(float *)(offset+*(unsigned int *)(o+0x68)),0.0f,0.0f,0.0f);
        if(*(int *)(offset+*(unsigned int *)(o+0x68)+4)==0x10FC) pos[1]+=3.0f;
        if(*(int *)(o+0xC4)) func_00336A38(o,*(int *)(offset+*(unsigned int *)(o+0x68)+4));
        else func_00336A38(o,func_00288FB8(*(int *)(offset+*(unsigned int *)(o+0x68)+4)));
        { char *entry=o+i*4;
            if(*(int *)(entry+0x6C)) {
                if(*(int *)(o+0xCC)==i) {
                    int x,y;
                    first.second=first.first=(*(unsigned int *)(o+0xAC)&0xffffff)|0x20000000;
                    colors=first;
                    x=(int)(pos[0]-(float)(func_00336A40(o)>>1)-2.0f-16.0f);
                    y=(int)(pos[1]+2.0f);
                    func_0027EAE8(x,y,(int)(pos[0]-(float)(func_00336A40(o)>>1)-2.0f-16.0f+8.0f),(int)(pos[1]-2.0f+16.0f),0,&colors);
                }
                if(*(int *)(o+0x60)==i) {
                    *(int *)func_00335E20((u8 *)o)=*(int *)(o+0xAC);
                    if(*(int *)(o+0xC8)) {
                        int x,y;
                        second.second=second.first=(*(unsigned int *)(o+0xAC)&0xffffff)|0x20000000;
                        colors=second;
                        x=(int)(pos[0]-(float)(func_00336A40(o)>>1)-8.0f);
                        y=(int)(pos[1]-2.0f);
                        func_0027EAE8(x,y,(int)(pos[0]+(float)(func_00336A40(o)>>1)+9.0f),(int)(pos[1]+2.0f+16.0f),0,&colors);
                    }
                } else *(int *)func_00335E20((u8 *)o)=*(int *)(o+0xB0);
            } else *(int *)func_00335E20((u8 *)o)=*(int *)(o+0xB4);
        }
        func_PAL_00338770(o);
    }
    func_0027F110();
}
