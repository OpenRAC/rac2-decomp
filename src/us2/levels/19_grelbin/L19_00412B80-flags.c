#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
#define I(p,o) (*(int *)((u8 *)(p)+(o)))
#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define B(p,o) (*((u8 *)(p)+(o)))
#define H(p,o) (*(u16 *)((u8 *)(p)+(o)))
typedef union { int i; float f; } Word;
#define R(p,o) (((Word *)((u8 *)(p)+(o)))->f)
extern int D_001A79F0;
extern u8 D_0019B2E8[], D_00189EA0[];
typedef struct { u8 prefix[0x464]; u8 flags[0]; } FlagTable;
extern FlagTable D_L18_0021E7B0;
typedef struct { u8 prefix[0x30]; float position[4]; u8 middle[0x30]; float rotation[4]; } Transform;
extern Transform *D_L18_001B290C MACRO_ADDR;
extern u8 *D_L18_001B281C;
extern int D_L18_001B9A80 NOT_SDA;
extern int func_002A7750(void *,int,int);
extern int func_L00_00329520(void *,int);
extern void func_0029F338(void *);
extern int func_002B38B8(void *),func_002B3868(void *);
extern void func_002A0430(int);
extern void *func_002A9640(void *,int,int);
extern void func_00282CC0(void *,void *,void *),func_00282CF0(void *,void *,void *);
extern void func_00282F20(void *,void *,float),func_00282D30(void *,void *,float);
extern void func_002ABBB8(void *,void *,void *,float,float,float,float,float,int,int,int,int,int,int,int,int,int,float,float);
extern void func_002B0A68(void *,int,float,float,float,float,void *,int);
extern int func_002E5CF8(int,int,void *);
extern float func_00283180(float),func_002AA150(float,float,float);
extern void func_US2_L18_002D0050(int),func_002AD6F0(void *,void *,void *,void *);

void func_US2_L19_00412B80(u8 *obj)
{
    float oldpos[4] __attribute__((aligned(16)));
    float oldrot[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(obj+0x68);
    float t;
    *(TI128 *)oldpos = *(TI128 *)(obj+0x10);
    *(TI128 *)oldrot = *(TI128 *)(obj+0xF0);
    switch (B(obj,0x20)) {
    case 0:
        if (I(state,0x80)==-1) {
            H(obj,0x34)|=2;
            func_002A7750(obj,4,-1);
            return;
        }
        I(state,0x88)=0;
        I(state,0x5C)|=1;
        *(TI128 *)(state+0x60) = *(TI128 *)(obj+0x10);
        *(TI128 *)(state+0x70) = *(TI128 *)(obj+0xF0);
        if (D_L18_0021E7B0.flags[I(state,0x8C)] ||
            (B(obj,0xB0)!=255 && B(state,0x92) && (D_0019B2E8[B(obj,0xB0)+D_001A79F0*16]&128)) ||
            (I(state,0x98)!=-1 && func_L00_00329520(D_00189EA0,I(state,0x98)))) {
            qcopy_nc(obj+0x10,D_L18_001B290C[I(state,0x80)].position);
            qcopy_nc(obj+0xF0,D_L18_001B290C[I(state,0x80)].rotation);
            H(obj,0x34)|=2;
            if (!B(state,0x91)) { func_0029F338(obj); return; }
            func_002A7750(obj,3,-1);
        } else func_002A7750(obj,1,-1);
        break;
    case 1:
        if (!B(obj,0xBC) && !func_002B38B8(obj) && I(state,0x8C)!=-1 &&
            B(D_L18_001B281C+I(state,0x8C)*256,0x20)!=254 &&
            B(D_L18_001B281C+I(state,0x8C)*256,0x20)!=253 &&
            !(B(obj,0xB0)!=255 && B(state,0x92) && (D_0019B2E8[B(obj,0xB0)+D_001A79F0*16]&128)) &&
            (I(state,0x98)==-1 || !func_L00_00329520(D_00189EA0,I(state,0x98)))) goto effects;
        if (I(state,0x94)!=-1) B(D_L18_001B281C+I(state,0x94)*256,0xBC)=1;
        if (B(state,0x93)) func_002A0430(B(obj,0xB0));
        func_002A7750(obj,2,-1);
    effects:
        if (!B(state,0x91) && func_002A9640(obj,0x40000,0)) {
            if (I(state,0x94)!=-1) B(D_L18_001B281C+I(state,0x94)*256,0xBC)=1;
            func_00282CC0(delta,obj+0xD0,obj+0xE0);
            func_00282F20(delta,delta,1.0f/12.0f);
            func_00282CC0(offset,obj+0x10,obj+0xE0);
            func_002ABBB8(obj,delta,offset,0,0,4,2,9,10,3,16,-1,1,1,-1,0,0x810001,1,15);
            func_002B0A68(obj,31,3,6,3,6,delta,255);
            H(obj,0x34)|=1;
            B(obj,0x31)=0;
            I(obj,0x98)=0;
            if (*(s16 *)(obj+0xAA)==0x10ED) func_002E5CF8(0,0,obj);
            if (B(state,0x93)) func_002A0430(B(obj,0xB0));
            func_002A7750(obj,2,-1);
        }
        B(obj,0xA8)=255;
        break;
    case 2:
        if (func_002B3868(obj) && (*(s16 *)(obj+0xAA)==0xEDB || *(s16 *)(obj+0xAA)==0x1146)) func_002E5CF8(0,0,obj);
        F(state,0x88)+=1.0f/F(state,0x84);
        if (F(state,0x88)>1) F(state,0x88)=1;
        t=1.0f-func_00283180(F(state,0x88)*3.1415927f);
        t*=0.5f;
        func_00282CF0(delta,D_L18_001B290C[I(state,0x80)].position,state+0x60);
        func_00282D30(delta,delta,t);
        func_00282CC0(obj+0x10,state+0x60,delta);
        R(obj,0xF8)=func_002AA150(F(state,0x78),D_L18_001B290C[I(state,0x80)].rotation[2],t);
        R(obj,0xF4)=func_002AA150(F(state,0x74),D_L18_001B290C[I(state,0x80)].rotation[1],t);
        R(obj,0xF0)=func_002AA150(F(state,0x70),D_L18_001B290C[I(state,0x80)].rotation[0],t);
        if (F(state,0x88)>=1) func_002A7750(obj,3,-1);
        break;
    case 3:
        if (I(state,0x94)!=-1 && B(D_L18_001B281C+I(state,0x94)*256,0xBC)) break;
        if (B(state,0x90)) { D_L18_001B9A80=0; func_US2_L18_002D0050(0); }
        H(obj,0x34)|=2;
        break;
    }
    if (B(obj,0x20)<3) {
        func_00282CF0(delta,obj+0x10,oldpos);
        func_002AD6F0(state+0x20,delta,oldrot,obj+0xF0);
    }
}
