#include "include_asm.h"

#include "common.h"
extern void func_002E6EF8(void (*f)(char *), char *arg);
extern char *blue_explosion_spawn_pal(void *pos, int a, int b, int c, int d, int e, int f, int g, int h,
                              int k, float scale);
extern float math_random_float_range(float lo, float hi);
extern float math_random_angle(void);
extern float math_random_signed_float_range(float a, float b);
extern int math_random_int_range(int lo, int hi);
extern void vec_build_spherical_offset(void *out, float x, float y, float z);
extern void FastVecSub(void *out, void *a, void *b);
extern void FastVecAdd(void *out, void *a, void *b);
extern void vec_scale_to_length(void *out, void *a, float scale);
extern void *part_spawn_spinning_particle_pal(void *pos, void *velocity, float speed, float size,
                              unsigned int colour, unsigned int colour2, int life, int a, int b,
                              int c, int d);
extern char g_camera_l00_position[];

/* one func_PAL_L00_0041D8A8 effect at pos, then two func_PAL_L00_00340CA0 particles with random
   velocities; before each, pos moves 0.3 of the way towards D_L00_001B8DC0 (FastVecSub,
   scale, FastVecAdd) */
void sheep_shot_spawn_hit_sparks_pal(float *pos, int unused, int mode)
{
    float velocity[4], offset[4], point[4];
    float pitch, heading, speed;
    int i;

    blue_explosion_spawn_pal(pos, 0, 15, 10, 0, 20, 0, 0, 1, 0, 0.1f);
    for (i = 0; i < 2; i++) {
        pitch = math_random_float_range(-0.9599312f, -1.3962636f);
        heading = math_random_angle();
        speed = math_random_float_range(0.0f, 0.5f);
        vec_build_spherical_offset(velocity, speed * 0.020000001f, heading, pitch);
        FastVecSub(offset, g_camera_l00_position, pos);
        vec_scale_to_length(offset, offset, 0.3f);
        FastVecAdd(pos, pos, offset);
        speed = math_random_float_range(25000.0f, 50000.0f);
        point[0] = pos[0] + math_random_signed_float_range(0.0f, 0.02f);
        point[1] = pos[1] + math_random_signed_float_range(0.0f, 0.02f);
        point[2] = pos[2] + math_random_signed_float_range(0.0f, 0.02f);
        if (mode)
            part_spawn_spinning_particle_pal(point, velocity, speed, 0.1f, 0x78ffffff, 0x101e1e1e,
                              math_random_int_range(8, 17), 1, 1, -1, 1);
        else
            part_spawn_spinning_particle_pal(point, velocity, speed, 0.1f, 0x78ffffff, 0x101e1e1e,
                              math_random_int_range(21, 50), 1, 1, -1, 1);
    }
}


typedef int TI128 __attribute__((mode(TI)));
extern void FastVecAdd(void *,void *,void *),vec_transform_or_copy(char *,char *);
extern void part_steer_effect_direction(int,int *,int),table_clear_entry_flag(int),moby_mark_spawned(char *);
extern void ref_L00_004045E8_00(void (*)(char *),char *);
extern void shop_trigger_current_state_effect(void *,void *),vec_add_object_direction_scaled(void *,void *,float);
extern void shot_handle_impact(void *,void *),part_spawn_spark_trail_between_points_pal(void *,void *,void *),shot_draw_glow_sparks(char *);
extern char *explosion_spawn_pal(void *,float,int,int,int,int,int,int,int,int,int);
extern int coll_process_hit(void *,int,void *,int,float);
extern char *g_area_hit_targets[];
extern char g_item_slot_to_record[],g_weapon_l00_table[],g_light_table[];
extern void FastVecSub(void *,void *,void *),vec_scale_to_length(void *,void *,float);
extern void make_hit_descriptor(void *,void *,float,int,void *),QueueMobyImpact(void *,void *);
extern void gfx_free_point_light(int);
extern int StartAttachedEffect_pal(void *,int,int);
extern int part_l00_alloc_effect_slot_2(void *,float,float,float,float,float);

/* Moves a projectile, applies its explosion hit to nearby objects, and updates
 * its persistent trail record while active. */
