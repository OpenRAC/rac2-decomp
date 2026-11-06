/* func_PAL_L12_003B8918, the PAL copy of func_L12_003B5240: the same C, where the timers run at 50 Hz,
   the turn rates are multiplied by 1.44f (6/5 squared) and the 0.3f becomes a variable set beside rate. */

#include "common.h"
extern void func_002AEC48(void *,void *,int,float,float);
extern void func_00282CF0(void *,void *,void *);
extern float func_00282E20(void *);
extern float func_00283248(float,float);
extern float func_00283BE0(float,float);
extern float func_002A7878(float,float);
extern int func_002A77E0(int);
extern void func_PAL_002A7E68(void *, s32, s32, s32);
typedef struct UpdateVars {
    u8 pad[0x100];
    float direction[4];
    int pad110;
    int timer114;
    int timer118;
    int timer11C;
    u8 *partner;
} UpdateVars;
extern u8 D_001A7AF8[] __attribute__((sda));
extern u8 D_001A7A40 MACRO_ADDR;
extern u32 D_001397DC, D_00138324;
extern int D_L12_001A8EFC[] __attribute__((sda));
extern int D_L12_001B2BE4[] __attribute__((sda));
extern u8 D_L12_001C0000[];
typedef struct HeroUpdateView {
    u8 pad[0x80];
    float pos[4];
    u8 pad90[0x50];
    float target[4];
    u8 padF0[0x20];
    float velocity[4];
} HeroUpdateView;
extern HeroUpdateView D_00189E20;
extern void func_L04_00423178(u8 *);
extern u8 *func_0029EFD0(int);
extern void func_002A0F48(u8 *);
extern void func_002A7750(void *, s32, s32);
extern void func_L01_003128C0(u8 *);
extern int func_L01_003245E0(u8 *, int, float);
extern void func_L01_003246D0(u8 *);
extern int func_00288AA0(void *, int);
extern void func_00288BE8(void *);
extern u8 *func_00288FB8(int);
extern void func_PAL_L00_0030FBC0(void *,int);
extern void func_L01_00324550(int,int);
extern int func_002F5D10(void);
extern void func_0029F338(u8 *);
extern void func_002A8598(int,int);
extern void func_00288308(int);
extern void func_PAL_002B1588(int,int);
extern void func_0029B3E0(int,int);
extern int func_00282948(int *);
extern int func_00283CF0(float);
extern float func_00282E80(void *,void *);
extern float func_00283C80(float,float);
extern float func_00282DF0(void *);
extern float func_00283B98(float,float);
extern void func_002AF000(void *,float,float,float);
extern void func_00282CC0(void *,void *,void *);
extern void func_002AF1D0(u8 *,u8 *,int,int);
static __inline__ void TurnJoint(void *self, void *joint, int index, float rate, float damping) {
    func_002AEC48(self,joint,index,rate*1.44f,damping*1.44f);
}

