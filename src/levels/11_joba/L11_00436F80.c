#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern int D_L11_001B359C __attribute__((sda));
extern char D_L11_001BA8C0[];
extern void func_00282CF0(float *, const float *, const float *);
extern void func_00282F20(char *, char *, float);
extern void func_00282CC0(char *, char *, char *);
extern int func_00283CF0(float);
extern void func_002A7470(void *, int, int, int);
extern void func_002A7750(void *, int, int);
extern char *func_002A9640(char *, int, int);
extern float func_002A96A0(char *, char *);
extern void func_002AB800(char *, char *);
extern int D_L11_001FFA78[];
extern void func_L11_00439640(char *, char *);
extern void func_L11_004393D8(char *, int, int);
extern void func_L11_00439BF0(char *);
extern void func_L11_0043AB28(char *);
extern void func_L11_004417A8(char *, char *);
extern void func_L11_00438F18(char *);
extern int func_L11_004390D0(char *);
extern int func_L11_00439D60(char *);
extern void func_L11_00438CD8(char *);
extern void func_L11_00438CE8(char *);
extern void func_L11_00438248(char *);
extern void func_L11_00437CF0(char *);
extern void func_L02_003FC248(char *, int, int);
extern int func_002B3868(char *);
extern int func_002E5CF8(int, int, char *);
extern void func_3739C0(int);
extern int func_373978(char *, int);
extern char D_00188660[];
extern float func_00282E80(void *, void *);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern void func_002833F0(char *, char *);
extern void func_002A7A00(float *, float, float);
extern void func_002B0A68(char *, int, float *, float, float, float, float, unsigned char);
extern int func_002B3BA8(char *, int, int, int, float, float);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(char *);
typedef struct { char pad[0x330]; int children[10]; char gap[0x28]; unsigned char flags[10]; } ChildSlots;
#define CHILD(o,i) ((char *)(D_L11_001B359C + (((ChildSlots *)(*(char **)((o)+0x68)))->children[i] << 8)))

void func_L11_004375B8(char *);

