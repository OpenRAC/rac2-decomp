#include "common.h"
extern void func_L11_003F2E38(void *, void *, f32 *, f32 *, f32 *);
extern void func_002A7750(void *, s32, s32);
extern void func_PAL_002A7E68(void *, s32, s32, s32);
extern s32 func_002B3868(void *);
extern f32 *func_L11_004417E8(s32);
extern f32 func_L11_003F2F00(void *, void *, void *);
extern f32 func_00282C48(f32);
extern void func_00282C88(void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, f32);
extern f32 func_00283180(f32), func_00283198(f32), func_00283CE0(s32);
extern void func_00283678(void *, void *), func_00283738(void *, void *, void *);
extern void func_L11_00332EE0(void *, void *, f32);
extern f32 func_0029F530(void *);
extern s32 func_002A77E0(s32);
extern void func_L11_003F2D18(void *), func_L11_003F2D38(void *), func_L11_003F2DC8(void *);
extern void func_L11_003F3098(void *), func_L11_003F3108(void *), func_L11_003F3140(void *), func_L11_003F31C0(void *);
extern void func_PAL_L11_00446380(s32, void *);
extern s32 func_L11_00440C80(s32);
extern void func_PAL_L02_004009A0(void *, s32, s32);
extern void func_PAL_L00_003FB330(void *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32, s32, s32);
extern void func_002E5DA0(s32, s32, void *, s32);
extern u8 D_L11_00189EA0[];
extern f32 D_L11_001B0548 __attribute__((sda));
extern f32 D_L11_001B054C __attribute__((sda));
extern f32 D_L11_001B0558 __attribute__((sda));
extern s32 D_L11_001B055C __attribute__((sda));
extern s32 D_L11_001B0560 __attribute__((sda));
extern f32 D_L11_001B0564 __attribute__((sda));
extern f32 D_L11_001B0568 __attribute__((sda));
extern s32 D_L11_001B056C __attribute__((sda));
extern f32 D_L11_001B0574 __attribute__((sda));
extern f32 D_L11_001B0578 __attribute__((sda));
extern f32 D_L11_001B0570 __attribute__((sda));
extern s32 D_L11_001B057C __attribute__((sda));
extern f32 D_L11_001B0580 __attribute__((sda));
extern f32 D_L11_001B0588 __attribute__((sda));
#define F(p,o) (*(f32 *)((u8 *)(p)+(o)))
#define W(p,o) (*(s32 *)((u8 *)(p)+(o)))
#define H(p,o) (*(s16 *)((u8 *)(p)+(o)))
#define U(p,o) (*(u16 *)((u8 *)(p)+(o)))
static __inline__ void SetAnimation(u8 *p, s32 animation, s32 mode, s32 blend)
{
    if (p[0x43] != animation) func_PAL_002A7E68(p, animation, mode, blend);
}
/* The two 16-bit counters at +0x278 and +0x27A, read as one value. */
static __inline__ unsigned long CounterPair(u8 *state)
{
    return *(u32 *)(state + 0x278);
}
/* func_PAL_L11_003F61F8, the PAL copy of func_L11_003F1F48: the same C, where the frame counts
   and rates are rescaled for 50 Hz. */
/* State machine: self[0x20] picks the state and self[0xBC] holds the sub-state. Each state's
   setup runs when func_002B3868 reports the object's first pending flag as newly set. */
