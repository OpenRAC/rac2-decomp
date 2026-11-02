/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* Tier: sol-high (v0982), USA v1.01, game -O2 -G8 -ffunction-sections.
 * Best check.py: 1196/1196 bytes, 0/1 places; first difference +0x2C.
 * Fixed a behavioral error in the previous draft: the collision query at
 * 0041ED40 runs every frame, outside the initialization guard. The entry
 * branch now matches. Path-index/-1 allocation, f0/f1 allocation, several
 * initialization stores and the scale-load order remain different.
 * D_001A7A60[0x1C] is the existing flag-array view: it reproduces both macro
 * accesses, unlike a separate scalar whose store moves into the call slot.
 * func_002B0A68 keeps alpha's real u8 width and the unchanged EE FP/GPR banks.
 * Raw state accesses match the later call setup more closely than a typed
 * state record. Explicit scalar captures, chained equal-value assignments,
 * qcopy_nc and native TI with qcopy/barrier do not close the residuals.
 * Next: independent lifetime evidence for the saved path index, or measured
 * initialization scheduling. Required declarations below; never linked.
 */
#include "common.h"
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
extern float D_L03_001B1C00 __attribute__((sda)), D_L03_001B1C04 __attribute__((sda)), D_L03_001B1C0C __attribute__((sda));
extern float D_L03_001B1C30[4] SDATA(D_L03_001B1C30) __attribute__((sda));
extern int D_0018C0B4 NOT_SDA;
extern int D_L03_001A9044[] NOT_SDA __attribute__((sda));
extern int D_L03_001A9044_gp SDATA(D_L03_001A9044) __attribute__((sda));
extern int D_L03_001A903C[] __attribute__((sda));
extern u8 D_001A7A60[] MACRO_ADDR;
extern float D_L03_001B9980[] NOT_SDA;
void func_L03_0041EAE0(u8 *entity) {
    u8 *state=*(u8 **)(entity+0x68);
    float point[4],velocity[4];
    void *hit;
    int pathIndex;
    float a,b,z;
    if(entity[0x20]==0) {
        if(*(int *)(state+0x340)!=-1) {
            func_002E59F8(*(int *)(state+0x340));
            *(int *)(state+0x340)=-1;
        }
        *(s16 *)(*(u8 **)(entity+0x24)+0x46)=5;
        if(*(int *)(state+0x288)) {
            func_002A7750(entity,4,1);
            func_002A7398(entity,0,0);
            *(float *)(state+0x20)=3;
            *(s16 *)(state+0x24)=3;
            *(float *)(state+0x33C)=4.5f;
        } else {
            pathIndex=*(int *)(state+0x280);
            if(pathIndex==-1) goto death_tail;
            qcopy(entity+0x10,D_L03_001FE700[pathIndex]+16);
            *(int *)(state+0x148)|=0x210;
            *(s16 *)(state+0x32C)=1;
            if(*(int *)(state+0x28C)) {
                func_002A7750(entity,9,4);
                func_002A7398(entity,0,0);
                *(float *)(state+0x33C)=0;
                *(int *)(entity+0x98)=0;
                *(u16 *)(entity+0x34)=(*(u16 *)(entity+0x34)|0x41)&0xEFFF;
            } else {
                func_002A7750(entity,3,0);
                func_002A7398(entity,0,0);
                *(float *)(state+0x33C)=6;
            }
        }
        *(u8 *)(state+0x48)=func_00283CF0(20);
        *(u8 *)(state+0x4A)=func_00283CF0(17.6f);
        *(u8 *)(state+0x70)=8;
        *(int *)(state+0xA8)=3;
        *(float *)(state+0x90)=0.5f;
        *(float *)(state+0x94)=0.5f;
        *(float *)(state+0x9C)=0.4f;
        z=*(float *)(entity+0x18)-1;
        a=D_L03_001B1C00*0.00027777778f;
        b=D_L03_001B1C04*0.016666668f;
        *(float *)(state+0xA0)=z;
        *(float *)(state+0x30)=0.75f;
        *(float *)(state+0x144)=0.05f;
        *(float *)(state+0x114)=0.25f;
        *(float *)(state+0x110)=0.5f;
        *(float *)(state+0x11C)=0.4f;
        *(float *)(state+0x120)=0.78539824f;
        *(float *)(state+0x140)=0.52359885f;
        *(float *)(state+0x330)=1;
        *(float *)(state+0x130)=a;
        *(float *)(state+0x138)=b;
        *(float *)(state+0x118)=0.4f;
        *(float *)(state+0x134)=a;
        *(float *)(entity+0x2C)=*(float *)(*(u8 **)(entity+0x24)+0x24)*D_L03_001B1C0C;
        *(int *)(state+0x290)=0;
    }
    hit=func_002A9640(entity,0x10000,0);
        if(hit && *(u8 **)((u8 *)hit+0x20)) {
            u8 *other=*(u8 **)((u8 *)hit+0x20);
            if(*(s16 *)(other+0xAA)==0xFFD && *(float *)(other+0x18)<*(float *)(entity+0x18)+2) entity[0xA8]=0xFF;
        }
    if(func_002B0ED8(entity,state+0x60,0) && *(float *)(state+0x20)<=0) {
        func_00283098(point,D_L03_001B1C30,entity+0xC0);
        func_00282CC0(point,point,entity+0x10);
        func_0032C700(point,0,25,20,20,20,45,0,0.5f,20.0f,1,0,0,0);
        func_00282F20(velocity,state+0xE0,0.06666667f);
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
death_tail:
        if(*(int *)(state+0x340)!=-1) {
            func_002E59F8(*(int *)(state+0x340));
            *(int *)(state+0x340)=-1;
        }
        func_0029F338(entity);
        return;
    }
    if(entity[0x31] && func_00282E48(entity+0x10,D_L03_001B9980)<24) {
        func_002A93B0(entity);
        entity[0x6F]=22;
    }
}