/* Runs the chain creature through its states: following its path, firing at the hero, and bursting apart when it dies. */
void func_L11_00436F80(char *obj)
{
    char *vars=*(char **)(obj+0x68);
    float target[4], pos[4], direction[4], velocity[4], random[4];
    int i, count;
    char *p;
    UpdateChainCreatureDamage(obj);
    qcopy(target,vars+0x50);
    vec_distance_xy(obj+0x10,(char *)target);
    { float x=target[0], y=target[1];
      float ox=*(float *)(obj+0x10), oy=*(float *)(obj+0x14);
      x-=ox;
      y-=oy;
      FastDiffRots(*(float *)(obj+0xF8),FastMatrixHelperA(x,y)); }

    switch (*(unsigned char *)(obj+0x95)) {
    case 0: break;
    case 1:
        if (!func_373978(obj,*(int *)(vars+0x38C))) *(int *)(vars+0x38C)=PlayMobySound(0,4,obj);
        break;
    }
    switch (*(unsigned char *)(obj+0x20)) {
    case 2:
        if (SetFirstPendingFlag(obj)) {
            if (*(unsigned char *)(obj+0x43)!=0) StartAnimationBlended(obj,0,0,10);
            ChooseNextPath(obj);
            p=*(char **)(vars+0x324);
            qcopy(obj+0x10,p+0x10);
            *(float *)(obj+0xF8)=FastMatrixHelperA(*(float *)(p+0x20)-*(float *)(obj+0x10),*(float *)(p+0x24)-*(float *)(obj+0x14));
            euler_rotation_basis(obj+0xC0,obj+0xF0);
            LayOutVerletChain(obj);
        } else if (FollowPathStep(obj)==1) SetMobyState(obj,3,-1);
        break;
    case 3:
        if (SetFirstPendingFlag(obj)) {
            if (*(unsigned char *)(obj+0x43)!=0) StartAnimationBlended(obj,0,0,10);
            ChooseNextPath(obj);
        } else if (FollowPathStep(obj)==1)
            SetMobyState(obj,PickIdleOrMoveState(obj),-1);
        break;
    case 4:
        if (SetFirstPendingFlag(obj)) {
            if (*(unsigned char *)(obj+0x43)!=0) StartAnimationBlended(obj,0,0,10);
            ChooseNextPath(obj);
        } else {
            if (FollowPathStep(obj)==1) SetMobyState(obj,PickIdleOrMoveState(obj),-1);
            if (*(unsigned char *)(obj+0x31)) {
                if (*(short *)(vars+0x374)==-1) ResetProjectileSequence(obj);
                FireNextSegmentProjectile(obj);
            }
        }
        break;
    case 5:
        if (SetFirstPendingFlag(obj)) {
            if (*(unsigned char *)(obj+0x43)!=4) StartAnimationBlended(obj,4,0,10);
            if (*(int *)(vars+0x38C)!=-1) {
                char *entry=gSoundState+*(int *)(vars+0x38C)*0x70;
                if (*(char **)(entry+0x88)==obj && *(unsigned char *)(entry+0x74)) func_3739C0(*(int *)(vars+0x38C));
            }
            *(int *)(vars+0x38C)=-1;
        }
        if (*(unsigned char *)(obj+0x60)&2) {
            if (*(unsigned char *)(obj+0x43)!=0) StartAnimationBlended(obj,0,0,7);
        }
        if (FollowPathStep(obj)==1) SetMobyState(obj,PickIdleOrMoveState(obj),-1);
        break;
    case 7: break;
    case 6:
        if (SetFirstPendingFlag(obj)) {
            *(unsigned short *)(obj+0x96)=0;
            if (*(unsigned char *)(obj+0x43)!=4) StartAnimationBlended(obj,4,0,10);
        }
        if (*(unsigned short *)(obj+0x96)>10) {
            FastVecSub(direction,(float *)D_L11_001BA8C0,(float *)(obj+0x10));
            vec_scale_to_length((char *)direction,(char *)direction,0.5f);
            qcopy(pos,vars+0x100);
            SpawnBlastBurstEffect(obj,(char *)pos);
            RandomDirectionVector(random,0.03333333507180214f,0.06666667014360428f);
            FastVecAdd((char *)velocity,(char *)direction,(char *)random);
                count=0;
            SpawnDebrisForMaskedParts(obj,1,velocity,3,6,3,6,255);
            for (i=0;i<10;i++) {
                if (!((ChildSlots *)vars)->flags[i]) {
                    if (count>=4) {
                        qcopy(pos,vars+0x100+i*16);
                        RandomDirectionVector(random,0.1666666716337204f,0.3333333432674408f);
                        FastVecAdd((char *)velocity,(char *)direction,(char *)random);
                        SpawnDebrisForMaskedParts(CHILD(obj,i),3,velocity,3,6,3,6,255);
                        SpawnBlastBurstEffect(obj,(char *)pos);
                        KillDroneWithEffects(CHILD(obj,i));
                    } else {
                        char *records=(char *)gMobyTable_L11;
                        (*(short *)(vars+0x378))--;
                        count++;
                        SpawnBlastBurstEffect(obj,records+(((ChildSlots *)*(char **)(obj+0x68))->children[i]<<8)+0x10);
                        AimRotorRecordAtEntry(obj,i,0);
                    }
                }
            }
            qcopy(pos,vars+0x1B0);
            RandomDirectionVector(random,0.3333333432674408f,0.5f);
            FastVecAdd((char *)velocity,(char *)direction,(char *)random);
            SpawnDebrisForMaskedParts((char *)(gMobyTable_L11+(*(int *)(*(char **)(obj+0x68)+0x358)<<8)),7,velocity,3,6,3,6,255);
            SpawnBlastBurstEffect(obj,(char *)pos);
            SetMobyAnimTypeThree(obj,0,-1);
            ClearChainSoundAndFlags(obj);
        }
        break;
    }
    UpdateChainBodyFrame(obj);
}

