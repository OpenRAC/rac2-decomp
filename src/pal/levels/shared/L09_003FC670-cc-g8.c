/* func_PAL_L09_003FC670, the PAL copy of func_L09_003F7CE0: the same C, where rename func_L02_0032B468 becomes func_PAL_L02_0032D5F8; rename func_002B3380 becomes func_PAL_002B3F18; rename func_L09_003F7518 becomes func_PAL_L09_003FBDF0. */
#include "common.h"
typedef struct { float data[12]; } InitBlock;
extern u8 D_L09_001A8F20[] MACRO_ADDR;
extern void *D_L09_001FE6C0[];
extern u8 D_L09_001B10D0[] SDATA(D_L09_001B10D0);
extern float D_L09_001B0F08 __attribute__((sda));
extern float D_L09_001B0F0C __attribute__((sda)),D_L09_001B0F10 __attribute__((sda)),D_L09_001B0F1C __attribute__((sda)),D_L09_001B0F20 __attribute__((sda)),D_L09_001B0F24 __attribute__((sda)),D_L09_001B0F30 __attribute__((sda));
extern int func_00283CF0(float),func_001163B0(void),func_002A7820(int,int);
extern u8 *func_0029EFD0(int),*func_PAL_L02_0032D5F8(void *,int,void *,void *,int,int,void *,void *,void *,float);
extern void func_002B60B0(u8 *,float,float,float,float);
extern float func_L01_003377C8(void *);
extern int func_PAL_002B3F18(void *,void *,void *),func_L09_003F7C50(void *,int,int);
extern void func_0029FCC0(void *,int,void *),func_0029FC20(void *,int,void *),func_00283678(void *,void *),func_002A0F48(void *),func_002AB028(void *),func_002A10E8(void *);
extern void func_00282CF0(void *,void *,void *),func_L09_003F73E8(void *),func_002A7750(void *,int,int),func_PAL_L09_003FBDF0(void *,int,int,int);
extern float func_002A89A8(void *,int,float);
void func_PAL_L09_003FC670(u8 *o) {
    u8 *d=*(u8 **)(o+0x68), *p,*pd; float transform[16]; float pos[4]; int i,j; u8 *parameters; u8 stage; float acceleration; int animation=9; float slow=0.006f;
    *(float *)(o+0x2C)*=D_L09_001B0F08;
    d[0x60]=14;
    *(int *)(d+0x98)=animation;
    d[0x61]=18;
    d[0x62]=17;
    d[0x66]=20;
    d[0x67]=255;
    *(float *)(d+0x6C)=0.44000003f;
    *(float *)(d+0x70)=0.14000002f;
    *(float *)(d+0x74)=slow;
    *(float *)(d+0x78)=0.012f;
    *(float *)(d+0x7C)=slow;
    *(float *)(d+0x8C)=0.4f;
    d[0xBC]=5;
    d[0xBD]=animation;
    stage=4;
    d[0xBF]=7;
    d[0xC2]=10;
    d[0xC3]=17;
    *(float *)(d+0x90)=*(float *)(d+0x310);
    *(float *)(d+0xF8)=0.45f;
    *(u8 **)(d+0x2F8)=0;
    *(u8 **)(d+0x2F0)=0;
    *(u8 **)(d+0x2F4)=0;
    *(float *)(d+0x80)=0.7f;
    *(float *)(d+0x84)=0.7f;
    d[0xBE]=stage;
    d[0x28]=3;
    *(float *)(d+0x30)=1.7f;
    d[0x2F]=8;
    d[0x2A]=2;
    d[0x4D]=0;
    d[0x2E]=1;
    d[0x48]=func_00283CF0(25.0f);d[0x4A]=func_00283CF0(16.0f);
    { float first,second,third,fourth;
    acceleration=D_L09_001B0F24*0.00040000002f;
    d[0x1E8]=12;d[0x1E9]=11;
    first=D_L09_001B0F0C*0.00040000002f;second=D_L09_001B0F10*0.020000001f;third=D_L09_001B0F1C*6.981318e-06f;
    fourth=D_L09_001B0F20*0.0003490659f;
    *(float *)(d+0x100)=0.7f;*(float *)(d+0x104)=0.5f;*(float *)(d+0x108)=0.5f;*(float *)(d+0x10C)=1.0f;
    *(float *)(d+0x110)=0.7853982448577881f;*(float *)(d+0x130)=0.349065899848938f;
    *(float *)(d+0x12C)=acceleration;
    func_002B60B0(o,first,second,third,fourth); }
    *(int *)(d+0x138)|=0x80;*(int *)(d+0x1DC)=0;*(float *)(d+0x1D4)=3.0f;
    *(u16 *)(d+0x1E4)=0;*(u16 *)(d+0x1E2)=0;*(int *)(d+0x1D0)=0;
    if(*(int *)(d+0x2BC)!=-1)func_L01_003377C8(D_L09_001FE6C0[*(int *)(d+0x2BC)]);
    if(*(int *)(d+0x2B4)!=-1)func_L01_003377C8(D_L09_001FE6C0[*(int *)(d+0x2B4)]);
    if(*(int *)(d+0x2B8)!=-1)func_L01_003377C8(D_L09_001FE6C0[*(int *)(d+0x2B8)]);
    p=func_0029EFD0(0xD0E);
    if(p) {
        *(u8 **)(d+0x2F8)=p;*(u16 *)(p+0x32)=*(u16 *)(o+0x32);p[0x30]=o[0x30];
        *(u64 *)(p+0x38)=*(u64 *)(o+0x38);*(int *)(p+0x78)=*(int *)(o+0x78);p[0x31]=1;
        *(float *)(p+0x2C)*=D_L09_001B0F08;
        func_0029FCC0(o,0,p+0x10);qcopy(p+0xF0,o+0xF0);
        pd=*(u8 **)(p+0x68);*(InitBlock *)(pd+0x20)=*(InitBlock *)(d+0x20);
        *(float *)(pd+0x20)=*(float *)(d+0x20);*(u16 *)(pd+0x24)=*(u16 *)(d+0x24);pd[0x28]=d[0x28];
        pd[0x2F]=stage;*(float *)(pd+0x30)=0.7f;pd[0x2A]=2;pd[0x4D]=1;pd[0x4A]=3;pd[0x2E]=1;*(u8 **)(pd+0x70)=o;
        func_0029FC20(o,0,transform);func_00283678(p+0xC0,transform);
        func_002A0F48(p);func_002AB028(p+0xC0);func_002A10E8(p);
        for(i=0;i<2;i++) {
            u8 *child;
            func_0029FCC0(*(u8 **)(d+0x2F8),i,pos);func_00282CF0(pos,pos,*(u8 **)(d+0x2F8)+0x10);
            child=func_PAL_L02_0032D5F8(*(u8 **)(d+0x2F8),0xD66,pos,D_L09_001A8F20,0,0,D_L09_001A8F20,D_L09_001A8F20,D_L09_001A8F20,0);
            if(child && *(s16 *)(child+0xAA)==0xD66 && child[0x20]!=254 && child[0x20]!=253) {
                *(u16 *)(child+0x32)=*(u16 *)(o+0x32);*(u8 **)(d+0x2F0+i*4)=child;*(u16 *)(child+0x34)|=2;
            }
        }
        parameters=pd+0x50;
        for(j=0;j<10;j++)parameters[j]=D_L09_001B10D0[j];
        switch(func_001163B0()%3) {
        case 0:parameters[4]=func_00283CF0((2.0f/ *(s16 *)(d+0x24))*255.0f);parameters[8]=func_00283CF0((1.0f/ *(s16 *)(d+0x24))*255.0f);break;
        case 1:parameters[5]=func_00283CF0((2.0f/ *(s16 *)(d+0x24))*255.0f);parameters[9]=func_00283CF0((1.0f/ *(s16 *)(d+0x24))*255.0f);break;
        case 2:parameters[7]=func_00283CF0((2.0f/ *(s16 *)(d+0x24))*255.0f);break;
        }
        func_PAL_002B3F18(*(u8 **)(d+0x2F8),pd+0x50,pd+0x20);{ u8 *partner=*(u8 **)(d+0x2F8);*(u16 *)(partner+0x7C)&=0xFCFF; }
    }
    if(d[0x302]&1) {
        d[0x302]=(d[0x302]|1)&0xFD;
        if(d[0x31F]) {
            u8 *partner; u8 **slots; int k;
            o[0x31]=0;*(int *)(o+0x98)=0;*(u16 *)(o+0x34)=(*(u16 *)(o+0x34)|1)&0xEFFF;
            partner=*(u8 **)(d+0x2F8);
            if(partner && *(s16 *)(partner+0xAA)==0xD0E && partner[0x20]!=254 && partner[0x20]!=253) {
                *(u16 *)(partner+0x34)|=1;(*(u8 **)(d+0x2F8))[0x31]=0;*(int *)(*(u8 **)(d+0x2F8)+0x98)=0;*(u16 *)(*(u8 **)(d+0x2F8)+0x34)&=0xEFFF;
            }
            slots=(u8 **)(d+0x2F0);
            for(k=0;k<2;k++) {
                u8 *child=slots[k];
                if(child && *(s16 *)(child+0xAA)==0xD66 && child[0x20]!=254 && child[0x20]!=253) {
                    *(u16 *)(child+0x34)|=1;slots[k][0x31]=0;
                }
            }
            d[0x31C]=0;d[0x31D]=1;*(u16 *)(o+0x34)|=2;
        }
    }
    if(*(float *)(d+0x4BC)<10.0f)*(float *)(d+0x4BC)=D_L09_001B0F30;
    func_L09_003F7C50(o,*(int *)(d+0x2B4),-1);func_L09_003F73E8(o);**(int **)(d+0x304)=0;
    if(*(int *)(d+0x2B0)!=-1) {
        *(int *)(d+0x2DC)=*(int *)(d+0x2B0);*(int *)(d+0x138)|=4;func_002A7750(o,1,1);
        if(func_002A89A8(o+0x10,0,0.5f)<*(float *)(o+0x18)-*(float *)(d+0x10C)-0.1f)
            func_PAL_L09_003FBDF0(o,2,0,func_002A7820(5,10));
        else
            func_PAL_L09_003FBDF0(o,13,0,func_002A7820(10,20));
        *(int *)(d+0x2D8)=*(int *)(d+0x2D0);
    } else {
        int state;func_002A7750(o,5,1);state=func_001163B0()&1;
        func_PAL_L09_003FBDF0(o,state,0,func_002A7820(10,20));
        *(int *)(d+0x2D8)=*(int *)(d+0x2D0);
    }
}
