#include "common.h"
typedef unsigned int U128 __attribute__((mode(TI)));
typedef union { U128 q; float f[4]; } SplitVector;
extern int func_00282978(short *);
extern void func_002B9180(void *);
extern float func_00283CE0(int);
extern int func_002A9568(int,int,float);
extern void func_00282CC0(void *,void *,void *);
extern void func_00300190(void *,void *);
extern int D_001B1688[] __attribute__((sda));
extern float func_002A7878(float,float);
extern float func_00282DF0(void *);
extern void func_00282F20(void *,void *,float);
extern void func_00282D30(void *,void *,float);
extern int func_002A7820(int,int);
extern int func_00283CF0(float);
extern void func_002BCB00(void *,void *,int,int,int,int,int,int,int,float);
/* Fades a trail particle along its colour ramp and drifts it forward. Now and then it throws off a small spark that flies away. */
void func_002C7050(char *self) {
    SplitVector saved, motion, random;
    char *data = self + 0x20;
    float ratio, speed;
    int life;
    if (FastDecTimer((short *)(self + 0xA))) {
        KillParticle(self);
        return;
    }
    ratio = IntToFloat(*(short *)(self+0xA));
    ratio /= IntToFloat(*(short *)(data+0x18));
    *(int *)(self+4) = ForwardTwoValuesAndAmount(*(int *)(data+0x14),*(int *)(data+0x10),ratio);
    FastVecAdd(self+0x10,self+0x10,data);
    *(float *)(data+8) -= *(float *)(data+0xC);
    qcopy(&saved,self+0x10);
    if (*(float *)(self+0x1C) != 0.0f) {
        if (*(float *)(self+0x1C) == 2.0f)
            TransformVectorOrCopy(self+0x10,self+0x10);
        *(float *)(self+0x1C) = 2.0f;
    }
    if (*(short *)(data+0x1A) && (gGameTime[0]&1)) {
        random.q = 0;
        random.f[0] = RandomFloatRange(-1.0f,1.0f);
        random.f[1] = RandomFloatRange(-1.0f,1.0f);
        random.f[2] = RandomFloatRange(-1.0f,1.0f);
        motion.q = random.q;
        speed = FastVecLength(data);
        vec_scale_to_length(&motion,&motion,speed*RandomFloatRange(0.15f,0.25f));
        FastVecAdd(&motion,&motion,data);
        FastVecScale(&motion,&motion,RandomFloatRange(0.75f,0.95f));
        life = RandomIntRange(15,30);
        SpawnSparkParticle_002BCB00(self+0x10,&motion,*(int *)(self+4),*(int *)(data+0x14),life,0,*(unsigned char *)(self+2),*(unsigned char *)(self+3),FloatToInt(*(float *)(self+0x1C)),*(float *)(self+0xC));
    } else {
        FastVecScale(data,data,0.96f);
    }
}
