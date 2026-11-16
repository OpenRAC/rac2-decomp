#include "common.h"

extern void moby_transform_joint_to_world(u8 *,int,void *);
extern void moby_update_eased_node(void *,void *,int,float,float);
extern void moby_copy_color(u8 *,u8 *);
extern f32 math_approach_target_with_direction_mode(void *,void *,int,float,float,float,float);
extern void guard_spray_flame_sprites(u8 *);
extern void FastVecSub(void *,void *,void *);
extern float vec_length_xy(void *);
extern float mat_fast_helper_a(float,float);
extern float fast_subtract_rotations(float,float);
extern float math_random_float_range(float,float);

typedef struct TodanoPartnerBlock { float x[12]; } TodanoPartnerBlock;
typedef struct TodanoPartnerSlot { u8 pad[0x38]; u8 *object; u32 tail; } TodanoPartnerSlot;
extern TodanoPartnerSlot g_contact_l12_push_table[];
extern u8 g_hero_prev_position[];
extern void InitStateDataWithPartner(u8 *);
extern void enemy_apply_stored_values_helper(u8 *);
extern void path_hand_state_to_nearest(u8 *);
extern void moby_destroy_linked(u8 *);
extern void guard_update_aim_point(u8 *);
extern int moby_apply_damage_to_object(u8 *, void *, int);
extern int part_spawn_damage_debris(u8 *, void *, void *);
extern void SpawnExplosionEffects(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern int math_random_int_below(int);
extern void anim_start_blended(void *, s32, s32, s32);
extern void FastVecScale(void *, void *, float);
extern float fast_vec_dist(void *, void *);
extern void moby_update_ground_check(u8 *);
extern int weapon_select_aim_target(u8 *, int, int, int, float, float);

extern u8 g_hero_l12_state_records[];

extern s32 func_315148();

extern void func_31E1D0();

extern s32 func_32D988();

extern s32 func_2F15C8(void *arg0);

extern void func_2F0A60(void *buf, s32 arg1, u32 arg2, s32 arg3, f32 x, f32 y, f32 z);

extern void func_322AF8(void *arg0, void *arg1);

extern void func_326948(void *arg0, void *arg1, s32 arg2, f32 x, f32 y);

extern s32 func_3205F8(void *arg0, s32 arg1, s32 arg2);

extern s32 func_364DF8(s32 arg0, s32 arg1, void *arg2);

extern void func_314008(void *arg0);

extern f32 func_2F2950(f32 x, f32 y);

extern s32 g_moby_list_start __attribute__((sda));

extern s32 D_L12_001B2E9C_2;

extern u16 *g_moby_l12_group_lists[];

extern s32 g_current_map_index __attribute__((sda));

extern s32 GetFirstMobyInGroup(u8 **out, s32 kind, s32 arg2, s32 arg3);

extern s32 GetNextMobyInGroup(u8 **out, u32 value, s32 arg2, s32 arg3);

extern void gfx_l00_draw_billboard_quad(void *arg0, s32 arg1, f32 arg2, f32 arg3);

typedef struct UpdateVars {
    u8 pad[0x100];
    float direction[4];
    int pad110;
    int timer114;
    int timer118;
    int timer11C;
    u8 *partner;
} UpdateVars;
/* An offset from a small symbol is retail's tied lui/load and lui $at/store, kept out of delay
   slots: these globals are read and written as elements, not as bare symbols. */
extern u8 g_item_owned_flags[] __attribute__((sda));
extern u8 g_unlocked_item_flags MACRO_ADDR;
extern u32 g_object_state_flags_f, g_pad_held_flags;
extern int g_partner_mode_words[] __attribute__((sda));
extern int g_glow_resize_flags[] __attribute__((sda));
extern u8 g_requirement_queue[];
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
extern s32 req_launch_queued(void *);
extern char *GetLocalizedString(int);
extern int level_l00_call_module_handler_with_arg_9(void *,int);
extern void text_print_localized_formatted(int,int);
extern int game_is_either_mode_two(void);
extern void moby_mark_spawned(u8 *);
extern void moby_set_byte_on_group(int,int);
extern void help_unlock_entry(int);
extern void value_set_entry_by_index(int,int);
extern int MemcardSave(int,int);
extern int math_fast_float_d(int *);
extern int FloatToInt(float);
extern float vec_distance_xy(void *,void *);
extern float FastDiffRots(float,float);
extern float FastVecLength(void *);
extern float FastAddRotations(float,float);
extern void vec_build_spherical_offset(void *,float,float,float);
extern void FastVecAdd(void *,void *,void *);
extern void moby_copy_joint_transform_to_object(u8 *,u8 *,int,int);


/* func_L12_003A0F00 is defined in L12_00398E50-mirror.c. */

/* func_L12_003A6F48 is defined in L12_00398E50-color-g8.c. */

/* Scales the tracked object's field by the level's own rate, for every match. */
void glow_resize_matching_mobys(u8 *object) {
    s32 mode = g_current_map_index;
    f32 scale = 1.2f;
    u8 *out;

    if (mode == 0 || mode == 0x12) {
        scale = 1.0f;
    }
    GetFirstMobyInGroup(&out, object[0x21], 0, 0);
    while (out != 0) {
        u8 *cur = out;

        if (cur[0x31] != 0) {
            u32 *cur_vars = *(u32 **)(cur + 0x68);

            if (*(s16 *)(cur + 0xAA) == *(s16 *)(object + 0xAA)) {
                f32 ratio = *(f32 *)(object + 0x2C) / *(f32 *)(*(u32 *)(object + 0x24) + 0x24);

                gfx_l00_draw_billboard_quad(cur + 0x10, cur_vars[1], scale * ratio, 0.5f);
            }
        }
        GetNextMobyInGroup(&out, (u32)out, 0, 0);
    }
}

/* Inlined, so its 0.3f is a constant loaded at each call rather than a pseudo shared across
   the first call. */
static __inline__ void TurnJoint(void *self, void *joint, int index, float rate) {
    moby_update_eased_node(self,joint,index,rate,0.3f);
}

/* Updates the item trade NPC (moby class 2001). It spawns a partner object, talks to the hero,
   and keeps turning its head to follow the hero or look around. */
void UpdateTodanoItemTradeNpc(u8 *self) {
    UpdateVars *vars = *(UpdateVars **)(self + 0x68);
    float target[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float pitch, turn;
    float rate;
    int active;
    u8 *partner;
    moby_reset_matching_effects(self);
    switch (self[0x20]) {
    case 0:
        if (!g_item_owned_flags[7]) {
            partner = CreateMoby(0x127B /* moby class 4731 */);
            vars->partner = partner;
            if (partner) {
                *(u16 *)(partner+0x32) = *(u16 *)(self+0x32);
                vars->partner[0x30] = self[0x30];
                *(u64 *)(vars->partner+0x38) = *(u64 *)(self+0x38);
                *(u32 *)(vars->partner+0x78) = *(u32 *)(self+0x78);
                vars->partner[0x31] = 1;
                func_002A0F48(vars->partner);
                if (g_object_state_flags_f & 0x200000) moby_set_state(self,2,-1);
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
            if (req_push_queue(g_requirement_queue,0x75)) {
                req_launch_queued(g_requirement_queue);
                moby_set_state(self,2,-1);
            }
        }
        break;
    case 2:
        g_glow_resize_flags[1] = 1;
        if (g_partner_mode_words[1] == 2) {
            self[0x31] = 0;
            {
                u16 flags = *(u16 *)(self+0x34) | 1;
                int partnerMode = g_partner_mode_words[1];
                *(u16 *)(self+0x34) = flags;
                if (partnerMode == 2) {
                    *(u16 *)(vars->partner+0x34) |= 1;
                    vars->partner[0x31] = 0;
                }
            }
        }
        if (!game_is_either_mode_two()) {
            g_glow_resize_flags[1] = 0;
            self[0x31] = 1;
            *(u16 *)(self+0x34) &= ~1;
            *(u16 *)(vars->partner+0x34) &= ~1;
            vars->partner[0x31] = 1;
            if (g_item_owned_flags[0x31]) moby_set_state(self,4,-1);
            else moby_set_state(self,3,-1);
        }
        break;
    case 3:
        if (g_item_owned_flags[0x31]) moby_set_state(self,4,-1);
        else if (hero_is_reachable_for_count(self,10,2.5f)) {
            level_l00_call_module_handler_with_arg_9(GetLocalizedString(0x27D3),2);
            level_apply_index_for_key(self);
        }
        break;
    case 4:
        if (!g_item_owned_flags[0x31]) moby_set_state(self,3,-1);
        else if (hero_is_reachable_for_count(self,10,2.5f)) {
            text_print_localized_formatted(0x27D4,-1);
            level_apply_index_for_key(self);
            if ((g_pad_held_flags & 0x10) && req_push_queue(g_requirement_queue,0x76)) {
                req_launch_queued(g_requirement_queue);
                moby_set_state(self,5,-1);
            }
        }
        break;
    case 5:
        g_glow_resize_flags[1] = 1;
        if (g_partner_mode_words[1] == 2) {
            self[0x31] = 0;
            {
                u16 flags = *(u16 *)(self+0x34) | 1;
                int partnerMode = g_partner_mode_words[1];
                *(u16 *)(self+0x34) = flags;
                if (partnerMode == 2) {
                    *(u16 *)(vars->partner+0x34) |= 1;
                    vars->partner[0x31] = 0;
                }
            }
        }
        if (!game_is_either_mode_two()) {
            g_glow_resize_flags[1] = 0;
            self[0x31] = 1;
            *(u16 *)(self+0x34) &= ~1;
            moby_mark_spawned(vars->partner);
            vars->partner = 0;
            if (self[0x21] != 0xFF) moby_set_byte_on_group(self[0x21],1);
            if (!g_item_owned_flags[7]) {
                g_item_owned_flags[0x31] = 0;
                g_item_owned_flags[0x69] = 0;
                help_unlock_entry(7);
                value_set_entry_by_index(0x1245,-1);
                MemcardSave(0,-1);
                moby_mark_spawned(self);
                return;
            }
        }
        break;
    }
    if (self[0x20] != 0) {
        if (self[0x43] < 2 && math_fast_float_d(&vars->timer11C)) {
            vars->timer11C = FloatToInt(math_random_float_range(1200.0f,2400.0f));
            if (self[0x43] != 2) anim_start_blended(self,2,0,10);
        }
        else if ((self[0x60] & 2) && self[0x43] == math_random_int_below(2))
            anim_start_blended(self,math_random_int_below(2)==0,0,10);
    }
    rate = 0.02f;
    active = 0;
    if (self[0x43] == 0 || self[0x43] == 2) {
        active = 1;
        if (vec_distance_xy(self+0x10,g_hero_state.pos) < 8.0f &&
            FastDiffRots(*(float *)(self+0xF8),mat_fast_helper_a(g_hero_state.target[0]-*(float *)(self+0x10),g_hero_state.target[1]-*(float *)(self+0x14))) < 1.5707964897155762f) {
                if (FastVecLength(g_hero_state.velocity) > 0.01f) vars->timer114 = 120;
                else math_fast_float_d(&vars->timer114);
        } else if (vars->timer114) {
            vars->timer114 = 0;
            qcopy(vars->direction,g_hero_state.target);
        }
        if (math_fast_float_d(&vars->timer118)) {
            float randomTurn;
            vars->timer118 = FloatToInt(math_random_float_range(180.0f,300.0f));
            randomTurn = FastAddRotations(*(float *)(self+0xF8),math_random_float_range(-90.0f,90.0f)*0.01745329424738884f);
            pitch = math_random_float_range(0.0f,30.0f)*0.01745329424738884f;
            vec_build_spherical_offset(vars->direction,6.0f,randomTurn,pitch);
            FastVecAdd(vars->direction,vars->direction,self+0x10);
        }
        if (vars->timer114) {
            qcopy(target,g_hero_state.target);
            rate = 0.04f;
        } else qcopy(target,vars->direction);
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
        *(float *)((u8 *)vars+0x64) = pitch;
        *(float *)((u8 *)vars+0x68) = turn*0.6f;
        *(float *)((u8 *)vars+0xE8) = turn*0.4f;
    }
    if (g_unlocked_item_flags) *(float *)((u8 *)vars+0x70) = 2.75f;
    TurnJoint(self,vars,0,rate);
    TurnJoint(self,(u8 *)vars+0x80,1,rate);
    if (vars->partner) moby_copy_joint_transform_to_object(self,vars->partner,2,0);
}

/* func_L12_003BE7D0 is defined in L12_003BE7D0-g8.c. */



/* func_L12_003D4110 is defined in L12_00398E50-spring-g8.c. */

/* func_L12_003DE4B0 is defined in L12_00398E50-g8.c (this unit has no $gp access for it). */

/* func_L12_003DF9A0 is defined in L12_00398E50-waypoint-g8.c. */

/* func_L12_003E04B8 is defined in L12_003E04B8-g8.c. */


/* func_L12_003E0858 is defined in L12_00398E50-launch-qcopy.c. */


/* func_L12_003E0BF0 is defined in L12_003E0BF0-g16.c. */

/* func_L12_003E1638 is defined in L12_00398E50-g8.c. */


/* Raises the measured flag on every record of the object's own table. */
/* Alerts every Mutant Test-Squirrel in the same group as this object. */
void squirrel_alert_group(s32 object) {
    s32 moby_base;
    s16 *entry;
    s16 *table;

    if (*(u8 *)(object + 0x21) == 0xFF)
        return;
    table = g_moby_l12_group_lists[*(u8 *)(object + 0x21)];
    if (table == 0)
        return;
    entry = table;
    moby_base = g_moby_list_start;
    do {
        u32 offset = (*(u16 *)entry & 0x7FFF) << 8;

        if (*(s8 *)(moby_base + offset + 0x20) >= 0) {
            if (*(s16 *)(moby_base + offset + 0xAA) == MOBY_CLASS_MUTANT_TEST_SQUIRREL)
                *(u16 *)(*(u32 *)(moby_base + offset + 0x68) + 0x366) = 1;
        }
    } while (*entry++ >= 0);
}

extern s32 *g_path_zone_table[];
extern s32 point_in_path_xy(void *, void *, s32);
extern void anim_start_blended(void *, s32, s32, s32);
extern void moby_set_state(void *, s32, s32);

/* Finds the Mutant Test-Squirrel in a group whose zone contains the given object, wakes it up
   and makes it go for that object. */
u8 *squirrel_alert_for_object(s32 index, u8 *obj)
{
    u16 *list = g_moby_l12_group_lists[index];
    u16 *entry;
    u8 *found = 0;

    if (list == 0) {
        return 0;
    }
    entry = list;
    do {
        u8 *rec = (u8 *)g_moby_list_start + (*entry & 0x7FFF) * 0x100;

        if (*(s16 *)(rec + 0xAA) == MOBY_CLASS_MUTANT_TEST_SQUIRREL) {
            u8 *vars = *(u8 **)(rec + 0x68);
            s32 *zone = g_path_zone_table[*(s32 *)(vars + 0x138)];

            if (point_in_path_xy(obj + 0x10, zone + 4, zone[0]) != 0) {
                if (rec[0x20] == 9) {
                    *(u16 *)(rec + 0x34) = (*(u16 *)(rec + 0x34) & 0xFFBE) | 0x1000;
                    *(s32 *)(rec + 0x98) = *(s32 *)(*(u8 **)(rec + 0x24) + 0x10);
                    if (rec[0x43] != 5) {
                        anim_start_blended(rec, 5, 0, 10);
                    }
                    moby_set_state(rec, 10, -1);
                } else if (rec != 0 && rec[0x20] != 0xFE && rec[0x20] != 0xFD) {
                    moby_set_state(rec, 11, 4);
                    if (rec[0x43] != 7) {
                        anim_start_blended(rec, 7, 0, 0x14);
                    }
                }
                *(u8 **)(vars + 0x374) = obj;
                found = rec;
                break;
            }
        }
    } while ((s16)*entry++ >= 0);
    return found;
}

/* func_L12_003EB470 is defined in L12_00398E50-g8.c. */

/* func_L12_00402B48 is defined in L12_00402B48-g16.c. */

/* func_L12_00402DF8 is defined in L12_00402DF8-g8.c. */

/* func_L12_00404778 is defined in L12_00398E50-g8.c (it reads a pointer through $gp). */


/* func_L12_00412548 is defined in L12_00398E50-collision.c. */

/* func_L12_00412898 is defined in L12_00412898-g8.c. */


/* func_L12_00412E50 is defined in L12_00412E50-g8.c. */

/* func_L12_00413108 is defined in L12_00413108-por.c. */

/* func_L12_004135A8 is defined in L12_00398E50-init-g8.c. */


/* Handles the guard being hurt. When it is hit or dies, it hands its helper objects over to
   its partner object and resets itself. */
void guard_handle_hit_handover(u8 *moby) {
    u8 *vars = *(u8 **)(moby+0x68);
    int old_state, hit_result;
    if (!moby[0x95]) InitStateDataWithPartner(moby);
    if (moby[0xA8] == 255) {
        u8 *partner=*(u8 **)(vars+0x2F8);
        if (partner && *(short *)(partner+0xAA)==0x114B /* moby class 4427 */ && partner[0x20]!=254 && partner[0x20]!=253) {
            int index;
            if (partner[0xA8]!=255) {
                TodanoPartnerSlot *slots=g_contact_l12_push_table;
                index=partner[0xA8];
                if (slots[index].object==partner) {
                    moby[0xA8]=index;
                    slots[moby[0xA8]].object=moby;
                }
            }
        }
    }
    old_state=moby[0x20];
    hit_result=moby_apply_damage_to_object(moby,vars+0x50,0);
    if (hit_result) {
        enemy_apply_stored_values_helper(moby);
        if (*(u8 **)(vars+0x2F8)) {
            if (hit_result==4) {
                u8 *p; int i; int alive;
                *(u16 *)(moby+0x34)&=0xEFFF;
                *(u16 *)(*(u8 **)(vars+0x2F8)+0x34)&=0xEFFF;
                *(u16 *)(*(u8 **)(vars+0x2F8)+0x7C)|=0x300;
                *(int *)(vars+0x20)=0;
                p=*(u8 **)(*(u8 **)(vars+0x2F8)+0x68);
                *(TodanoPartnerBlock *)(p+0x20)=*(TodanoPartnerBlock *)(vars+0x20);
                part_spawn_damage_debris(*(u8 **)(vars+0x2F8),p+0x50,p+0x20);
                path_hand_state_to_nearest(moby);
                SpawnExplosionEffects(*(u8 **)(vars+0x2F8),vars+0xD0,0,0,0,4,0,0,2,1,9,1,-1,0,0,0,-1,0,0x810001);
                moby_destroy_linked(moby);
                if (old_state>=4 && !math_random_int_below(2)) {
                    if (moby[0x43]!=17) anim_start_blended(moby,17,0,5);
                    *(float *)(vars+0xB0)=*(s8 *)(vars+0xBF);
                    *(float *)(vars+0xA4)=*(s8 *)(vars+0xBE);
                    *(int *)(vars+0xCC)=-1;
                    FastVecScale(vars+0xD0,vars+0xD0,0.05f);
                } else qzero(vars+0xD0);
                alive=1;
                p=vars+0x2F0;
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
                p=*(u8 **)(*(u8 **)(vars+0x2F8)+0x68);
                *(TodanoPartnerBlock *)(p+0x20)=*(TodanoPartnerBlock *)(vars+0x20);
                part_spawn_damage_debris(*(u8 **)(vars+0x2F8),p+0x50,p+0x20);
                anim_start_blended(*(u8 **)(vars+0x2F8),moby[0x43],0,3);
                *(float *)(*(u8 **)(vars+0x2F8)+0x48)=*(float *)(moby+0x48);
                if (!(*(u16 *)(*(u8 **)(vars+0x2F8)+0x7C)&0x80)) {
                    vars[0x30F]=1;
                    if(moby[0x95]!=9) func_31E1D0(moby,13,8);
                }
                { u8 *partner=*(u8 **)(vars+0x2F8);
                if(!(*(u16 *)(partner+0x7C)&0x10)) *(u16 *)(partner+0x7C)|=0x100; }
                { u8 *partner=*(u8 **)(vars+0x2F8);
                if(!(*(u16 *)(partner+0x7C)&0x20)) *(u16 *)(partner+0x7C)|=0x200; }
                for(i=0;i<2;i++) {
                    p=vars+0x2F0+i*4;
                    other=*(u8 **)p;
                    if(other && !((*(u16 *)(*(u8 **)(vars+0x2F8)+0x7C)>>(i+4))&1)) {
                        *(u16 *)(other+0x34)&=0xFFFD;
                        *(u8 **)p=0;
                    }
                }
            }
        }
    }
    if(moby[0x31] && fast_vec_dist(moby+0x10,g_hero_prev_position)<24.0f) {
        moby_update_ground_check(moby); moby[0x6F]=22;
    }
    weapon_select_aim_target(moby,*(int *)(vars+0x2D8),0,0,0,0);
    guard_update_aim_point(moby);
}

/* Aims the guard's partner object and its two hand objects at the target, and shakes them
   randomly when the guard is stunned. */
void guard_aim_partner_hands(u8 *moby) {
    u8 *vars=*(u8 **)(moby+0x68); float offset[4]; int i;
    u8 *p=*(u8 **)(vars+0x2F8);
    if(p && *(short *)(p+0xAA)==0x114B /* moby class 4427 */ && p[0x20]!=254 && p[0x20]!=253) {
        moby_copy_color(moby,p);
        moby_transform_joint_to_world(moby,0,*(u8 **)(vars+0x2F8)+0x10);
        math_approach_target_with_direction_mode(*(u8 **)(vars+0x2F8)+0xF8,vars+0x2FC,0,*(float *)(vars+0x2EC),*(float *)(vars+0x114),*(float *)(vars+0x118),*(float *)(vars+0x11C));
        *(float *)(*(u8 **)(vars+0x2F8)+0x48)=*(float *)(moby+0x48);
        if(moby[0x20]>=1 && moby[0x20]<=3) guard_spray_flame_sprites(moby);
        if(*(int *)(vars+0x204)==1 && !vars[0x30F]) {
            moby_transform_joint_to_world(*(u8 **)(vars+0x2F8),4,offset);
            FastVecSub(offset,vars+0x1F0,offset);
            *(float *)(vars+0x274)=fast_subtract_rotations(-mat_fast_helper_a(vec_length_xy(offset),offset[2]),*(float *)(*(u8 **)(vars+0x2F8)+0xF4));
            *(float *)(vars+0x278)=fast_subtract_rotations(mat_fast_helper_a(offset[0],offset[1]),*(float *)(*(u8 **)(vars+0x2F8)+0xF8));
        }
        moby_update_eased_node(*(u8 **)(vars+0x2F8),vars+0x210,3,0.02f,0.3f);
        if(!vars[0x30F] && (*(u8 **)(vars+0x2F8))[0x42]>=8 && (*(u8 **)(vars+0x2F8))[0x42]<11) {
                for(i=0;i<2;i++) {
                    u8 *joint_vars=vars+i*0x80;
                    if((*(u16 *)(*(u8 **)(vars+0x2F8)+0x7C)>>(i+4))&1) {
                        moby_transform_joint_to_world(*(u8 **)(vars+0x2F8),i,offset);
                        FastVecSub(offset,vars+0x1F0,offset);
                        *(float *)(joint_vars+0x384)=-mat_fast_helper_a(vec_length_xy(offset),offset[2]);
                        *(float *)(joint_vars+0x388)=fast_subtract_rotations(mat_fast_helper_a(offset[0],offset[1]),*(float *)(*(u8 **)(vars+0x2F8)+0xF8));
                        if(i) { if(*(float *)(joint_vars+0x388)>0.087266475f) *(float *)(joint_vars+0x388)=0.087266475f; }
                        else { if(*(float *)(vars+0x388)<-0.087266475f) *(float *)(vars+0x388)=-0.087266475f; }
                    }
                }
        } else if(vars[0x30F]) {
            u8 *joint_vars=vars;
            for(i=1;i>=0;i--,joint_vars+=0x80) {
                *(float *)(joint_vars+0x384)=math_random_float_range(-1.57079637f,1.57079637f)*0.5f;
                *(float *)(joint_vars+0x388)=math_random_float_range(-1.57079637f,1.57079637f)*0.5f;
            }
        }
        for(i=0;i<2;i++) moby_update_eased_node(*(u8 **)(vars+0x2F8),vars+0x320+i*0x80,i+7,0.02f,0.3f);
    }
}

/* Clears the measured state word and, for the tracked object, the mirror. */
void guard_clear_hit_value(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);
    u8 *tracked;

    *(s32 *)(object + 0x98) = 0;
    tracked = *(u8 **)(state + 0x2F8);
    if (tracked != 0) {
        if (*(s16 *)(tracked + 0xAA) == 0x114B /* moby class 4427 */) {
            if (*(u8 *)(tracked + 0x20) != 0xFE) {
                if (*(u8 *)(tracked + 0x20) != 0xFD)
                    *(s32 *)(tracked + 0x98) = 0;
            }
        }
    }
}

/* Copies the tracked object's timer into the state word, for both objects. */
void guard_restore_hit_value(u8 *object) {
    if (object != 0) {
        if (*(u8 *)(object + 0x20) != 0xFE) {
            if (*(u8 *)(object + 0x20) != 0xFD) {
                u8 *tracked;
                *(s32 *)(object + 0x98) = *(s32 *)(*(u8 **)(object + 0x24) + 0x10);
                tracked = *(u8 **)(*(u8 **)(object + 0x68) + 0x2F8);
                if (tracked != 0) {
                    if (*(s16 *)(tracked + 0xAA) == 0x114B /* moby class 4427 */) {
                        if (*(u8 *)(tracked + 0x20) != 0xFE) {
                            if (*(u8 *)(tracked + 0x20) != 0xFD)
                                *(s32 *)(tracked + 0x98) = *(s32 *)(*(u8 **)(tracked + 0x24) + 0x10);
                        }
                    }
                }
            }
        }
    }
}

/* Registers the measured two-slot primitive on the given object. */
void gfx_add_two_glow_sprites(u8 *object) {
    s32 buffer[4];

    func_315148(object, 2, buffer);
    func_2F0A60(buffer, 0x2E, 0x8080FFFF, 1, 0.25f, 0.0f, 0.0f);
    func_2F0A60(buffer, 0xC, 0x8020F020, 1, 0.25f, 0.0f, 0.0f);
}

/* Advances the measured state machine of the given object. */
void rising_object_update(u8 *object) {
    switch (object[0x20]) {
    case 0:
        if (func_32D988(object) != 0)
            func_31E1D0(object, 1, -1);
        break;
    case 1:
        if (*(f32 *)(object + 0x18) < 160.0f)
            *(f32 *)(object + 0x18) = *(f32 *)(object + 0x18) + 0.0833333358f;
        break;
    }
}

/* Re-arms the measured two-slot primitive after the counter step. */
void joint_pair_advance_counter(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);
    u16 counter;

    func_322AF8(object, state + 0x50);
    func_326948(object, state + 0x6C0, 1, 0.03f, 0.3f);
    func_326948(object, state + 0x640, 0, 0.03f, 0.3f);
    counter = *(u16 *)(object + 0x96);
    if (counter <= 0xFFFE)
        *(u16 *)(object + 0x96) = counter + 1;
}

/* Resets the measured slot state and re-arms the primitive. */
void joint_slots_reset_advance(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);
    u16 counter;

    func_322AF8(object, state + 0x50);
    func_2F15C8(state + 0x360);
    func_2F15C8(state + 0x362);
    counter = *(u16 *)(object + 0x96);
    if (counter <= 0xFFFE)
        *(u16 *)(object + 0x96) = counter + 1;
    func_326948(object, state + 0x240, 1, 0.03f, 0.3f);
    func_326948(object, state + 0x2C0, 0, 0.03f, 0.3f);
}

/* Opens the measured window and starts the sub-object. */
void spinning_effect_update_todano(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);
    u8 *record;
    s32 index;

    if (*(u8 *)(object + 0x20) == 0) {
        *(u8 *)(object + 0x20) = 1;
        *(u8 *)(object + 0x30) = 0x20;
        *(u16 *)(object + 0x32) = 0x20;
        *(s32 *)(state + 0) = -1;
    }
    *(f32 *)(object + 0xF8) = func_2F2950(*(f32 *)(object + 0xF8), 0.017453294f);
    index = *(s32 *)(state + 0);
    record = g_hero_l12_state_records + index * 0x70;
    if (*(u8 **)(record + 0x88) != object || *(u8 *)(record + 0x74) == 0)
        *(s32 *)(state + 0) = func_364DF8(0, 4, object);
    if (func_3205F8(object, 0x10000, 0) != 0)
        func_314008(object);
}
