/* func_PAL_L11_0045ED20, the PAL copy of func_L11_004590F0: the same C, where particle lifetime 60 becomes 50,
 * the fade length 16 and 15 becomes 13 and 12, and the particles' last argument is scaled by 1.44. */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
typedef struct { Vector direction; u8 *source; u32 mask; u8 kind,enabled; u16 type; float strength; int mode; } ImpactInfo;
typedef struct { Vector previous,normal,start; ImpactInfo impact; } BeamQuery;
typedef struct { u8 reserved[0x18]; u8 *other; u32 reserved1c; Vector position; } HitView;
extern HitView g_collision_l11_result __attribute__((nosda));
extern float g_effect_size_min __attribute__((sda)),g_effect_size_max __attribute__((sda));
extern float g_ground_effect_param __attribute__((sda));
extern u32 g_ground_effect_kind_a __attribute__((sda)),g_ground_effect_kind_b __attribute__((sda));
extern void cam_compute_view_direction(void *,void *,int);
extern void FastVecAdd(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern int CollLine(void *,void *,int,void *,int);
extern void part_spray_smoke_and_sparks_pal(void *,int,int);
extern void part_init_effect_record(char *,int,int,float);
extern int coll_process_hit(void *,int,void *,void *,float);
extern int math_fast_float_d(int *);
extern float math_random_float_range(float,float);
extern int math_random_int_below(int);
extern float IntToFloat(int);
extern int func_001163B0(void);
extern u8 *part_spawn_ground_effect(void *,int,u32,float,float,int,int,void *,int,float);
extern void moby_mark_spawned(void *);
extern void joba_effect_prepare_offsets_pal(u8 *);

/* Move and test the beam endpoint, then emit its fading or impact particles.
 * The interleaved particle arguments preserve the EE integer/FP register banks. */
void beam_shot_update_pal(u8 *moby)
{
    BeamQuery query;
    ImpactInfo impact;
    u8 *vars=*(u8 **)(moby+0x68);

    qcopy(&query.previous,moby+0x10);
    cam_compute_view_direction(moby+0x10,&query.normal,1);
    qcopy(&query.start,moby+0x10);
    if(moby[0x20]==0) {
        FastVecAdd(moby+0x10,moby+0x10,vars+0x40);
        query.impact.source=moby;
        query.impact.mask=0x10001;
        query.impact.strength=*(float *)(vars+0x64);
        query.impact.mode=1;
        qcopy(&query.impact.direction,vars+0x40);
        vec_scale_to_length(&query.impact.direction,&query.impact.direction,1.0f);
        query.impact.direction.f[3]=5627.9248046875f;
        query.impact.kind=1;
        query.impact.enabled=1;
        query.impact.type=*(u16 *)(moby+0xAA);
        if(CollLine(&query.start,moby+0x10,0,moby,0)) {
            int same=0;
            if(g_collision_l11_result.other && *(u8 **)(vars+0x50))
                if(*(s16 *)(g_collision_l11_result.other+0xAA)==*(s16 *)(*(u8 **)(vars+0x50)+0xAA)) same=1;
            if(!same) {
            if(!g_collision_l11_result.other) part_spray_smoke_and_sparks_pal(&g_collision_l11_result.position,1,0);
            else if(*(int *)(g_collision_l11_result.other+0x98)) part_spray_smoke_and_sparks_pal(&g_collision_l11_result.position,1,1);
            part_init_effect_record((char *)&impact,(int)moby,0x810001,*(float *)(vars+0x64));
            impact.kind=2;impact.enabled=1;
            impact.type=*(u16 *)(*(u8 **)(vars+0x50)+0xAA);
            coll_process_hit(&g_collision_l11_result.position,16,moby,&impact,0.2f);
            moby_mark_spawned(moby);
            return;
            }
        }
    }
    if(math_fast_float_d((int *)(vars+0x58))) {
        u8 *position=moby+0x10;
        float size;
        int sign,left;
        float value,inner_scale,rate_scale;
        size=math_random_float_range(g_effect_size_min,g_effect_size_max);
        sign=math_random_int_below(2);if(sign==0)sign--;
        left=4;
        do {
            query.impact.direction.f[2]=math_random_float_range(-1.0f,1.0f);
            query.impact.direction.f[1]=math_random_float_range(-1.0f,1.0f);
            query.impact.direction.f[0]=math_random_float_range(-1.0f,1.0f);
            vec_scale_to_length(&query.impact.direction,&query.impact.direction,0.025f);
            rate_scale=1.44f;
            inner_scale=0.35f;
            value=math_random_float_range(0,0.1f);
            query.impact.direction.f[2]=value;
            part_spawn_ground_effect(position,50,g_ground_effect_kind_a,size*inner_scale,size,0,sign,&query.impact.direction,0,g_ground_effect_param*rate_scale);
            value=0.7f;
            part_spawn_ground_effect(position,50,g_ground_effect_kind_b,size*0.245f,size*value,1,sign,&query.impact.direction,0,g_ground_effect_param*rate_scale);
            sign=-sign;
        } while(--left>=0);
        moby_mark_spawned(moby);
        return;
    }
    if(*(int *)(vars+0x58)<13) {
        *(float *)(vars+0x60)=IntToFloat(*(int *)(vars+0x58))/IntToFloat(12);
        if(func_001163B0()%3==0) {
            int sign;
            float size;
            sign=math_random_int_below(2);if(sign==0)sign--;
            size=math_random_float_range(g_effect_size_min,g_effect_size_max);
            query.impact.direction.f[2]=math_random_float_range(-1.0f,1.0f);
            query.impact.direction.f[1]=math_random_float_range(-1.0f,1.0f);
            query.impact.direction.f[0]=math_random_float_range(-1.0f,1.0f);
            vec_scale_to_length(&query.impact.direction,&query.impact.direction,0.025f);
            part_spawn_ground_effect(moby+0x10,50,g_ground_effect_kind_a,size*0.05f,size,0,sign,&query.impact.direction,0,g_ground_effect_param*1.44f);
            part_spawn_ground_effect(moby+0x10,50,g_ground_effect_kind_b,size*0.0035f,size*0.035f,1,sign,&query.impact.direction,0,g_ground_effect_param*1.44f);
        }
    }
    if(*(float *)(moby+0x10)<2.0f || *(float *)(moby+0x10)>1021.0f ||
       *(float *)(moby+0x14)<2.0f || *(float *)(moby+0x14)>1021.0f ||
       *(float *)(moby+0x18)<2.0f || *(float *)(moby+0x18)>1021.0f) moby_mark_spawned(moby);
    else joba_effect_prepare_offsets_pal(moby);
}
