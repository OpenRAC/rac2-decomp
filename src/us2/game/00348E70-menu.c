#include "include_asm.h"
typedef unsigned char u8;
extern float *func_00335E10(void *);
extern void func_0027F110(void);
extern int func_00336A40(void *);
extern void func_US2_003378A0(void *);
extern void func_0027EAE8(int,int,int,int,int,void *);
extern int func_00335E20(u8 *);
extern void func_00335F88(void *,float,float,float,float);
extern void func_00336A38(void *,int);
extern int func_00288FB8(int);
typedef struct {unsigned int first,second;} MenuColors;
/* func_US2_00348E70, the USA v2.00 copy of func_00348138: the same C, where the fields move 0x10 on,
   text id 0x31E4 becomes 0x307A and the call to func_0027F120 at the top is gone. */
void func_US2_00348E70(char *o)
{
    float *pos=func_00335E10(o);
    int i=0;
    MenuColors colors, first, second;
    pos[0]=(*(float **)(o+0x5c))[0];
    for(i=0;i<*(int *)(o+0xc0);i++) {
        int offset=i*20;
        pos[1]=(float)(*(int *)(o+0xb8)+*(int *)(o+0xbc)*i)+(*(float **)(o+0x5c))[1];
        func_00335F88(o,*(float *)(offset+*(unsigned int *)(o+0x68)),0.0f,0.0f,0.0f);
        if(*(int *)(offset+*(unsigned int *)(o+0x68)+4)==0x307a) pos[1]+=3.0f;
        if(*(int *)(o+0xc4)) func_00336A38(o,*(int *)(offset+*(unsigned int *)(o+0x68)+4));
        else func_00336A38(o,func_00288FB8(*(int *)(offset+*(unsigned int *)(o+0x68)+4)));
        { char *entry=o+i*4;
            if(*(int *)(entry+0x6c)) {
                if(*(int *)(o+0xcc)==i) {
                    int x,y;
                    first.second=first.first=(*(unsigned int *)(o+0xac)&0xffffff)|0x20000000;
                    colors=first;
                    x=(int)(pos[0]-(float)(func_00336A40(o)>>1)-2.0f-16.0f);
                    y=(int)(pos[1]+2.0f);
                    func_0027EAE8(x,y,(int)(pos[0]-(float)(func_00336A40(o)>>1)-2.0f-16.0f+8.0f),(int)(pos[1]-2.0f+16.0f),0,&colors);
                }
                if(*(int *)(o+0x60)==i) {
                    *(int *)func_00335E20((u8 *)o)=*(int *)(o+0xac);
                    if(*(int *)(o+0xc8)) {
                        int x,y;
                        second.second=second.first=(*(unsigned int *)(o+0xac)&0xffffff)|0x20000000;
                        colors=second;
                        x=(int)(pos[0]-(float)(func_00336A40(o)>>1)-8.0f);
                        y=(int)(pos[1]-2.0f);
                        func_0027EAE8(x,y,(int)(pos[0]+(float)(func_00336A40(o)>>1)+9.0f),(int)(pos[1]+2.0f+16.0f),0,&colors);
                    }
                } else *(int *)func_00335E20((u8 *)o)=*(int *)(o+0xb0);
            } else *(int *)func_00335E20((u8 *)o)=*(int *)(o+0xb4);
        }
        func_US2_003378A0(o);
    }
    func_0027F110();
}
