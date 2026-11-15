#include "names.h"
/* func_US2_L08_003F7AB0, the USA v2.00 copy of func_L08_003F6610: the same C, where the frame test becomes a threshold call
   (ref_US2_L08_003F7AB0_00: func_US2_L08_003326F0 in level 8, func_US2_002AF9C8 in level 17). */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern u8 g_hero_position[];
extern void FastVecSub(void *,void *,void *);
extern void FastVecScale(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
#define E_I(p,o) (*(int *)((u8 *)(p)+(o)))
#define E_F(p,o) (*(float *)((u8 *)(p)+(o)))
extern void destructible_update(void *,void *);
extern float fast_vec_dist(void *,void *);
extern void moby_update_ground_check(void *);
extern int D_L08_001B2508;
extern u8 D_L08_001B9B00[];
extern u8 *D_L08_001FE7C0[];
extern u8 *D_L08_001B2ACC __attribute__((sda));
extern float D_L08_001B0B5C __attribute__((sda));
extern u8 D_L08_001AC5E0[] MACRO_ADDR;
extern void moby_mark_spawned(void *);
extern int GetFirstMobyInGroup(void **,int,int,int);
extern int FastDecTimer(void *);
extern int math_random_int_below(int);
extern void FindHeroOrMobyTarget(void *,void *,void *,int,void *,int,float);
extern int list_count_entries(void *,void *);
extern void anim_start_blended(void *,int,int,int);
extern int ref_US2_L08_003F7AB0_00(void *,float);
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
typedef struct { u8 pad[0x120]; float speed; int path,object; u16 delay, timer; u8 limit,count,nearest,pad2; int children[2]; int pad3; int targets[4]; } FVars;
void func_US2_L08_003F7AB0(u8 *m)
{
    void *found;
    struct { TI128 target, direction, velocity, step; } frame;
    u8 *p=*(u8 **)(m+0x68);
    int index;

    void *a2,*t0;
    int a3,t1;
    destructible_update(m,p);
    if(m[0x31] && fast_vec_dist(m+0x10,D_L08_001B9B00)<24.0f) {
        moby_update_ground_check(m);m[0x6f]=0x16;
    }
    switch(m[0x20]) {
    case 0:
        if(D_L08_001B2508) {
            int i;
            found=0;
            for(i=0;i<2;i++) {
                while(!GetFirstMobyInGroup(&found,((FVars *)p)->children[i],0,0)) moby_mark_spawned(found);
            }
            m[0x20]=1;
        }
        p[0x29]=1;
        break;
    case 1:
        if(!FastDecTimer(p+0x12e)) break;
        if(!math_random_int_below(7)) {
            a2=0;a3=0;t0=0;t1=0;
            if(E_I(p,0x124)!=-1) {a2=p+0x124;a3=1;}
            if(E_I(p,0x128)!=-1) {u8 *obj=D_L08_001FE7C0[E_I(p,0x128)];t1=E_I(obj,0);t0=obj+0x10;}
            FindHeroOrMobyTarget(m,p+0xc0,a2,a3,t0,t1,E_F(p,0x120));
        } else {
            u8 *obj=*(u8 **)(p+0x100);
            if(obj && obj[0x20]!=0xfe && obj[0x20]!=0xfd) qcopy(p+0xc0,obj+0x10);
            else {E_I(p,0x100)=0;E_I(p,0x104)=2;}
        }
        if(E_I(p,0x104)==2) break;
        index=list_count_entries(m,p);
        if(p[0x130]>p[0x131] && index!=-1) {
            m[0x20]=2;
            if(m[0x43]!=1) anim_start_blended(m,1,0,10);
        }
        break;
    case 2: {
        u8 *chosen;
        float f;
        if(m[0x60]&2) {
            m[0x20]=1;
            if(m[0x43]) anim_start_blended(m,0,0,10);
            break;
        }
        if(!ref_US2_L08_003F7AB0_00(m,12.0f)) break;
        chosen=0;
        if(p[0x132]) {
            int i;
            float best, d;
            best=100000.0f;
            for(i=0;i<4;i++) {
                if(((FVars *)p)->targets[i]!=-1) {
                    u8 *obj=D_L08_001B2ACC+((FVars *)p)->targets[i]*128;
                    d=fast_vec_dist(g_hero_position,obj+0x30);
                    if(d<best) {chosen=obj;best=d;}
                }
            }
            if(!chosen) {
                FastVecSub(&frame.target,p+0xc0,(m+0x10));
                FastVecScale(&frame.target,&frame.target,0.5f);
                if(E_F(p,0x120)>3.0f) vec_fast_divide_helper(&frame.target,&frame.target,3.0f);
                if(FastVecLength(&frame.target)<3.0f) vec_scale_to_length(&frame.target,&frame.target,3.0f);
                FastVecAdd(&frame.target,&frame.target,(m+0x10));
            } else qcopy(&frame.target,chosen+0x30);
        } else {
            int k=math_random_int_range(0,3);
            int i;
            for(i=0;i<4;i++) {
                int slot=(i+k)%4;
                if(((FVars *)p)->targets[slot]!=-1) {
                    chosen=D_L08_001B2ACC+((FVars *)p)->targets[slot]*128;
                    break;
                }
            }
            if(!chosen) {
                float radius=E_F(p,0x120);if(radius<3.0f) radius=3.0f;
                math_random_planar_offset(&frame.target,radius);
                FastVecAdd(&frame.target,&frame.target,(m+0x10));
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
        FastVecSub(&frame.direction,&frame.target,(m+0x10));
        f=FastVecLength(&frame.direction)/D_L08_001B0B5C<0.08000000566f ? FastVecLength(&frame.direction)/D_L08_001B0B5C : 0.08000000566f;
        vec_scale_to_length(&frame.direction,&frame.direction,f);
        moby_transform_joint_to_world(m,0,&frame.velocity);
        vec_scale_to_length(&frame.step,&frame.direction,0.05f);
        vec_add_random_offset(&frame.step,0.025f);
        FastVecAdd(&frame.velocity,&frame.velocity,&frame.step);
        E_F(&frame.direction,8)=weapon_compute_shot_launch_speed(&frame.velocity,&frame.target,0,f,-0.002722222358f);
        pool_alloc_owned_object(m,&frame.velocity,&frame.direction);
        ((FVars *)p)->timer=((FVars *)p)->delay;
        ((FVars *)p)->count++;
        break;
    }
    case 3:
        mine_fall(m,p+0x60);
        if(m[0x60]&2) {
            m[0x20]=1;
            if(m[0x43]) anim_start_blended(m,0,0,20);
        }
        break;
    case 4:
        if(mine_fall(m,p+0x60)&0x40) {
            vec_scale_to_length(&frame.target,D_L08_001AC5E0,0.1666666716f);
            SpawnExplosionEffects(m,&frame.target,0,0.0f,0.0f,30,8,20,8.0f,4.0f,18.0f,1.0f,1,15.0f,1,1,-1,0,0x810001);
            moby_mark_spawned(m);
        }
        break;
    }
}
