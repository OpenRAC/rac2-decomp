#include "common.h"
extern u8 D_00189EA0[];
extern u8 D_0019B2E8[];
extern int D_001A79F0 __attribute__((sda));
extern u8 D_001A7B2F[1] __attribute__((sda));
extern unsigned int D_001A7390[1] __attribute__((sda));
extern unsigned int D_0018CE48[1];
extern u8 *D_L19_001B2B0C __attribute__((sda));
extern u8 *D_L19_001B2A1C __attribute__((sda));
extern float D_L19_001B2628 __attribute__((sda));
extern int D_L19_001C9FC0;
extern int func_002ACBC8(void *, int);
extern void func_002A7750(void *, int, int);
extern void func_00288E18(int,int);
extern int func_002B3868(void *);
extern float func_00283248(float,float);
extern float func_00283198(float);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282D30(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern int func_00282948(void *);
extern void func_0029B3E0(int,int);
#define I(p,o) (*(int *)((p)+(o)))
#define F(p,o) (*(float *)((p)+(o)))
/* Per-frame update for a moby of class 3125. It moves a linked object along a smooth arc between two other objects until it arrives. */
void func_L19_003E9400(u8 *moby)
{
    float start[4] __attribute__((aligned(16)));
    float end[4] __attribute__((aligned(16)));
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *linkedMoby, *linkedVars;
    if (I(vars,0x38) > 0 && IsPointInCuboid(gHeroPosition,I(vars,0x38))) {
        D_L19_001B2628 = F((u8 *)((I(vars,0x38) << 7) + (int)D_L19_001B2B0C),0x38);
    } else {
        if (*(float *)((int)vars + (D_L19_001C9FC0 << 2)) > 0.0f)
            D_L19_001B2628 = *(float *)((int)vars + (D_L19_001C9FC0 << 2));
    }
    switch (moby[0x20]) {
    case 0:
        moby[0x30] = 0xFF;
        I(vars,0x24) = (D_0019B2E8[I(vars,0x20) + gCurrentMapIndex * 16] >> 7) ^ 1;
        SetMobyState(moby,1,-1);
        break;
    case 1:
        if (!D_001A7B2F[0] && IsPointInCuboid(gHeroPosition,I(vars,0x10)) &&
            D_001A7390[0] - D_0018CE48[0] > 3600U)
            RequestSubtitleVoiceLine(0xA12,0x69);
        if (D_0019B2E8[I(vars,0x20) + gCurrentMapIndex * 16] & 0x80) {
            if (I(vars,0x24)) SetMobyState(moby,2,-1);
        }
        break;
    case 2:
        linkedMoby = gMobyArray_L19 + (I(vars,0x14) << 8);
        linkedVars = 0;
        if (linkedMoby) linkedVars = *(u8 **)(linkedMoby + 0x68);
        if (SetFirstPendingFlag(moby)) {
            I(vars,0x24) = 0;
            if (I(vars,0x18) < 0 || I(vars,0x1C) < 0 || I(vars,0x14) < 0) {
                SetMobyState(moby,1,-1);
                break;
            }
            linkedMoby[0xBC] = 1;
            I(vars,0x28) = I(vars,0x2C) = I(linkedVars,0x2C);
        }
        qcopy_nc(start,(u8 *)((I(vars,0x18) << 8) + (int)gMobyArray_L19) + 0x10);
        start[2] += F(vars,0x30);
        qcopy_nc(end,(u8 *)((I(vars,0x1C) << 8) + (int)gMobyArray_L19) + 0x10);
        end[2] += F(vars,0x34);
        F(linkedVars,0x18) = FastMatrixHelperA(end[0]-start[0],end[1]-start[1]);
        FastVecSub(end,end,start);
        {
            float ratio = (float)I(vars,0x2C) / (float)I(vars,0x28);
            float swing = FastSinOrCosB((1.0f - ratio) * 3.1415927f + -1.5707964f);
            FastVecScale(end,end,swing * 0.45f + 0.45f);
        }
        FastVecAdd(linkedVars,start,end);
        if (FastFloatHelperD(vars + 0x2C)) {
            MemcardSave(0,-1);
            SetMobyState(moby,1,-1);
        }
        break;
    }
}
