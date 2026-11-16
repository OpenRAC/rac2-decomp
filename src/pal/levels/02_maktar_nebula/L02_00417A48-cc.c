/* func_PAL_L02_00417A48, the PAL copy of func_L02_00412D50: the same C, where rename func_002A7470 becomes func_PAL_002A7E68; rename func_L00_002C42E0 becomes func_PAL_L00_002C4480; rename func_L00_002B9D60 becomes func_PAL_L00_002B9CD8; rename func_L02_00413730 becomes func_PAL_L02_00418428. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 quad; float f[4]; } LiftVector;
typedef struct {
    u8 pad0[0x80];
    float position[4];
    u8 pad90[0x33C - 0x90];
    u8 *lift;
    s32 active;
    u8 pad344[0x22B6 - 0x344];
    u8 boarding;
} LiftHero;
extern LiftHero g_hero_state;
typedef struct {
    u8 pad0[0x60];
    s32 launch_nodes[2];
    s32 cameras[2];
    u8 pad70[8];
    s32 flag;
    s32 stops[2];
    s32 sound;
    u8 pad88[8];
    LiftVector position;
    LiftVector rotation;
    u8 padB0[12];
    s32 side;
    u8 padC0[12];
    float speed;
} LiftState;
extern u8 g_moby_group_flags[];
typedef struct { u8 bytes[0x70]; } LiftSoundStride;
extern LiftSoundStride g_sound_state[];
extern u8 g_inventory_have_flags[] __attribute__((sda));
extern s32 g_current_map_index[] MACRO_ADDR;
typedef struct {
    LiftVector axes[3];
    LiftVector position;
    u8 pad40[0x30];
    LiftVector rotation;
} LiftNode;
extern LiftNode *g_matrix_l02_record_table MACRO_ADDR;
extern s32 g_frame_l02_counter[] MACRO_ADDR;
extern float g_grab_highlight_level[] MACRO_ADDR;
extern float g_lift_target_speed __attribute__((sda));
extern float g_lift_accel_step __attribute__((sda));
extern LiftVector g_lift_probe_offset __attribute__((sda));
extern float g_lift_sweep_radius[] MACRO_ADDR;
extern char g_str_lift_distance[];
extern u8 g_camera_l02_position[];
extern void math_trap_always(void);
extern void moby_set_state(u8 *, s32, s32);
extern void func_PAL_002A7E68(void *, s32, s32, s32);
extern void scale_vector(void *, void *, float);
extern s32 math_fast_helper_a(void *, float);
extern void moby_mark_spawned(void *);
extern void FastVecSub(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern float vec_length_xy(void *);
extern void vec_transform_by_object_or_given(char *, char *, char *, char *);
extern double __extendsfdf2(float);
extern void STUB_printf(const char *, ...);
extern int func_PAL_L00_002C4480(s32, s32);
extern float vec_distance_xy(void *, void *);
extern void cam_set_mode_state(s32);
extern s32 flag_set_first_pending(u8 *);
extern void SetCamera5Pose(void *, void *, s32, s32, s32);
extern void hero_start_target_state(void *, s32, float);
extern s32 PlayMobySound(s32, s32, char *);
extern float ApproachValue(float *, float, float);
extern void vec_scale_to_length(void *, void *, float);
extern s32 coll_sweep_from_object(void *, void *, u32, float, float, float, s32, s32, s32);
extern float mat_fast_helper_a(float, float);
extern float StepAngleTowardTarget(float *, s32, float, float);
extern void object_copy_vector_to_selected(void *);
extern void cam_set_state_rotation(void *);
extern void snd_stop_voice(s32);
extern void anim_start_immediate(s8 *, s32, s32);
extern void euler_rotation_basis(void *, void *);
extern void FastVecScale(void *, void *, float);
extern void hero_reset_position_and_direction_pal(void *, void *, s32, s32);
extern void cam_reset_entry(s32);
extern void func_PAL_L02_00418428(u8 *);
extern void mat_combine_and_store(void *, void *, void *, void *);

/*
 * Move between the two lift poses, coordinating the camera and boarding state.
 * -G16 and the qcopy flags are this unit's own; its gp-relative data does not fit -G8.
 * func_002AA800 returns a float (it ends by calling func_002AA738, like its sibling
 * func_002AA898): the ignored call_value is what orders the yaw loads.
 */
