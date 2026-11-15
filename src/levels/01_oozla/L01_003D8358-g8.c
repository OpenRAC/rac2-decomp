/*
 * func_L01_003D8358 (oozla, -G8 profile). Case 0 waits for a positive
 * height from func_L01_003BAFB0, then either picks two random angles and
 * moves to case 1 (linked object at s+0x8C) or calls func_0026FEB8 and
 * moves to case 2. Case 1 falls to case 2 once the linked object is gone or
 * in state 0xFE/0xFD. In case 2, when hero mode (0x34E) is 0 and hero+0x33C
 * points at this object, two func_002AA898 springs are driven by dot
 * products of the hero offset and the hero is moved by the resulting change;
 * otherwise the height eases towards s+0x84, the springs relax and a
 * one-shot func_002E5CF8 fires when the threshold is crossed.
 *
 * Shape notes: height stays distinct from the first dot product. The scale
 * constant is its own variable (k), read once for -k*y and k*x; reusing one
 * variable for the constant and the product made sched2 issue the zero
 * direction argument before k*x. speed*step is added to the height as one
 * product so the multiply keeps retail's operand order.
 */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
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
/* Raft on the water. It bobs up and down, and tilts when the hero stands on it. */
void func_L01_003D8358(u8 *moby)
{
    f32 delta[4] __attribute__((aligned(16)));
    f32 rotation[4] __attribute__((aligned(16)));
    f32 relative[4] __attribute__((aligned(16)));
    f32 oldAngle[4] __attribute__((aligned(16)));
    f32 oldPos[4] __attribute__((aligned(16)));
    f32 move[4] __attribute__((aligned(16)));
    u8 *vars = *(u8 **)(moby+0x68);
    f32 tiltScale, height, previous, slopeX, slopeY, pitch, scale, speed, step;
    u8 *linkedMoby;
    FastVecScale(delta,moby+0x10,-1.0f);
    qcopy(rotation,moby+0xF0);
    previous=F(moby,0x18);
    height=GetWaterHeight();
    F(vars,0x84)=height+0.2f;
    switch(moby[0x20]) {
    case 0:
        if(height>0.0f) {
            I(vars,0x80)=1;
            qcopy(vars+0x60,moby+0xF0);
            qzero_nc(vars+0x70);
            if(I(vars,0x8C)!=-1) {
                F(moby,0x18)=F(vars,0x84)-5.0f;
                F(moby,0xF0)=RandomFloatRange(-1.57079637f,1.57079637f);
                F(moby,0xF4)=RandomFloatRange(-1.57079637f,1.57079637f);
                moby[0x20]=1;
            } else {
                STUB_printf(D_L01_002A4E20,H(moby,0xB2),H(moby,0xAA));
                moby[0x20]=2;
            }
        }
        break;
    case 1:
        linkedMoby=gMobyTable_L01+(I(vars,0x8C)<<8);
        if(!linkedMoby || linkedMoby[0x20]==0xFE || linkedMoby[0x20]==0xFD) moby[0x20]=2;
        break;
    case 2:
        if(gHeroState.mode==0 && *(u8 **)(HERO+0x33C)==moby) {
            FastVecSub(relative,HERO+0x80,moby+0x10);
            slopeX=FastVecDot(relative,moby+0xC0);
            slopeY=FastVecDot(relative,moby+0xD0);
            tiltScale=D_L01_001B076C;
            pitch=-tiltScale*slopeY;
            *(Quad *)oldAngle=*(Quad *)(vars+0x60);
            *(Quad *)oldPos=*(Quad *)(moby+0x10);
            scale=tiltScale*slopeX;
            ApproachWithVelocity(vars+0x60,pitch,vars+0x70,D_L01_001B077C,D_L01_001B0780,D_L01_001B0784,0);
            ApproachWithVelocity(vars+0x64,scale,vars+0x74,D_L01_001B077C,D_L01_001B0780,D_L01_001B0784,0);
            TransformOffsetByTwoMatrices(HERO+0x80,move,moby+0x10,oldAngle,vars+0x60);
            FastVecSub(HERO+0x100,move,HERO+0x80);
            F(HERO,0x108)+=F(moby,0x18)-oldPos[2];
        } else {
            speed=D_L01_001B0774;
            step=(F(vars,0x84)-F(moby,0x18))*0.016666668f;
            F(moby,0x18)=F(moby,0x18)+speed*step;
            if(F(moby,0x18)<F(vars,0x84)-2.0f) F(moby,0x18)+=speed*0.016666668f;
            else {
                ApproachWithVelocity(vars+0x60,0.0f,vars+0x70,D_L01_001B0788,D_L01_001B078C,D_L01_001B0790,0);
                ApproachWithVelocity(vars+0x64,0.0f,vars+0x74,D_L01_001B0788,D_L01_001B078C,D_L01_001B0790,0);
            }
            if(F(moby,0x18)>F(vars,0x84)) F(moby,0x18)=F(vars,0x84);
            if(previous<height-D_L01_001B0768 && F(moby,0x18)>=height-D_L01_001B0768 && !I(vars,0xA0)) {
                PlayMobySound(0,0,moby);
                I(vars,0xA0)=1;
            }
        }
        ScaleOwnerWordsByAngles(moby,vars+0x90,vars+0x94,0.0200712885708f,0.00727220624685f,0.00901753548533f);
        F(moby,0xF0)=FastAddRotations(F(vars,0x60),F(moby,0xF0));
        F(moby,0xF4)=FastAddRotations(F(vars,0x64),F(moby,0xF4));
        FastVecAdd(delta,delta,moby+0x10);
        CombineTransformsAndStore(vars+0x20,delta,rotation,moby+0xF0);
        break;
    }
}
