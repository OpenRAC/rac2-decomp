#include "common.h"
extern void aim_get_target_heading_distances(void *, void *, f32 *, f32 *, f32 *);
extern void moby_set_state(void *, s32, s32);
extern void func_PAL_002A7E68(void *, s32, s32, s32);
extern s32 flag_set_first_pending(void *);
extern f32 *arena_get_center_point(s32);
extern f32 math_signed_triangle_area(void *, void *, void *);
extern f32 math_fabs(f32);
extern void vec_clear_128(void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, f32);
extern f32 math_fast_sin_or_cos_a(f32), math_fast_sin_or_cos_b(f32), IntToFloat(s32);
extern void copy_matrix3x4(void *, void *), multiply_matrix3x3(void *, void *, void *);
extern void mat_build_direction_roll(void *, void *, f32);
extern f32 moby_get_anim_value(void *);
extern s32 math_random_int_below(s32);
extern void joba_enemy_return_state(void *), joba_enemy_choose_attack_state(void *), joba_enemy_enter_hit_reaction(void *);
extern void joba_enemy_reset(void *), joba_enemy_set_counters_one(void *), joba_enemy_set_counters_two(void *), joba_enemy_clear_counters(void *);
extern int arena_launch_fighter_toward_target_pal(s32, void *);
extern s32 arena_get_fighter_count(s32);
extern void moby_set_anim_type_three_pal(void *, s32, s32);
extern char *SpawnExplosion_pal(void *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32, s32, s32);
extern int snd_play_from_class_bank(s32, s32, void *, s32);
extern u8 g_hero_l11_state_data[];
extern f32 g_joba_attack_min_value __attribute__((sda));
extern f32 g_joba_attack_max_value __attribute__((sda));
extern f32 g_joba_orbit_radius __attribute__((sda));
extern s32 g_joba_slam_frame_period __attribute__((sda));
extern s32 g_joba_charge_frame_limit __attribute__((sda));
extern f32 g_joba_push_length __attribute__((sda));
extern f32 g_joba_height_offset __attribute__((sda));
extern s32 g_joba_max_fighter_count __attribute__((sda));
extern f32 g_joba_state_value_a __attribute__((sda));
extern f32 g_joba_state_value_b __attribute__((sda));
extern f32 g_joba_damage_threshold __attribute__((sda));
extern s32 g_joba_move_frame_count __attribute__((sda));
extern f32 g_joba_move_distance __attribute__((sda));
extern f32 g_joba_height_tolerance __attribute__((sda));
#define F(p,o) (*(f32 *)((u8 *)(p)+(o)))
#define W(p,o) (*(s32 *)((u8 *)(p)+(o)))
#define H(p,o) (*(s16 *)((u8 *)(p)+(o)))
#define U(p,o) (*(u16 *)((u8 *)(p)+(o)))
static __inline__ void SetAnimation(u8 *p, s32 animation, s32 mode, s32 blend)
{
    if (p[0x43] != animation) func_PAL_002A7E68(p, animation, mode, blend);
}
/* The two 16-bit counters at +0x278 and +0x27A, read as one value. */
static __inline__ unsigned long CounterPair(u8 *state)
{
    return *(u32 *)(state + 0x278);
}
/* func_PAL_L11_003F61F8, the PAL copy of func_L11_003F1F48: the same C, where the frame counts
   and rates are rescaled for 50 Hz. */
/* State machine: self[0x20] picks the state and self[0xBC] holds the sub-state. Each state's
   setup runs when func_002B3868 reports the object's first pending flag as newly set. */
