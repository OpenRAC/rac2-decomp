/* func_PAL_L13_00420460, the PAL copy of func_L13_0041B670: the same C with 50 Hz rates, where mode 0 also resets
 * D_PAL_001B16F8 from D_001A7904, and the locked sound can come from D_PAL_001A7988 (as v2.00's func_US2_L30_0040D208).
 * Each sound keeps its own call: jump2 cross-jumps them. */
#include "common.h"

typedef struct { float acceleration, deceleration, speed; } MotionSettings_L13;
typedef struct {
    int primary, secondary, flagA, flagB;   /* 0x00 */
    char pad10[0x10];
    float f20, f24;                         /* 0x20 */
    int i28, i2C;                           /* 0x28 */
    char pad30[4];
    float timer;                            /* 0x34 */
    int enabled, busy, locked;              /* 0x38 */
} RingState_L13;
typedef struct {
    char pad0[0x10];
    float position[4];                      /* 0x10 */
    u8 mode;                                /* 0x20 */
    char pad21[0x68 - 0x21];
    RingState_L13 *state;                   /* 0x68 */
    char pad6C[0xF0 - 0x6C];
    char fF0[8];                            /* 0xF0 */
    float fF8;                              /* 0xF8 */
    char padFC[4];
} Ring_L13;
typedef struct {
    char pad0[0x33C];
    Ring_L13 *target;                       /* 0x33C */
    char pad340[0x34E - 0x340];
    short busy;                             /* 0x34E */
} Hero_L13_0041B670;
extern Hero_L13_0041B670 g_hero_state;
extern int g_current_map_index;
extern unsigned char g_moby_group_flags[];
extern unsigned int g_pad_held_flags[];
extern int g_warp_ring_state;
extern Ring_L13 *g_object_table_base;
extern unsigned char g_grab_flag[];
extern MotionSettings_L13 g_warp_ring_motion_settings __attribute__((sda));
extern int g_arena_state_flag;
extern int g_current_level_set __attribute__((sda));
extern int g_level_toggle_flag __attribute__((sda));
extern void warp_ring_show_message_pal(Ring_L13 *);
extern int PlayMobySound(int, int, Ring_L13 *);
extern void hero_start_target_state(float *, int, float);
extern int coll_sweep_from_object(void *, void *, int, int, int, int, float, float, float);
extern int hero_get_target_state_kind(void);
extern void hero_reset_position_and_direction(void *, void *, int, int);
extern void data_set_small_value_and_refresh(int, int);
extern void DrawMobyRadiusRing(void *);
extern void gfx_add_draw_callback_first(void (*)(void *), void *);
extern float ApproachValue(float *, float, float);
extern float math_step_value_toward_target(float *, float *, float, float, float, float);

/* Updates a warp ring: while the hero stands on it and presses the button, takes the hero
 * to the linked ring (PAL: 50 Hz rates). */
void warp_ring_update_pal(Ring_L13 *object)
{
    float position[4] __attribute__((aligned(16)));
    RingState_L13 *state = object->state;
    Ring_L13 *destination;
    RingState_L13 *target_state;
    int code;

    if (state->enabled == 0)
        return;
    switch (object->mode) {
    case 0:
        object->mode = 1;
        g_level_toggle_flag = 0;
        if (g_arena_state_flag == 1) {
            g_level_toggle_flag = 1;
            g_arena_state_flag = 0;
        }
        return;
    case 1:
        if (state->flagA >= 0 && !(g_moby_group_flags[state->flagA + g_current_map_index * 16] & 0x80))
            return;
        if (state->primary == -1 && state->locked == 0 && state->busy == 0)
            return;
        if (g_hero_state.target != object || g_hero_state.busy != 0)
            return;
        warp_ring_show_message_pal(object);
        if (!(g_pad_held_flags[0] & 0x10))
            return;
        if (g_warp_ring_state == 11) {
            PlayMobySound(0, 0, object);
            object->mode = 2;
            state->i28 = 0;
            state->i2C = 0;
            hero_start_target_state(object->position, 0, object->fF8);
            coll_sweep_from_object(object, object->position, 0x10000, 0, 1, 0, 1.5f, 20.0f, 1.0f);
        }
        return;
    case 2:
        code = hero_get_target_state_kind();
        if (code == 2) {
            state->timer = 1.95f;
            object->mode = 3;
        } else if (code == 0) {
            object->mode = 4;
        }
        return;
    case 3:
        if (state->timer == 0.0f) {
            if (state->busy == 0 && state->locked == 0) {
                destination = &g_object_table_base[state->primary];
                if (state->secondary != -1 && (g_moby_group_flags[state->flagB + g_current_map_index * 16] & 0x80))
                    destination = &g_object_table_base[state->secondary];
                target_state = destination->state;
                qcopy(position, destination->position);
                position[2] += 0.2f;
                hero_reset_position_and_direction(position, destination->fF0, 0, 1);
                g_grab_flag[0] = 1;
                destination->mode = 4;
                target_state->timer = 0.0f;
                target_state->i28 = 0;
                target_state->i2C = 0;
                target_state->f20 = 1.0f;
                target_state->f24 = 1.0f;
                PlayMobySound(1, 0, destination);
                object->mode = 1;
                state->timer = 1.95f;
                state->f24 = 0;
                state->i28 = 0;
                state->i2C = 0;
                state->f20 = 0;
            } else {
                if (state->locked) {
                    if (g_level_toggle_flag)
                        data_set_small_value_and_refresh(g_current_level_set, 1);
                    else
                        data_set_small_value_and_refresh(13, 1);
                } else {
                    data_set_small_value_and_refresh(21, 1);
                }
            }
            return;
        }
        gfx_add_draw_callback_first(DrawMobyRadiusRing, object);
        ApproachValue(&state->timer, 0.0f, 0.080000006f);
        return;
    case 4:
        if (state->timer < 1.95f) {
            gfx_add_draw_callback_first(DrawMobyRadiusRing, object);
            ApproachValue(&state->timer, 1.95f, 0.080000006f);
            return;
        }
        if (state->f24 > 0.0f) {
            math_step_value_toward_target(&state->f24, (float *)&state->i28, 0.0f,
                g_warp_ring_motion_settings.acceleration * 0.00040000002f,
                g_warp_ring_motion_settings.deceleration * 0.00040000002f,
                g_warp_ring_motion_settings.speed * 0.020000001f);
            return;
        }
        if (state->f20 > 0.0f) {
            math_step_value_toward_target(&state->f20, (float *)&state->i2C, 0.0f,
                g_warp_ring_motion_settings.acceleration * 0.00040000002f,
                g_warp_ring_motion_settings.deceleration * 0.00040000002f,
                g_warp_ring_motion_settings.speed * 0.020000001f);
            return;
        }
        object->mode = 1;
    }
}
