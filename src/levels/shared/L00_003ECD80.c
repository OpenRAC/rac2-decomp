#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vector;
extern char D_L00_001B8DC0[];
extern void func_002A0F48(void *);
typedef struct { char pad[0x2290]; char *camera; int mode; char gap[0x254]; short alternate; } ProjectileOwner;
extern ProjectileOwner D_00189E20;
extern void func_00282D30(char *, char *, float);
extern float func_002A7940(void);
extern char *func_0029EFD0(int);
extern unsigned char D_00139587;
typedef struct { char pad[0x50]; float speed; char rest[0x8C]; } ProjectileTuning;
extern ProjectileTuning D_L00_00262570[];
extern char D_L00_001BF220[];
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern int func_002761F8(void *, void *, int, void *, int);
extern char *func_002AB1F0(void *);
extern void func_002AFFD8(void *, void *, int);
extern void func_003001E0(void *, void *, void *);
extern void func_L00_003EE100(void *);
extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern float func_002A7878(float, float);

/* Allocate a projectile and initialize its position, velocity and random phases. */
/* Creates a homing shot and sets its start place, speed and target. */
char *func_L00_003ECD80(char *position, char *source, char *target)
{
    Vector scratchA,scratchB,scratchC,scratchD;
    char *object = CreateMoby(0xCBB /* moby class 3259 */);
    char *state, *info;
    float speed;
    if (object) {
        *(unsigned char *)(object+0x30) = 255;
        *(short *)(object+0x34) = 256;
        *(short *)(object+0x32) = 255;
        object[0x31] = 1;
        *(char **)(object+0xB8) = source;
        object[0x20] = 0;
        state = *(char **)(object+0x68);
        speed = (*(ProjectileTuning *)(D_00139587 * 224 + (char *)gWeaponTable_L00)).speed * 0.016666667f;
        if (gHeroState.mode==29 && (*(unsigned short *)(gHeroState.camera+0x34)&1)) {
            qcopy(object+0x10,gCameraPosition_L00);
            FastVecScale((char *)&scratchA,gCameraPosition_L00+0x250,-0.5f);
            FastVecAdd(object+0x10,object+0x10,&scratchA);
            FastVecScale((char *)&scratchB,gCameraPosition_L00+0x240,-0.25f);
            FastVecAdd(object+0x10,object+0x10,&scratchB);
            FastVecScale((char *)&scratchC,gCameraPosition_L00+0x230,0.1f);
            FastVecAdd(object+0x10,object+0x10,&scratchC);
            FastVecScale((char *)&scratchD,gCameraPosition_L00+0x230,20.0f);
            FastVecAdd(&scratchD,gCameraPosition_L00,&scratchD);
            if(CollLine(gCameraPosition_L00,&scratchD,0,gHeroState.camera,0)) qcopy(&scratchD,D_L00_001BF220);
            FastVecSub(state+0x20,&scratchD,object+0x10);
            vec_scale_to_length(state+0x20,state+0x20,speed);
        } else {
            if (gHeroState.alternate==1) {
                vec_scale_to_length(state+0x20,source+0xD0,-speed);
                qcopy(object+0x10,position);
            } else {
                if(target) {
                    qcopy(&scratchA,target+0x10);
                    info=GetMobyPrivateValue0(target);
                    if(info) {
                        ComputeViewDirection(target+0x10,&scratchB,1);
                        FastVecScale((char *)&scratchB,(char *)&scratchB,*(float *)(info+0x10));
                        FastVecAdd(&scratchA,&scratchA,&scratchB);
                    }
                    FastVecSub(state+0x20,&scratchA,position);
                    vec_scale_to_length(state+0x20,state+0x20,speed);
                } else vec_scale_to_length(state+0x20,source+0xC0,speed);
                qcopy(object+0x10,position);
            }
        }
        *(float *)(state+0x2C)=speed;
        AddTransformedVectorOrCopy(state+0x20,state+0x20,position);
        PulseObjectAxisScale(object);
        *(int *)(state+0x38)=FloatToInt(20.0f);
        { float duration = IntToFloat(*(int *)(state+0x38));
            *(float *)(state+0x3C)=1.0f/duration; }
        *(float *)(object+0x2C)=*(float *)(*(char **)(object+0x24)+0x24)*6.0f;
        object[0x20]=0;
        *(char **)(state+0x1C)=target;
        if(target) {
            info=GetMobyPrivateValue0(target);
            if(info) *(unsigned short *)(info+0x1E)|=0x80;
        }
        *(float *)(state+0x30)=0.0f;
        *(float *)(state+0x40)=1.0f;
        speed=*(float *)(state+0x30);
        *(float *)(state+0x44)=RandomFloatRange(speed,0.069813177f);
        *(float *)(state+0x48)=RandomFloatRange(speed,0.13962635f);
        *(float *)(state+0x4C)=RandomFloatRange(speed,0.2792527f);
        *(float *)(object+0xF0)=RandomAngle();
        *(float *)(object+0xF4)=RandomAngle();
        *(float *)(object+0xF8)=RandomAngle();
        *(float *)(state+4)=RandomAngle();
        *(float *)(state+8)=RandomAngle();
        *(float *)(state+12)=RandomAngle();
        func_002A0F48(object);
    }
    return object;
}