void func_PAL_L11_003F61F8(u8 *self) {
    u8 *state = *(u8 **)(self + 0x68);
    u8 query[16] __attribute__((aligned(16)));
    u8 vector[64] __attribute__((aligned(16)));
    u8 matrix[48] __attribute__((aligned(16)));
    f32 a,b,c;
    f32 distance, amplitude;
    f32 *pos;
    aim_get_target_heading_distances(self,query,&a,&b,&c);
    switch (self[0x20]) {
    case 1:
        if (!self[0x42]) U(self,0x34) |= 0x46;
        break;
    case 2:
        moby_set_state(self,4,-1);
        joba_enemy_enter_hit_reaction(self);
        break;
    case 3:
        if (flag_set_first_pending(self)) { SetAnimation(self,8,0,8); }
        if (self[0x60] & 2) moby_set_state(self,self[0x94],H(*(u8 **)(self+0x68),0x294));
        break;
    case 4:
        if (flag_set_first_pending(self)) {
            u8 *here=self+0x10;
            pos = arena_get_center_point(W(self,0xB8));
            if (math_signed_triangle_area(query,here,pos) > 0) {
                self[0xBC] = 1;
                if (self[0x95] == 1) SetAnimation(self,1,0,8);
                else SetAnimation(self,2,0,8);
                F(self,0x48) = g_joba_state_value_b;
            } else {
                self[0xBC] = 0;
                if (self[0x95] == 1) SetAnimation(self,2,0,8);
                else SetAnimation(self,1,0,8);
                F(self,0x48) = g_joba_state_value_b;
            }
        }
        if (math_fabs(F(g_hero_l11_state_data,8) - F(self,0x18)) < g_joba_height_tolerance) moby_set_state(self,5,-1);
        else if (b > g_joba_attack_min_value && b < g_joba_attack_max_value) joba_enemy_choose_attack_state(self);
        break;
    case 5:
        if (flag_set_first_pending(self)) {
            self[0xBC]=0; SetAnimation(self,9,0,8);
            vec_clear_128(state+0x1E0);
            if (self[0x95] == 2) F(state,0x1E8)=g_joba_move_distance / (f32)((g_joba_move_frame_count * 5 + 2) / 6);
            else F(state,0x1E8)=-g_joba_move_distance / (f32)((g_joba_move_frame_count * 5 + 2) / 6);
            F(state,0x270)=3.1415927410125732f / (f32)((g_joba_move_frame_count * 5 + 2) / 6);
            H(state,0x298)=0;
        } else if (self[0xBC] == 0) {
            if (self[0x60]&2) { self[0xBC]=1; SetAnimation(self,10,0,0); }
        } else if (self[0xBC] == 1) {
            if (U(self,0x96) > ((g_joba_move_frame_count >> 1) * 5 + 2) / 6) self[0xBC]=2;
        } else if (self[0xBC] == 2) {
            if (U(self,0x96) > ((g_joba_move_frame_count - 10) * 5 + 2) / 6) {
                self[0xBC]=3; SetAnimation(self,9,4,0); F(self,0x48)=-1;
            }
        } else if (self[0xBC] == 3) {
            if (moby_get_anim_value(self) < 2) {
                if (F(self,0x18)>490) moby_set_state(self,4,1);
                else moby_set_state(self,4,2);
            }
        }
        FastVecAdd(self+0x10,self+0x10,state+0x1E0);
        mat_build_direction_roll(vector,self+0xE0,F(state,0x270));
        copy_matrix3x4(matrix,vector);
        multiply_matrix3x3(self+0xC0,matrix,self+0xC0);
        amplitude=g_joba_orbit_radius*(1-(H(state,0x298)*2.0f)/IntToFloat(g_joba_move_frame_count))*(1-(H(state,0x298)*2.0f)/IntToFloat(g_joba_move_frame_count));
        F(self,0x10)=amplitude*math_fast_sin_or_cos_a(F(state,0x250))+arena_get_center_point(W(self,0xB8))[0];
        F(self,0x14)=amplitude*math_fast_sin_or_cos_b(F(state,0x250))+arena_get_center_point(W(self,0xB8))[1];
        U(state,0x298)++;
        break;
    case 6:
        if (flag_set_first_pending(self)) {
            SetAnimation(self,3,0,8); H(state,0x296)=0; self[0xBC]=0; joba_enemy_set_counters_one(self);
        }
        distance=moby_get_anim_value(self);
        if (!self[0xBC] && CounterPair(state)==0x10001 && self[0x42]==3 && distance>30) {
            joba_enemy_set_counters_two(self); self[0xBC]=1;
        } else if (self[0xBC]==1 && self[0x42]==3 && (self[0x60]&2)) {
            SetAnimation(self,0,0,8); self[0xBC]=2;
        } else if (self[0xBC]==2 && CounterPair(state)==0) {
            joba_enemy_return_state(self); if (H(state,0x296)) joba_enemy_enter_hit_reaction(self);
        }
        break;
    case 7:
        if (flag_set_first_pending(self)) { SetAnimation(self,4,0,8); self[0xBC]=0; joba_enemy_set_counters_one(self); }
        switch (self[0xBC]) {
        case 0:
            if (self[0x60]&2) { SetAnimation(self,5,0,8); self[0xBC]=1; U(self,0x96)=(g_joba_slam_frame_period * 5 + 2) / 6 - 1; }
            break;
        case 1:
            if (U(self,0x96) % ((g_joba_slam_frame_period * 5 + 2) / 6) == 0) {
                u8 *v=vector;
                u8 *position=self+0x10;
                pos=arena_get_center_point(W(self,0xB8));
                FastVecSub(v,position,pos);
                W(vector,8)=0;
                vec_scale_to_length(v,v,g_joba_push_length);
                pos=arena_get_center_point(W(self,0xB8));
                FastVecAdd(v,v,pos);
                if (self[0x95]==2) F(vector,8)=F(self,0x18)+g_joba_height_offset;
                else if (self[0x95]==1) F(vector,8)=F(self,0x18)-g_joba_height_offset;
                arena_launch_fighter_toward_target_pal(W(self,0xB8),vector);
            }
            if (arena_get_fighter_count(W(self,0xB8)) >= g_joba_max_fighter_count || U(self,0x96)>(g_joba_charge_frame_limit * 5 + 2) / 6) {
                SetAnimation(self,6,0,8); self[0xBC]=2;
            }
            if (math_fabs(F(g_hero_l11_state_data,8)-F(self,0x18)) < g_joba_height_tolerance) moby_set_state(self,5,-1);
            break;
        case 2:
            if (self[0x60]&2) joba_enemy_return_state(self);
            break;
        }
        break;
    case 8:
        if (flag_set_first_pending(self)) {
            SetAnimation(self,7,0,2);
            if (U(state,0x278)<2 && U(state,0x27A)<2) { self[0xBC]=0; H(state,0x296)=0; joba_enemy_set_counters_one(self); }
            else self[0xBC]=3;
            if (F(state,0x20)<=0) moby_set_state(self,9,-1);
        }
        distance=moby_get_anim_value(self);
        if (self[0xBC]==0 && CounterPair(state)==0x10001 && self[0x42]==7 && distance>32) {
            joba_enemy_set_counters_two(self); self[0xBC]=1;
        } else if (self[0xBC]==1 && self[0x42]==7 && (self[0x60]&2)) {
            SetAnimation(self,0,0,8); self[0xBC]=2;
        } else if (self[0xBC]==2 && CounterPair(state)==0) {
            joba_enemy_return_state(self); if (H(state,0x296)) joba_enemy_enter_hit_reaction(self);
        } else if (self[0xBC]==3 && self[0x42]==7 && (self[0x60]&2)) joba_enemy_return_state(self);
        break;
    case 9:
        if (flag_set_first_pending(self)) {
            pos=arena_get_center_point(W(self,0xB8));
            FastVecSub(state+0x1E0,pos,self+0x10);
            W(state,0x1E8)=0;
            vec_scale_to_length(state+0x1E0,state+0x1E0,0.20000002f);
            F(self,0x48)=g_joba_state_value_a;
            joba_enemy_clear_counters(self);
            U(self,0x34)&=0xEFFF;
        }
        F(state,0x1E8)-=0.004f;
        FastVecAdd(self+0x10,self+0x10,state+0x1E0);
        pos=arena_get_center_point(W(self,0xB8));
        if (F(self,0x18)<pos[2]+5 || !math_random_int_below(0x1C2) || U(self,0x96)>=301) {
            moby_set_anim_type_three_pal(self,0,-1);
            joba_enemy_reset(self);
            SpawnExplosion_pal(self+0x10,0,25,15,30,20,30,0,3,0,1,1,0,0);
            snd_play_from_class_bank(0,0,self,0xDF7);
        }
        break;
    }
}
