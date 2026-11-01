#include "common.h"
extern char D_00189EA0[];
extern void func_002A7750(char *,int,int);
extern float func_002AA2E8(float *,float,float);
extern int func_00282948(void *);
extern char *D_L02_001FF1C0[];
extern char D_L02_001A8F20[] MACRO_ADDR, D_L02_001BA500[];
extern float func_00282E48(void *, void *);
extern int func_00283CF0(float);
extern float func_00283248(float,float), func_00283C80(float,float);
extern int func_002ACBC8(void *,int);
extern void *func_L02_003CD5B0(int);
extern void func_002AA548(float *,float *,float,float,float,float);
extern void func_002C9828(void *,int,void *,void *,int,float);
extern float func_002A89A8(void *,int,float);
extern int func_002E5CF8(int,int,void *);
extern void func_L02_003CD668(void *,void *);
extern int func_002A8508(int,int);
extern void func_0029F338(char *);
extern void func_L02_00401BF8(char *),func_L02_00401D38(char *,void *);
extern void func_00282CF0(void *,void *,void *);
extern void *func_002A9640(void *,u32,s32);
extern float func_002A96A0(void *,void *);
extern void func_002B0A68(char *,int,void *,u8,float,float,float,float);
extern void func_00282F20(void *,void *,float);
extern void func_0032DA58(void *,void *,void *,float);
void func_L02_00401638(char *e) {
    float old[4] __attribute__((aligned(16))), temp[4] __attribute__((aligned(16)));
    char *s = *(char **)(e+0x68), *p;
    float x,y,z,t;
    void *obj;
    if ((unsigned)(*(u8 *)(e+0x20)-2)<3) qcopy(&old,e+0x10);
    switch (*(u8 *)(e+0x20)) {
    case 0: {
        float inv;
        if (!*(s16 *)(s+0x24)) { *(s16 *)(s+0x24)=40; *(float *)(s+0x20)=40.0f; }
        func_002A7750(e,1,-1);
        *(int *)(s+0x16c)=-1;
        p=D_L02_001FF1C0[*(int *)(s+0x100)];
        *(char **)(s+0x164)=p;
        inv=func_00282E48(p+0x10,p+0x20);
        inv=1.0f/inv;
        *(float *)(s+0x15c)=inv*0.5f;
        *(float *)(s+0x154)=inv*0.0013888889f;
        *(float *)(s+0x158)=inv*0.0027777778f;
        *(float *)(s+0x160)=inv;
        *(int *)(s+0x150)=0;
        qcopy(s+0x120,*(char **)(s+0x164)+0x10);
        *(int *)(e+0x98)=0;
        *(u16 *)(e+0x34)=(*(u16 *)(e+0x34)|0x41)&0xefff;
        break; }
    case 1:
        if (func_002ACBC8(D_00189EA0,*(int *)(s+0x104))) {
            if (!func_L02_003CD5B0(*(int *)(s+0x110))) {func_0029F338(e);return;}
            func_002AA548((float *)(s+0x14c),(float *)(s+0x150),(float)**(int **)(s+0x164)-1.0f,*(float *)(s+0x15c),*(float *)(s+0x158),*(float *)(s+0x15c));
            *(int *)(s+0x14c)=0; func_002A7750(e,2,-1);
            *(u16 *)(e+0x34)=(*(u16 *)(e+0x34)&0xffbe)|0x1000;
            *(int *)(e+0x98)=*(int *)(*(char **)(e+0x24)+0x10);
        }
        break;
    case 2:
        x=*(float *)(s+0x150)*60.0f;
        x+=*(float *)(s+0x14c);
        { float limit=(float)(**(int **)(s+0x164)-2); if(limit<x)x=limit; }
        y=x+1.0f;
        {
            int highIndex=func_00283CF0(y);
            int lowIndex=func_00283CF0(x);
            char *path=*(char **)(s+0x164);
            char *lo=path+lowIndex*16;
            path+=highIndex*16;
            z=*(float *)(path+0x10)-*(float *)(lo+0x10);
        }
        {
            int highIndex=func_00283CF0(y);
            int lowIndex=func_00283CF0(x);
            char *path=*(char **)(s+0x164);
            char *lo=path+lowIndex*16;
            path+=highIndex*16;
            t=*(float *)(path+0x14);
            t=func_00283248(z,t-*(float *)(lo+0x14));
        }
        t=1.0f-func_00283C80(t,*(float *)(s+0x138)); if(t<0.1f)t=0.1f;
        func_002AA548((float *)(s+0x14c),(float *)(s+0x150),(float)**(int **)(s+0x164)-1.0f,*(float *)(s+0x154),*(float *)(s+0x158),t**(float *)(s+0x15c));
        func_002C9828(*(void **)(s+0x164),0,s+0x120,s+0x130,0,*(float *)(s+0x14c));
        if(*(float *)(s+0x14c)>=(float)**(int **)(s+0x164)-1.0f)func_002A7750(e,3,-1);
        break;
    case 3:
        if(*(int *)(s+0x110)!=-1 && func_00282948(s+0x168)) {
            obj=func_L02_003CD5B0(*(int *)(s+0x110));
            if(obj){ qcopy(&temp,e+0x10); temp[2]=func_002A89A8(&temp,0,0.5f);func_002E5CF8(0,0,e);func_L02_003CD668(obj,&temp);*(int *)(s+0x168)=120; }
            else if(!func_002A8508(*(int *)(s+0x110),-1))func_002A7750(e,4,-1);
        }
        break;
    case 4:
        func_002AA2E8((float *)(s+0x11c),0.16666667f,0.0013888889f);
        *(float *)(s+0x128)+=*(float *)(s+0x11c);
        if(!*(u8 *)(e+0x31)){func_0029F338(e);return;}
    }
    *(float *)(e+0x2c)=*(float *)(*(char **)(e+0x24)+0x24)*1.5f;
    if(*(u8 *)(e+0x31)||*(u8 *)(e+0x20)==2||*(u8 *)(e+0x20)==4)func_L02_00401BF8(e);
    if(*(u8 *)(e+0x31)) {
        if(*(u8 *)(e+0x20)<2)return;
        if(*(u8 *)(e+0x20)<5){func_00282CF0(&temp,e+0x10,&old);func_L02_00401D38(e,&temp);}
    }
    if(*(u8 *)(e+0x20)>=2){
        void *hit=func_002A9640(e,0x10000,0); x=func_002A96A0(e,hit);
        func_002AA2E8((float *)(s+0x20),0.0f,x); *(u8 *)(e+0xa8)=255;
        if(*(float *)(s+0x20)==0.0f){func_002E5CF8(2,0,e);func_002B0A68(e,0x7f7,D_L02_001A8F20,255,5.0f,10.0f,5.0f,10.0f);func_00282CF0(&temp,D_L02_001BA500,e+0x10);func_00282F20(&temp,&temp,1.0f);func_0032DA58(e,e+0x10,&temp,0.0f);func_0029F338(e);}
    }
}


