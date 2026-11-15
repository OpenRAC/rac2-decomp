#include "include_asm.h"
#include "names.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
extern int D_L02_001B03DC __attribute__((sda));
extern float D_L02_001B03D4 __attribute__((sda)),D_L02_001B03D8 __attribute__((sda));
extern float D_L02_001B03C8 __attribute__((sda)),D_L02_001B03CC __attribute__((sda)),D_L02_001B03D0 __attribute__((sda));
typedef struct { void *colours; void *sizes; void *lifetimes; int kind; int count; float acceleration; } EffectParameters24;
extern EffectParameters24 D_L02_001B03B0 __attribute__((sda));
extern char g_camera_l02_position[];
extern int math_random_int_below(int);
extern void vec_clear_128(Quad *),FastVecAdd(void *,void *,void *),FastVecSub(void *,void *,void *),vec_scale_to_length(void *,void *,float),vec_add_random_offset(float *,float);
extern float math_random_float_range(float,float);
extern void *enemy_spawn_record(void *,void *,void *,void *,int);

void func_PAL_L02_003DB148(char *object) {
    Vector velocity,origin,direction;
    float speed;
    int variant;
    if (math_random_int_below(D_L02_001B03DC)) return;
    velocity.q=0;
    vec_clear_128(&origin.q);
    FastVecAdd(&origin,&origin,object+0x10);
    origin.f[3]=0.0f;
    origin.f[2]+=D_L02_001B03D4;
    FastVecSub(&direction,g_camera_l02_position,&origin);
    direction.f[2]=0.0f;
    vec_scale_to_length(&direction,&direction,D_L02_001B03D8);
    FastVecAdd(&origin,&origin,&direction);
    vec_add_random_offset(origin.f,D_L02_001B03C8);
    speed=math_random_float_range(D_L02_001B03CC,D_L02_001B03D0);
    velocity.f[2]=speed*0.020000001f;
    variant=math_random_int_below(2);
    enemy_spawn_record(&origin,&velocity,&D_L02_001B03B0,(void *)variant,1);
}
