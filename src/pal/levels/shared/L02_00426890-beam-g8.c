/* func_PAL_L02_00426890, the PAL copy of func_L02_00421860: the same C, where the particles' 60 becomes 50, the
 * state counter's 16 and 15 become 13 and 12, and D_L02_001B1FB8 is scaled by 1.44f (1.2f squared) for 50 Hz. */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
typedef struct { Vector direction; u8 *source; u32 mask; u8 kind,enabled; u16 type; float strength; int mode; } ImpactInfo;
typedef struct { Vector previous,normal,start; ImpactInfo impact; } BeamQuery;
typedef struct { u8 reserved[0x18]; u8 *other; u32 reserved1c; Vector position; } HitView;
extern HitView g_collision_l02_result __attribute__((nosda));
extern float g_impact_size_min __attribute__((sda)),g_impact_size_max __attribute__((sda));
extern float g_ground_effect_last_arg __attribute__((sda));
extern u32 g_ground_effect_color_a __attribute__((sda)),g_ground_effect_color_b __attribute__((sda));
extern void cam_compute_view_direction(void *,void *,int);
extern void FastVecAdd(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern int CollLine(void *,void *,int,void *,int);
extern int PlayMobySound(int,int,void *);
extern void part_spawn_impact_particles_pal(void *,int,int);
extern void part_spawn_spark_ring_burst_pal(u8 *,void *);
extern void part_init_effect_record(char *,int,int,float);
extern int coll_process_hit(void *,int,void *,void *,float);
extern int math_fast_float_d(int *);
extern float math_random_float_range(float,float);
extern int math_random_int_below(int);
extern float IntToFloat(int);
extern int func_001163B0(void);
extern u8 *part_spawn_ground_effect(void *,int,u32,float,float,int,int,void *,int,float);
extern void moby_mark_spawned(void *);
extern void moby_update_spinning_frame_orientation_pal(u8 *);

/* Move and test the beam endpoint, then emit its fading or impact particles.
 * The interleaved particle arguments preserve the EE integer/FP register banks. */
void beam_update_endpoint_and_particles_pal(u8 *object)
{
    BeamQuery query;
    ImpactInfo impact;
    u8 *state=*(u8 **)(object+0x68);

    qcopy(&query.previous,object+0x10);
    cam_compute_view_direction(object+0x10,&query.normal,1);
    qcopy(&query.start,object+0x10);
    if(object[0x20]==0) {
        FastVecAdd(object+0x10,object+0x10,state+0x40);
        query.impact.source=object;
        query.impact.mask=0x10000;
        query.impact.strength=*(float *)(state+0x64);
        query.impact.mode=1;
        qcopy(&query.impact.direction,state+0x40);
        vec_scale_to_length(&query.impact.direction,&query.impact.direction,1.0f);
        query.impact.direction.f[3]=5627.9248046875f;
        query.impact.kind=1;
        query.impact.enabled=1;
        query.impact.type=*(u16 *)(object+0xAA);
        if(CollLine(&query.start,object+0x10,0,object,0) && g_collision_l02_result.other!=*(u8 **)(state+0x50)) {
            PlayMobySound(0,0,object);
            if(!g_collision_l02_result.other) part_spawn_impact_particles_pal(&g_collision_l02_result.position,5,0);
            else if(*(int *)(g_collision_l02_result.other+0x98)) part_spawn_impact_particles_pal(&g_collision_l02_result.position,10,1);
            part_spawn_spark_ring_burst_pal(object,&g_collision_l02_result.position);
            part_init_effect_record((char *)&impact,(int)object,0x810001,*(float *)(state+0x64));
            impact.kind=2;impact.enabled=1;
            impact.type=*(u16 *)(*(u8 **)(state+0x50)+0xAA);
            coll_process_hit(&g_collision_l02_result.position,16,object,&impact,0.8f);
            moby_mark_spawned(object);
            return;
        }
    }
    if(math_fast_float_d((int *)(state+0x58))) {
        u8 *position=object+0x10;
        float size;
        int sign,left;
        size=math_random_float_range(g_impact_size_min,g_impact_size_max);
        sign=math_random_int_below(2);if(sign==0)sign--;
        left=4;
        do {
            query.impact.direction.f[2]=math_random_float_range(-1.0f,1.0f);
            query.impact.direction.f[1]=math_random_float_range(-1.0f,1.0f);
            query.impact.direction.f[0]=math_random_float_range(-1.0f,1.0f);
            vec_scale_to_length(&query.impact.direction,&query.impact.direction,0.025f);
            query.impact.direction.f[2]=math_random_float_range(0,0.1f);
            {
                float rate=g_ground_effect_last_arg*1.44f;
                float scale=0.35f;
                u32 texture=g_ground_effect_color_a;
                part_spawn_ground_effect(position,50,texture,size*scale,size,0,sign,&query.impact.direction,0,rate);
            }
            part_spawn_ground_effect(position,50,g_ground_effect_color_b,size*0.245f,size*0.7f,1,sign,&query.impact.direction,0,g_ground_effect_last_arg*1.44f);
            sign=-sign;
        } while(--left>=0);
        moby_mark_spawned(object);
        return;
    }
    if(*(int *)(state+0x58)<13) {
        *(float *)(state+0x60)=IntToFloat(*(int *)(state+0x58))/IntToFloat(12);
        if(func_001163B0()%3==0) {
            int sign;
            float size;
            sign=math_random_int_below(2);if(sign==0)sign--;
            size=math_random_float_range(g_impact_size_min,g_impact_size_max);
            query.impact.direction.f[2]=math_random_float_range(-1.0f,1.0f);
            query.impact.direction.f[1]=math_random_float_range(-1.0f,1.0f);
            query.impact.direction.f[0]=math_random_float_range(-1.0f,1.0f);
            vec_scale_to_length(&query.impact.direction,&query.impact.direction,0.025f);
            part_spawn_ground_effect(object+0x10,50,g_ground_effect_color_a,size*0.05f,size,0,sign,&query.impact.direction,0,g_ground_effect_last_arg*1.44f);
            part_spawn_ground_effect(object+0x10,50,g_ground_effect_color_b,size*0.0035f,size*0.035f,1,sign,&query.impact.direction,0,g_ground_effect_last_arg*1.44f);
        }
    }
    if(*(float *)(object+0x10)<2.0f || *(float *)(object+0x10)>1021.0f ||
       *(float *)(object+0x14)<2.0f || *(float *)(object+0x14)>1021.0f ||
       *(float *)(object+0x18)<2.0f || *(float *)(object+0x18)>1021.0f) moby_mark_spawned(object);
    else moby_update_spinning_frame_orientation_pal(object);
}
