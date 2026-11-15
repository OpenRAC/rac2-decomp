#include "names.h"
/* func_PAL_L12_003B8918, the PAL copy of func_L12_003B5240: the same C, where the timers run at 50 Hz,
   the turn rates are multiplied by 1.44f (6/5 squared) and the 0.3f becomes a variable set beside rate. */

#include "common.h"
extern void moby_update_eased_node(void *,void *,int,float,float);
extern void FastVecSub(void *,void *,void *);
extern float vec_length_xy(void *);
extern float mat_fast_helper_a(float,float);
extern float fast_subtract_rotations(float,float);
extern float math_random_float_range(float,float);
extern int math_random_int_below(int);
extern void func_PAL_002A7E68(void *, s32, s32, s32);
typedef struct UpdateVars {
    u8 pad[0x100];
    float direction[4];
    int pad110;
    int timer114;
    int timer118;
    int timer11C;
    u8 *partner;
} UpdateVars;
extern u8 g_item_owned_flags[] __attribute__((sda));
extern u8 D_001A7A40 MACRO_ADDR;
extern u32 D_001397DC, D_00138324;
extern int D_L12_001A8EFC[] __attribute__((sda));
extern int D_L12_001B2BE4[] __attribute__((sda));
extern u8 D_L12_001C0000[];
typedef struct HeroUpdateView {
    u8 pad[0x80];
    float pos[4];
    u8 pad90[0x50];
    float target[4];
    u8 padF0[0x20];
    float velocity[4];
} HeroUpdateView;
extern HeroUpdateView g_hero_state;
extern void moby_reset_matching_effects(u8 *);
extern u8 *CreateMoby(int);
extern void func_002A0F48(u8 *);
extern void moby_set_state(void *, s32, s32);
extern void moby_reset_vars_defaults(u8 *);
extern int hero_is_reachable_for_count(u8 *, int, float);
extern void level_apply_index_for_key(u8 *);
extern int req_push_queue(void *, int);
extern void req_launch_queued(void *);
extern u8 *GetLocalizedString(int);
extern void func_PAL_L00_0030FBC0(void *,int);
extern void text_print_localized_formatted(int,int);
extern int game_is_either_mode_two(void);
extern void moby_mark_spawned(u8 *);
extern void moby_set_byte_on_group(int,int);
extern void help_unlock_entry(int);
extern void func_PAL_002B1588(int,int);
extern void MemcardSave(int,int);
extern int math_fast_float_d(int *);
extern int FloatToInt(float);
extern float vec_distance_xy(void *,void *);
extern float FastDiffRots(float,float);
extern float FastVecLength(void *);
extern float FastAddRotations(float,float);
extern void vec_build_spherical_offset(void *,float,float,float);
extern void FastVecAdd(void *,void *,void *);
extern void moby_copy_joint_transform_to_object(u8 *,u8 *,int,int);
static __inline__ void TurnJoint(void *self, void *joint, int index, float rate, float damping) {
    moby_update_eased_node(self,joint,index,rate*1.44f,damping*1.44f);
}

