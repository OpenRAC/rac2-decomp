#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern char *func_0029EFD0(int);
extern void func_003001E0(char *,char *,char *);
extern float func_00283248(float,float);
extern void func_002A0F48(char *);
extern unsigned short D_L18_001B18FC __attribute__((sda));
extern float D_L18_001B191C __attribute__((sda));

/* Creates a bouncing fireball (moby class 3998) at a position with a given direction, owner and strength, and returns it. */
char *func_L18_00437AA0(int owner, char *position, char *velocity, int value, float scale, float extra)
{
    char *object = CreateMoby(0xf9e /* moby class 3998 */);
    char *state;
    float angle;
    float sizeFactor;
    unsigned short timer;
    if (object != 0) {
        state = *(char **)(object + 0x68);
        *(unsigned char *)(object + 0x30) = 0xff;
        *(short *)(object + 0x32) = 0xff;
        object[0x31] = 1;
        object[0x20] = 0;
        *(int *)(state + 0x24) = owner;
        *(TI128 *)(object + 0x10) = *(TI128 *)position;
        *(TI128 *)(state + 0x10) = *(TI128 *)velocity;
        timer = D_L18_001B18FC;
        *(float *)(state + 0x1c) = scale;
        *(int *)(state + 0x20) = value;
        *(short *)(state + 0x28) = timer;
        *(short *)(state + 0x2a) = 0;
        *(int *)(object + 0xf0) = 0;
        *(int *)(object + 0xf4) = 0;
        angle = FastMatrixHelperA(*(float *)velocity, *(float *)(velocity+4));
        *(float *)(object + 0xf8) = angle;
        *(float *)(state + 0x30) = extra;
        sizeFactor = D_L18_001B191C;
        *(float *)(object + 0x2c) = *(float *)(object + 0x2c) * sizeFactor;
        func_002A0F48(object);
    }
    return object;
}

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
extern void func_L18_002CFF48(int),func_002AD6F0(void *,void *,void *,void *);
/* Updates a mover (moby class 4333): it waits for a trigger or a hit, then glides smoothly to its target spot and turn, and flags a linked object when done. */
void func_L18_00439960(u8 *obj)
{
    float oldpos[4] __attribute__((aligned(16)));
    float oldrot[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(obj+0x68);
    float ease;
    *(TI128 *)oldpos = *(TI128 *)(obj+0x10);
    *(TI128 *)oldrot = *(TI128 *)(obj+0xF0);
    switch (B(obj,0x20)) {
    case 0:
        if (I(state,0x80)==-1) {
            H(obj,0x34)|=2;
            SetMobyState(obj,4,-1);
            return;
        }
        I(state,0x88)=0;
        I(state,0x5C)|=1;
        *(TI128 *)(state+0x60) = *(TI128 *)(obj+0x10);
        *(TI128 *)(state+0x70) = *(TI128 *)(obj+0xF0);
        if (D_L18_0021E7B0.flags[I(state,0x8C)] ||
            (B(obj,0xB0)!=255 && B(state,0x92) && (D_0019B2E8[B(obj,0xB0)+gCurrentMapIndex*16]&128)) ||
            (I(state,0x98)!=-1 && IsPointInsideRegion(gHeroPosition,I(state,0x98)))) {
            qcopy_nc(obj+0x10,gWaypointTable[I(state,0x80)].position);
            qcopy_nc(obj+0xF0,gWaypointTable[I(state,0x80)].rotation);
            H(obj,0x34)|=2;
            if (!B(state,0x91)) { MarkMobySpawned(obj); return; }
            SetMobyState(obj,3,-1);
        } else SetMobyState(obj,1,-1);
        break;
    case 1:
        if (!B(obj,0xBC) && !IsThirdPendingFlagSet(obj) && I(state,0x8C)!=-1 &&
            B(gMobyTable_L18+I(state,0x8C)*256,0x20)!=254 &&
            B(gMobyTable_L18+I(state,0x8C)*256,0x20)!=253 &&
            !(B(obj,0xB0)!=255 && B(state,0x92) && (D_0019B2E8[B(obj,0xB0)+gCurrentMapIndex*16]&128)) &&
            (I(state,0x98)==-1 || !IsPointInsideRegion(gHeroPosition,I(state,0x98)))) goto effects;
        if (I(state,0x94)!=-1) B(gMobyTable_L18+I(state,0x94)*256,0xBC)=1;
        if (B(state,0x93)) MarkTableEntryFlagged(B(obj,0xB0));
        SetMobyState(obj,2,-1);
    effects:
        if (!B(state,0x91) && FindOwnedEffectSlot(obj,0x40000,0)) {
            if (I(state,0x94)!=-1) B(gMobyTable_L18+I(state,0x94)*256,0xBC)=1;
            FastVecAdd(delta,obj+0xD0,obj+0xE0);
            vec_scale_to_length(delta,delta,1.0f/12.0f);
            FastVecAdd(offset,obj+0x10,obj+0xE0);
            SpawnExplosionEffects(obj,delta,offset,0,0,4,2,9,10,3,16,-1,1,1,-1,0,0x810001,1,15);
            SpawnDebrisForMaskedParts(obj,31,3,6,3,6,delta,255);
            H(obj,0x34)|=1;
            B(obj,0x31)=0;
            I(obj,0x98)=0;
            if (*(s16 *)(obj+0xAA)==0x10ED /* moby class 4333 */) PlayMobySound(0,0,obj);
            if (B(state,0x93)) MarkTableEntryFlagged(B(obj,0xB0));
            SetMobyState(obj,2,-1);
        }
        B(obj,0xA8)=255;
        break;
    case 2:
        if (SetFirstPendingFlag(obj) && (*(s16 *)(obj+0xAA)==0xEDB /* moby class 3803 */ || *(s16 *)(obj+0xAA)==0x1146 /* moby class 4422 */)) PlayMobySound(0,0,obj);
        F(state,0x88)+=1.0f/F(state,0x84);
        if (F(state,0x88)>1) F(state,0x88)=1;
        ease=1.0f-FastSinOrCosA(F(state,0x88)*3.1415927f);
        ease*=0.5f;
        FastVecSub(delta,gWaypointTable[I(state,0x80)].position,state+0x60);
        FastVecScale(delta,delta,ease);
        FastVecAdd(obj+0x10,state+0x60,delta);
        R(obj,0xF8)=MoveAngleTowardTarget(F(state,0x78),gWaypointTable[I(state,0x80)].rotation[2],ease);
        R(obj,0xF4)=MoveAngleTowardTarget(F(state,0x74),gWaypointTable[I(state,0x80)].rotation[1],ease);
        R(obj,0xF0)=MoveAngleTowardTarget(F(state,0x70),gWaypointTable[I(state,0x80)].rotation[0],ease);
        if (F(state,0x88)>=1) SetMobyState(obj,3,-1);
        break;
    case 3:
        if (I(state,0x94)!=-1 && B(gMobyTable_L18+I(state,0x94)*256,0xBC)) break;
        if (B(state,0x90)) { D_L18_001B9A80=0; DetachHeroFromObject(0); }
        H(obj,0x34)|=2;
        break;
    }
    if (B(obj,0x20)<3) {
        FastVecSub(delta,obj+0x10,oldpos);
        CombineTransformsAndStore(state+0x20,delta,oldrot,obj+0xF0);
    }
}
