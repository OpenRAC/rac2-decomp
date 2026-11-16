#include "names.h"
/* func_PAL_L08_003FAD78, the PAL copy of func_L08_003F6610: the same C at 50 Hz, with the frame test made by func_PAL_002AF6C0. */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern u8 g_hero_position[];
extern void FastVecSub(void *,void *,void *);
extern void FastVecScale(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
#define E_I(p,o) (*(int *)((u8 *)(p)+(o)))
#define E_F(p,o) (*(float *)((u8 *)(p)+(o)))
extern void destructible_update_pal(void *,void *);
extern float fast_vec_dist(void *,void *);
extern void moby_update_ground_check(void *);
extern int g_frame_l08_counter;
extern u8 g_hero_position_vec[];
extern u8 *g_path_list_table[];
extern u8 *g_collision_box_table __attribute__((sda));
extern float g_spawner_speed_divisor __attribute__((sda));
extern u8 g_normalize_length_vec[] MACRO_ADDR;
extern void moby_mark_spawned(void *);
extern int GetFirstMobyInGroup(void **,int,int,int);
extern int FastDecTimer(void *);
extern int math_random_int_below(int);
extern int FindHeroOrMobyTarget(void *,void *,void *,int,void *,int,float);
extern int list_count_entries(void *,void *);
extern void anim_start_blended(void *,int,int,int);
extern int math_is_value_within_step_pal(void *,float);
extern float FastVecLength(void *);
extern void vec_fast_divide_helper(void *,void *,float);
extern void vec_scale_to_length(void *,void *,float);
extern int math_random_int_range(int,int);
extern void math_random_planar_offset(void *,float);
extern float math_random_float_range(float,float);
extern float coll_probe_ground_height_below(void *,int,float);
extern void moby_transform_joint_to_world(void *,int,void *);
extern void vec_add_random_offset(void *,float);
extern float weapon_compute_shot_launch_speed(void *,void *,int,float,float);
extern u8 *pool_alloc_owned_object(void *,void *,void *);
extern int mine_fall(void *,void *);
extern void SpawnExplosionEffects(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
typedef struct { u8 pad[0x120]; float speed; int path,object; s16 delay, timer; u8 limit,count,nearest,pad2; int children[2]; int pad3; int targets[4]; } FVars;
/* Updates a Spawner (moby class 3098): it fires off child objects (each aimed at a target or random spot) while it has some left, and removes itself when destroyed (PAL: 50 Hz timings). */
void spawner_l08_update_pal(u8 *moby)
{
    void *found;
    struct { TI128 target, direction, velocity, step; } frame;
    u8 *vars=*(u8 **)(moby+0x68);
    int index;

    void *ids_ptr,*target_pos;
    int id_count,target_id;
    destructible_update_pal(moby,vars);
    if(moby[0x31] && fast_vec_dist(moby+0x10,g_hero_position_vec)<24.0f) {
        moby_update_ground_check(moby);moby[0x6f]=0x16;
    }
    switch(moby[0x20]) {
    case 0:
        if(g_frame_l08_counter) {
            int i;
            found=0;
            for(i=0;i<2;i++) {
                while(!GetFirstMobyInGroup(&found,((FVars *)vars)->children[i],0,0)) moby_mark_spawned(found);
            }
            moby[0x20]=1;
        }
        vars[0x29]=1;
        break;
    case 1:
        if(!FastDecTimer(vars+0x12e)) break;
        if(!math_random_int_below(7)) {
            ids_ptr=0;id_count=0;target_pos=0;target_id=0;
            if(E_I(vars,0x124)!=-1) {ids_ptr=vars+0x124;id_count=1;}
            if(E_I(vars,0x128)!=-1) {u8 *obj=g_path_list_table[E_I(vars,0x128)];target_id=E_I(obj,0);target_pos=obj+0x10;}
            FindHeroOrMobyTarget(moby,vars+0xc0,ids_ptr,id_count,target_pos,target_id,E_F(vars,0x120));
        } else {
            u8 *obj=*(u8 **)(vars+0x100);
            if(obj && obj[0x20]!=0xfe && obj[0x20]!=0xfd) qcopy(vars+0xc0,obj+0x10);
            else {E_I(vars,0x100)=0;E_I(vars,0x104)=2;}
        }
        if(E_I(vars,0x104)==2) break;
        index=list_count_entries(moby,vars);
        if(vars[0x130]>vars[0x131] && index!=-1) {
            moby[0x20]=2;
            if(moby[0x43]!=1) anim_start_blended(moby,1,0,((s32)(10)*5+2)/6);
        }
        break;
    case 2: {
        u8 *chosen;
        float speed;
        if(moby[0x60]&2) {
            moby[0x20]=1;
            if(moby[0x43]) anim_start_blended(moby,0,0,((s32)(10)*5+2)/6);
            break;
        }
        if(!math_is_value_within_step_pal(moby,12.0f)) break;
        chosen=0;
        if(vars[0x132]) {
            int i;
            float best, dist;
            best=100000.0f;
            for(i=0;i<4;i++) {
                if(((FVars *)vars)->targets[i]!=-1) {
                    u8 *obj=g_collision_box_table+((FVars *)vars)->targets[i]*128;
                    dist=fast_vec_dist(g_hero_position,obj+0x30);
                    if(dist<best) {chosen=obj;best=dist;}
                }
            }
            if(!chosen) {
                FastVecSub(&frame.target,vars+0xc0,(moby+0x10));
                FastVecScale(&frame.target,&frame.target,0.5f);
                if(E_F(vars,0x120)>3.0f) vec_fast_divide_helper(&frame.target,&frame.target,3.0f);
                if(FastVecLength(&frame.target)<3.0f) vec_scale_to_length(&frame.target,&frame.target,3.0f);
                FastVecAdd(&frame.target,&frame.target,(moby+0x10));
            } else qcopy(&frame.target,chosen+0x30);
        } else {
            int k=math_random_int_range(0,3);
            int i;
            for(i=0;i<4;i++) {
                int slot=(i+k)%4;
                if(((FVars *)vars)->targets[slot]!=-1) {
                    chosen=g_collision_box_table+((FVars *)vars)->targets[slot]*128;
                    break;
                }
            }
            if(!chosen) {
                float radius=E_F(vars,0x120);if(radius<3.0f) radius=3.0f;
                math_random_planar_offset(&frame.target,radius);
                FastVecAdd(&frame.target,&frame.target,(moby+0x10));
            } else qcopy(&frame.target,chosen+0x30);
        }
        if(chosen) {
            FastVecScale(&frame.direction,chosen,math_random_float_range(-1.0f,1.0f));
            FastVecAdd(&frame.target,&frame.target,&frame.direction);
            FastVecScale(&frame.direction,chosen+0x10,math_random_float_range(-1.0f,1.0f));
            FastVecAdd(&frame.target,&frame.target,&frame.direction);
        }
        {float height=coll_probe_ground_height_below(&frame.target,0,0.5f);
        if(height!=0.0f) E_F(&frame.target,8)=height;}
        FastVecSub(&frame.direction,&frame.target,(moby+0x10));
        speed=FastVecLength(&frame.direction)/g_spawner_speed_divisor<0.09600001f ? FastVecLength(&frame.direction)/g_spawner_speed_divisor : 0.09600001f;
        vec_scale_to_length(&frame.direction,&frame.direction,speed);
        moby_transform_joint_to_world(moby,0,&frame.velocity);
        vec_scale_to_length(&frame.step,&frame.direction,0.05f);
        vec_add_random_offset(&frame.step,0.025f);
        FastVecAdd(&frame.velocity,&frame.velocity,&frame.step);
        E_F(&frame.direction,8)=weapon_compute_shot_launch_speed(&frame.velocity,&frame.target,0,speed,-0.00392f);
        pool_alloc_owned_object(moby,&frame.velocity,&frame.direction);
        ((FVars *)vars)->timer=((s32)(((FVars *)vars)->delay)*5+2)/6;
        ((FVars *)vars)->count++;
        break;
    }
    case 3:
        mine_fall(moby,vars+0x60);
        if(moby[0x60]&2) {
            moby[0x20]=1;
            if(moby[0x43]) anim_start_blended(moby,0,0,((s32)(20)*5+2)/6);
        }
        break;
    case 4:
        if(mine_fall(moby,vars+0x60)&0x40) {
            vec_scale_to_length(&frame.target,g_normalize_length_vec,0.20000002f);
            SpawnExplosionEffects(moby,&frame.target,0,0.0f,0.0f,30,8,20,8.0f,4.0f,18.0f,1.0f,1,15.0f,1,1,-1,0,0x810001);
            moby_mark_spawned(moby);
        }
        break;
    }
}
