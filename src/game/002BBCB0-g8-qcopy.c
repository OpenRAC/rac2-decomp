#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern float D_001B168C;
extern float D_001B1690 __attribute__((sda));
extern unsigned char *D_001F256C[];
typedef struct { float v[4]; int color,endcolor; unsigned char a,c,b,life; float size; } MotionBCB0;
extern int func_002A77E0(int);
extern char *func_002B9030(int);
extern int func_00283CF0(float);
extern int func_001163B0(void);
extern float func_002A7878(float,float);
extern void func_00282F20(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
/* Creates a small firework spark that flies off with some random scatter. It does nothing if there is no life or the screen is too busy. */
char *func_002BBCB0(void *pos,void *velocity,int color,int endcolor,int life,int a,int b,int c,float size,float jitter)
{
    char *particle; MotionBCB0 *motion;
    float scatter[4] __attribute__((aligned(16)));
    float randomDir[4] __attribute__((aligned(16)));
    if(!life) return 0;
    {
        if ((D_001B168C>0.85f || D_001B1690>0.85f) && !RandomIntBelow(3)) return 0;
        if ((D_001B168C>0.9f || D_001B1690>0.9f) && !RandomIntBelow(2)) return 0;
        if ((D_001B168C>1.0f || D_001B1690>1.0f) && !RandomIntBelow(1)) return 0;
    }
    particle=AllocParticle(11);
    if(particle) {
        qcopy(particle+16,pos);
        *(int *)(particle+4)=color;
        particle[9]=FloatToInt(4.0f)-96;
        particle[3]=RandomIntBelow(100)<20?0x44:0x48;
        particle[1]=0;
        *(float *)(particle+12)=0;
        motion=(MotionBCB0 *)(particle+32);
        particle[8]=Rand();
        particle[2]=D_001F256C[0][0];
        *(TI128 *)randomDir=0;
        randomDir[0]=RandomFloatRange(-1.0f,1.0f);
        randomDir[1]=RandomFloatRange(-1.0f,1.0f);
        randomDir[2]=RandomFloatRange(-1.0f,1.0f);
        *(TI128 *)scatter=*(TI128 *)randomDir;
        vec_scale_to_length(scatter,scatter,jitter);
        FastVecAdd(motion,velocity,scatter);
        motion->v[3]=jitter*0.75f;
        *(short *)(particle+10)=life;
        motion->life=life;motion->a=a;
        motion->size=size;
        motion->color=color;motion->endcolor=endcolor;
        motion->b=b;motion->c=c;
    }
    return particle;
}
