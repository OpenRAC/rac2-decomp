/* func_PAL_L00_00340E18, the PAL copy of func_L00_0033EA00: the same C, where rename func_002BCB00 becomes func_PAL_002BD790; scale func_002A7820(15,30). */
#include "common.h"
typedef int EffectQuad __attribute__((mode(TI)));
#define FI(p,o) (*(int *)((char *)(p)+(o)))
#define FF(p,o) (*(float *)((char *)(p)+(o)))
#define FS(p,o) (*(short *)((char *)(p)+(o)))
#define FB(p,o) (*(unsigned char *)((char *)(p)+(o)))
extern int FastDecTimer(short *);
extern void part_kill(void *);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern int math_lerp_int_fraction(int,int,float);
extern void FastVecAdd(void *,void *,void *);
extern void vec_transform_or_copy(char *,char *);
extern float math_random_float_range(float,float);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecScale(void *,void *,float);
extern int math_random_int_range(int,int);
extern void *func_PAL_002BD790(void *,void *,int,int,int,int,int,int,float,int);
extern int g_frame_l00_counter MACRO_ADDR;
void func_PAL_L00_00340E18(char *p)
{
    float old[4], velocity[4], random[4];
    char *q=p+32;
    char *pos;
    char *initial;
    float t, length;
    int life;
    if (FastDecTimer((short *)(p+10))) { part_kill(p); return; }
    initial=p+16;
    t=IntToFloat(FS(p,10));
    t=t/IntToFloat(FS(q,24));
    FI(p,4)=math_lerp_int_fraction(FI(q,20),FI(q,16),t);
    FastVecAdd(initial,initial,q);
    FF(q,8)-=FF(q,12);
    qcopy(old,initial);
    pos=initial;
    if (FF(p,28)!=0.0f) {
        if (FF(p,28)==2.0f) vec_transform_or_copy(pos,pos);
        FF(p,28)=2.0f;
    }
    if (FS(q,26) && (g_frame_l00_counter&1)) {
        *(EffectQuad *)random=0;
        random[0]=math_random_float_range(-1.0f,1.0f);
        random[1]=math_random_float_range(-1.0f,1.0f);
        random[2]=math_random_float_range(-1.0f,1.0f);
        *(EffectQuad *)velocity=*(EffectQuad *)random;
        length=FastVecLength(q);
        vec_scale_to_length(velocity,velocity,length*math_random_float_range(0.15f,0.25f));
        FastVecAdd(velocity,velocity,q);
        FastVecScale(velocity,velocity,math_random_float_range(0.75f,0.95f));
        life=(((int)(math_random_int_range(15,30)) * 5 + 2) / 6);
        func_PAL_002BD790(pos,velocity,FI(p,4),FI(q,20),life,0,FB(p,2),FB(p,3),FF(p,12),FloatToInt(FF(p,28)));
    } else FastVecScale(q,q,0.96f);
}