void func_PAL_L12_003B8918(u8 *self) {
    UpdateVars *v = *(UpdateVars **)(self + 0x68);
    float target[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float pitch, turn;
    float rate, damping;
    int active;
    u8 *partner;
    func_L04_00423178(self);
    switch (self[0x20]) {
    case 0:
        if (!D_001A7AF8[7]) {
            partner = func_0029EFD0(0x127B);
            v->partner = partner;
            if (partner) {
                *(u16 *)(partner+0x32) = *(u16 *)(self+0x32);
                v->partner[0x30] = self[0x30];
                *(u64 *)(v->partner+0x38) = *(u64 *)(self+0x38);
                *(u32 *)(v->partner+0x78) = *(u32 *)(self+0x78);
                v->partner[0x31] = 1;
                func_002A0F48(v->partner);
                if (D_001397DC & 0x200000) func_002A7750(self,2,-1);
                else func_002A7750(self,1,-1);
            }
            func_L01_003128C0(self);
        } else {
            func_0029F338(self);
            return;
        }
        break;
    case 1:
        if (func_L01_003245E0(self,10,2.5f)) {
            func_L01_003246D0(self);
            if (func_00288AA0(D_L12_001C0000,0x75)) {
                func_00288BE8(D_L12_001C0000);
                func_002A7750(self,2,-1);
            }
        }
        break;
    case 2:
        D_L12_001B2BE4[1] = 1;
        if (D_L12_001A8EFC[1] == 2) {
            self[0x31] = 0;
            {
                u16 flags = *(u16 *)(self+0x34) | 1;
                int partnerMode = D_L12_001A8EFC[1];
                *(u16 *)(self+0x34) = flags;
                if (partnerMode == 2) {
                    *(u16 *)(v->partner+0x34) |= 1;
                    v->partner[0x31] = 0;
                }
            }
        }
        if (!func_002F5D10()) {
            D_L12_001B2BE4[1] = 0;
            self[0x31] = 1;
            *(u16 *)(self+0x34) &= ~1;
            *(u16 *)(v->partner+0x34) &= ~1;
            v->partner[0x31] = 1;
            if (D_001A7AF8[0x31]) func_002A7750(self,4,-1);
            else func_002A7750(self,3,-1);
        }
        break;
    case 3:
        if (D_001A7AF8[0x31]) func_002A7750(self,4,-1);
        else if (func_L01_003245E0(self,10,2.5f)) {
            func_PAL_L00_0030FBC0(func_00288FB8(0x1325),2);
            func_L01_003246D0(self);
        }
        break;
    case 4:
        if (!D_001A7AF8[0x31]) func_002A7750(self,3,-1);
        else if (func_L01_003245E0(self,10,2.5f)) {
            func_L01_00324550(0x1326,-1);
            func_L01_003246D0(self);
            if ((D_00138324 & 0x10) && func_00288AA0(D_L12_001C0000,0x76)) {
                func_00288BE8(D_L12_001C0000);
                func_002A7750(self,5,-1);
            }
        }
        break;
    case 5:
        D_L12_001B2BE4[1] = 1;
        if (D_L12_001A8EFC[1] == 2) {
            self[0x31] = 0;
            {
                u16 flags = *(u16 *)(self+0x34) | 1;
                int partnerMode = D_L12_001A8EFC[1];
                *(u16 *)(self+0x34) = flags;
                if (partnerMode == 2) {
                    *(u16 *)(v->partner+0x34) |= 1;
                    v->partner[0x31] = 0;
                }
            }
        }
        if (!func_002F5D10()) {
            D_L12_001B2BE4[1] = 0;
            self[0x31] = 1;
            *(u16 *)(self+0x34) &= ~1;
            func_0029F338(v->partner);
            v->partner = 0;
            if (self[0x21] != 0xFF) func_002A8598(self[0x21],1);
            if (!D_001A7AF8[7]) {
                D_001A7AF8[0x31] = 0;
                D_001A7AF8[0x69] = 0;
                func_00288308(7);
                func_PAL_002B1588(0x1245,-1);
                func_0029B3E0(0,-1);
                func_0029F338(self);
                return;
            }
        }
        break;
    }
    if (self[0x20] != 0) {
        if (self[0x43] < 2 && func_00282948(&v->timer11C)) {
            v->timer11C = func_00283CF0(((func_002A7878(1200.0f,2400.0f)) * 5.0f + 2.0f) * 0.16666667f);
            if (self[0x43] != 2) func_PAL_002A7E68(self,2,0,8);
        }
        else if ((self[0x60] & 2) && self[0x43] == func_002A77E0(2))
            func_PAL_002A7E68(self,func_002A77E0(2)==0,0,8);
    }
    rate = 0.02f;
    damping = 0.3f;
    active = 0;
    if (self[0x43] == 0 || self[0x43] == 2) {
        active = 1;
        if (func_00282E80(self+0x10,D_00189E20.pos) < 8.0f &&
            func_00283C80(*(float *)(self+0xF8),func_00283248(D_00189E20.target[0]-*(float *)(self+0x10),D_00189E20.target[1]-*(float *)(self+0x14))) < 1.5707964897155762f) {
                if (func_00282DF0(D_00189E20.velocity) > 0.01f) v->timer114 = 100;
                else func_00282948(&v->timer114);
        } else if (v->timer114) {
            v->timer114 = 0;
            qcopy(v->direction,D_00189E20.target);
        }
        if (func_00282948(&v->timer118)) {
            float randomTurn;
            v->timer118 = func_00283CF0(((func_002A7878(180.0f,300.0f)) * 5.0f + 2.0f) * 0.16666667f);
            randomTurn = func_00283B98(*(float *)(self+0xF8),func_002A7878(-90.0f,90.0f)*0.01745329424738884f);
            pitch = func_002A7878(0.0f,30.0f)*0.01745329424738884f;
            func_002AF000(v->direction,6.0f,randomTurn,pitch);
            func_00282CC0(v->direction,v->direction,self+0x10);
        }
        if (v->timer114) {
            qcopy(target,D_00189E20.target);
            rate = 0.04f;
            damping = 0.3f;
        } else qcopy(target,v->direction);
    }
    if (active) {
        qcopy(position,self+0x10);
        position[2] += 2.0f;
        func_00282CF0(delta,target,position);
        turn = func_00283BE0(func_00283248(delta[0],delta[1]),*(float *)(self+0xF8));
        pitch = -func_00283248(func_00282E20(delta),delta[2]);
        if (turn > 1.5707964897155762f) turn = 1.5707964897155762f;
        else if (turn < -1.5707964897155762f) turn = -1.5707964897155762f;
        if (pitch > 0.523598849773407f) pitch = 0.523598849773407f;
        else if (pitch < -0.523598849773407f) pitch = -0.523598849773407f;
        *(float *)((u8 *)v+0x64) = pitch;
        *(float *)((u8 *)v+0x68) = turn*0.6f;
        *(float *)((u8 *)v+0xE8) = turn*0.4f;
    }
    if (D_001A7A40) *(float *)((u8 *)v+0x70) = 2.75f;
    TurnJoint(self,v,0,rate,damping);
    TurnJoint(self,(u8 *)v+0x80,1,rate,damping);
    if (v->partner) func_002AF1D0(self,v->partner,2,0);
}
