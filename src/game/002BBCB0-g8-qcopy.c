#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern float g_frame_time_scale;
extern float g_tick_time_scale __attribute__((sda));
extern unsigned char *g_firework_spark_textures[];
typedef struct { float v[4]; int color,endcolor; unsigned char a,c,b,life; float size; } MotionBCB0;
extern int math_random_int_below(int);
extern char *part_alloc(int);
extern int FloatToInt(float);
extern int func_001163B0(void);
extern float math_random_float_range(float,float);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
/* Creates a small firework spark that flies off with some random scatter. It does nothing if there is no life or the screen is too busy. */
char *part_spawn_firework_spark(void *pos,void *velocity,int color,int endcolor,int life,int a,int b,int c,float size,float jitter)
{
    char *particle; MotionBCB0 *motion;
    float scatter[4] __attribute__((aligned(16)));
    float random_dir[4] __attribute__((aligned(16)));
    if(!life) return 0;
    {
        if ((g_frame_time_scale>0.85f || g_tick_time_scale>0.85f) && !math_random_int_below(3)) return 0;
        if ((g_frame_time_scale>0.9f || g_tick_time_scale>0.9f) && !math_random_int_below(2)) return 0;
        if ((g_frame_time_scale>1.0f || g_tick_time_scale>1.0f) && !math_random_int_below(1)) return 0;
    }
    particle=part_alloc(11);
    if(particle) {
        qcopy(particle+16,pos);
        *(int *)(particle+4)=color;
        particle[9]=FloatToInt(4.0f)-96;
        particle[3]=math_random_int_below(100)<20?0x44:0x48;
        particle[1]=0;
        *(float *)(particle+12)=0;
        motion=(MotionBCB0 *)(particle+32);
        particle[8]=func_001163B0();
        particle[2]=g_firework_spark_textures[0][0];
        *(TI128 *)random_dir=0;
        random_dir[0]=math_random_float_range(-1.0f,1.0f);
        random_dir[1]=math_random_float_range(-1.0f,1.0f);
        random_dir[2]=math_random_float_range(-1.0f,1.0f);
        *(TI128 *)scatter=*(TI128 *)random_dir;
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
