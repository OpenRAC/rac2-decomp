#include "names.h"
/* func_PAL_L08_003D1A30, the PAL copy of func_L08_003CDB78: the same C, where rename func_002ABBB8 becomes func_PAL_002AC718; rename func_L08_002D2ED8 becomes func_PAL_L08_002D3078; rename func_002A7470 becomes func_PAL_002A7E68; rename func_L00_002D2168 becomes func_PAL_L00_002D2668. */
#include "common.h"
typedef int ContactQuad __attribute__((mode(TI)));
typedef union { ContactQuad q; float f[4]; } ContactVector;
typedef struct { char pad[0x2290]; void *collision; char gap[0x24CC-0x2294]; int contact; } ContactHero;
extern ContactHero g_hero_state;
extern char g_collision_l08_hit_point[], g_str_effect_name[] MACRO_ADDR;
typedef struct { char pad[0x10]; ContactQuad position; char tail[0xE0]; } ContactEntry;
extern ContactEntry *g_moby_array __attribute__((sda));
extern float g_vehicle_bounce_scale_b __attribute__((sda)), g_vehicle_bounce_scale_a __attribute__((sda));
extern float g_vehicle_collision_probe_z __attribute__((sda));
extern float g_vehicle_collision_velocity_scale __attribute__((sda)), g_vehicle_fall_speed __attribute__((sda));
extern float g_vehicle_saved_x MACRO_ADDR, g_vehicle_saved_y MACRO_ADDR;
extern float g_vehicle_collision_x MACRO_ADDR, g_vehicle_collision_y MACRO_ADDR;
extern int g_current_map_index;
extern void vec_scale_to_length(void *,void *,float),FastVecAdd(void *,void *,void *);
extern int coll_test_point(void *,int,float,void *);
extern void moby_transform_joint_to_world(void *,int,void *);
extern int CollLine(void *,void *,int,void *,void *);
extern float fast_vec_dist(void *,void *);
extern void FastVecSub(void *,void *,void *),vec_fast_normalize(void *,void *,void *);
extern void FastVecScale(void *,void *,float);
extern void SpawnExplosionEffects_pal(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
extern int snd_play_from_class_bank(int,int,void *,int),GetCollHitMaterial(void);
extern int hero_l08_enter_state_pal(int,int);
extern void anim_start_blended_pal(void *,int,int,int),moby_set_state(void *,int,int);
extern void moby_place_at_stored_transform(void *),set_hero_animation_pal(int,int,float);

/* Resolve the movement probes and update the D_L08_001BFF60 response. */
int vehicle_handle_collision_pal(char *object, void *previous)
{
    ContactVector temporary, point;
    char *state=*(char **)(object+0x68);
    int hit,index,result;
    float whole,part,drop;
    ContactHero *hero=&g_hero_state;

    vec_scale_to_length(&temporary,object+0xC0,g_vehicle_bounce_scale_b);
    FastVecAdd(&point,&temporary,object+0x10);
    vec_scale_to_length(&temporary,object+0xE0,g_vehicle_bounce_scale_a);
    FastVecAdd(&point,&point,&temporary);
    hit=coll_test_point(&point,0,g_vehicle_collision_probe_z,hero->collision);
    if (!hit) {
        moby_transform_joint_to_world(object,1,&temporary);
        hit=CollLine(&point,&temporary,0x10,hero->collision,0);
        if (!hit) {
            moby_transform_joint_to_world(object,4,&temporary);
            hit=CollLine(&point,&temporary,0x10,hero->collision,0);
            if (!hit) {
                qcopy(&point,previous);
                qcopy(&temporary,state);
                hit=CollLine(previous,state,0x10,hero->collision,0);
            }
        }
        if (hit) {
            whole=fast_vec_dist(&point,&temporary);
            part=fast_vec_dist(&point,g_collision_l08_hit_point);
            FastVecSub(g_collision_l08_hit_point+0x10,&point,&temporary);
            vec_scale_to_length(g_collision_l08_hit_point+0x10,g_collision_l08_hit_point+0x10,whole-part);
            FastVecAdd(g_collision_l08_hit_point+0x10,g_collision_l08_hit_point+0x10,&point);
        }
    }
    if (hit) {
        SpawnExplosionEffects_pal(object,g_str_effect_name,g_collision_l08_hit_point,0.0f,0.0f,3,3,3,0.0f,0.0f,9.0f,0.8f,-1,0.0f,0,3,-1,7,0x810001);
        if (!*(int *)(state+0xB0)) {
            snd_play_from_class_bank(4,0,object,0x988);
            *(int *)(state+0xB0)=12;
        }
        FastVecSub(&point,state,&point);
        FastVecAdd(g_collision_l08_hit_point+0x10,g_collision_l08_hit_point+0x10,&point);
        if (g_current_map_index!=9 && (result=GetCollHitMaterial())==1) {
            g_vehicle_collision_x=g_vehicle_saved_x;
            g_vehicle_collision_y=g_vehicle_saved_y;
            *(int *)(state+0x50)=0;
            hero_l08_enter_state_pal(0,1);
            if (*(unsigned char *)(object+0x43)) anim_start_blended_pal(object,0,0,10);
            index=*(int *)(state+0x6C);
            if (index>0) {
                qcopy(state,&g_moby_array[index].position);
                moby_place_at_stored_transform(object);
            }
            moby_set_state(object,1,-1);
            g_hero_state.contact=result;
        } else {
            qcopy(state,g_collision_l08_hit_point+0x10);
            vec_fast_normalize(state+0x20,state+0x20,g_collision_l08_hit_point+0x20);
            FastVecScale(state+0x20,state+0x20,g_vehicle_collision_velocity_scale);
            drop=g_vehicle_fall_speed*0.00040000002f;
            *(float *)(state+0x28)-=drop;
            if (*(unsigned char *)(object+0x20)!=9) {
                if (*(float *)(state+0x28)>0.0f) *(float *)(state+0x28)=-drop;
                set_hero_animation_pal(0x80,0,12.0f);
                moby_set_state(object,9,-1);
            }
            FastVecAdd(object+0x10,object+0x10,state+0x20);
        }
    }
    return hit;
}
