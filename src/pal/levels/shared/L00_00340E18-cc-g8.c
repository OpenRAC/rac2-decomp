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
extern void *part_spawn_spark_pal(void *,void *,int,int,int,int,int,int,float,int);
extern int g_frame_l00_counter MACRO_ADDR;
/* Updates a spark shedder: fades it and, every other frame, sheds a new spark (PAL). */
void part_update_spark_shedder_pal(char *particle)
{
    float old[4], velocity[4], random[4];
    char *motion=particle+32;
    char *pos;
    char *initial;
    float fraction, length;
    int life;
    if (FastDecTimer((short *)(particle+10))) { part_kill(particle); return; }
    initial=particle+16;
    fraction=IntToFloat(FS(particle,10));
    fraction=fraction/IntToFloat(FS(motion,24));
    FI(particle,4)=math_lerp_int_fraction(FI(motion,20),FI(motion,16),fraction);
    FastVecAdd(initial,initial,motion);
    FF(motion,8)-=FF(motion,12);
    qcopy(old,initial);
    pos=initial;
    if (FF(particle,28)!=0.0f) {
        if (FF(particle,28)==2.0f) vec_transform_or_copy(pos,pos);
        FF(particle,28)=2.0f;
    }
    if (FS(motion,26) && (g_frame_l00_counter&1)) {
        *(EffectQuad *)random=0;
        random[0]=math_random_float_range(-1.0f,1.0f);
        random[1]=math_random_float_range(-1.0f,1.0f);
        random[2]=math_random_float_range(-1.0f,1.0f);
        *(EffectQuad *)velocity=*(EffectQuad *)random;
        length=FastVecLength(motion);
        vec_scale_to_length(velocity,velocity,length*math_random_float_range(0.15f,0.25f));
        FastVecAdd(velocity,velocity,motion);
        FastVecScale(velocity,velocity,math_random_float_range(0.75f,0.95f));
        life=(((int)(math_random_int_range(15,30)) * 5 + 2) / 6);
        part_spawn_spark_pal(pos,velocity,FI(particle,4),FI(motion,20),life,0,FB(particle,2),FB(particle,3),FF(particle,12),FloatToInt(FF(particle,28)));
    } else FastVecScale(motion,motion,0.96f);
}
