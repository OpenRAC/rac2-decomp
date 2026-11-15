#include "names.h"
/* func_PAL_002C7D8C, the PAL copy of func_002C7050: the same C, where rename func_002BCB00 becomes func_PAL_002BD790; scale func_002A7820(15,30). */
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
extern void *func_PAL_002BD790(void *,void *,int,int,int,int,int,int,int,float);
void func_PAL_002C7D8C(char *self) {
    SplitVector saved, motion, random;
    char *p = self + 0x20;
    float ratio, speed;
    int life;
    if (FastDecTimer((short *)(self + 0xA))) {
        part_kill(self);
        return;
    }
    ratio = IntToFloat(*(short *)(self+0xA));
    ratio /= IntToFloat(*(short *)(p+0x18));
    *(int *)(self+4) = moby_forward_two_values_and_amount(*(int *)(p+0x14),*(int *)(p+0x10),ratio);
    FastVecAdd(self+0x10,self+0x10,p);
    *(float *)(p+8) -= *(float *)(p+0xC);
    qcopy(&saved,self+0x10);
    if (*(float *)(self+0x1C) != 0.0f) {
        if (*(float *)(self+0x1C) == 2.0f)
            vec_transform_or_copy(self+0x10,self+0x10);
        *(float *)(self+0x1C) = 2.0f;
    }
    if (*(short *)(p+0x1A) && (g_game_time[0]&1)) {
        random.q = 0;
        random.f[0] = math_random_float_range(-1.0f,1.0f);
        random.f[1] = math_random_float_range(-1.0f,1.0f);
        random.f[2] = math_random_float_range(-1.0f,1.0f);
        motion.q = random.q;
        speed = FastVecLength(p);
        vec_scale_to_length(&motion,&motion,speed*math_random_float_range(0.15f,0.25f));
        FastVecAdd(&motion,&motion,p);
        FastVecScale(&motion,&motion,math_random_float_range(0.75f,0.95f));
        life = (((int)(math_random_int_range(15,30)) * 5 + 2) / 6);
        func_PAL_002BD790(self+0x10,&motion,*(int *)(self+4),*(int *)(p+0x14),life,0,*(unsigned char *)(self+2),*(unsigned char *)(self+3),FloatToInt(*(float *)(self+0x1C)),*(float *)(self+0xC));
    } else {
        FastVecScale(p,p,0.96f);
    }
}
