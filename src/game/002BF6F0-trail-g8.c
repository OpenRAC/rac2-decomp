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
void func_002C7050(char *self) {
    SplitVector saved, motion, random;
    char *p = self + 0x20;
    float ratio, speed;
    int life;
    if (FastDecTimer((short *)(self + 0xA))) {
        func_002B9180(self);
        return;
    }
    ratio = IntToFloat(*(short *)(self+0xA));
    ratio /= IntToFloat(*(short *)(p+0x18));
    *(int *)(self+4) = func_002A9568(*(int *)(p+0x14),*(int *)(p+0x10),ratio);
    FastVecAdd(self+0x10,self+0x10,p);
    *(float *)(p+8) -= *(float *)(p+0xC);
    qcopy(&saved,self+0x10);
    if (*(float *)(self+0x1C) != 0.0f) {
        if (*(float *)(self+0x1C) == 2.0f)
            func_00300190(self+0x10,self+0x10);
        *(float *)(self+0x1C) = 2.0f;
    }
    if (*(short *)(p+0x1A) && (D_001B1688[0]&1)) {
        random.q = 0;
        random.f[0] = func_002A7878(-1.0f,1.0f);
        random.f[1] = func_002A7878(-1.0f,1.0f);
        random.f[2] = func_002A7878(-1.0f,1.0f);
        motion.q = random.q;
        speed = FastVecLength(p);
        vec_scale_to_length(&motion,&motion,speed*func_002A7878(0.15f,0.25f));
        FastVecAdd(&motion,&motion,p);
        FastVecScale(&motion,&motion,func_002A7878(0.75f,0.95f));
        life = func_002A7820(15,30);
        func_002BCB00(self+0x10,&motion,*(int *)(self+4),*(int *)(p+0x14),life,0,*(unsigned char *)(self+2),*(unsigned char *)(self+3),FloatToInt(*(float *)(self+0x1C)),*(float *)(self+0xC));
    } else {
        FastVecScale(p,p,0.96f);
    }
}
