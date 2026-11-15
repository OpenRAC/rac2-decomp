#include "common.h"
typedef unsigned int UpdateBits __attribute__((mode(TI)));
#define D_00189EA0 (D_00189E20+0x80)
#define D_00189EB0 (D_00189E20+0x90)
extern unsigned char D_001395B8;
extern char D_00189E20[];
extern unsigned char D_0019B2E8[];
extern int D_001A79F0 __attribute__((sda));
extern int D_L00_001A8F00 __attribute__((sda));
extern char *D_L00_001B1F8C __attribute__((sda));
extern int D_L00_001FA920[];
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002833F0(void *,void *);
extern void func_00283410(void *,void *);
extern float func_00283B98(float,float);
extern float func_00283C80(float,float);
extern void func_002A0430(int);
extern void func_002A7750(void *,int,int);
extern int func_002A8508(int,int);
extern void func_002AA800(void *,int,float,float);
extern int func_002B3868(void *);
extern void func_002DF3F8(void *,void *);
extern int func_002E5CF8(int,int,void *);
extern void func_L00_002B9D60(void *,void *,int,int);
extern void func_L00_002D40A0(void *,int,float);
extern void func_L00_003294F0(void *,int);
extern void func_L00_00429020(int);
extern int func_L00_00429048(int);

/* Turns the object by a set angle when triggered, with a sound and an optional camera cut, then settles at the final angle. */
void func_L00_003CF610(unsigned char *obj) {
    union { UpdateBits q; float f[4]; } first,second;
    int *ctx=*(int **)(obj+0x68);
    if(!ctx) return;
    if((unsigned char)obj[0x20]==0) {
        if(D_L00_001FA920[ctx[0]]==0) {
            if(ctx[2]) { obj[0x20]=3; return; }
            if(!ctx[5]) { obj[0x20]=2; return; }
            *(float *)(ctx+6)=*(float *)(obj+0xF4);
            *(float *)(obj+0xF4)=FastAddRotations(*(float *)(obj+0xF4),-1.5707965f);
            SetMobyState(obj,4,-1);
            return;
        }
        if(CountMobysInGroupNotInState(ctx[0],-1)==0) {
            if((D_0019B2E8[(unsigned char)obj[0xB0]+gCurrentMapIndex*16]&0x80)==0) {
                obj[0x20]=1;
                if(!ctx[2]) return;
                D_001395B8=1;
                LockCameraEntry(ctx[4]);
                MarkTableEntryFlagged((unsigned char)obj[0xB0]);
                first.q=*(UpdateBits *)(D_L00_001B1F8C+ctx[3]*128+0x30);
                second.q=*(UpdateBits *)(D_L00_001B1F8C+ctx[3]*128+0x70);
                CaptureCheckpointState(&first,&second);
                return;
            }
            obj[0x20]=3;
        } else if(D_0019B2E8[(unsigned char)obj[0xB0]+gCurrentMapIndex*16]&0x80) obj[0x20]=3;
    }
    if((unsigned char)obj[0x20]==1) {
        if(ctx[4]) {
            if(IsCameraTriggerReady(ctx[4])) {
                char *bank=D_L00_001B1F8C+ctx[3]*128;
                qcopy_nc(gHeroPosition,bank+0x30);
                qcopy_nc(D_00189EB0,bank+0x70);
                obj[0x20]=3;
                SetObjectFlagBit(obj,1);
            }
        }
    }
    if((unsigned char)obj[0x20]==3) {
        if(*(float *)(ctx+1)==0.0f) PlayMobySound(0,0,obj);
        *(float *)(obj+0xF4)+=-0.017453294f;
        euler_rotation_basis(obj+0xC0,obj+0xF0);
        *(float *)(ctx+1)+=1.0f;
        if(*(float *)(ctx+1)>135.0f) { PlayMobySound(1,0,obj); obj[0x20]=2; }
    }
    if((unsigned char)obj[0x20]!=4) return;
    if(D_L00_001A8F00) return;
    if(SetFirstPendingFlag(obj)) {
        PlayMobySound(1,0,obj);
        qcopy(&second,gHeroPosition);
        euler_to_matrix(gHeroState,D_00189EB0);
        vec_scale_to_length(&first,gHeroState,-2.5f);
        FastVecAdd(&first,&second,&first);
        ResetHeroPositionAndDirection(&first,D_00189EB0,0,1);
        StartHeroTargetState(&second,1,*(float *)(D_00189EB0+8));
    }
    StepAngleTowardTarget(obj+0xF4,0,*(float *)(ctx+6),0.02617994323372841f);
    if(FastDiffRots(*(float *)(obj+0xF4),*(float *)(ctx+6))<0.001f) obj[0x20]=2;
}
