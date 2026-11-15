#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
#define I(p,o) (*(int *)((u8 *)(p)+(o)))
#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define B(p,o) (*((u8 *)(p)+(o)))
#define H(p,o) (*(u16 *)((u8 *)(p)+(o)))
/* A rotation component written through its int/float union: such a store may alias any later load. */
typedef union { int i; float f; } Word;
#define R(p,o) (((Word *)((u8 *)(p)+(o)))->f)
extern int D_001A79F0;
extern u8 D_0019B2E8[], D_00189EA0[];
typedef struct { u8 prefix[0x464]; u8 flags[0]; } FlagTable;
extern FlagTable D_L19_0021EA30;
typedef struct { u8 prefix[0x30]; float position[4]; u8 middle[0x30]; float rotation[4]; } Transform;
extern Transform *D_L19_001B2B0C MACRO_ADDR;
extern u8 *D_L19_001B2A1C;
extern int D_L19_001B9D00 NOT_SDA;
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
extern void func_L18_002CFF48(int),func_002AD6F0(void *,void *,void *,void *);
/* Waits for a trigger or a hit, then smoothly moves and turns the object to a target spot, and removes it or leaves it there. */
void func_L19_00411890(u8 *moby)
{
    float oldpos[4] __attribute__((aligned(16)));
    float oldrot[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    u8 *vars = *(u8 **)(moby+0x68);
    float ease;
    *(TI128 *)oldpos = *(TI128 *)(moby+0x10);
    *(TI128 *)oldrot = *(TI128 *)(moby+0xF0);
    switch (B(moby,0x20)) {
    case 0:
        if (I(vars,0x80)==-1) {
            H(moby,0x34)|=2;
            SetMobyState(moby,4,-1);
            return;
        }
        I(vars,0x88)=0;
        I(vars,0x5C)|=1;
        *(TI128 *)(vars+0x60) = *(TI128 *)(moby+0x10);
        *(TI128 *)(vars+0x70) = *(TI128 *)(moby+0xF0);
        if (D_L19_0021EA30.flags[I(vars,0x8C)] ||
            (B(moby,0xB0)!=255 && B(vars,0x92) && (D_0019B2E8[B(moby,0xB0)+gCurrentMapIndex*16]&128)) ||
            (I(vars,0x98)!=-1 && IsPointInsideRegion(gHeroPosition,I(vars,0x98)))) {
            qcopy_nc(moby+0x10,D_L19_001B2B0C[I(vars,0x80)].position);
            qcopy_nc(moby+0xF0,D_L19_001B2B0C[I(vars,0x80)].rotation);
            H(moby,0x34)|=2;
            if (!B(vars,0x91)) { MarkMobySpawned(moby); return; }
            SetMobyState(moby,3,-1);
        } else SetMobyState(moby,1,-1);
        break;
    case 1:
        if (!B(moby,0xBC) && !IsThirdPendingFlagSet(moby) && I(vars,0x8C)!=-1 &&
            B(gMobyArray_L19+I(vars,0x8C)*256,0x20)!=254 &&
            B(gMobyArray_L19+I(vars,0x8C)*256,0x20)!=253 &&
            !(B(moby,0xB0)!=255 && B(vars,0x92) && (D_0019B2E8[B(moby,0xB0)+gCurrentMapIndex*16]&128)) &&
            (I(vars,0x98)==-1 || !IsPointInsideRegion(gHeroPosition,I(vars,0x98)))) goto effects;
        if (I(vars,0x94)!=-1) B(gMobyArray_L19+I(vars,0x94)*256,0xBC)=1;
        if (B(vars,0x93)) MarkTableEntryFlagged(B(moby,0xB0));
        SetMobyState(moby,2,-1);
    effects:
        if (!B(vars,0x91) && FindOwnedEffectSlot(moby,0x40000,0)) {
            if (I(vars,0x94)!=-1) B(gMobyArray_L19+I(vars,0x94)*256,0xBC)=1;
            FastVecAdd(delta,moby+0xD0,moby+0xE0);
            vec_scale_to_length(delta,delta,1.0f/12.0f);
            FastVecAdd(offset,moby+0x10,moby+0xE0);
            SpawnExplosionEffects(moby,delta,offset,0,0,4,2,9,10,3,16,-1,1,1,-1,0,0x810001,1,15);
            SpawnDebrisForMaskedParts(moby,31,3,6,3,6,delta,255);
            H(moby,0x34)|=1;
            B(moby,0x31)=0;
            I(moby,0x98)=0;
            if (*(s16 *)(moby+0xAA)==0x10ED /* moby class 4333 */) PlayMobySound(0,0,moby);
            if (B(vars,0x93)) MarkTableEntryFlagged(B(moby,0xB0));
            SetMobyState(moby,2,-1);
        }
        B(moby,0xA8)=255;
        break;
    case 2:
        if (SetFirstPendingFlag(moby) && (*(s16 *)(moby+0xAA)==0xEDB /* moby class 3803 */ || *(s16 *)(moby+0xAA)==0x1146 /* moby class 4422 */)) PlayMobySound(0,0,moby);
        F(vars,0x88)+=1.0f/F(vars,0x84);
        if (F(vars,0x88)>1) F(vars,0x88)=1;
        ease=1.0f-FastSinOrCosA(F(vars,0x88)*3.1415927f);
        ease*=0.5f;
        FastVecSub(delta,D_L19_001B2B0C[I(vars,0x80)].position,vars+0x60);
        FastVecScale(delta,delta,ease);
        FastVecAdd(moby+0x10,vars+0x60,delta);
        R(moby,0xF8)=MoveAngleTowardTarget(F(vars,0x78),D_L19_001B2B0C[I(vars,0x80)].rotation[2],ease);
        R(moby,0xF4)=MoveAngleTowardTarget(F(vars,0x74),D_L19_001B2B0C[I(vars,0x80)].rotation[1],ease);
        R(moby,0xF0)=MoveAngleTowardTarget(F(vars,0x70),D_L19_001B2B0C[I(vars,0x80)].rotation[0],ease);
        if (F(vars,0x88)>=1) SetMobyState(moby,3,-1);
        break;
    case 3:
        if (I(vars,0x94)!=-1 && B(gMobyArray_L19+I(vars,0x94)*256,0xBC)) break;
        if (B(vars,0x90)) { D_L19_001B9D00=0; DetachHeroFromObject(0); }
        H(moby,0x34)|=2;
        break;
    }
    if (B(moby,0x20)<3) {
        FastVecSub(delta,moby+0x10,oldpos);
        CombineTransformsAndStore(vars+0x20,delta,oldrot,moby+0xF0);
    }
}
