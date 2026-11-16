#include "include_asm.h"
/* func_US2_L19_0042BE14, the USA v2.00 copy of func_L19_0042A9A0: the same C, plus
 * `object[0x30] = 0xff;` in case 0 and a call to func_US2_L19_0042BBF8 at the top of the
 * `if (object[0x20])` block. */
#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
typedef struct { u8 prefix[0x30]; int field30,field34,field38,field3c,field40,field44; } L19UtilityQueueView;
extern int g_frame_l19_counter[] __attribute__((sda));
extern int g_glow_state_flags[4] __attribute__((sda));
extern int g_hero_l19_mode __attribute__((sda));
extern u8 *g_moby_l19_array __attribute__((sda));
extern u8 g_unlocked_item_flags[] __attribute__((sda));
extern u32 g_glow_class_flags;
extern L19UtilityQueueView g_request_l19_queue;
typedef union { u8 b[0x2600]; s32 i[0x980]; f32 f[0x980]; Quadword q[0x260]; } Hero;
extern u8 g_hero_state[];
extern void mystic_glow_all(void);
extern int func_US2_L19_0042BBF8(void);
extern int text_sum_subtitle_lengths(void);
extern void moby_mark_spawned(void *);
extern void moby_set_state(u8 *,u8,int);
extern void moby_reset_vars_defaults(char *);
extern int hero_is_reachable_for_count(u8 *,int,float);
extern void level_apply_index_for_key(u8 *);
extern int req_push_queue(u8 *,int);
extern int req_launch_queued(L19UtilityQueueView *);
extern int game_is_either_mode_two(void);
extern int FastDecTimer(void *);
extern int math_fast_float_d(void *);
extern float math_random_float_range(float,float);
extern int FloatToInt(float);
extern void anim_start_blended(u8 *,int,int,int);
extern float vec_distance_xy(void *,void *);
extern float mat_fast_helper_a(float,float);
extern float FastDiffRots(float,float);
extern float FastVecLength(void *);
extern float FastAddRotations(float,float);
extern void vec_build_spherical_offset(float *,float,float,float);
extern void FastVecAdd(void *,void *,void *);
extern void FastVecSub(void *,void *,void *);
extern float fast_subtract_rotations(float,float);
extern float vec_length_xy(void *);
extern void moby_update_eased_node(void *,void *,int,float,float);

void func_US2_L19_0042BE14(u8 *object)
{
    Vector target, origin, direction;
    u8 *state = *(u8 **)(object + 0x68);
    float rate, yaw, pitch, rotation, radians;
    int aiming;
    float blend = 0.3f;

    mystic_glow_all();
    if (g_frame_l19_counter[0] == 5) text_sum_subtitle_lengths();
    switch (object[0x20]) {
    case 0:
        object[0x30] = 0xff;
        text_sum_subtitle_lengths();
        if (g_glow_class_flags & 0x4000000) {
            if (*(int *)(state+0x124) != -1)
                moby_mark_spawned(g_moby_l19_array + *(int *)(state+0x124)*0x100);
            *(int *)(state+0x124) = -1;
            moby_mark_spawned(object);
            return;
        }
        if (g_glow_class_flags & 0x1000000) {
            moby_mark_spawned(object);
            return;
        }
        moby_set_state(object,1,-1);
        moby_reset_vars_defaults((char *)object);
        break;
    case 1:
        if (hero_is_reachable_for_count(object,10,2.5f)) {
            level_apply_index_for_key(object);
            if (req_push_queue((u8 *)&g_request_l19_queue,0x98)) {
                req_launch_queued(&g_request_l19_queue);
                moby_set_state(object,2,-1);
            }
        }
        break;
    case 2:
        g_glow_state_flags[1] = 1;
        if (g_hero_l19_mode == 2) {
            object[0x31]=0;
            *(u16 *)(object+0x34) |= 1;
        }
        if (!game_is_either_mode_two()) {
            g_glow_state_flags[1] = 0;
            object[0x31] = 1;
            *(u16 *)(object+0x34) &= 0xfffe;
            moby_mark_spawned(object);
            return;
        }
        break;
    }
    if (object[0x20]) {
        func_US2_L19_0042BBF8();
        if (object[0x43] == 1 && FastDecTimer(state+0x11e)) {
            *(short *)(state+0x11e) = FloatToInt(math_random_float_range(1200.0f,2400.0f));
            if (object[0x43] != 2) anim_start_blended(object,2,0,10);
        } else if (object[0x60] & 2) {
            if (object[0x43] != 1) anim_start_blended(object,1,0,10);
        }
    }
    aiming = 0;
    rate = 0.02f;
    if (object[0x43] == 1) {
        aiming = 1;
        if (vec_distance_xy(object+0x10,&((Hero *)g_hero_state)->q[8]) < 8.0f &&
            FastDiffRots(*(float *)(object+0xf8),
                mat_fast_helper_a(((Hero *)g_hero_state)->f[0xe0 / 4]-*(float *)(object+0x10),
                             ((Hero *)g_hero_state)->f[0xe4 / 4]-*(float *)(object+0x14))) < 1.5707965f) {
            if (FastVecLength(&((Hero *)g_hero_state)->q[0x110 / 16])>0.01f) *(int *)(state+0x114)=120;
            else math_fast_float_d(state+0x114);
        } else if (*(int *)(state+0x114)) {
            *(int *)(state+0x114)=0;
            qcopy(state+0x100, &((Hero *)g_hero_state)->q[0xe0 / 16]);
        }
        if (math_fast_float_d(state+0x118)) {
            radians=0.017453294f;
            *(int *)(state+0x118)=FloatToInt(math_random_float_range(180.0f,300.0f));
            rotation=FastAddRotations(*(float *)(object+0xf8),math_random_float_range(-90.0f,90.0f)*radians);
            vec_build_spherical_offset((float *)(state+0x100),6.0f,rotation,math_random_float_range(0.0f,30.0f)*radians);
            FastVecAdd(state+0x100,state+0x100,object+0x10);
        }
        if (*(int *)(state+0x114)) {
            qcopy(&target, &((Hero *)g_hero_state)->q[0xe0 / 16]);
            rate=0.04f;
        } else qcopy(&target, state+0x100);
    }
    if (aiming) {
        qcopy(&origin, object+0x10);
        origin.f[2]+=2.0f;
        FastVecSub(&direction,&target,&origin);
        yaw=fast_subtract_rotations(mat_fast_helper_a(direction.f[0],direction.f[1]),*(float *)(object+0xf8));
        pitch=-mat_fast_helper_a(vec_length_xy(&direction),direction.f[2]);
        if (yaw>1.5707965f) yaw=1.5707965f;
        else if (yaw< -1.5707965f) yaw= -1.5707965f;
        if (pitch>0.52359885f) pitch=0.52359885f;
        else if (pitch< -0.52359885f) pitch= -0.52359885f;
        *(float *)(state+0x64)=pitch;
        *(float *)(state+0x68)=yaw*0.6f;
        *(float *)(state+0xe8)=yaw*0.4f;
    }
    if (g_unlocked_item_flags[0]) *(float *)(state+0x70)=1.9f;
    moby_update_eased_node(object,state,0,rate,blend);
    moby_update_eased_node(object,state+0x80,1,rate,blend);
}
