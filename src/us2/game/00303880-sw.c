#include "include_asm.h"

#include "common.h"
#define FIELD(type,p,off) (*(type *)((char *)(p)+(off)))
extern void func_00303210(void *);
extern float func_002A7878(float, float);
extern void func_002A7750(unsigned char *, unsigned char, int);
extern int func_002B3868(unsigned char *);
extern int func_00282948(int *);
extern float func_002AA548(float *, float *, float, float, float, float);
extern void func_00303BF8(void *);
extern void func_00303AC8(void *);
extern void func_US2_00303B98(void *);
extern void func_00304128(void *);
extern void func_00303070(void *);
extern void func_0027CE90(void (*)(void *), void *);
extern float D_002222E0[];

void func_US2_00303880(unsigned char *object)
{
    char *work=FIELD(char *,object,0x68);
    int i,ticks;
    switch(object[0x20]) {
    case 0:
        if(FIELD(int,work,0x1C)<=0)FIELD(int,work,0x1C)=20;
        ticks=FIELD(int,work,0x1C);
        FIELD(int,work,4)=0;
        FIELD(float,work,0x14)=(FIELD(float,work,0x18)+FIELD(float,work,0x18))/(float)ticks;
        FIELD(float,work,0)=FIELD(float,work,0x18)*4/(float)(ticks*ticks);
        func_00303210(object);
        FIELD(float,work,0x30)=1/FIELD(float,work,0x30);
        FIELD(int,work,0x8C)=FIELD(int,work,0x84);FIELD(int,work,0x98)=-1;
        if(!FIELD(int,work,0x40)) {
            object[0x30]=255;
            for(i=0;i<64;++i) {
                D_002222E0[i * 8 + 2]=func_002A7878(0.5f,2);
                D_002222E0[i * 8 + 3]=func_002A7878(0.002f,0.006f);
            }
        }
        func_002A7750(object,1,-1);return;
    case 1:
        if(func_002B3868(object)){FIELD(int,work,8)=0;FIELD(int,work,0x20)=FIELD(int,work,0x1C);}
        if(func_00282948((int *)(work+0x20)))func_002A7750(object,2,-1);
        func_002AA548((float *)(work+4),(float *)(work+8),FIELD(float,work,0x18),FIELD(float,work,0),FIELD(float,work,0),FIELD(float,work,0x14));
        break;
    case 2:
        if(func_002B3868(object)){FIELD(int,work,0x20)=FIELD(int,work,12);FIELD(float,work,4)=FIELD(float,work,0x18);}
        if(func_00282948((int *)(work+0x20)))func_002A7750(object,3,-1);
        break;
    case 3:
        if(func_002B3868(object)){FIELD(int,work,8)=0;FIELD(int,work,0x20)=FIELD(int,work,0x1C);}
        if(func_00282948((int *)(work+0x20)))func_002A7750(object,4,-1);
        func_002AA548((float *)(work+4),(float *)(work+8),0,FIELD(float,work,0),FIELD(float,work,0),FIELD(float,work,0x14));
        break;
    case 4:
        if(func_002B3868(object)){FIELD(int,work,4)=0;FIELD(int,work,0x20)=FIELD(int,work,16);}
        if(func_00282948((int *)(work+0x20)))func_002A7750(object,1,-1);
        break;
    case 5:break;
    default:break;
    }
    if(!FIELD(int,work,0x40))func_00303BF8(object);
    func_00303AC8(object);func_US2_00303B98(object);func_00304128(object);
    func_0027CE90(func_00303070,object);
}
