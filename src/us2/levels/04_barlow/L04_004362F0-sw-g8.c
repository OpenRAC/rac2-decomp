#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
#define COST ((WeaponSettings *)(D_L04_0027B470 + D_00139568[0x27]*0xE0))->cost
#define INT(p,o) (*(int *)((char *)(p)+(o)))
#define FLOAT(p,o) (*(float *)((char *)(p)+(o)))
#define HALF(p,o) (*(short *)((char *)(p)+(o)))
#define UHALF(p,o) (*(u16 *)((char *)(p)+(o)))
extern u8 g_skill_point_zone_flag, g_level_event_flag NOT_SDA, g_level_event_byte, g_unlocked_item_flags;
extern unsigned g_pad_held_flags NOT_SDA;
extern u32 g_request_flag_table[];
extern int g_current_map_index MACRO_ADDR;
extern int g_player_bolts[] __attribute__((sda));
typedef struct {
    u8 prefix[0x80]; float position[4]; u8 gap90[0x50];
    float target[4]; u8 gapF0[0x20]; float velocity[4];
} ResidentPlayerPrefix;
extern u8 g_moby_nibble_table[];
extern ResidentPlayerPrefix g_hero_state;
typedef struct { u8 prefix[0x80]; int cost; u8 tail[0x5C]; } WeaponSettings;
extern u8 g_item_l04_record_table[];
extern u8 g_item_slot_to_record[];
extern char *g_moby_l04_pool[] __attribute__((sda));
extern int g_game_tick_counter, g_game_l04_mode;
extern int g_cutscene_flags[] __attribute__((sda));
extern char g_request_l04_queue[];
typedef struct { u8 pad[0x464]; u8 active[0]; } SlotFlagView;
typedef struct { u8 pad[0x9c]; int x9c; } OtherVars;
extern SlotFlagView g_slot_flag_view_a, g_slot_flag_view_b;
extern void moby_reset_matching_effects_alt(char *);
extern void moby_mark_spawned(char *);
extern void anim_start_blended(void *,int,int,int);
extern void moby_set_state(void *,int,int);
extern void moby_reset_vars_defaults(char *);
extern void *CreateMoby(int);
extern void func_002A0F48(void *);
extern void hero_copy_field_to_moby(u8 *);
extern int hero_is_reachable_for_count(u8 *,int,float);
extern void level_apply_index_for_key(int);
extern int req_push_queue(u8 *,int);
extern int req_launch_queued(void *);
extern int game_is_either_mode_two(void);
extern float FastAddRotations(float,float);
extern void hero_reset_position_and_direction(void *,void *,int,int);
extern void moby_set_byte_on_group(int,int);
extern int subtitle_request_voice_line_us2(int,int);
extern int IsPointInCuboid(void *,int);
extern void func_L00_0030C710(int);
extern void value_set_entry_by_index_us2(int,int);
extern int MemcardSave(int,int);
extern void text_print_localized_formatted(int,int,int);
extern void moby_update_eased_node(void *,void *,int,float,float);
extern float vec_distance_xy(void *,void *);
extern float mat_fast_helper_a(float,float);
extern float FastDiffRots(float,float);
extern float vec_length_xy(void *);
extern int math_fast_float_d(int *);
extern float math_random_float_range(float,float);
extern int FloatToInt(float);
extern void moby_copy_joint_transform_to_object(void *,void *,int,int);
extern void FastVecAdd(void *,void *,void *);
extern void FastVecSub(void *,void *,void *);
extern float FastVecLength(void *);
extern void help_unlock_entry(int);
extern float fast_subtract_rotations(float,float);
extern void vec_build_spherical_offset(float *,float,float,float);
extern int moby_handle_request_slot_state(int);

/* Offers the item in slot 0x27 of D_00139568 for sale: compares the currency with
   its cost, and on purchase plays a cutscene, charges the cost and clears the
   linked object's flags. D_L04_001B2224[1] is set while the cutscene runs. */