void func_PAL_L11_003F61F8(u8 *self) {
    u8 *state = *(u8 **)(self + 0x68);
    u8 query[16] __attribute__((aligned(16)));
    u8 vector[64] __attribute__((aligned(16)));
    u8 matrix[48] __attribute__((aligned(16)));
    f32 a,b,c;
    f32 distance, amplitude;
    f32 *pos;
    func_L11_003F2E38(self,query,&a,&b,&c);
    switch (self[0x20]) {
    case 1:
        if (!self[0x42]) U(self,0x34) |= 0x46;
        break;
    case 2:
        func_002A7750(self,4,-1);
        func_L11_003F2DC8(self);
        break;
    case 3:
        if (func_002B3868(self)) { SetAnimation(self,8,0,8); }
        if (self[0x60] & 2) func_002A7750(self,self[0x94],H(*(u8 **)(self+0x68),0x294));
        break;
    case 4:
        if (func_002B3868(self)) {
            u8 *here=self+0x10;
            pos = func_L11_004417E8(W(self,0xB8));
            if (func_L11_003F2F00(query,here,pos) > 0) {
                self[0xBC] = 1;
                if (self[0x95] == 1) SetAnimation(self,1,0,8);
                else SetAnimation(self,2,0,8);
                F(self,0x48) = D_L11_001B0578;
            } else {
                self[0xBC] = 0;
                if (self[0x95] == 1) SetAnimation(self,2,0,8);
                else SetAnimation(self,1,0,8);
                F(self,0x48) = D_L11_001B0578;
            }
        }
        if (func_00282C48(F(D_L11_00189EA0,8) - F(self,0x18)) < D_L11_001B0588) func_002A7750(self,5,-1);
        else if (b > D_L11_001B0548 && b < D_L11_001B054C) func_L11_003F2D38(self);
        break;
    case 5:
        if (func_002B3868(self)) {
            self[0xBC]=0; SetAnimation(self,9,0,8);
            func_00282C88(state+0x1E0);
            if (self[0x95] == 2) F(state,0x1E8)=D_L11_001B0580 / (f32)((D_L11_001B057C * 5 + 2) / 6);
            else F(state,0x1E8)=-D_L11_001B0580 / (f32)((D_L11_001B057C * 5 + 2) / 6);
            F(state,0x270)=3.1415927410125732f / (f32)((D_L11_001B057C * 5 + 2) / 6);
            H(state,0x298)=0;
        } else if (self[0xBC] == 0) {
            if (self[0x60]&2) { self[0xBC]=1; SetAnimation(self,10,0,0); }
        } else if (self[0xBC] == 1) {
            if (U(self,0x96) > ((D_L11_001B057C >> 1) * 5 + 2) / 6) self[0xBC]=2;
        } else if (self[0xBC] == 2) {
            if (U(self,0x96) > ((D_L11_001B057C - 10) * 5 + 2) / 6) {
                self[0xBC]=3; SetAnimation(self,9,4,0); F(self,0x48)=-1;
            }
        } else if (self[0xBC] == 3) {
            if (func_0029F530(self) < 2) {
                if (F(self,0x18)>490) func_002A7750(self,4,1);
                else func_002A7750(self,4,2);
            }
        }
        func_00282CC0(self+0x10,self+0x10,state+0x1E0);
        func_L11_00332EE0(vector,self+0xE0,F(state,0x270));
        func_00283678(matrix,vector);
        func_00283738(self+0xC0,matrix,self+0xC0);
        amplitude=D_L11_001B0558*(1-(H(state,0x298)*2.0f)/func_00283CE0(D_L11_001B057C))*(1-(H(state,0x298)*2.0f)/func_00283CE0(D_L11_001B057C));
        F(self,0x10)=amplitude*func_00283180(F(state,0x250))+func_L11_004417E8(W(self,0xB8))[0];
        F(self,0x14)=amplitude*func_00283198(F(state,0x250))+func_L11_004417E8(W(self,0xB8))[1];
        U(state,0x298)++;
        break;
    case 6:
        if (func_002B3868(self)) {
            SetAnimation(self,3,0,8); H(state,0x296)=0; self[0xBC]=0; func_L11_003F3108(self);
        }
        distance=func_0029F530(self);
        if (!self[0xBC] && CounterPair(state)==0x10001 && self[0x42]==3 && distance>30) {
            func_L11_003F3140(self); self[0xBC]=1;
        } else if (self[0xBC]==1 && self[0x42]==3 && (self[0x60]&2)) {
            SetAnimation(self,0,0,8); self[0xBC]=2;
        } else if (self[0xBC]==2 && CounterPair(state)==0) {
            func_L11_003F2D18(self); if (H(state,0x296)) func_L11_003F2DC8(self);
        }
        break;
    case 7:
        if (func_002B3868(self)) { SetAnimation(self,4,0,8); self[0xBC]=0; func_L11_003F3108(self); }
        switch (self[0xBC]) {
        case 0:
            if (self[0x60]&2) { SetAnimation(self,5,0,8); self[0xBC]=1; U(self,0x96)=(D_L11_001B055C * 5 + 2) / 6 - 1; }
            break;
        case 1:
            if (U(self,0x96) % ((D_L11_001B055C * 5 + 2) / 6) == 0) {
                u8 *v=vector;
                u8 *position=self+0x10;
                pos=func_L11_004417E8(W(self,0xB8));
                func_00282CF0(v,position,pos);
                W(vector,8)=0;
                func_00282F20(v,v,D_L11_001B0564);
                pos=func_L11_004417E8(W(self,0xB8));
                func_00282CC0(v,v,pos);
                if (self[0x95]==2) F(vector,8)=F(self,0x18)+D_L11_001B0568;
                else if (self[0x95]==1) F(vector,8)=F(self,0x18)-D_L11_001B0568;
                func_PAL_L11_00446380(W(self,0xB8),vector);
            }
            if (func_L11_00440C80(W(self,0xB8)) >= D_L11_001B056C || U(self,0x96)>(D_L11_001B0560 * 5 + 2) / 6) {
                SetAnimation(self,6,0,8); self[0xBC]=2;
            }
            if (func_00282C48(F(D_L11_00189EA0,8)-F(self,0x18)) < D_L11_001B0588) func_002A7750(self,5,-1);
            break;
        case 2:
            if (self[0x60]&2) func_L11_003F2D18(self);
            break;
        }
        break;
    case 8:
        if (func_002B3868(self)) {
            SetAnimation(self,7,0,2);
            if (U(state,0x278)<2 && U(state,0x27A)<2) { self[0xBC]=0; H(state,0x296)=0; func_L11_003F3108(self); }
            else self[0xBC]=3;
            if (F(state,0x20)<=0) func_002A7750(self,9,-1);
        }
        distance=func_0029F530(self);
        if (self[0xBC]==0 && CounterPair(state)==0x10001 && self[0x42]==7 && distance>32) {
            func_L11_003F3140(self); self[0xBC]=1;
        } else if (self[0xBC]==1 && self[0x42]==7 && (self[0x60]&2)) {
            SetAnimation(self,0,0,8); self[0xBC]=2;
        } else if (self[0xBC]==2 && CounterPair(state)==0) {
            func_L11_003F2D18(self); if (H(state,0x296)) func_L11_003F2DC8(self);
        } else if (self[0xBC]==3 && self[0x42]==7 && (self[0x60]&2)) func_L11_003F2D18(self);
        break;
    case 9:
        if (func_002B3868(self)) {
            pos=func_L11_004417E8(W(self,0xB8));
            func_00282CF0(state+0x1E0,pos,self+0x10);
            W(state,0x1E8)=0;
            func_00282F20(state+0x1E0,state+0x1E0,0.20000002f);
            F(self,0x48)=D_L11_001B0574;
            func_L11_003F31C0(self);
            U(self,0x34)&=0xEFFF;
        }
        F(state,0x1E8)-=0.004f;
        func_00282CC0(self+0x10,self+0x10,state+0x1E0);
        pos=func_L11_004417E8(W(self,0xB8));
        if (F(self,0x18)<pos[2]+5 || !func_002A77E0(0x1C2) || U(self,0x96)>=301) {
            func_PAL_L02_004009A0(self,0,-1);
            func_L11_003F3098(self);
            func_PAL_L00_003FB330(self+0x10,0,25,15,30,20,30,0,3,0,1,1,0,0);
            func_002E5DA0(0,0,self,0xDF7);
        }
        break;
    }
}
