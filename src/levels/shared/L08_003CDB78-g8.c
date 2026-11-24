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
extern void SpawnExplosionEffects(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
extern int snd_play_from_class_bank(int,int,void *,int),GetCollHitMaterial(void);
extern int hero_l08_set_move_state(int,int);
extern void anim_start_blended(void *,int,int,int),moby_set_state(void *,int,int);
extern void moby_place_at_stored_transform(void *),set_hero_animation(int,int,float);

/* Checks whether the object has hit a wall or floor this frame. On a hit it bounces the object,
   plays a sound and sparks, and may send the hero back to a saved spot. */
/* Resolve the movement probes and update the D_L08_001BFF60 response. */
int vehicle_handle_collision(char *object, void *prev_pos)
{
    ContactVector temp_vec, hit_point;
    char *vars=*(char **)(object+0x68);
    int hit,checkpoint_index,result;
    float full_dist,part_dist,fall_speed;
    ContactHero *hero=&g_hero_state;

    vec_scale_to_length(&temp_vec,object+0xC0,g_vehicle_bounce_scale_b);
    FastVecAdd(&hit_point,&temp_vec,object+0x10);
    vec_scale_to_length(&temp_vec,object+0xE0,g_vehicle_bounce_scale_a);
    FastVecAdd(&hit_point,&hit_point,&temp_vec);
    hit=coll_test_point(&hit_point,0,g_vehicle_collision_probe_z,hero->collision);
    if (!hit) {
        moby_transform_joint_to_world(object,1,&temp_vec);
        hit=CollLine(&hit_point,&temp_vec,0x10,hero->collision,0);
        if (!hit) {
            moby_transform_joint_to_world(object,4,&temp_vec);
            hit=CollLine(&hit_point,&temp_vec,0x10,hero->collision,0);
            if (!hit) {
                qcopy(&hit_point,prev_pos);
                qcopy(&temp_vec,vars);
                hit=CollLine(prev_pos,vars,0x10,hero->collision,0);
            }
        }
        if (hit) {
            full_dist=fast_vec_dist(&hit_point,&temp_vec);
            part_dist=fast_vec_dist(&hit_point,g_collision_l08_hit_point);
            FastVecSub(g_collision_l08_hit_point+0x10,&hit_point,&temp_vec);
            vec_scale_to_length(g_collision_l08_hit_point+0x10,g_collision_l08_hit_point+0x10,full_dist-part_dist);
            FastVecAdd(g_collision_l08_hit_point+0x10,g_collision_l08_hit_point+0x10,&hit_point);
        }
    }
    if (hit) {
        SpawnExplosionEffects(object,g_str_effect_name,g_collision_l08_hit_point,0.0f,0.0f,3,3,3,0.0f,0.0f,9.0f,0.8f,-1,0.0f,0,3,-1,7,0x810001);
        if (!*(int *)(vars+0xB0)) {
            snd_play_from_class_bank(4,0,object,0x988);
            *(int *)(vars+0xB0)=15;
        }
        FastVecSub(&hit_point,vars,&hit_point);
        FastVecAdd(g_collision_l08_hit_point+0x10,g_collision_l08_hit_point+0x10,&hit_point);
        if (g_current_map_index!=9 && (result=GetCollHitMaterial())==1) {
            g_vehicle_collision_x=g_vehicle_saved_x;
            g_vehicle_collision_y=g_vehicle_saved_y;
            *(int *)(vars+0x50)=0;
            hero_l08_set_move_state(0,1);
            if (*(unsigned char *)(object+0x43)) anim_start_blended(object,0,0,10);
            checkpoint_index=*(int *)(vars+0x6C);
            if (checkpoint_index>0) {
                qcopy(vars,&g_moby_array[checkpoint_index].position);
                moby_place_at_stored_transform(object);
            }
            moby_set_state(object,1,-1);
            g_hero_state.contact=result;
        } else {
            qcopy(vars,g_collision_l08_hit_point+0x10);
            vec_fast_normalize(vars+0x20,vars+0x20,g_collision_l08_hit_point+0x20);
            FastVecScale(vars+0x20,vars+0x20,g_vehicle_collision_velocity_scale);
            fall_speed=g_vehicle_fall_speed*0.00027777778450399637f;
            *(float *)(vars+0x28)-=fall_speed;
            if (*(unsigned char *)(object+0x20)!=9) {
                if (*(float *)(vars+0x28)>0.0f) *(float *)(vars+0x28)=-fall_speed;
                set_hero_animation(0x80,0,15.0f);
                moby_set_state(object,9,-1);
            }
            FastVecAdd(object+0x10,object+0x10,vars+0x20);
        }
    }
    return hit;
}
