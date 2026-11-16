#include "include_asm.h"
#include "names.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
extern float g_twin_puff_height_offset_b __attribute__((sda)),g_twin_puff_direction_length __attribute__((sda));
extern float g_twin_puff_speed_b_min __attribute__((sda)),g_twin_puff_speed_b_max __attribute__((sda));
extern float g_twin_puff_height_offset_a __attribute__((sda)),g_twin_puff_origin_offset __attribute__((sda));
extern float g_twin_puff_speed_a_min __attribute__((sda)),g_twin_puff_speed_a_max __attribute__((sda));
typedef struct { unsigned int colour, field04, field08; unsigned short lifetime, reserved; } EffectParameters16;
extern EffectParameters16 g_twin_puff_params_b __attribute__((sda)),g_twin_puff_params_a __attribute__((sda));
extern char g_camera_l02_position[];
extern void FastVecSub(void *,void *,void *),vec_scale_to_length(void *,void *,float),FastVecAdd(void *,void *,void *),vec_add_random_offset(float *,float);
extern float math_random_float_range(float,float);
extern int math_random_int_below(int);
extern void *part_spawn_object_relative_particle(void *,void *,void *,void *,int);

/* The child consumes five GPR inputs and deliberately returns a pointer. */
void part_spawn_twin_puffs_pal(char *object) {
    Vector velocity,origin,direction;
    int variant;
    velocity.q=0;
    origin.q=*(Quad *)(object+0x10);
    origin.f[2]+=g_twin_puff_height_offset_b;
    FastVecSub(&direction,g_camera_l02_position,&origin);
    direction.f[2]=0.0f;
    vec_scale_to_length(&direction,&direction,g_twin_puff_direction_length);
    FastVecAdd(&origin,&origin,&direction);
    velocity.f[2]=math_random_float_range(g_twin_puff_speed_b_min,g_twin_puff_speed_b_max)*0.020000001f;
    variant=math_random_int_below(2);
    part_spawn_object_relative_particle(object,&origin,&velocity,&g_twin_puff_params_b,variant);
    origin.q=*(Quad *)(object+0x10);
    origin.f[2]+=g_twin_puff_height_offset_a;
    vec_add_random_offset(origin.f,g_twin_puff_origin_offset);
    velocity.f[2]=math_random_float_range(g_twin_puff_speed_a_min,g_twin_puff_speed_a_max)*0.020000001f;
    variant=math_random_int_below(2);
    part_spawn_object_relative_particle(object,&origin,&velocity,&g_twin_puff_params_a,variant);
}
