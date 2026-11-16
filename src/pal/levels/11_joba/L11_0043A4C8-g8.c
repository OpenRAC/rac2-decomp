#include "include_asm.h"

#include "common.h"
extern int g_hero_l11_input_blocked __attribute__((sda));
extern char g_hero_l11_position[];
extern int FloatToInt(float);
extern float math_random_float_range(float,float);
extern int math_random_int_below(int);
extern void enemy_reset_to_idle_pal(char *);
extern char *part_find_owned_effect_slot(char *,int,int);
extern char *arena_get_center_point(int);
extern void FastVecSub(float *,const float *,const float *);
extern void vec_scale_to_length(char *,char *,float);
extern float FastVecDot(void *,void *);
extern float FastVecLength(void *);
extern int moby_apply_damage_to_object_pal(char *,char *,int);
extern void enemy_update_target_lock(char *);
extern void matrix_from_basis_rows(void *,void *);
extern void cam_compute_view_direction(void *,void *,int);
extern int arena_is_point_in_inner_zone(int,void *);
extern void moby_set_state(void *,int,int);
extern float func_L00_002EE290(void *);
extern void FastVecAdd(char *,char *,char *);
extern float fast_vec_dist(void *,void *);
extern void moby_update_ground_check(char *);
#define F(p,t,o) (*(t *)((char *)(p)+(o)))

/* Initializes the object, adjusts hit velocity, and keeps active movement near its target. */
void flying_enemy_hit_and_init_pal(char *moby) {
    char *vars=F(moby,char *,0x68), *hit;
    float vector[4], angle, ground_z;
    if (F(moby,unsigned char,0x20)==0) {
        F(vars,unsigned char,0x48)=FloatToInt(15.0f);
        F(vars,unsigned char,0x4A)=FloatToInt(4.0f);
        F(vars,unsigned char,0x29)=1;
        F(vars,char *,0x18)=vars+0x100;
        angle=math_random_float_range(15.0f,40.0f)*0.017453294f;
        if(math_random_int_below(2)) angle=-angle;
        F(vars,float,0x274)=angle;
        if(math_random_int_below(2)==1) F(moby,unsigned short,0x34)|=0x8000;
        F(vars,short,0x282)=0;
        F(vars,unsigned char,0x60)=10;
        F(vars,int,0x98)=4;
        F(vars,float,0x84)=0.65f;
        F(vars,float,0x80)=0.6f;
        F(vars,float,0x100)=0.6f;
        F(vars,float,0x104)=0.05f;
        F(vars,float,0x8C)=0.4f;
        F(vars,float,0x108)=0.4f;
        F(vars,float,0x10C)=0.4f;
        F(vars,float,0x134)=0.01f;
        F(vars,float,0x110)=1.5707964897155762f;
        F(vars,float,0x130)=0.523598849773407f;
        F(vars,float,0x12C)=0.004f;
        F(vars,unsigned char,0x28)=3;
        enemy_reset_to_idle_pal(moby);
    }
    if(F(moby,unsigned char,0x95)>=2) {
        hit=part_find_owned_effect_slot(moby,0x10000,1);
        if(hit) {
            char *other=F(hit,char *,0x20);
            if(other && !F(moby,unsigned char,0x31) &&
            (F(other,short,0xAA)==0xA03 || F(other,short,0xAA)==0xB89)) F(hit,int,0x2C)=0;
            if(F(vars,short,0x286)) {
                char *velocity=hit+0x10;
                FastVecSub(vector,(float *)arena_get_center_point(F(moby,int,0xB8)),(float *)(moby+0x10));
                vector[2]=0;
                vec_scale_to_length((char *)vector,(char *)vector,1.0f);
                vec_scale_to_length((char *)vector,(char *)vector,FastVecDot(velocity,vector));
                angle=FastVecLength(velocity);
                FastVecSub((float *)velocity,(float *)velocity,vector);
                vec_scale_to_length(velocity,velocity,angle);
            }
        }
        if(moby_apply_damage_to_object_pal(moby,vars+0x50,0)==5) {
            F(vars,int,0xE0)=0;
            F(vars,float,0xE4)=1.0053098f;
        }
        enemy_update_target_lock(moby);
        if(F(vars,short,0x286)) {
            matrix_from_basis_rows(vars+0x210,moby+0xC0);
            cam_compute_view_direction(moby+0x10,vars+0x240,0);
            if(!arena_is_point_in_inner_zone(F(moby,int,0xB8),moby+0x10)) {
                F(vars,int,0x20)=0;
                moby_set_state(moby,11,4);
            }
            if(F(moby,unsigned char,0x20)!=11) {
                ground_z=F(moby,float,0x18);
                FastVecSub(vector,(float *)(moby+0x10),(float *)arena_get_center_point(F(moby,int,0xB8)));
                vector[2]=0;
                if(func_L00_002EE290(vector)>225.0f) {
                    vec_scale_to_length((char *)vector,(char *)vector,15.0f);
                    FastVecAdd(moby+0x10,(char *)vector,arena_get_center_point(F(moby,int,0xB8)));
                    F(moby,float,0x18)=ground_z;
                }
            }
        }
    }
    if(!F(vars,short,0x286) && F(moby,unsigned char,0x20)!=11 && !g_hero_l11_input_blocked) {
        F(moby,unsigned short,0x34)|=0x400;
        if(F(moby,unsigned char,0x31) && fast_vec_dist(moby+0x10,g_hero_l11_position)<24.0f) {
            moby_update_ground_check(moby);
            F(moby,unsigned char,0x6F)=22;
        }
    } else F(moby,unsigned short,0x34)&=0xFBFF;
    if(F(moby,unsigned char,0x20)>=2 && F(vars,unsigned char,0x2E)==2) enemy_reset_to_idle_pal(moby);
}
