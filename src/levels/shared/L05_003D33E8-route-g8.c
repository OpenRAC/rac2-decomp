#include "common.h"
typedef union { int q __attribute__((mode(TI))); float f[4]; } Vector;
extern int state_get_stored_pointer_value(void);
extern void moby_init_effect_from_table(void *);
extern void level_append_object(int, int, int, int);
extern void func_L05_00417730(void *);
extern int moby_get_motion_data(void *);
extern void follower_set_state(void *, unsigned int);
extern void follower_set_push_vector(void *, void *);
extern int follower_has_reached_target(void *);
extern void moby_update_movement_state(void *);
extern void moby_check_player_in_view_and_range(void *, int, float);
extern float fast_vec_dist(void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float FastVecDot(void *, void *);
extern int math_fast_float_d(void *);
extern int snd_play_from_class_bank(int, int, void *, int);
extern float math_random_float_range(float, float);
extern int FloatToInt(float);
extern void part_l05_spawn_tail_trail_marks(void *);
extern int D_L05_001B0F50 __attribute__((sda));
extern int D_L05_00221D48 NOT_SDA;
extern char *D_L05_001FE380[];
extern char *D_L05_001B251C MACRO_ADDR;
extern u8 g_sound_state[];

typedef struct { u8 pad[0x11C]; int mode; } Movement;
/* Moves the object along a route of points each frame and restarts it from the route start
   when it is new. */
void func_L05_004170C8(u8 *actor)
{
    Vector direction, facing;
    u8 *state = *(u8 **)(actor + 0x68);
    u8 *movement;
    char *path;
    int one, mode;
    if (actor[0x20] == 0) {
        actor[0x30] = 0xFF;
        if (state_get_stored_pointer_value() == 0)
            return;
        moby_init_effect_from_table(actor);
        if (*(int *)(state + 0x1B4) != 0)
            level_append_object((int)actor, (int)func_L05_00417730, 0, 0);
        D_L05_001B0F50 = 0;
        return;
    }
    movement = (u8 *)moby_get_motion_data(actor);
    if (*(int *)(movement + 0x110) == 0)
        return;
    path = D_L05_001FE380[D_L05_00221D48];
    one = 1;
    follower_set_state(actor, 11);
    if (*(int *)(state + 0x1B8) == 0) {
        *(int *)(state + 0x1B8) = one;
        *(int *)(state + 0x1BC) = one;
        qcopy(actor + 0x10, path + 0x10);
        *(int *)(state + 0x1BC) = 2;
        follower_set_push_vector(actor, path + 0x20);
        FastVecSub(movement + 0x90, movement + 0x60, actor + 0x10);
        vec_scale_to_length(movement + 0x90, movement + 0x90, 1.0f);
        *(int *)(movement + 0x130) = 2000000;
    } else if (follower_has_reached_target(actor) != 0) {
        int next = *(int *)(state + 0x1BC);
        if (next >= *(int *)path)
            D_L05_001B0F50 = one;
        else {
            *(int *)(state + 0x1BC) = next + 1;
            follower_set_push_vector(actor, path + (next * 16 + 16));
            *(int *)(movement + 0x130) = 2000000;
        }
    }
    if (D_L05_001B0F50 == 0) {
        moby_update_movement_state(actor);
        moby_check_player_in_view_and_range(actor, 1, 32.0f);
    }
    mode = *(int *)(movement + 0x110);
    if (mode == 1) {
        if (*(int *)(state + 0x1B0) != -1) {
            u8 *other;
            ((Movement *)movement)->mode = mode;
            other = (u8 *)D_L05_001B251C + (*(int *)(state + 0x1B0) << 8);
            *(u8 **)(movement + 0x120) = other;
            if (fast_vec_dist(other + 0x10, actor + 0x10) < 15.0f) {
                float alignment;
                FastVecSub(&direction, actor + 0x10, *(u8 **)(movement + 0x120) + 0x10);
                vec_scale_to_length(&direction, &direction, 1.0f);
                vec_scale_to_length(&facing, *(u8 **)(movement + 0x120) + 0xC0, 1.0f);
                alignment = FastVecDot(&facing, &direction);
                if (alignment > 0.4f) {
                    if (math_fast_float_d(state + 0x1C8) != 0) {
                        *(int *)(state + 0x1C4) = snd_play_from_class_bank(14, 0, actor, 0xFBF);
                        *(int *)(state + 0x1C8) = FloatToInt(math_random_float_range(180.0f, 240.0f));
                    }
                } else if (alignment < -0.4f && math_fast_float_d(state + 0x1C8) != 0) {
                    snd_play_from_class_bank(11, 0, actor, 0xFBF);
                    *(int *)(state + 0x1C8) = FloatToInt(math_random_float_range(180.0f, 240.0f));
                }
            }
        }
        part_l05_spawn_tail_trail_marks(actor);
    }
    {
        u8 *sound = g_sound_state + *(int *)(state + 0x1C0) * 0x70;
        if (*(u8 **)(sound + 0x88) != actor || sound[0x74] == 0)
            *(int *)(state + 0x1C0) = snd_play_from_class_bank(0, 6, actor, 0xF82);
    }
}
