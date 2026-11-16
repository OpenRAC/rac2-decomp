#include "include_asm.h"

#include "common.h"
typedef struct TodanoPartnerBlock { float x[12]; } TodanoPartnerBlock;
typedef struct TodanoPartnerSlot { u8 pad[0x38]; u8 *object; u32 tail; } TodanoPartnerSlot;
extern TodanoPartnerSlot g_contact_l12_push_table[];
extern u8 g_hero_prev_position[];
extern void func_PAL_L12_004184A0(u8 *);
extern void enemy_apply_stored_values_helper(u8 *);
extern void func_PAL_L12_00418BD8(u8 *);
extern void moby_destroy_linked(u8 *);
extern void guard_update_aim_point(u8 *);
extern int func_PAL_002B1A50(u8 *, void *, int);
extern int part_spawn_damage_debris_pal(u8 *, void *, void *);
extern void SpawnExplosionEffects_pal(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern int math_random_int_below(int);
extern void func_PAL_002A7E68(void *, s32, s32, s32);
extern void FastVecScale(void *, void *, float);
extern float fast_vec_dist(void *, void *);
extern void moby_update_ground_check(u8 *);
extern int weapon_select_aim_target(u8 *, int, int, int, float, float);
extern u8 g_hero_l12_state_records[];
extern s32 func_315148();
extern void moby_set_state();
extern s32 func_32D988();
extern s32 func_2F15C8(void *arg0);
extern s32 func_3205F8(void *arg0, s32 arg1, s32 arg2);
extern s32 func_364DF8(s32 arg0, s32 arg1, void *arg2);
extern s32 g_moby_list_start __attribute__((sda));
extern s32 D_L12_001B2E9C_2;
extern u16 *g_moby_l12_group_lists[];
extern s32 g_current_map_index __attribute__((sda));
extern s32 GetFirstMobyInGroup(u8 **out, s32 kind, s32 arg2, s32 arg3);
extern s32 GetNextMobyInGroup(u8 **out, u32 value, s32 arg2, s32 arg3);
extern u8 g_item_owned_flags[] __attribute__((sda));
extern u8 g_unlocked_item_flags MACRO_ADDR;
extern u32 g_object_state_flags_f, g_pad_held_flags;
extern u8 g_requirement_queue[];
extern u8 *CreateMoby(int);
extern char *GetLocalizedString(int);
extern s32 *g_path_zone_table[];
extern s32 point_in_path_xy(void *, void *, s32);
extern void func_PAL_002A7E68(void *, s32, s32, s32);

void guard_handle_hit_handover_pal(u8 *o) {
    u8 *d = *(u8 **)(o+0x68);
    int old, result;
    if (!o[0x95]) func_PAL_L12_004184A0(o);
    if (o[0xA8] == 255) {
        u8 *partner=*(u8 **)(d+0x2F8);
        if (partner && *(short *)(partner+0xAA)==0x114B && partner[0x20]!=254 && partner[0x20]!=253) {
            int index;
            if (partner[0xA8]!=255) {
                TodanoPartnerSlot *slots=g_contact_l12_push_table;
                index=partner[0xA8];
                if (slots[index].object==partner) {
                    o[0xA8]=index;
                    slots[o[0xA8]].object=o;
                }
            }
        }
    }
    old=o[0x20];
    result=func_PAL_002B1A50(o,d+0x50,0);
    if (result) {
        enemy_apply_stored_values_helper(o);
        if (*(u8 **)(d+0x2F8)) {
            if (result==4) {
                u8 *p; int i; int alive;
                *(u16 *)(o+0x34)&=0xEFFF;
                *(u16 *)(*(u8 **)(d+0x2F8)+0x34)&=0xEFFF;
                *(u16 *)(*(u8 **)(d+0x2F8)+0x7C)|=0x300;
                *(int *)(d+0x20)=0;
                p=*(u8 **)(*(u8 **)(d+0x2F8)+0x68);
                *(TodanoPartnerBlock *)(p+0x20)=*(TodanoPartnerBlock *)(d+0x20);
                part_spawn_damage_debris_pal(*(u8 **)(d+0x2F8),p+0x50,p+0x20);
                func_PAL_L12_00418BD8(o);
                SpawnExplosionEffects_pal(*(u8 **)(d+0x2F8),d+0xD0,0,0,0,4,0,0,2,1,9,1,-1,0,0,0,-1,0,0x810001);
                moby_destroy_linked(o);
                if (old>=4 && !math_random_int_below(2)) {
                    if (o[0x43]!=17) func_PAL_002A7E68(o,17,0,5);
                    *(float *)(d+0xB0)=*(s8 *)(d+0xBF);
                    *(float *)(d+0xA4)=*(s8 *)(d+0xBE);
                    *(int *)(d+0xCC)=-1;
                    FastVecScale(d+0xD0,d+0xD0,0.05f);
                } else qzero(d+0xD0);
                alive=1;
                p=d+0x2F0;
                for(i=1;i>=0;i--,p+=4) {
                    if (*(u8 **)p) {
                        *(u16 *)(*(u8 **)p+0x34)&=0xFFFD;
                        *(u16 *)(*(u8 **)p+0x34)&=0xFFFE;
                        (*(u8 **)p)[0x31]=alive;
                        *(u8 **)p=0;
                    }
                }
            } else {
                u8 *p; u8 *other; int i;
                p=*(u8 **)(*(u8 **)(d+0x2F8)+0x68);
                *(TodanoPartnerBlock *)(p+0x20)=*(TodanoPartnerBlock *)(d+0x20);
                part_spawn_damage_debris_pal(*(u8 **)(d+0x2F8),p+0x50,p+0x20);
                func_PAL_002A7E68(*(u8 **)(d+0x2F8),o[0x43],0,2);
                *(float *)(*(u8 **)(d+0x2F8)+0x48)=*(float *)(o+0x48);
                if (!(*(u16 *)(*(u8 **)(d+0x2F8)+0x7C)&0x80)) {
                    d[0x30F]=1;
                    if(o[0x95]!=9) moby_set_state(o,13,8);
                }
                { u8 *partner=*(u8 **)(d+0x2F8);
                if(!(*(u16 *)(partner+0x7C)&0x10)) *(u16 *)(partner+0x7C)|=0x100; }
                { u8 *partner=*(u8 **)(d+0x2F8);
                if(!(*(u16 *)(partner+0x7C)&0x20)) *(u16 *)(partner+0x7C)|=0x200; }
                for(i=0;i<2;i++) {
                    p=d+0x2F0+i*4;
                    other=*(u8 **)p;
                    if(other && !((*(u16 *)(*(u8 **)(d+0x2F8)+0x7C)>>(i+4))&1)) {
                        *(u16 *)(other+0x34)&=0xFFFD;
                        *(u8 **)p=0;
                    }
                }
            }
        }
    }
    if(o[0x31] && fast_vec_dist(o+0x10,g_hero_prev_position)<24.0f) {
        moby_update_ground_check(o); o[0x6F]=22;
    }
    weapon_select_aim_target(o,*(int *)(d+0x2D8),0,0,0,0);
    guard_update_aim_point(o);
}


extern void moby_transform_joint_to_world(u8 *,int,void *);
extern void moby_update_eased_node(void *,void *,int,float,float);
extern void moby_copy_color(u8 *,u8 *);
extern f32 math_approach_target_with_direction_mode(void *,void *,int,float,float,float,float);
extern void func_PAL_L12_00417F48(u8 *);
extern void FastVecSub(void *,void *,void *);
extern float vec_length_xy(void *);
extern float mat_fast_helper_a(float,float);
extern float fast_subtract_rotations(float,float);
extern float math_random_float_range(float,float);

void guard_aim_partner_hands_pal(u8 *o) {
    u8 *d=*(u8 **)(o+0x68); float v[4]; int i;
    u8 *p=*(u8 **)(d+0x2F8);
    if(p && *(short *)(p+0xAA)==0x114B && p[0x20]!=254 && p[0x20]!=253) {
        moby_copy_color(o,p);
        moby_transform_joint_to_world(o,0,*(u8 **)(d+0x2F8)+0x10);
        math_approach_target_with_direction_mode(*(u8 **)(d+0x2F8)+0xF8,d+0x2FC,0,*(float *)(d+0x2EC),*(float *)(d+0x114),*(float *)(d+0x118),*(float *)(d+0x11C));
        *(float *)(*(u8 **)(d+0x2F8)+0x48)=*(float *)(o+0x48);
        if(o[0x20]>=1 && o[0x20]<=3) func_PAL_L12_00417F48(o);
        if(*(int *)(d+0x204)==1 && !d[0x30F]) {
            moby_transform_joint_to_world(*(u8 **)(d+0x2F8),4,v);
            FastVecSub(v,d+0x1F0,v);
            *(float *)(d+0x274)=fast_subtract_rotations(-mat_fast_helper_a(vec_length_xy(v),v[2]),*(float *)(*(u8 **)(d+0x2F8)+0xF4));
            *(float *)(d+0x278)=fast_subtract_rotations(mat_fast_helper_a(v[0],v[1]),*(float *)(*(u8 **)(d+0x2F8)+0xF8));
        }
        moby_update_eased_node(*(u8 **)(d+0x2F8),d+0x210,3,0.028800001f,0.43200004f);
        if(!d[0x30F] && (*(u8 **)(d+0x2F8))[0x42]>=8 && (*(u8 **)(d+0x2F8))[0x42]<11) {
                for(i=0;i<2;i++) {
                    u8 *r=d+i*0x80;
                    if((*(u16 *)(*(u8 **)(d+0x2F8)+0x7C)>>(i+4))&1) {
                        moby_transform_joint_to_world(*(u8 **)(d+0x2F8),i,v);
                        FastVecSub(v,d+0x1F0,v);
                        *(float *)(r+0x384)=-mat_fast_helper_a(vec_length_xy(v),v[2]);
                        *(float *)(r+0x388)=fast_subtract_rotations(mat_fast_helper_a(v[0],v[1]),*(float *)(*(u8 **)(d+0x2F8)+0xF8));
                        if(i) { if(*(float *)(r+0x388)>0.087266475f) *(float *)(r+0x388)=0.087266475f; }
                        else { if(*(float *)(d+0x388)<-0.087266475f) *(float *)(d+0x388)=-0.087266475f; }
                    }
                }
        } else if(d[0x30F]) {
            u8 *r=d;
            for(i=1;i>=0;i--,r+=0x80) {
                *(float *)(r+0x384)=math_random_float_range(-1.57079637f,1.57079637f)*0.5f;
                *(float *)(r+0x388)=math_random_float_range(-1.57079637f,1.57079637f)*0.5f;
            }
        }
        for(i=0;i<2;i++) moby_update_eased_node(*(u8 **)(d+0x2F8),d+0x320+i*0x80,i+7,0.028800001f,0.43200004f);
    }
}

