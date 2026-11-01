#include "include_asm.h"

#include "common.h"
#define WORD(p,o) (*(s32 *)((u8 *)(p)+(o)))
#define HALF(p,o) (*(s16 *)((u8 *)(p)+(o)))
#define UHALF(p,o) (*(u16 *)((u8 *)(p)+(o)))
#define FLOAT(p,o) (*(float *)((u8 *)(p)+(o)))
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; struct { float x,y,z,w; } v; } VecE2D8;
extern VecE2D8 D_L03_001B1C30 SDATA(D_L03_001B1C30);
extern float D_L03_001B1C08 __attribute__((sda));
extern u8 D_L03_001B9980[], D_00189EA0[];
typedef struct { u8 pad[0x80]; float x,y; u8 gap[0x222C]; u8 flag; } HeroE2D8;
extern HeroE2D8 D_00189E20;
extern u8 D_L03_001A8F20[] __attribute__((sda));
extern u8 *D_L03_001B2B0C;
extern u8 *D_L03_001FE700[];
extern void func_PAL_L03_00423F28(u8 *);
extern void func_L03_0041EF90(u8 *);
extern void func_L03_0041F178(u8 *);
extern void func_L03_0041F720(u8 *);
extern int func_002ACBC8(void *, int);
extern void func_002E59F8(int);
extern int func_002B1C20(void *,void *);
extern int func_002B3868(void *);
extern int func_002B38B8(void *);
extern void func_L00_003294F0(void *,int);
extern float func_00282C48(float);
extern void func_00283098(void *,void *,void *);
extern void func_002830C0(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void *func_PAL_L00_003FB330(void *,int,int,int,int,int,int,int,float,float,int,int,int,int);
extern void func_PAL_002B15D8(void *,float,float,int,void *,float,float,int);
extern int func_002E5CF8(int,int,void *);
extern void func_PAL_002A7650(void *,int,int);
extern void func_002A7750(void *,int,int);
extern void func_PAL_002A7E68(void *,int,int,int);
extern void func_002AA2E8(void *,float,float);
extern float func_00283B98(float,float);
extern int func_PAL_L01_00323068(void *,void *);
extern void func_L00_002E6CF0(void *,void *);
extern void func_0029FCC0(int,int,void *);
extern int func_00277258(void *,float,int,void *);
extern void func_0029F338(void *);
extern float func_00283248(float,float);
extern float func_00283198(float);
extern int func_PAL_002B5E30(void *,float);
extern int func_002A8C28(void *,void *,int,float,float,float,int,int,int);
extern int func_L02_002EF388(void *,void *,void *,void *,int);

void func_PAL_L03_00423720(u8 *entity) {
    u8 *state = *(u8 **)(entity + 0x68);
    int flags;
    u8 *path;
    VecE2D8 point, delta;
    float angle;
    func_PAL_L03_00423F28(entity);
    switch (entity[0x95]) {
    case 0:
        if (WORD(state,0x294) != -1) {
            if (!func_002ACBC8(D_L03_001B9980,WORD(state,0x294))) {
                if (WORD(state,0x340) != -1) {
                    func_002E59F8(WORD(state,0x340));
                    WORD(state,0x340) = -1;
                }
                entity[0x31] = 0;
                UHALF(entity,0x34) |= 1;
                return;
            }
            entity[0x31] = 1;
            UHALF(entity,0x34) &= 0xFFFE;
        }
        break;
    case 3:
        flags = func_002B1C20(entity,state+0x60);
        if (func_002B3868(entity)) {
            if (WORD(state,0x340) != -1) {
                func_002E59F8(WORD(state,0x340));
                WORD(state,0x340) = -1;
            }
        }
        if ((flags & 1) || func_00282C48(FLOAT(entity,0xF4)) > 0.1f) {
            func_00283098(&point,&D_L03_001B1C30,entity+0xC0);
            func_00282CC0(&point,&point,entity+0x10);
            func_PAL_L00_003FB330(&point,0,25,20,20,20,45,0,0.5f,20.0f,1,0,0,0);
            func_00282CF0(&delta,entity+0x10,D_00189EA0);
            delta.v.z = 0;
            func_00282F20(&delta,&delta,0.120000005f);
            func_PAL_002B15D8(entity,3.0f,6.0f,31,&delta,3.0f,6.0f,255);
            func_002E5CF8(3,0,entity);
            func_PAL_002A7650(entity,0,3);
            func_0029F338(entity);
            return;
        }
        if (flags & 2) {
            if (WORD(state,0x288)) {
                func_002A7750(entity,4,1);
                if (entity[0x43]) func_PAL_002A7E68(entity,0,0,8);
            } else {
                func_002A7750(entity,3,0);
                if (entity[0x43]) func_PAL_002A7E68(entity,0,0,8);
            }
        }
        break;
    }
    switch (entity[0x20]) {
    case 3:
        path = D_L03_001FE700[WORD(state,0x280)];
        if (func_002B3868(entity)) {
            UHALF(state,0x334)=0;
            UHALF(state,0x336)=0;
        } else if (func_002B38B8(entity)) {
            func_L00_003294F0(entity,0);
            FLOAT(state,0x134)=0.004f;
            FLOAT(state,0x130)=0.004f;
            WORD(state,0x138)=0;
        }
        func_002AA2E8(state+0x33C,6.0f,0.060000002f);
        func_L03_0041F178(entity);
        FLOAT(entity,0xF8)=func_00283B98(FLOAT(entity,0xF8),D_L03_001B1C08*0.0003490659f);
        if (func_PAL_L01_00323068(entity,path+(HALF(state,0x32C)*16+16))&0x80)
            HALF(state,0x32C)=(HALF(state,0x32C)+1)%WORD(path,0);
        if (UHALF(entity,0x96)>=6) func_L00_002E6CF0(func_L03_0041F720,entity);
        break;
    case 2:
        if (!WORD(state,0x290)) {
            func_002E5CF8(4,0,entity);
            WORD(state,0x290)=1;
        }
        point.q=0; point.v.x=6.0f; point.v.w=1.0f;
        func_002830C0(&point,&point,D_L03_001B2B0C+WORD(state,0x284)*128);
        if (func_PAL_L01_00323068(entity,&point)&0x80) func_002A7750(entity,3,-1);
        break;
    case 6:
        point.q=0;point.v.z=0.5f;
        func_00283098(&point,&point,entity+0xC0);
        func_0029FCC0(WORD(state,0x338),2,&delta);
        qcopy(entity+0x10,&delta);
        FLOAT(entity,0x18)-=0.75f;
        func_00282CF0(entity+0x10,entity+0x10,&point);
        func_002AA2E8(entity+0xF4,1.5707964f,0.12566373f);
        func_002AA2E8(state+0x33C,10.0f,0.080000006f);
        func_L03_0041F178(entity);
        func_L00_002E6CF0(func_L03_0041F720,entity);
        break;
    case 7:
        FLOAT(state,0x1B8)-=0.006f;
        func_00282CC0(entity+0x10,entity+0x10,state+0x1B0);
        point.q=0;point.v.z=0.5f;
        func_00283098(&point,&point,entity+0xC0);
        func_00282CC0(&point,&point,entity+0x10);
        func_L03_0041F178(entity);
        func_L00_002E6CF0(func_L03_0041F720,entity);
        if (func_00277258(&point,0.5f,0,entity)) {
            func_00283098(&delta,&D_L03_001B1C30,entity+0xC0);
            func_00282CC0(&delta,&delta,entity+0x10);
            func_PAL_L00_003FB330(&delta,0,25,20,20,20,45,0,0.5f,20.0f,1,0,0,0);
            func_PAL_002B15D8(entity,3.0f,6.0f,31,D_L03_001A8F20,3.0f,6.0f,255);
            func_0029F338(entity);
            return;
        }
        break;
    case 4:
        if (D_00189E20.flag == 1) func_002A7750(entity,5,-1);
        break;
    case 5:
        FLOAT(state,0x29C)=func_00283B98(FLOAT(state,0x29C),0.12566373f);
        angle=func_00283248(D_00189E20.x-FLOAT(entity,0x10),D_00189E20.y-FLOAT(entity,0x14));
        func_PAL_002B5E30(entity,func_00283B98(angle,func_00283198(FLOAT(state,0x29C))*0.087266475f));
        func_L03_0041F178(entity);
        if (UHALF(entity,0x96)>=6) func_L00_002E6CF0(func_L03_0041F720,entity);
        if (D_00189E20.flag!=1) func_002A7750(entity,4,-1);
        break;
    case 9:
        if (func_002B3868(entity)) {
            if (WORD(state,0x340)!=-1) {
                func_002E59F8(WORD(state,0x340));
                WORD(state,0x340)=-1;
            }
        }
        if (func_002B38B8(entity)) {
            func_L00_003294F0(entity,0);
            func_002A7750(entity,2,0);
            UHALF(entity,0x34)=(UHALF(entity,0x34)&0xFFBE)|0x1000;
            WORD(entity,0x98)=WORD(*(u8 **)(entity+0x24),0x10);
            func_002A8C28(entity,entity+0x10,0x10001,0.5f,2.0f,1.0f,0,1,0);
            { u8 *transform=D_L03_001B2B0C+WORD(state,0x284)*128;
            func_L02_002EF388(entity,transform+0x30,transform+0x70,0,0); }
            entity[0x7F]=0;
        }
        WORD(entity,0x98)=0;
        UHALF(entity,0x34)=(UHALF(entity,0x34)|0x41)&0xEFFF;
        break;
    }
    func_L03_0041EF90(entity);
}