void UpdateBarlowItemVendor_us2(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    union { Quad q; float f[4]; } target, rotation, difference;
    float smoothing;
    float blend = 0.3f;
    int facing;
    moby_reset_matching_effects_alt(moby);

    switch ((u8)moby[0x20]) {
    case 0: {
        char *child;
        if (g_game_tick_counter < 2) return;
        if (g_skill_point_zone_flag) {
            char *other;
            unsigned index;
            int save;
            other = g_moby_l04_pool[0] + INT(vars,0x124)*256;
            other[0x20] = 2;
            (*(OtherVars **)(other+0x68))->x9c = 0;
            save = g_current_map_index<<10;
            g_slot_flag_view_a.active[HALF(other,0xb2)] = 0;
            g_slot_flag_view_b.active[HALF(other,0xb2)] = 0;
            index = UHALF(other,0xb2);
            {
                u8 *entry = &g_moby_nibble_table[((short)index>>1)+save];
                unsigned flags = *entry;
                unsigned value = flags & 0xf8;
                if (index&1) value = flags & 0x8f;
                *entry = value;
            }
            if (INT(vars,0x12c) != -1) moby_mark_spawned(g_moby_l04_pool[0] + INT(vars,0x12c)*256);
            moby_mark_spawned(moby);
            return;
        }
        if (g_request_flag_table[0x38 / sizeof(u32)] & 0x8000000) {
            if (((u8 *)moby)[0x43] != 1) anim_start_blended(moby,1,0,10);
            moby_set_state(moby,2,-1);
        }
        moby_reset_vars_defaults(moby);
        *(char **)(vars+0x11c) = CreateMoby(0xd99);
        child = *(char **)(vars+0x11c);
        if (child) {
            (*(char **)(vars+0x11c))[0x30] = moby[0x30];
            UHALF(*(char **)(vars+0x11c),0x32) = UHALF(moby,0x32);
            (*(char **)(vars+0x11c))[0x31] = 1;
            func_002A0F48(*(char **)(vars+0x11c));
            hero_copy_field_to_moby((u8 *)*(char **)(vars+0x11c));
        }
        moby_set_state(moby,1,-1);
        if (g_request_flag_table[0x38 / sizeof(u32)] & 0x8000000) {
            if (((u8 *)moby)[0x43] != 1) anim_start_blended(moby,1,0,10);
            moby_set_state(moby,4,-1);
            if (INT(vars,0x12c) != -1)
                moby_mark_spawned(g_moby_l04_pool[0] + INT(vars,0x12c)*256);
        }
        break;
    }
    case 1: {
        char *other = g_moby_l04_pool[0] + INT(vars,0x12c)*256;
        if (hero_is_reachable_for_count((u8 *)moby,10,4.0f) &&
            (!other || (u8)other[0x20] == 254 || (u8)other[0x20] == 253)) {
            g_level_event_flag = 1;
            FLOAT(moby,0x48) = 1.0f;
            level_apply_index_for_key((int)moby);
            req_push_queue((u8 *)g_request_l04_queue,59);
            req_launch_queued(g_request_l04_queue);
            moby_set_state(moby,2,-1);
        }
        break;
    }
    case 2:
        g_cutscene_flags[1] = 1;
        if (g_game_l04_mode == 2) {
            moby[0x31] = 0;
            UHALF(moby,0x34) |= 1;
        }
        if (!game_is_either_mode_two()) {
            target.f[0] = 338.0f;
            target.f[1] = 366.81f;
            target.f[2] = 63.0f;
            qcopy(&rotation, (moby+0xf0));
            rotation.f[2] = FastAddRotations(rotation.f[2],3.1415929794311523f);
            hero_reset_position_and_direction(&target,&rotation,0,1);
            g_cutscene_flags[1] = 0;
            moby[0x31] = 1;
            UHALF(moby,0x34) &= 0xfffe;
            if (((u8 *)moby)[0x43] != 1) anim_start_blended(moby,1,0,10);
            if (g_player_bolts[0] < COST) moby_set_state(moby,3,-1);
            else moby_set_state(moby,4,-1);
        }
        break;
    case 3:
        if (COST < g_player_bolts[0]) moby_set_state(moby,4,-1);
        else if (hero_is_reachable_for_count((u8 *)moby,10,2.5f)) {
            func_L00_0030C710(180);
            text_print_localized_formatted(0x12F2,COST,-1);
            level_apply_index_for_key((int)moby);
        }
        break;
    case 4:
        if (g_player_bolts[0] < COST) {
            func_L00_0030C710(180);
            moby_set_state(moby,3,-1);
        } else if (hero_is_reachable_for_count((u8 *)moby,10,2.5f) && IsPointInCuboid(g_hero_state.position,INT(vars,0x120))) {
            func_L00_0030C710(180);
            text_print_localized_formatted(0x12F1,COST,-1);
            level_apply_index_for_key((int)moby);
            if (g_pad_held_flags & 16) {
                req_push_queue((u8 *)g_request_l04_queue,60);
                req_launch_queued(g_request_l04_queue);
                moby_set_state(moby,5,-1);
            }
        }
        break;
    case 5: {
        char *other;
        unsigned index;
        int save;
        g_cutscene_flags[1] = 1;
        if (g_game_l04_mode == 2) {
            moby[0x31] = 0;
            UHALF(moby,0x34) |= 1;
        }
        if (!game_is_either_mode_two()) {
            target.f[0] = 338.0f;
            target.f[1] = 366.81f;
            target.f[2] = 63.0f;
            qcopy(&rotation, (moby+0xf0));
            rotation.f[2] = FastAddRotations(rotation.f[2],-1.5707964897155762f);
            hero_reset_position_and_direction(&target,&rotation,0,1);
            g_cutscene_flags[1] = 0;
            moby[0x31] = 1;
            UHALF(moby,0x34) &= 0xfffe;
            if (((u8 *)moby)[0x21] != 255) moby_set_byte_on_group(((u8 *)moby)[0x21],1);
            if (!g_skill_point_zone_flag) {
                g_player_bolts[0] = g_player_bolts[0] - COST;
                func_L00_0030C710(180);
                help_unlock_entry(39);
                moby_handle_request_slot_state(39);
                value_set_entry_by_index_us2(0x122a,-1);
            }
            if (INT(vars,0x128) != -1) g_moby_l04_pool[0][INT(vars,0x128)*256+0xbc] = 1;
            other = g_moby_l04_pool[0] + INT(vars,0x124)*256;
            other[0x20] = 2;
            (*(OtherVars **)(other+0x68))->x9c = 0;
            save = g_current_map_index<<10;
            g_slot_flag_view_a.active[HALF(other,0xb2)] = 0;
            g_slot_flag_view_b.active[HALF(other,0xb2)] = 0;
            index = UHALF(other,0xb2);
            {
                u8 *entry = &g_moby_nibble_table[((short)index>>1)+save];
                unsigned flags = *entry;
                unsigned value = flags & 0xf8;
                if (index&1) value = flags & 0x8f;
                *entry = value;
            }
            subtitle_request_voice_line_us2(0x9dc,0x33);
            MemcardSave(0,-1);
            moby_mark_spawned(moby);
            return;
        }
        break;
    }
    }
    smoothing = 0.02f;
    facing = 0;
    if ((u8)moby[0x20] >= 2) {
        FLOAT(moby,0xf0) = 0.0f;
        if (((u8 *)moby)[0x43] == 1) {
            float distance, angle;
            facing = 1;
            distance = vec_distance_xy(moby+0x10,g_hero_state.position);
            if (distance < 8.0f) {
                angle = mat_fast_helper_a(g_hero_state.target[0]-FLOAT(moby,0x10),g_hero_state.target[1]-FLOAT(moby,0x14));
                if (FastDiffRots(FLOAT(moby,0xf8),angle) < 1.5707964897155762f) {
                    if (FastVecLength(g_hero_state.velocity) > 0.01f) INT(vars,0x114) = 120;
                    else math_fast_float_d((int *)(vars+0x114));
                } else goto stopTracking;
            } else {
stopTracking:
                if (INT(vars,0x114)) {
                    INT(vars,0x114) = 0;
                    qcopy((vars+0x100), (g_hero_state.target));
                }
            }
            if (math_fast_float_d((int *)(vars+0x118))) {
                float turn = 0.01745329424738884f;
                INT(vars,0x118) = FloatToInt(math_random_float_range(180.0f,300.0f));
                angle = FastAddRotations(FLOAT(moby,0xf8),math_random_float_range(-90.0f,90.0f)*turn);
                vec_build_spherical_offset((float *)(vars+0x100),6.0f,angle,math_random_float_range(0.0f,30.0f)*turn);
                FastVecAdd(vars+0x100,vars+0x100,moby+0x10);
            }
            if (INT(vars,0x114) != 0) {
                qcopy(&target, (g_hero_state.target));
                smoothing = 0.04f;
            } else qcopy(&target, (vars+0x100));
        }
    } else {
        FLOAT(moby,0x48) = 0.0f;
        FLOAT(moby,0xf0) = -0.0872664749622345f;
    }
    if (facing) {
        float yaw, pitch;
        qcopy(&rotation, (moby+0x10));
        rotation.f[2] += 2.0f;
        FastVecSub(&difference,&target,&rotation);
        yaw = fast_subtract_rotations(mat_fast_helper_a(difference.f[0],difference.f[1]),FLOAT(moby,0xf8));
        pitch = -mat_fast_helper_a(vec_length_xy(&difference),difference.f[2]);
        if (yaw > 1.5707964897155762f) yaw = 1.5707964897155762f;
        else if (yaw < -1.5707964897155762f) yaw = -1.5707964897155762f;
        if (pitch > 0.523598849773407f) pitch = 0.523598849773407f;
        else if (pitch < -0.523598849773407f) pitch = -0.523598849773407f;
        FLOAT(vars,100) = pitch;
        FLOAT(vars,0x68) = yaw*0.6f;
        FLOAT(vars,0xe8) = yaw*0.4f;
    }
    if (g_unlocked_item_flags) FLOAT(vars,0x70) = 2.75f;
    moby_update_eased_node(moby,vars,0,smoothing,blend);
    moby_update_eased_node(moby,vars+0x80,1,smoothing,blend);
    if (INT(vars,0x11c)) moby_copy_joint_transform_to_object(moby,*(char **)(vars+0x11c),2,0);
}
