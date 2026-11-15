#include "common.h"
extern void func_0029FCC0(void *,int,void *);
extern void func_002AF1D0(void *,void *,int,int);
extern void func_002A05A8(void *);
extern void func_002A0F48(void *);
extern void func_002833F0(void *,void *);
extern void func_002A10E8(void *);
extern void func_L18_00433460(void *);
extern void func_L18_00433B70(void *);
extern void func_L18_00432F18(void *);
extern void func_L18_00434FC0(void *);
extern void func_L00_002E6EF8(void (*)(void *),void *);
extern int func_002A77E0(int);
extern int func_002A7820(int,int);
extern void func_L18_004350E0(void *,int);
extern float func_00282E48(void *,void *);
extern float D_L18_001B97C0[];
extern void func_002A93B0(void *);
extern void func_002B0990(void *,float *,float,int,int);

/* Updates the Extermibot every frame: counts time, keeps the torso and beam parts attached to the body, draws its electric beam, and puffs smoke when the torso is gone. */
void func_L18_00432310(unsigned char *object)
{
    float position[4] __attribute__((aligned(16)));
    unsigned char *state=*(unsigned char **)(object+0x68);
    if(*(unsigned short *)(object+0x96)<0xFFFF)
        ++*(unsigned short *)(object+0x96);
    if(*(short *)(state+0x804)<0x7FFF)
        ++*(unsigned short *)(state+0x804);
    if(*(void **)(state+0x7C0)) {
        TransformMobyJointToWorld(object,0,position);
        {
            unsigned char *child=*(unsigned char **)(state+0x7C0);
            qcopy(child+0x10,position);
            *(float *)(child+0x48)=*(float *)(object+0x48);
        }
        if(*(void **)(state+0x7C8))
            CopyJointTransformToObject(*(void **)(state+0x7C0),*(void **)(state+0x7C8),2,0);
        if(*(void **)(state+0x7C4)) {
            *(float *)(*(unsigned char **)(state+0x7C4)+0x48)=*(float *)(object+0x48);
            TransformMobyJointToWorld(*(void **)(state+0x7C0),0,position);
            {
                unsigned char *child=*(unsigned char **)(state+0x7C4);
                qcopy(child+0x10,position);
                qcopy(child+0xF0,*(unsigned char **)(state+0x7C0)+0xF0);
                func_002A05A8(child);
            }
            func_002A0F48(*(void **)(state+0x7C4));
            {
                unsigned char *child=*(unsigned char **)(state+0x7C4);
                euler_rotation_basis(child+0xC0,child+0xF0);
            }
            func_002A10E8(*(void **)(state+0x7C4));
        }
    }
    if(object && object[0x20]!=0xFE && object[0x20]!=0xFD && object[0x20]>=2) {
        if(*(short *)(state+0x7FC)==0 && *(void **)(state+0x7C8)) {
            UpdateExtermibotElectricBeam(object);
            AddDrawCallbackToList3(DrawPairedBranchingRibbonEffects,object);
        }
        if(object[0x31])
            AddDrawCallbackToList3(UpdateLinkedParts,object);
        if(!*(void **)(state+0x7C0)) {
            TransformMobyJointToWorld(object,0,position);
            if(RandomIntBelow(20)==0)
                SpawnSmallSparkSmokeBurst(position,RandomIntRange(10,15));
            AddDrawCallbackToList3(SpawnGlowFlashAtMoby,object);
        }
    }
    if(object[0x31] && fast_vec_dist(object+0x10,gCameraPosition_L18)<24.0f) {
        UpdateMobyGroundCheck(object);
        object[0x6F]=22;
    }
    {
        void *child=*(void **)(state+0x7C4);
        *(short *)(state+0x808)=0;
        if(child)
            SetValueAndStartSmoothChange(child,(float *)(state+0x810),2.5f,5,1);
    }
}
