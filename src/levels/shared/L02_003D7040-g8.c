#include "include_asm.h"
#include "names.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;

extern int g_puff_skip_chance __attribute__((sda));
extern float g_puff_height_offset __attribute__((sda)),g_puff_direction_length __attribute__((sda));
extern float g_puff_origin_jitter __attribute__((sda)),g_puff_speed_min __attribute__((sda)),g_puff_speed_max __attribute__((sda));
/* Six-word parameter record, verified in retail and read through +0x14. */
typedef struct { void *colours; void *sizes; void *lifetimes; int kind; int count; float acceleration; } EffectParameters24;
extern EffectParameters24 g_puff_spawn_record __attribute__((sda));
extern char g_camera_l02_position[];
extern int math_random_int_below(int);
extern void vec_clear_128(Quad *),FastVecAdd(void *,void *,void *),FastVecSub(void *,void *,void *),vec_scale_to_length(void *,void *,float),vec_add_random_offset(float *,float);
extern float math_random_float_range(float,float);
extern void *enemy_spawn_record(void *,void *,void *,void *,int);
/* Sometimes spawns a small puff effect near the object, drifting upward. */
void part_spawn_puff_at_moby(char *object) {
    Vector velocity,origin,direction;
    float speed;
    int variant;
    if (math_random_int_below(g_puff_skip_chance)) return;
    velocity.q=0;
    vec_clear_128(&origin.q);
    FastVecAdd(&origin,&origin,object+0x10);
    origin.f[3]=0.0f;
    origin.f[2]+=g_puff_height_offset;
    FastVecSub(&direction,g_camera_l02_position,&origin);
    direction.f[2]=0.0f;
    vec_scale_to_length(&direction,&direction,g_puff_direction_length);
    FastVecAdd(&origin,&origin,&direction);
    vec_add_random_offset(origin.f,g_puff_origin_jitter);
    speed=math_random_float_range(g_puff_speed_min,g_puff_speed_max);
    velocity.f[2]=speed*0.0166666675f;
    variant=math_random_int_below(2);
    enemy_spawn_record(&origin,&velocity,&g_puff_spawn_record,(void *)variant,1);
}