void func_PAL_L12_003B8918(u8 *self) {
    UpdateVars *v = *(UpdateVars **)(self + 0x68);
    float target[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float pitch, turn;
    float rate, damping;
    int active;
    u8 *partner;
    moby_reset_matching_effects(self);
    switch (self[0x20]) {
    case 0:
        if (!g_item_owned_flags[7]) {
            partner = CreateMoby(0x127B);
            v->partner = partner;
            if (partner) {
                *(u16 *)(partner+0x32) = *(u16 *)(self+0x32);
                v->partner[0x30] = self[0x30];
                *(u64 *)(v->partner+0x38) = *(u64 *)(self+0x38);
                *(u32 *)(v->partner+0x78) = *(u32 *)(self+0x78);
                v->partner[0x31] = 1;
                func_002A0F48(v->partner);
                if (D_001397DC & 0x200000) moby_set_state(self,2,-1);
                else moby_set_state(self,1,-1);
            }
            moby_reset_vars_defaults(self);
        } else {
            moby_mark_spawned(self);
            return;
        }
        break;
    case 1:
        if (hero_is_reachable_for_count(self,10,2.5f)) {
            level_apply_index_for_key(self);
            if (req_push_queue(D_L12_001C0000,0x75)) {
                req_launch_queued(D_L12_001C0000);
                moby_set_state(self,2,-1);
            }
        }
        break;
    case 2:
        D_L12_001B2BE4[1] = 1;
        if (D_L12_001A8EFC[1] == 2) {
            self[0x31] = 0;
            {
                u16 flags = *(u16 *)(self+0x34) | 1;
                int partnerMode = D_L12_001A8EFC[1];
                *(u16 *)(self+0x34) = flags;
                if (partnerMode == 2) {
                    *(u16 *)(v->partner+0x34) |= 1;
                    v->partner[0x31] = 0;
                }
            }
        }
        if (!game_is_either_mode_two()) {
            D_L12_001B2BE4[1] = 0;
            self[0x31] = 1;
            *(u16 *)(self+0x34) &= ~1;
            *(u16 *)(v->partner+0x34) &= ~1;
            v->partner[0x31] = 1;
            if (g_item_owned_flags[0x31]) moby_set_state(self,4,-1);
            else moby_set_state(self,3,-1);
        }
        break;
    case 3:
        if (g_item_owned_flags[0x31]) moby_set_state(self,4,-1);
        else if (hero_is_reachable_for_count(self,10,2.5f)) {
            func_PAL_L00_0030FBC0(GetLocalizedString(0x1325),2);
            level_apply_index_for_key(self);
        }
        break;
    case 4:
        if (!g_item_owned_flags[0x31]) moby_set_state(self,3,-1);
        else if (hero_is_reachable_for_count(self,10,2.5f)) {
            text_print_localized_formatted(0x1326,-1);
            level_apply_index_for_key(self);
            if ((D_00138324 & 0x10) && req_push_queue(D_L12_001C0000,0x76)) {
                req_launch_queued(D_L12_001C0000);
                moby_set_state(self,5,-1);
            }
        }
        break;
    case 5:
        D_L12_001B2BE4[1] = 1;
        if (D_L12_001A8EFC[1] == 2) {
            self[0x31] = 0;
            {
                u16 flags = *(u16 *)(self+0x34) | 1;
                int partnerMode = D_L12_001A8EFC[1];
                *(u16 *)(self+0x34) = flags;
                if (partnerMode == 2) {
                    *(u16 *)(v->partner+0x34) |= 1;
                    v->partner[0x31] = 0;
                }
            }
        }
        if (!game_is_either_mode_two()) {
            D_L12_001B2BE4[1] = 0;
            self[0x31] = 1;
            *(u16 *)(self+0x34) &= ~1;
            moby_mark_spawned(v->partner);
            v->partner = 0;
            if (self[0x21] != 0xFF) moby_set_byte_on_group(self[0x21],1);
            if (!g_item_owned_flags[7]) {
                g_item_owned_flags[0x31] = 0;
                g_item_owned_flags[0x69] = 0;
                help_unlock_entry(7);
                func_PAL_002B1588(0x1245,-1);
                MemcardSave(0,-1);
                moby_mark_spawned(self);
                return;
            }
        }
        break;
    }
    if (self[0x20] != 0) {
        if (self[0x43] < 2 && math_fast_float_d(&v->timer11C)) {
            v->timer11C = FloatToInt(((math_random_float_range(1200.0f,2400.0f)) * 5.0f + 2.0f) * 0.16666667f);
            if (self[0x43] != 2) func_PAL_002A7E68(self,2,0,8);
        }
        else if ((self[0x60] & 2) && self[0x43] == math_random_int_below(2))
            func_PAL_002A7E68(self,math_random_int_below(2)==0,0,8);
    }
    rate = 0.02f;
    damping = 0.3f;
    active = 0;
    if (self[0x43] == 0 || self[0x43] == 2) {
        active = 1;
        if (vec_distance_xy(self+0x10,g_hero_state.pos) < 8.0f &&
            FastDiffRots(*(float *)(self+0xF8),mat_fast_helper_a(g_hero_state.target[0]-*(float *)(self+0x10),g_hero_state.target[1]-*(float *)(self+0x14))) < 1.5707964897155762f) {
                if (FastVecLength(g_hero_state.velocity) > 0.01f) v->timer114 = 100;
                else math_fast_float_d(&v->timer114);
        } else if (v->timer114) {
            v->timer114 = 0;
            qcopy(v->direction,g_hero_state.target);
        }
        if (math_fast_float_d(&v->timer118)) {
            float randomTurn;
            v->timer118 = FloatToInt(((math_random_float_range(180.0f,300.0f)) * 5.0f + 2.0f) * 0.16666667f);
            randomTurn = FastAddRotations(*(float *)(self+0xF8),math_random_float_range(-90.0f,90.0f)*0.01745329424738884f);
            pitch = math_random_float_range(0.0f,30.0f)*0.01745329424738884f;
            vec_build_spherical_offset(v->direction,6.0f,randomTurn,pitch);
            FastVecAdd(v->direction,v->direction,self+0x10);
        }
        if (v->timer114) {
            qcopy(target,g_hero_state.target);
            rate = 0.04f;
            damping = 0.3f;
        } else qcopy(target,v->direction);
    }
    if (active) {
        qcopy(position,self+0x10);
        position[2] += 2.0f;
        FastVecSub(delta,target,position);
        turn = fast_subtract_rotations(mat_fast_helper_a(delta[0],delta[1]),*(float *)(self+0xF8));
        pitch = -mat_fast_helper_a(vec_length_xy(delta),delta[2]);
        if (turn > 1.5707964897155762f) turn = 1.5707964897155762f;
        else if (turn < -1.5707964897155762f) turn = -1.5707964897155762f;
        if (pitch > 0.523598849773407f) pitch = 0.523598849773407f;
        else if (pitch < -0.523598849773407f) pitch = -0.523598849773407f;
        *(float *)((u8 *)v+0x64) = pitch;
        *(float *)((u8 *)v+0x68) = turn*0.6f;
        *(float *)((u8 *)v+0xE8) = turn*0.4f;
    }
    if (D_001A7A40) *(float *)((u8 *)v+0x70) = 2.75f;
    TurnJoint(self,v,0,rate,damping);
    TurnJoint(self,(u8 *)v+0x80,1,rate,damping);
    if (v->partner) moby_copy_joint_transform_to_object(self,v->partner,2,0);
}
