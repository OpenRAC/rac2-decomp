/* functional: high. Near-miss draft within a few instructions of retail: differences are register allocation, scheduling and instruction shape. */
/*
 * Tier: sol-high, task v0925, USA v1.01, game profile:
 * -O2 -G8 -ffunction-sections. Best check.py: 1108/1108 bytes, 0/1 places.
 * Only two instructions differ: at 003D8580 and 003D8588 the scale multiply
 * (mul.s f20,f20,f21) and direction setup (daddu a2,zero,zero) are swapped.
 * Important semantic correction to the earlier draft: the hero-carrying branch
 * jumps directly to 003D8704, bypassing the unattended height clamp and crossing
 * event. Keep height distinct from the first dot product. Fixing these lifetimes
 * also reproduces retail's initial height-add register assignment and scheduling.
 * qzero_nc clears the real velocity vector and flushes the constant-1 equivalence
 * so the state byte is rematerialized after the random calls, as in retail.
 * That vector is disjoint from the other state fields accessed around the clear.
 * Giving pitch its own temporary fixes the multiply operand order. Computing
 * scale before/after the vector captures, multiple ABI-preserving spring-call
 * interleavings, and -g all leave the final multiply/direction scheduling tie.
 * Stop on the tie; no linked match claimed. Compile as an isolated -g8.c unit.
 * All required declarations follow below; spring signature agrees with its
 * definition in src/game/002AA800.c.
 */
#include "common.h"
typedef int QuadT __attribute__((mode(TI)));
#define F(p,o) (*(f32 *)((u8 *)(p)+(o)))
#define I(p,o) (*(s32 *)((u8 *)(p)+(o)))
#define H(p,o) (*(s16 *)((u8 *)(p)+(o)))
typedef struct { u8 pad[0x34E]; s16 mode; } Hero;
extern Hero D_00189E20 NOT_SDA;
#define HERO ((u8 *)&D_00189E20)
extern u8 *D_L01_001B255C;
extern u8 D_L01_002A4E20[];
extern f32 D_L01_001B0768 __attribute__((sda));
extern f32 D_L01_001B076C __attribute__((sda));
extern f32 D_L01_001B0774 __attribute__((sda));
extern f32 D_L01_001B077C __attribute__((sda));
extern f32 D_L01_001B0780 __attribute__((sda));
extern f32 D_L01_001B0784 __attribute__((sda));
extern f32 D_L01_001B0788 __attribute__((sda));
extern f32 D_L01_001B078C __attribute__((sda));
extern f32 D_L01_001B0790 __attribute__((sda));
extern void func_00282D30(void *,void *,f32);
extern f32 func_L01_003BAFB0(void);
extern f32 func_002A7878(f32,f32);
extern void func_0026FEB8(void *,s32,s32);
extern void func_00282CF0(void *,void *,void *);
extern f32 func_00282DB0(void *,void *);
extern f32 func_002AA898(void *,f32,void *,f32,f32,f32,s32);
extern void func_L01_00316C48(void *,void *,void *,void *,void *);
extern s32 func_002E5CF8(s32,s32,void *);
extern void func_002AEF28(void *,void *,void *,f32,f32,f32);
extern f32 func_00283B98(f32,f32);
extern void func_00282CC0(void *,void *,void *);
extern void func_002AD6F0(void *,void *,void *,void *);
void func_L01_003D8358(u8 *m)
{
    f32 delta[4] __attribute__((aligned(16)));
    f32 rotation[4] __attribute__((aligned(16)));
    f32 relative[4] __attribute__((aligned(16)));
    f32 oldAngle[4] __attribute__((aligned(16)));
    f32 oldPos[4] __attribute__((aligned(16)));
    f32 move[4] __attribute__((aligned(16)));
    u8 *s = *(u8 **)(m+0x68);
    f32 height, previous, x, y, pitch, scale, speed, step;
    u8 *other;
    func_00282D30(delta,m+0x10,-1.0f);
    qcopy(rotation,m+0xF0);
    previous=F(m,0x18);
    height=func_L01_003BAFB0();
    F(s,0x84)=height+0.2f;
    switch(m[0x20]) {
    case 0:
        if(height>0.0f) {
            I(s,0x80)=1;
            qcopy(s+0x60,m+0xF0);
            qzero_nc(s+0x70);
            if(I(s,0x8C)!=-1) {
                F(m,0x18)=F(s,0x84)-5.0f;
                F(m,0xF0)=func_002A7878(-1.57079637f,1.57079637f);
                F(m,0xF4)=func_002A7878(-1.57079637f,1.57079637f);
                m[0x20]=1;
            } else {
                func_0026FEB8(D_L01_002A4E20,H(m,0xB2),H(m,0xAA));
                m[0x20]=2;
            }
        }
        break;
    case 1:
        other=D_L01_001B255C+(I(s,0x8C)<<8);
        if(!other || other[0x20]==0xFE || other[0x20]==0xFD) m[0x20]=2;
        break;
    case 2:
        if(D_00189E20.mode==0 && *(u8 **)(HERO+0x33C)==m) {
            func_00282CF0(relative,HERO+0x80,m+0x10);
            x=func_00282DB0(relative,m+0xC0);
            y=func_00282DB0(relative,m+0xD0);
            scale=D_L01_001B076C;
            pitch=-scale;
            pitch=pitch*y;
            *(QuadT *)oldAngle=*(QuadT *)(s+0x60);
            *(QuadT *)oldPos=*(QuadT *)(m+0x10);
            scale=scale*x;
            func_002AA898(s+0x60,pitch,s+0x70,D_L01_001B077C,D_L01_001B0780,D_L01_001B0784,0);
            func_002AA898(s+0x64,scale,s+0x74,D_L01_001B077C,D_L01_001B0780,D_L01_001B0784,0);
            func_L01_00316C48(HERO+0x80,move,m+0x10,oldAngle,s+0x60);
            func_00282CF0(HERO+0x100,move,HERO+0x80);
            F(HERO,0x108)+=F(m,0x18)-oldPos[2];
        } else {
            speed=D_L01_001B0774;
            step=(F(s,0x84)-F(m,0x18))*0.016666668f;
            step=speed*step;
            F(m,0x18)=F(m,0x18)+step;
            if(F(m,0x18)<F(s,0x84)-2.0f) F(m,0x18)+=speed*0.016666668f;
            else {
                func_002AA898(s+0x60,0.0f,s+0x70,D_L01_001B0788,D_L01_001B078C,D_L01_001B0790,0);
                func_002AA898(s+0x64,0.0f,s+0x74,D_L01_001B0788,D_L01_001B078C,D_L01_001B0790,0);
            }
            if(F(m,0x18)>F(s,0x84)) F(m,0x18)=F(s,0x84);
            if(previous<height-D_L01_001B0768 && F(m,0x18)>=height-D_L01_001B0768 && !I(s,0xA0)) {
                func_002E5CF8(0,0,m);
                I(s,0xA0)=1;
            }
        }
        func_002AEF28(m,s+0x90,s+0x94,0.0200712885708f,0.00727220624685f,0.00901753548533f);
        F(m,0xF0)=func_00283B98(F(s,0x60),F(m,0xF0));
        F(m,0xF4)=func_00283B98(F(s,0x64),F(m,0xF4));
        func_00282CC0(delta,delta,m+0x10);
        func_002AD6F0(s+0x20,delta,rotation,m+0xF0);
        break;
    }
}
