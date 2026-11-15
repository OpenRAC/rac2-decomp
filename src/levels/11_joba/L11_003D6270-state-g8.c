#include "common.h"
extern void func_L11_003F2E38(void *, void *, f32 *, f32 *, f32 *);
extern void func_002A7750(void *, s32, s32);
extern void func_002A7470(void *, s32, s32, s32);
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
extern void func_L11_00440B28(s32, void *);
extern s32 func_L11_00440C80(s32);
extern void func_L02_003FC248(void *, s32, s32);
extern void func_0032C700(void *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32, s32, s32);
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
    if (p[0x43] != animation) StartAnimationBlended(p, animation, mode, blend);
}
/* The two 16-bit counters at +0x278 and +0x27A, read as one value. */
static __inline__ unsigned long CounterPair(u8 *state)
{
    return *(u32 *)(state + 0x278);
}
/* State machine: self[0x20] picks the state and self[0xBC] holds the sub-state. Each state's
   setup runs when func_002B3868 reports the object's first pending flag as newly set. */
/* Runs the enemy's main state machine: waiting, turning, attacking, taking a hit and
   dying, and switches its animations to match. */
void func_L11_003F1F48(u8 *self) {
    u8 *state = *(u8 **)(self + 0x68);
    u8 query[16] __attribute__((aligned(16)));
    u8 vector[64] __attribute__((aligned(16)));
    u8 matrix[48] __attribute__((aligned(16)));
    f32 a,b,c;
    f32 distance, amplitude;
    f32 *pos;
    GetTargetHeadingAndDistances(self,query,&a,&b,&c);
    switch (self[0x20]) {
    case 1:
        if (!self[0x42]) U(self,0x34) |= 0x46;
        break;
    case 2:
        SetMobyState(self,4,-1);
        EnterJobaEnemyHitReaction(self);
        break;
    case 3:
        if (SetFirstPendingFlag(self)) { SetAnimation(self,8,0,10); }
        if (self[0x60] & 2) SetMobyState(self,self[0x94],H(*(u8 **)(self+0x68),0x294));
        break;
    case 4:
        if (SetFirstPendingFlag(self)) {
            u8 *here=self+0x10;
            pos = GetArenaCenterPoint(W(self,0xB8));
            if (SignedTriangleArea(query,here,pos) > 0) {
                self[0xBC] = 1;
                if (self[0x95] == 1) SetAnimation(self,1,0,10);
                else SetAnimation(self,2,0,10);
                F(self,0x48) = D_L11_001B0578;
            } else {
                self[0xBC] = 0;
                if (self[0x95] == 1) SetAnimation(self,2,0,10);
                else SetAnimation(self,1,0,10);
                F(self,0x48) = D_L11_001B0578;
            }
        }
        if (FloatAbs(F(D_L11_00189EA0,8) - F(self,0x18)) < D_L11_001B0588) SetMobyState(self,5,-1);
        else if (b > D_L11_001B0548 && b < D_L11_001B054C) ChooseJobaEnemyAttackState(self);
        break;
    case 5:
        if (SetFirstPendingFlag(self)) {
            self[0xBC]=0; SetAnimation(self,9,0,10);
            ClearVector128(state+0x1E0);
            if (self[0x95] == 2) F(state,0x1E8)=D_L11_001B0580 / (f32)D_L11_001B057C;
            else F(state,0x1E8)=-D_L11_001B0580 / (f32)D_L11_001B057C;
            F(state,0x270)=3.1415927410125732f / (f32)D_L11_001B057C;
            H(state,0x298)=0;
        } else if (self[0xBC] == 0) {
            if (self[0x60]&2) { self[0xBC]=1; SetAnimation(self,10,0,0); }
        } else if (self[0xBC] == 1) {
            if (U(self,0x96) > (D_L11_001B057C >> 1)) self[0xBC]=2;
        } else if (self[0xBC] == 2) {
            if (U(self,0x96) > D_L11_001B057C-10) {
                self[0xBC]=3; SetAnimation(self,9,4,0); F(self,0x48)=-1;
            }
        } else if (self[0xBC] == 3) {
            if (GetMobyAnimationValue(self) < 2) {
                if (F(self,0x18)>490) SetMobyState(self,4,1);
                else SetMobyState(self,4,2);
            }
        }
        FastVecAdd(self+0x10,self+0x10,state+0x1E0);
        BuildDirectionRollMatrix(vector,self+0xE0,F(state,0x270));
        copy_matrix3x4(matrix,vector);
        multiply_matrix3x3(self+0xC0,matrix,self+0xC0);
        amplitude=D_L11_001B0558*(1-(H(state,0x298)*2.0f)/IntToFloat(D_L11_001B057C))*(1-(H(state,0x298)*2.0f)/IntToFloat(D_L11_001B057C));
        F(self,0x10)=amplitude*FastSinOrCosA(F(state,0x250))+GetArenaCenterPoint(W(self,0xB8))[0];
        F(self,0x14)=amplitude*FastSinOrCosB(F(state,0x250))+GetArenaCenterPoint(W(self,0xB8))[1];
        U(state,0x298)++;
        break;
    case 6:
        if (SetFirstPendingFlag(self)) {
            SetAnimation(self,3,0,10); H(state,0x296)=0; self[0xBC]=0; SetJobaEnemyCountersToOne(self);
        }
        distance=GetMobyAnimationValue(self);
        if (!self[0xBC] && CounterPair(state)==0x10001 && self[0x42]==3 && distance>30) {
            SetJobaEnemyCountersToTwo(self); self[0xBC]=1;
        } else if (self[0xBC]==1 && self[0x42]==3 && (self[0x60]&2)) {
            SetAnimation(self,0,0,10); self[0xBC]=2;
        } else if (self[0xBC]==2 && CounterPair(state)==0) {
            EnterJobaEnemyState4(self); if (H(state,0x296)) EnterJobaEnemyHitReaction(self);
        }
        break;
    case 7:
        if (SetFirstPendingFlag(self)) { SetAnimation(self,4,0,10); self[0xBC]=0; SetJobaEnemyCountersToOne(self); }
        switch (self[0xBC]) {
        case 0:
            if (self[0x60]&2) { SetAnimation(self,5,0,10); self[0xBC]=1; U(self,0x96)=D_L11_001B055C-1; }
            break;
        case 1:
            if (U(self,0x96) % D_L11_001B055C == 0) {
                u8 *v=vector;
                u8 *position=self+0x10;
                pos=GetArenaCenterPoint(W(self,0xB8));
                FastVecSub(v,position,pos);
                W(vector,8)=0;
                vec_scale_to_length(v,v,D_L11_001B0564);
                pos=GetArenaCenterPoint(W(self,0xB8));
                FastVecAdd(v,v,pos);
                if (self[0x95]==2) F(vector,8)=F(self,0x18)+D_L11_001B0568;
                else if (self[0x95]==1) F(vector,8)=F(self,0x18)-D_L11_001B0568;
                LaunchFighterTowardTarget(W(self,0xB8),vector);
            }
            if (GetArenaFighterCount(W(self,0xB8)) >= D_L11_001B056C || U(self,0x96)>D_L11_001B0560) {
                SetAnimation(self,6,0,10); self[0xBC]=2;
            }
            if (FloatAbs(F(D_L11_00189EA0,8)-F(self,0x18)) < D_L11_001B0588) SetMobyState(self,5,-1);
            break;
        case 2:
            if (self[0x60]&2) EnterJobaEnemyState4(self);
            break;
        }
        break;
    case 8:
        if (SetFirstPendingFlag(self)) {
            SetAnimation(self,7,0,3);
            if (U(state,0x278)<2 && U(state,0x27A)<2) { self[0xBC]=0; H(state,0x296)=0; SetJobaEnemyCountersToOne(self); }
            else self[0xBC]=3;
            if (F(state,0x20)<=0) SetMobyState(self,9,-1);
        }
        distance=GetMobyAnimationValue(self);
        if (self[0xBC]==0 && CounterPair(state)==0x10001 && self[0x42]==7 && distance>32) {
            SetJobaEnemyCountersToTwo(self); self[0xBC]=1;
        } else if (self[0xBC]==1 && self[0x42]==7 && (self[0x60]&2)) {
            SetAnimation(self,0,0,10); self[0xBC]=2;
        } else if (self[0xBC]==2 && CounterPair(state)==0) {
            EnterJobaEnemyState4(self); if (H(state,0x296)) EnterJobaEnemyHitReaction(self);
        } else if (self[0xBC]==3 && self[0x42]==7 && (self[0x60]&2)) EnterJobaEnemyState4(self);
        break;
    case 9:
        if (SetFirstPendingFlag(self)) {
            pos=GetArenaCenterPoint(W(self,0xB8));
            FastVecSub(state+0x1E0,pos,self+0x10);
            W(state,0x1E8)=0;
            vec_scale_to_length(state+0x1E0,state+0x1E0,0.1666666716337204f);
            F(self,0x48)=D_L11_001B0574;
            ClearJobaEnemyCounters(self);
            U(self,0x34)&=0xEFFF;
        }
        F(state,0x1E8)-=0.0027777778450399637f;
        FastVecAdd(self+0x10,self+0x10,state+0x1E0);
        pos=GetArenaCenterPoint(W(self,0xB8));
        if (F(self,0x18)<pos[2]+5 || !RandomIntBelow(0x1C2) || U(self,0x96)>=301) {
            SetMobyAnimTypeThree(self,0,-1);
            ResetJobaEnemy(self);
            SpawnExplosion(self+0x10,0,25,15,30,20,30,0,3,0,1,1,0,0);
            PlaySoundFromClassBank(0,0,self,0xDF7);
        }
        break;
    }
}
