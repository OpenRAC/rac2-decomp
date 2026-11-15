#include "common.h"
typedef unsigned int U128 __attribute__((mode(TI)));
typedef union { U128 q; float f[4]; } SplitVector;
extern int FastDecTimer(short *);
extern void part_kill(void *);
extern float IntToFloat(int);
extern int moby_forward_two_values_and_amount(int,int,float);
extern void FastVecAdd(void *,void *,void *);
extern void vec_transform_or_copy(void *,void *);
extern int g_game_time[] __attribute__((sda));
extern float math_random_float_range(float,float);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecScale(void *,void *,float);
extern int math_random_int_range(int,int);
extern int FloatToInt(float);
extern void part_spawn_spark(void *,void *,int,int,int,int,int,int,int,float);
/* Fades a trail particle along its colour ramp and drifts it forward. Now and then it throws off a small spark that flies away. */
void UpdateParticleTrail(char *self) {
    SplitVector saved, motion, random;
    char *data = self + 0x20;
    float ratio, speed;
    int life;
    if (FastDecTimer((short *)(self + 0xA))) {
        part_kill(self);
        return;
    }
    ratio = IntToFloat(*(short *)(self+0xA));
    ratio /= IntToFloat(*(short *)(data+0x18));
    *(int *)(self+4) = moby_forward_two_values_and_amount(*(int *)(data+0x14),*(int *)(data+0x10),ratio);
    FastVecAdd(self+0x10,self+0x10,data);
    *(float *)(data+8) -= *(float *)(data+0xC);
    qcopy(&saved,self+0x10);
    if (*(float *)(self+0x1C) != 0.0f) {
        if (*(float *)(self+0x1C) == 2.0f)
            vec_transform_or_copy(self+0x10,self+0x10);
        *(float *)(self+0x1C) = 2.0f;
    }
    if (*(short *)(data+0x1A) && (g_game_time[0]&1)) {
        random.q = 0;
        random.f[0] = math_random_float_range(-1.0f,1.0f);
        random.f[1] = math_random_float_range(-1.0f,1.0f);
        random.f[2] = math_random_float_range(-1.0f,1.0f);
        motion.q = random.q;
        speed = FastVecLength(data);
        vec_scale_to_length(&motion,&motion,speed*math_random_float_range(0.15f,0.25f));
        FastVecAdd(&motion,&motion,data);
        FastVecScale(&motion,&motion,math_random_float_range(0.75f,0.95f));
        life = math_random_int_range(15,30);
        part_spawn_spark(self+0x10,&motion,*(int *)(self+4),*(int *)(data+0x14),life,0,*(unsigned char *)(self+2),*(unsigned char *)(self+3),FloatToInt(*(float *)(self+0x1C)),*(float *)(self+0xC));
    } else {
        FastVecScale(data,data,0.96f);
    }
}
