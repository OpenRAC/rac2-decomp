#include "common.h"
extern void func_L01_003CDEA8(u8 *);
extern void func_L01_003CDE58(u8 *);
extern void func_002A7470(void *,int,int,int);
extern u8 *D_L01_001B255C_base[] __asm__("D_L01_001B255C") __attribute__((sda));
extern void func_L01_003CDD00(u8 *);
extern void func_L01_003CBCD8(u8 *, int, int, int);
extern u8 *D_L01_001FE180[];
extern int func_002A77E0(int);
extern void func_L01_00323310(int,int);
extern void func_002A7750(u8 *,int,int);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282FB8(void *,void *,float);
extern void func_00282F20(void *,void *,float);
extern float func_00283248(float,float);
extern float func_00282DF0(void *);
extern void func_002A7CA0(void *,void *,float,float,float,float);
extern int func_002A8AF0(void *,void *,int);
extern void func_L01_00337A60(void *,void *,void *,int);
extern void func_002A8598(int,int);
extern void func_002A6C58(void *,int,int);
extern void func_0029F338(void *);

/* Steps the owner state, moving along its path and releasing expired objects.
 * Separate unit for the jump table and small-data entity-base access. */
/* Updates the Swamp Monster I eye. It moves, plays its animations and is removed when it is finished. */
void func_L01_003CE228(u8 *moby)
{
    u8 *state = *(u8 **)(moby + 0x68);
    float offset[4] __attribute__((aligned(16)));
    float step[4] __attribute__((aligned(16)));
    float value;
    ApplyBodyPartDamage(moby);
    switch (moby[0x95]) {
    case 0:
        InitLinkedBodyPart(moby);
        break;
    case 1:
        if (moby[0x60] & 2) {
            if (moby[0x42] != 2 && !RandomIntBelow(15)) {
                if (moby[0x43] != 2) StartAnimationBlended(moby,2,0,10);
            } else if (moby[0x43] != 1) StartAnimationBlended(moby,1,0,10);
        }
        if (*(int *)(state+0xBC)) {
            QueueKeyedRequest(*(int *)(state+0xD0),*(int *)(state+0xD8));
            if (moby[0x43]!=1) StartAnimationBlended(moby,1,0,10);
            SetMobyState(moby,0,5);
        }
        break;
    case 2:
        if (!RandomIntBelow(5)) SpawnSwampMonsterSplash(moby,3,10,1);
        if (moby[0x60] & 2) {
            *(u16 *)(moby+0x34) &= 0xEFFF;
            if (moby[0x43]) StartAnimationBlended(moby,0,0,10);
            *(float *)(moby+0x48)=0.0f;
            SetMobyState(moby,0,4);
        }
        break;
    case 3:
        if (!RandomIntBelow(5)) SpawnSwampMonsterSplash(moby,3,10,1);
        if (moby[0x60] & 2) {
            *(u16 *)(moby+0x34) |= 0x1000;
            if (moby[0x43]!=1) StartAnimationBlended(moby,1,0,10);
            SetMobyState(moby,0,5);
        }
        break;
    case 4:
        if (*(int *)(state+0xBC)>0) {
            *(float *)(moby+0x48)=1.0f;
            if (moby[0x43]) StartAnimationBlended(moby,0,0,10);
            SetMobyState(moby,0,3);
        }
        break;
    case 5:
        if (moby[0x60] & 2) {
            if (moby[0x42] != 2 && !RandomIntBelow(15)) {
                if (moby[0x43] != 2) StartAnimationBlended(moby,2,0,10);
            } else if (moby[0x43] != 1) StartAnimationBlended(moby,1,0,10);
        }
        {
            if (!*(int *)(state+0xBC)) qcopy(state+0x70,state+0x60);
            FastVecSub(offset,state+0x70,moby+0x10);
            FastVectorDivideHelper(offset,offset,0.050000004f);
            FastVecAdd(moby+0x10,moby+0x10,offset);
            value=FastMatrixHelperA(*(float *)(state+0x80)-*(float *)(moby+0x10),*(float *)(state+0x84)-*(float *)(moby+0x14));
            MobySpringTurn(moby,state+0xB8,value,0.001163553f,0.1f,0.10471977f);
            if (!*(int *)(state+0xBC)) {
                QueueKeyedRequest(*(int *)(state+0xD4),*(int *)(state+0xDC));
                *(u16 *)(moby+0x34) &= 0xEFFF;
                if (moby[0x43] != 3) StartAnimationBlended(moby,3,0,20);
                SetMobyState(moby,0,2);
            }
        }
        break;
    case 6:
        FastVecAdd(offset,moby+0x10,state+0x90);
        if (point_in_path_xy(offset,D_L01_001FE180[*(int *)(state+0xA8)]+0x10,*(int *)D_L01_001FE180[*(int *)(state+0xA8)]))
            qcopy(moby+0x10,offset);
        else {
            ClosestPointOnPolygonEdge(moby+0x10,offset,D_L01_001FE180[*(int *)(state+0xA8)]+0x10,*(int *)D_L01_001FE180[*(int *)(state+0xA8)]);
            FastVecSub(step,state+0x60,moby+0x10);
            vec_scale_to_length(step,step,0.033333335f);
            FastVecAdd(moby+0x10,moby+0x10,step);
        }
        value=FastVecLength(state+0x90)-0.0030555557f;
        if (value<0.0f) value=0.0f;
        vec_scale_to_length(state+0x90,state+0x90,value);
        if (*(float *)(state+0x20)<=0.0f && !RandomIntBelow(4)) SpawnSwampMonsterSplash(moby,3,10,1);
        if (moby[0x60]&2) {
            if (*(float *)(state+0x20)<=0.0f) {
                *(u16 *)(moby+0x34) &= 0xEFFF;
                SetMobyState(moby,0,7);
            } else {
                *(u16 *)(moby+0x34) |= 0x1000;
                if (moby[0x43]!=1) StartAnimationBlended(moby,1,0,10);
                SetMobyState(moby,0,5);
            }
        }
        break;
    case 7:
        QueueKeyedRequest(*(int *)(state+0xD4),*(int *)(state+0xDC));
        if (*(int *)(state+0xB0)!=-1) SetByteOnGroupMobys(*(int *)(state+0xB0),1);
        SetDeathBits(moby,0x200,3);
        if (*(int *)(state+0xCC)!=-1) MarkMobySpawned(D_L01_001B255C_base[0]+(*(int *)(state+0xCC)<<8));
        *(int *)(state+0xCC)=-1;
        MarkMobySpawned(moby);
        return;
    }
    ReleaseBodyPartTimers(moby);
}
