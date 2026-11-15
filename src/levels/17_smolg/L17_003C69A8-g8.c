#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern char *D_L17_001FE880[];
extern float D_L17_001B0344 __attribute__((sda));
extern float D_L17_001B0348 __attribute__((sda));
extern float D_L17_001B034C __attribute__((sda));
extern float D_L17_001B0350 __attribute__((sda));
extern float D_L17_001B0354 __attribute__((sda));
extern float D_L17_001B0358 __attribute__((sda));
/* Incomplete view, reading only the measured sound-bank byte at [0]. */
extern unsigned char D_L17_001DBF82[];
extern unsigned char D_00188660[];
extern void func_00282CF0(void *,void *,void *);
extern float func_00282DF0(void *);
extern float func_00282E48(void *,void *);
extern float func_00282E20(void *);
extern float func_002AA2E8(void *,float,float);
extern void func_00282F20(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern float func_00283248(float,float);
extern float func_002AAA00(void *,float,void *,int,float,float,float);
/* Same target: p,q,mode in the integer bank; four floats in the FP bank. */
extern float func_002AAA00_yaw(void *,float,void *,float,float,float,int) __asm__("func_002AAA00");
extern int func_002E59B0(void *,int);
extern int func_002E5DA0(int,int,void *,int);
extern void func_002E59F8(int);

/* Moves along the selected path, turns smoothly, and manages its movement sound. */
int func_L17_003C69A8(char *object,int pathIndex,int *sound)
{
    Vec target,delta;
    char *state=*(char **)(object+0x68);
    char **path=&gPathTable_L17[pathIndex];
    int complete=0;
    float speedSquared,deceleration,distance,pitch;
    qcopy(&target,*path+16+*(int *)(state+0x94)*16);
    FastVecSub(&delta,&target,object+16);
    if(FastVecLength(&delta)<(D_L17_001B0344*0.016666668f)*2.0f) {
        (*(int *)(state+0x94))++;
        complete=*(int *)(state+0x94)==*(int *)*path;
    }
    distance=fast_vec_dist(object+16,*path+*(int *)*path*16);
    deceleration=D_L17_001B0348*0.0002777777845f;
    speedSquared=*(float *)(state+0x90)* *(float *)(state+0x90);
    if(distance<=speedSquared/(deceleration*2.0f))
        ApproachValue(state+0x90,0.0f,speedSquared/(distance*2.0f));
    else ApproachValue(state+0x90,D_L17_001B0344*0.016666668f,deceleration);
    vec_scale_to_length(&delta,&delta,*(float *)(state+0x90));
    FastVecAdd(object+16,&delta,object+16);
    pitch=-FastMatrixHelperA(vec_length_xy(&delta),delta.f[2]);
    if(pitch>0.261799425f) pitch=0.261799425f;
    else if(pitch< -0.261799425f) pitch= -0.261799425f;
    ApproachTargetWithDirectionMode(object+0xf4,pitch,state+0x9c,0,D_L17_001B034C*0.00000484813743f,D_L17_001B034C*0.00000484813743f,0.209439546f);
    func_002AAA00_yaw(object+0xf8,FastMatrixHelperA(target.f[0]-*(float *)(object+16),target.f[1]-*(float *)(object+20)),state+0x98,D_L17_001B0350*0.00000484813743f,D_L17_001B0350*0.00000484813743f,0.209439546f,0);
    ApproachTargetWithDirectionMode(object+0xf0,*(float *)(state+0x98)* *(float *)(state+0x90)*D_L17_001B0358,state+0xa0,0,D_L17_001B0354*0.00000484813743f,D_L17_001B0354*0.00000484813743f,0.209439546f);
    if(!complete) {
        if(!IsVoicePlayingForOwner(object,*sound) && D_L17_001DBF82[0]!=255)
            *sound=PlaySoundFromClassBank(0,4,object,0x922);
    } else {
        if(*sound!=-1) {
            char *voice=(char *)gSoundState+*sound*0x70;
            if(*(char **)(voice+0x88)==object && ((u8 *)voice)[0x74]) StopSoundVoice(*sound);
        }
        *sound=-1;
    }
    return complete;
}
