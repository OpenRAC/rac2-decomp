#include "common.h"

/* func_L03_0041EAE0 reaches several level words through $gp, so it needs -G8.
 * Its state record is written through struct members: their MEMs are
 * in-struct, which lets the scheduler place the $gp scalar loads above the
 * record's stores as retail does. */
extern void func_002E59F8(int);
extern void func_002A7750(void *,int,int);
extern void func_002A7398(void *,int,int);
extern int func_00283CF0(float);
extern void *func_002A9640(void *,u32,int);
extern int func_002B0ED8(void *,void *,int);
extern void func_00283098(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern void *func_0032C700(void *,int,int,int,int,int,int,int,float,float,int,int,int,int);
extern void func_00282F20(void *,void *,float);
extern void func_002B0A68(void *,int,void *,float,float,float,float,u8);
extern int func_002E5E58(int,int,void *);
extern void func_002B0A18(int,int);
extern int func_002E5CF8(int,int,void *);
extern void func_002A6C58(void *,int,int);
extern void func_0029F338(void *);
extern float func_00282E48(void *,void *);
extern void func_002A93B0(void *);
extern u8 *D_L03_001FE700[] NOT_SDA;
extern float D_L03_001B1C00 __attribute__((sda));
extern float D_L03_001B1C04 __attribute__((sda));
extern float D_L03_001B1C0C __attribute__((sda));
extern float D_L03_001B1C30[4] SDATA(D_L03_001B1C30) __attribute__((sda));
extern int D_0018C0B4 NOT_SDA;
extern int D_L03_001A9044[] NOT_SDA __attribute__((sda));
extern int D_L03_001A9044_gp SDATA(D_L03_001A9044) __attribute__((sda));
extern int D_L03_001A903C[] __attribute__((sda));
extern u8 D_001A7A60[] MACRO_ADDR;
extern float D_L03_001B9980[] NOT_SDA;
typedef struct {
    u8 pad0[0x20];
    float f20;
    s16 f24;
    u8 pad26[0xA];
    float f30;
    u8 pad34[0x14];
    u8 f48;
    u8 pad49[0x1];
    u8 f4A;
    u8 pad4B[0x15];
    u8 f60[0x10];
    u8 f70;
    u8 pad71[0x1F];
    float f90;
    float f94;
    u8 pad98[0x4];
    float f9C;
    float fA0;
    u8 padA4[0x4];
    int fA8;
    u8 padAC[0x34];
    float fE0[4];
    u8 padF0[0x20];
    float f110;
    float f114;
    float f118;
    float f11C;
    float f120;
    u8 pad124[0xC];
    float f130;
    float f134;
    float f138;
    u8 pad13C[0x4];
    float f140;
    float f144;
    int f148;
    u8 pad14C[0x134];
    int f280;
    u8 pad284[0x4];
    int f288;
    int f28C;
    int f290;
    u8 pad294[0x98];
    s16 f32C;
    u8 pad32E[0x2];
    float f330;
    u8 pad334[0x8];
    float f33C;
    int f340;
} StateEAE0;
void func_L03_0041EAE0(u8 *entity) {
    StateEAE0 *st=*(StateEAE0 **)(entity+0x68);
    float point[4],velocity[4];
    void *hit;
    int pathIndex;
    float a,b;
    if(entity[0x20]==0) {
        if(st->f340!=-1) {
            func_002E59F8(st->f340);
            st->f340=-1;
        }
        *(s16 *)(*(u8 **)(entity+0x24)+0x46)=5;
        if(st->f288) {
            func_002A7750(entity,4,1);
            func_002A7398(entity,0,0);
            st->f20=3;
            st->f24=3;
            st->f33C=4.5f;
        } else {
            pathIndex=st->f280;
            if(pathIndex==-1) {
                if(st->f340!=-1) {
                    func_002E59F8(st->f340);
                    st->f340=-1;
                }
                func_0029F338(entity);
                return;
            }
            qcopy(entity+0x10,D_L03_001FE700[pathIndex]+16);
            st->f148|=0x210;
            st->f32C=1;
            if(st->f28C) {
                func_002A7750(entity,9,4);
                func_002A7398(entity,0,0);
                st->f33C=0;
                *(int *)(entity+0x98)=0;
                *(u16 *)(entity+0x34)=(*(u16 *)(entity+0x34)|0x41)&0xEFFF;
            } else {
                func_002A7750(entity,3,0);
                func_002A7398(entity,0,0);
                st->f33C=6;
            }
        }
        st->f48=func_00283CF0(20);
        st->f4A=func_00283CF0(17.6f);
        st->f70=8;
        st->fA8=3;
        st->f90=0.5f;
        st->f94=0.5f;
        st->f9C=0.4f;
        st->fA0=*(float *)(entity+0x18)-1;
        a=D_L03_001B1C00*0.00027777778f;
        b=D_L03_001B1C04*0.016666668f;
        st->f30=0.75f;
        st->f144=0.05f;
        st->f114=0.25f;
        st->f118=0.4f;
        st->f134=a;
        st->f110=0.5f;
        st->f11C=0.4f;
        st->f120=0.78539824f;
        st->f140=0.52359885f;
        st->f330=1;
        st->f130=a;
        st->f138=b;
        *(float *)(entity+0x2C)=*(float *)(*(u8 **)(entity+0x24)+0x24)*D_L03_001B1C0C;
        st->f290=0;
    }
    hit=func_002A9640(entity,0x10000,0);
    if(hit && *(u8 **)((u8 *)hit+0x20)) {
        u8 *other=*(u8 **)((u8 *)hit+0x20);
        if(*(s16 *)(other+0xAA)==0xFFD && *(float *)(other+0x18)<*(float *)(entity+0x18)+2) entity[0xA8]=0xFF;
    }
    if(func_002B0ED8(entity,st->f60,0) && st->f20<=0) {
        func_00283098(point,D_L03_001B1C30,entity+0xC0);
        func_00282CC0(point,point,entity+0x10);
        func_0032C700(point,0,25,20,20,20,45,0,0.5f,20.0f,1,0,0,0);
        func_00282F20(velocity,st->fE0,0.06666667f);
        func_002B0A68(entity,31,velocity,3,6,3,6,255);
        if(D_0018C0B4==49) {
            D_L03_001A9044_gp=D_L03_001A9044[0]+1;
            if(D_L03_001A9044_gp>=10 && !D_001A7A60[0x1C]) {
                D_001A7A60[0x1C]=1;
                func_002E5E58(1,0,0);
                func_002B0A18(0x1233,-1);
                D_L03_001A903C[0]=1;
            }
        }
        func_002E5CF8(3,0,entity);
        func_002A6C58(entity,0,3);
        if(st->f340!=-1) {
            func_002E59F8(st->f340);
            st->f340=-1;
        }
        func_0029F338(entity);
        return;
    }
    if(entity[0x31] && func_00282E48(entity+0x10,D_L03_001B9980)<24) {
        func_002A93B0(entity);
        entity[0x6F]=22;
    }
}
