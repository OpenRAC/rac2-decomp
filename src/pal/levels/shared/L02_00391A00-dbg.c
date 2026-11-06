/* func_PAL_L02_00391A00, the PAL copy of func_L00_00385370: the same C, where the timers in fields
   0x1C, 0x84, 0xC and 0x10 take the 50 Hz scale. */
#include "include_asm.h"
#include "common.h"
#define FIELD(type,p,off) (*(type *)((char *)(p)+(off)))
extern float func_002A7878(float,float);
extern int func_00282948(int *);
extern void func_00303210(void *);
extern void func_PAL_00304D90(void *);
extern void func_00303AC8(void *);
extern void func_PAL_00303F38(void *);
extern void func_PAL_00305348(void *);
extern void func_00303070(void *);
extern void func_L00_002E6DB8(void (*)(void *),void *);
extern void func_002A7750(unsigned char *,unsigned char,int);
extern int func_002B3868(unsigned char *);
extern float func_002AA548(float *,float *,float,float,float,float);
typedef struct { float x,y,a,b; float pad[4]; } Spark;
extern Spark D_L00_00232AC0[];
void func_PAL_L02_00391A00(unsigned char *object)
{
    char *work=FIELD(char *,object,0x68);
    int i,ticks;
    switch(object[0x20]) {
    case 0:
        if(FIELD(int,work,0x1C)<=0)FIELD(int,work,0x1C)=20;
        FIELD(int,work,0x1C)=((s32)FIELD(int,work,0x1C)*5+2)/6;
        ticks=FIELD(int,work,0x1C);
        FIELD(int,work,4)=0;
        FIELD(float,work,0x14)=(FIELD(float,work,0x18)+FIELD(float,work,0x18))/(float)ticks;
        FIELD(float,work,0)=FIELD(float,work,0x18)*4/(float)(ticks*ticks);
        func_00303210(object);
        FIELD(int,work,0x8C)=((s32)FIELD(int,work,0x84)*5+2)/6;
        FIELD(float,work,0x30)=1/FIELD(float,work,0x30);
        FIELD(int,work,0x98)=-1;
        if(!FIELD(int,work,0x40)) {
            int alpha=255;
            object[0x30]=alpha;
            for(i=0;i<64;++i) {
                D_L00_00232AC0[i].a=func_002A7878(0.5f,2);
                D_L00_00232AC0[i].b=func_002A7878(0.002f,0.006f);
            }
        }
        func_002A7750(object,1,-1);return;
    case 1:
        if(func_002B3868(object)){FIELD(int,work,8)=0;FIELD(int,work,0x20)=FIELD(int,work,0x1C);}
        if(func_00282948((int *)(work+0x20)))func_002A7750(object,2,-1);
        func_002AA548((float *)(work+4),(float *)(work+8),FIELD(float,work,0x18),FIELD(float,work,0),FIELD(float,work,0),FIELD(float,work,0x14));
        break;
    case 2:
        if(func_002B3868(object)){FIELD(int,work,0x20)=((s32)FIELD(int,work,12)*5+2)/6;FIELD(float,work,4)=FIELD(float,work,0x18);}
        if(func_00282948((int *)(work+0x20)))func_002A7750(object,3,-1);
        break;
    case 3:
        if(func_002B3868(object)){FIELD(int,work,8)=0;FIELD(int,work,0x20)=FIELD(int,work,0x1C);}
        if(func_00282948((int *)(work+0x20)))func_002A7750(object,4,-1);
        func_002AA548((float *)(work+4),(float *)(work+8),0,FIELD(float,work,0),FIELD(float,work,0),FIELD(float,work,0x14));
        break;
    case 4:
        if(func_002B3868(object)){FIELD(int,work,0x20)=((s32)FIELD(int,work,16)*5+2)/6;FIELD(int,work,4)=0;}
        if(func_00282948((int *)(work+0x20)))func_002A7750(object,1,-1);
        break;
    case 5:break;
    default:break;
    }
    if(!FIELD(int,work,0x40))func_PAL_00304D90(object);
    func_00303AC8(object);func_PAL_00303F38(object);func_PAL_00305348(object);
    func_L00_002E6DB8(func_00303070,object);
}
