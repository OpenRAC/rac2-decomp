#include "include_asm.h"

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
extern float func_002AAA00_yaw(void *,float,void *,float,float,float,int) __asm__("func_002AAA00");
extern int func_002E59B0(void *,int);
extern int func_002E5DA0(int,int,void *,int);
extern void func_002E59F8(int);

/* Moves along the selected path, turns smoothly, and manages its movement sound. */
int func_PAL_L17_003CAA80(char *object,int pathIndex,int *sound)
{
    Vec target,delta;
    char *state=*(char **)(object+0x68);
    char **path=&D_L17_001FE880[pathIndex];
    int complete=0;
    float speedSquared,deceleration,distance,pitch;
    qcopy(&target,*path+16+*(int *)(state+0x94)*16);
    func_00282CF0(&delta,&target,object+16);
    if(func_00282DF0(&delta)<(D_L17_001B0344*0.020000001f)*2.0f) {
        (*(int *)(state+0x94))++;
        complete=*(int *)(state+0x94)==*(int *)*path;
    }
    distance=func_00282E48(object+16,*path+*(int *)*path*16);
    deceleration=D_L17_001B0348*0.00040000002f;
    speedSquared=*(float *)(state+0x90)* *(float *)(state+0x90);
    if(distance<=speedSquared/(deceleration*2.0f))
        func_002AA2E8(state+0x90,0.0f,speedSquared/(distance*2.0f));
    else func_002AA2E8(state+0x90,D_L17_001B0344*0.020000001f,deceleration);
    func_00282F20(&delta,&delta,*(float *)(state+0x90));
    func_00282CC0(object+16,&delta,object+16);
    pitch=-func_00283248(func_00282E20(&delta),delta.f[2]);
    if(pitch>0.261799425f) pitch=0.261799425f;
    else if(pitch< -0.261799425f) pitch= -0.261799425f;
    func_002AAA00(object+0xf4,pitch,state+0x9c,0,D_L17_001B034C*6.981318e-06f,D_L17_001B034C*6.981318e-06f,0.25132746f);
    func_002AAA00_yaw(object+0xf8,func_00283248(target.f[0]-*(float *)(object+16),target.f[1]-*(float *)(object+20)),state+0x98,D_L17_001B0350*6.981318e-06f,D_L17_001B0350*6.981318e-06f,0.25132746f,0);
    func_002AAA00(object+0xf0,*(float *)(state+0x98)* *(float *)(state+0x90)*D_L17_001B0358,state+0xa0,0,D_L17_001B0354*6.981318e-06f,D_L17_001B0354*6.981318e-06f,0.25132746f);
    if(!complete) {
        if(!func_002E59B0(object,*sound) && D_L17_001DBF82[0]!=255)
            *sound=func_002E5DA0(0,4,object,0x922);
    } else {
        if(*sound!=-1) {
            char *voice=(char *)D_00188660+*sound*0x70;
            if(*(char **)(voice+0x88)==object && ((u8 *)voice)[0x74]) func_002E59F8(*sound);
        }
        *sound=-1;
    }
    return complete;
}

/* Moves along the selected path, turns smoothly, and manages its movement sound. */
int func_PAL_L17_003CADC0(char *object,int pathIndex,int *sound)
{
    Vec target,delta;
    char *state=*(char **)(object+0x68);
    char **path=&D_L17_001FE880[pathIndex];
    int complete=0;
    float speedSquared,deceleration,distance,pitch;
    qcopy(&target,*path+16+*(int *)(state+0x94)*16);
    func_00282CF0(&delta,&target,object+16);
    if(func_00282DF0(&delta)<(D_L17_001B0344*0.020000001f)*2.0f) {
        (*(int *)(state+0x94))--;
        complete=*(int *)(state+0x94)==-1;
    }
    distance=func_00282E48(object+16,*path+16);
    deceleration=D_L17_001B0348*0.00040000002f;
    speedSquared=*(float *)(state+0x90)* *(float *)(state+0x90);
    if(distance<=speedSquared/(deceleration*2.0f))
        func_002AA2E8(state+0x90,0.0f,speedSquared/(distance*2.0f));
    else func_002AA2E8(state+0x90,D_L17_001B0344*0.020000001f,deceleration);
    func_00282F20(&delta,&delta,*(float *)(state+0x90));
    func_00282CC0(object+16,&delta,object+16);
    pitch=-func_00283248(func_00282E20(&delta),delta.f[2]);
    if(pitch>0.261799425f) pitch=0.261799425f;
    else if(pitch< -0.261799425f) pitch= -0.261799425f;
    func_002AAA00(object+0xf4,pitch,state+0x9c,0,D_L17_001B034C*6.981318e-06f,D_L17_001B034C*6.981318e-06f,0.25132746f);
    func_002AAA00_yaw(object+0xf8,func_00283248(target.f[0]-*(float *)(object+16),target.f[1]-*(float *)(object+20)),state+0x98,D_L17_001B0350*6.981318e-06f,D_L17_001B0350*6.981318e-06f,0.25132746f,0);
    func_002AAA00(object+0xf0,*(float *)(state+0x98)* *(float *)(state+0x90)*D_L17_001B0358,state+0xa0,0,D_L17_001B0354*6.981318e-06f,D_L17_001B0354*6.981318e-06f,0.25132746f);
    if(!complete) {
        if(!func_002E59B0(object,*sound) && D_L17_001DBF82[0]!=255)
            *sound=func_002E5DA0(0,4,object,0x922);
    } else {
        if(*sound!=-1) {
            char *voice=(char *)D_00188660+*sound*0x70;
            if(*(char **)(voice+0x88)==object && ((u8 *)voice)[0x74]) func_002E59F8(*sound);
        }
        *sound=-1;
    }
    return complete;
}

extern float D_L17_001B032C __attribute__((sda));
extern float D_L17_001B0330 __attribute__((sda));
extern float D_L17_001B0334 __attribute__((sda));
extern float D_L17_001B0338 __attribute__((sda));
extern float D_L17_001B033C __attribute__((sda));
extern void func_002AEE70(char *, char *, char *, float, float, float);
extern void func_002AEF28(char *, char *, char *, float, float, float);

/* Re-aims one record's two angle pairs from the level's shared angle words: the 0x118/0x11C
   pair takes 0.000290888245f (arcseconds to radians) times the shared 0x1B0330 word, with the
   record's own 0x12C float as the third argument in the type-3 arm and -1.0f otherwise; the
   0x120/0x124 pair then takes the other two scaled words. */
void func_PAL_L17_003CB0F0(char *arg0)
{
    char *state = *(char **)(arg0 + 0x68);

    if (*(u8 *)(arg0 + 0x20) == 3) {
        func_002AEE70(arg0, state + 0x11C, state + 0x118, D_L17_001B032C,
                      D_L17_001B0330 * 0.0003490659f,
                      *(f32 *)(state + 0x12C));
    } else {
        func_002AEE70(arg0, state + 0x11C, state + 0x118, D_L17_001B032C,
                      D_L17_001B0330 * 0.0003490659f, -1.0f);
    }
    func_002AEF28(arg0, state + 0x120, state + 0x124, D_L17_001B0334,
                  D_L17_001B0338 * 0.0003490659f,
                  D_L17_001B033C * 0.0003490659f);
}