void func_PAL_L02_00417A48(u8 *object)
{
    LiftVector old_position;
    LiftVector old_rotation;
    LiftVector delta;
    LiftVector point;
    LiftVector aim;
    LiftVector launch;
    LiftVector rotation;
    LiftState *state = *(LiftState **)(object + 0x68);
    s32 side;
    float distance;
    float target;
    s32 i;

    qcopy_nc(&old_position, (object + 0x10));
    qcopy_nc(&old_rotation, (object + 0xF0));
    switch (object[0x20]) {
    case 0: {
        s32 index;
        object[0x30] = 0xFF;
        state->sound = -1;
        if (state->stops[0] == -1 || state->stops[1] == -1) {
            moby_mark_spawned(object);
            return;
        }
        if (state->launch_nodes[0] == -1 || state->launch_nodes[1] == -1)
            math_trap_always();
        if (state->cameras[0] == -1 || state->cameras[1] == -1)
            math_trap_always();
        if (state->flag != -1) {
            if (g_inventory_have_flags[0x1E]) {
                moby_mark_spawned(object);
                return;
            }
            *(s32 *)(object + 0x98) = 0;
            {
                s16 flags = (*(u16 *)(object + 0x34) | 0x41) & 0xEFFF;
                *(u16 *)(object + 0x34) = flags;
            }
            moby_set_state(object, 4, -1);
        } else
            moby_set_state(object, 1, -1);
        if (object[0x43] != 2)
            func_PAL_002A7E68(object, 2, 0, 1);
        index = state->stops[0];
        qcopy_nc(&state->position, &g_matrix_l02_record_table[index].position);
        qcopy_nc(&state->rotation, &g_matrix_l02_record_table[index].rotation);
        break;
    }
    case 4:
        if (g_moby_group_flags[state->flag + (g_current_map_index[0] << 4)] & 0x80) {
            scale_vector(&delta, object, 0.0009765625f);
            if (math_fast_helper_a(&delta, 64.0f) == -1) {
                s16 flags = (*(u16 *)(object + 0x34) & 0xFFBE) | 0x1000;
                *(u16 *)(object + 0x34) = flags;
                *(u32 *)(object + 0x98) = *(u32 *)(*(u8 **)(object + 0x24) + 0x10);
                moby_set_state(object, 1, -1);
            }
        }
        break;
    case 1: {
        LiftNode *record;
        if (state->flag != -1 && g_inventory_have_flags[0x1E]) {
            moby_mark_spawned(object);
            return;
        }
        if (g_hero_state.lift == object && g_hero_state.active) {
            FastVecSub(&delta, g_hero_state.position, object + 0x10);
            point.quad = 0;
            point.f[0] = -1.2f;
            point.f[2] = -0.69f;
            matrix_mul_vec3(&point, &point, object + 0xC0);
            FastVecAdd(&point, &point, object + 0x10);
            FastVecSub(&aim, &point, g_hero_state.position);
            distance = vec_length_xy(&aim);
            vec_transform_by_object_or_given((char *)object, (char *)&delta, (char *)&delta, 0);
            if (delta.f[2] < -0.6f) {
                STUB_printf(g_str_lift_distance, __extendsfdf2(distance));
                func_PAL_L00_002C4480(0x6F, 1);
                moby_set_state(object, 2, -1);
            }
        } else if ((g_frame_l02_counter[0] & 0x3F) == 0) {
            float current;
            side = (state->side + 1) & 1;
            record = &g_matrix_l02_record_table[state->stops[side]];
            distance = vec_distance_xy(g_hero_state.position, &record->position);
            record = &g_matrix_l02_record_table[state->stops[state->side]];
            current = vec_distance_xy(g_hero_state.position, &record->position);
            if (distance < current) {
                s32 index;
                state->side = side;
                index = state->stops[side];
                qcopy_nc(&state->position, &g_matrix_l02_record_table[index].position);
                qcopy_nc(&state->rotation, &g_matrix_l02_record_table[index].rotation);
                qcopy_nc((object + 0x10), (&state->position));
                qcopy_nc((object + 0xF0), (&state->rotation));
            }
        }
        break;
    }
    case 2: {
        LiftNode *record;
        s32 count;
        u32 layer;
        if (g_hero_state.active == 0) {
            cam_set_mode_state(0);
            break;
        }
        if (flag_set_first_pending(object)) {
            SetCamera5Pose(g_camera_l02_position, g_camera_l02_position + 0x10, 1, 0, 0);
            delta.quad = 0;
            delta.f[0] = -1.2f;
            delta.f[2] = -0.69f;
            matrix_mul_vec3(&delta, &delta, object + 0xC0);
            FastVecAdd(&delta, &delta, object + 0x10);
            hero_start_target_state(&delta, 0, *(float *)(object + 0xF8));
            g_hero_state.boarding = 1;
            PlayMobySound(1, 0, (char *)object);
            if (object[0x43])
                func_PAL_002A7E68(object, 0, 0, 37);
        }
        ApproachValue(&state->speed, g_lift_target_speed * 0.020000001f, g_lift_accel_step * 0.00040000002f);
        vec_scale_to_length(&delta, object + 0xC0, state->speed);
        delta.f[2] = 0.0f;
        FastVecAdd(&state->position, &state->position, &delta);
        i = 0;
        count = 2;
        layer = 0x10000;
        do {
            qcopy_nc(&point, &g_lift_probe_offset);
            if (i)
                point.f[1] = -point.f[1];
            matrix_mul_vec3(&point, &point, object + 0xC0);
            FastVecAdd(&point, &point, object + 0x10);
            coll_sweep_from_object(object, &point, layer, g_lift_sweep_radius[0], 1.0f, 1.0f, 0, 1, 0);
        } while (++i < count);
        qcopy_nc(&point, g_camera_l02_position);
        point.f[2] += 0.020000001f;
        qcopy_nc(&aim, (g_camera_l02_position + 0x10));
        distance = vec_distance_xy(&point, g_hero_state.position);
        target = mat_fast_helper_a(distance, g_hero_state.position[2] - point.f[2]);
        StepAngleTowardTarget(aim.f + 1, 0, -target, 0.015707966f);
        target = mat_fast_helper_a(g_hero_state.position[0] - point.f[0], g_hero_state.position[1] - point.f[1]);
        StepAngleTowardTarget(aim.f + 2, 0, target, 0.031415932f);
        object_copy_vector_to_selected(&point);
        cam_set_state_rotation(&aim);
        {
            u16 previous = *(u16 *)(object + 0x96);
            s32 ticks = previous + 1;
            {
                s16 stored = ticks;
                *(u16 *)(object + 0x96) = stored;
            }
            if (previous >= 101)
                ApproachValue(&g_grab_highlight_level[0], 1.0f, 0.040000003f);
            else {
                s32 slot;
                u8 *sound_record;
                if ((u16)ticks == 37)
                    func_PAL_L00_002C4480(0x6F, 1);
                slot = state->sound;
                sound_record = (u8 *)&g_sound_state[slot];
                if (*(u8 **)(sound_record + 0x88) != object || !sound_record[0x74])
                    state->sound = PlayMobySound(0, 4, (char *)object);
            }
        }
        if (g_grab_highlight_level[0] >= 1.0f) {
            s32 slot;
            func_PAL_L00_002C4480(0, 1);
            slot = state->sound;
            if (slot != -1) {
                u8 *sound_record = (u8 *)&g_sound_state[slot];
                if (*(u8 **)(sound_record + 0x88) == object && sound_record[0x74])
                    snd_stop_voice(slot);
            }
            state->sound = -1;
            anim_start_immediate((s8 *)object, 2, 0);
            moby_set_state(object, 3, -1);
            state->side = (state->side + 1) & 1;
            {
                s32 index = state->stops[state->side];
                qcopy_nc(&state->position, &g_matrix_l02_record_table[index].position);
                qcopy_nc(&state->rotation, &g_matrix_l02_record_table[index].rotation);
            }
            euler_rotation_basis(object + 0xC0, &state->rotation);
            record = &g_matrix_l02_record_table[state->launch_nodes[state->side]];
            FastVecScale(&launch, record, -0.9f);
            FastVecAdd(&launch, &launch, &record->position);
            qcopy_nc(&rotation, (&record->rotation));
            hero_reset_position_and_direction_pal(&launch, &rotation, 0, 1);
            hero_start_target_state(&record->position, 1, record->rotation.f[2]);
            cam_set_mode_state(0);
            cam_reset_entry(state->cameras[state->side]);
            func_PAL_L02_00418428(object);
        }
        break;
    }
    case 3:
        ApproachValue(&g_grab_highlight_level[0], 0.0f, 0.040000003f);
        if (g_grab_highlight_level[0] <= 0.0f) {
            state->speed = 0.0f;
            moby_set_state(object, 1, -1);
        }
        break;
    }
    if (object[0x31])
        func_PAL_L02_00418428(object);
    FastVecSub(&delta, object + 0x10, &old_position);
    mat_combine_and_store((u8 *)state + 0x20, &delta, &old_rotation, object + 0xF0);
}
