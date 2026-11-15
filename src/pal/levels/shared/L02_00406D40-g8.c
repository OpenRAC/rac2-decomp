#include "include_asm.h"
#include "names.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
extern float D_L02_001B17B8 __attribute__((sda)),D_L02_001B17BC __attribute__((sda));
extern float D_L02_001B17AC __attribute__((sda)),D_L02_001B17B0 __attribute__((sda));
extern float D_L02_001B17B4 __attribute__((sda)),D_L02_001B17A0 __attribute__((sda));
extern float D_L02_001B17A4 __attribute__((sda)),D_L02_001B17A8 __attribute__((sda));
typedef struct { unsigned int colour, field04, field08; unsigned short lifetime, reserved; } EffectParameters16;
extern EffectParameters16 D_L02_001B1790 __attribute__((sda)),D_L02_001B1780 __attribute__((sda));
extern char g_camera_l02_position[];
extern void FastVecSub(void *,void *,void *),vec_scale_to_length(void *,void *,float),FastVecAdd(void *,void *,void *),vec_add_random_offset(float *,float);
extern float math_random_float_range(float,float);
extern int math_random_int_below(int);
extern void *part_spawn_object_relative_particle(void *,void *,void *,void *,int);

/* The child consumes five GPR inputs and deliberately returns a pointer. */
void func_PAL_L02_00406D40(char *object) {
    Vector velocity,origin,direction;
    int variant;
    velocity.q=0;
    origin.q=*(Quad *)(object+0x10);
    origin.f[2]+=D_L02_001B17B8;
    FastVecSub(&direction,g_camera_l02_position,&origin);
    direction.f[2]=0.0f;
    vec_scale_to_length(&direction,&direction,D_L02_001B17BC);
    FastVecAdd(&origin,&origin,&direction);
    velocity.f[2]=math_random_float_range(D_L02_001B17AC,D_L02_001B17B0)*0.020000001f;
    variant=math_random_int_below(2);
    part_spawn_object_relative_particle(object,&origin,&velocity,&D_L02_001B1790,variant);
    origin.q=*(Quad *)(object+0x10);
    origin.f[2]+=D_L02_001B17B4;
    vec_add_random_offset(origin.f,D_L02_001B17A0);
    velocity.f[2]=math_random_float_range(D_L02_001B17A4,D_L02_001B17A8)*0.020000001f;
    variant=math_random_int_below(2);
    part_spawn_object_relative_particle(object,&origin,&velocity,&D_L02_001B1780,variant);
}