void UpdateExplodingTrailProjectile_pal(char *moby)
{
    float old[4],delta[4];
    char hit[48] __attribute__((aligned(16)));
    char *ctx=*(char **)(moby+104);
    int hit_count, count, boosted;
    char **objects;
    char *target,*light,*weapon;
    float force;
    switch (*(unsigned char *)(moby+32)) {
    case 0:
        *(int *)(ctx+24)=-1;
        *(unsigned char *)(moby+32)=1;
        *(float *)(ctx+28)=math_random_angle();
        break;
    case 1:
        qcopy(old,moby+16);
        FastVecAdd(moby+16,(int *)ctx,moby+16);
        vec_transform_or_copy(moby+16,moby+16);
        shop_trigger_current_state_effect(ctx,ctx);
        part_steer_effect_direction(*(int *)(ctx+48),(int *)ctx,0);
        vec_add_object_direction_scaled(moby+16,ctx,0.0012f);
        shot_handle_impact(moby,old);
        if (*(float *)(moby+16)<2.0f || *(float *)(moby+16)>1021.0f ||
            *(float *)(moby+20)<2.0f || *(float *)(moby+20)>1021.0f ||
            *(float *)(moby+24)<2.0f || *(float *)(moby+24)>1021.0f) {
            table_clear_entry_flag(*(int *)(ctx+48));
            moby_mark_spawned(moby);
            return;
        }
        break;
    case 2:
        explosion_spawn_pal(moby+16,0.5f,1,50,40,40,40,90,1,1,1);
        hit_count=coll_process_hit(moby+16,0,moby,0,3.0f);
        if(hit_count>0) {
            objects=g_area_hit_targets;
            count=hit_count;
            do {
                target=*objects;
                if (*(short *)(*(char **)(target+36)+70)==5 || (*(unsigned short *)(target+52)&0x4000)) {
                    FastVecSub(delta,target+16,moby+16);
                    vec_scale_to_length(delta,delta,1.0f);
                    vec_scale_to_length(hit,hit,1.0f);
                    force=10.0f;
                    weapon=g_weapon_l00_table+224*(unsigned char)g_item_slot_to_record[32];
                    boosted=*(int *)weapon && (unsigned char)weapon[4]==3;
                    if(boosted) force=20.0f;
                    make_hit_descriptor(hit,moby,force,0x810000,delta);
                    *(TI128 *)(hit)=*(TI128 *)(delta);
                    *(float *)(hit+12)=5627.9248046875f;
                    hit[25]=3; *(int *)(hit+32)=1; hit[24]=5;
                    *(unsigned short *)(hit+26)=*(unsigned short *)(target+170);
                    QueueMobyImpact(target,hit);
                    StartAttachedEffect_pal(target,78,*(int *)(*(char **)(ctx+52)+184));
                }
                objects++;
            } while(--count);
        }
        if (*(int *)(ctx+24)!=-1) gfx_free_point_light(*(int *)(ctx+24));
        *(int *)(ctx+24)=-1;
        /* Fall through to the shared teardown. */
    case 3:
        table_clear_entry_flag(*(int *)(ctx+48));
        moby_mark_spawned(moby);
        return;
    }
    ref_L00_004045E8_00(shot_draw_glow_sparks,moby);
    *(TI128 *)(delta)=*(TI128 *)(moby+16);
    part_spawn_spark_trail_between_points_pal(moby,delta,old);
    FastVecAdd((char *)delta,moby+16,ctx+32);
    FastVecAdd(hit,(char *)old,ctx+32);
    part_spawn_spark_trail_between_points_pal(moby,delta,hit);
    if (*(int *)(ctx+24)==-1)
        *(int *)(ctx+24)=part_l00_alloc_effect_slot_2(moby+16,5.0f,0.0f,1.0f,0.8f,0.25f);
    else {
        light=g_light_table+32**(int *)(ctx+24);
        qcopy(light+16,moby+16);
        *(float *)(light+24)+=1.0f;
        *(float *)(light+28)=5.0f;
        *(float *)light=1.0f; *(float *)(light+4)=0.8f;
        *(float *)(light+8)=0.25f; *(int *)(light+12)=0;
    }
}

