/* func_L05_003D15E8, in a unit of its own (default flags), where its callees are external. The
   sub-object's fields are struct members, so its stores do not order the object table's load
   (retail loads the table pointer before the index). */
#include "common.h"

/* The record func_002ED688 hands back for an object (func_L05_0037B948 sets 0x104 and 0x108
   from its tests on the target). */
struct Sub_003D15E8 {
    /* 0x000 */ char pad000[0x104];
    /* 0x104 */ int f104;
    /* 0x108 */ int f108;
    /* 0x10C */ int pad10C;
    /* 0x110 */ int mode;
    /* 0x114 */ int pad114[2];
    /* 0x11C */ int targetMode;
    /* 0x120 */ char *target;
};

/* The table of live objects, 0x100 bytes each. */
extern char *D_L05_001B251C MACRO_ADDR;
/* The sound records, 0x70 bytes each. */
extern char g_sound_state[];

extern void *state_get_stored_pointer_value(char *);
extern struct Sub_003D15E8 *moby_get_motion_data(char *);
extern void moby_init_state_and_position(char *);
extern void vec_clear_128(void *);
extern void level_append_object(char *, void *, int, int);
extern void blast_hook_empty(void);
extern void AttachManipulator(char *, int, void *);
extern void moby_update_movement_state(char *);
extern int moby_process_collision_hit(char *, int, int, int);
extern void moby_check_player_in_view_and_range(char *, int, float);
extern float fast_vec_dist(void *, void *);
extern int math_random_int_below(int);
extern int snd_play_from_class_bank(int, int, char *, int);
extern int follower_get_state(char *);
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_sin_or_cos_a(float);
extern void moby_spawn_effect_after_guards(char *);
extern int moby_can_take_next_step(char *);
extern int list_count_objects_matching_value(char *, int);
extern void moby_l05_set_state_value(char *, int);
extern void moby_start_movement_state(char *);
extern int math_fast_float_d(void *);
extern void func_L05_003D1AB8(char *);

/* The object's update: on its first frame it sets itself up; afterwards, while its record is
   active, it aims at the object its state names (with a chance of a sound when close), turns
   its two vectors, may take its next step, and keeps its looping sound playing. */
/* Runs the object each frame, aiming at its target, firing and keeping its looping sound alive. */
void func_L05_003D15E8(char *obj)
{
    char *state = *(char **)(obj + 0x68);
    struct Sub_003D15E8 *sub;
    float tmp[4];
    int one, mode;

    if (!*(unsigned char *)(obj + 0x20)) {
        *(unsigned char *)(obj + 0x30) = 0xff;
        if (!state_get_stored_pointer_value(obj))
            return;
        moby_init_state_and_position(obj);
        vec_clear_128(tmp);
        if (*(int *)(state + 0x264))
            level_append_object(obj, blast_hook_empty, 0, 0);
        AttachManipulator(obj, 2, state + 0x270);
        AttachManipulator(obj, 3, state + 0x2b0);
        return;
    }
    sub = moby_get_motion_data(obj);
    if (!sub->mode)
        return;
    one = 1;
    moby_update_movement_state(obj);
    moby_process_collision_hit(obj, 0, 0, 0);
    moby_check_player_in_view_and_range(obj, 1, 32.0f);
    mode = sub->mode;
    if (mode == one) {
        if (*(int *)(state + 0x260) != -1) {
            sub->targetMode = mode;
            sub->target = D_L05_001B251C + (*(int *)(state + 0x260) << 8);
            if (fast_vec_dist(sub->target + 0x10, obj + 0x10) < 10.0f) {
                char *sound1 = g_sound_state + *(int *)(state + 0x2f4) * 0x70;

                if ((*(char **)(sound1 + 0x88) != obj || !*(unsigned char *)(sound1 + 0x74))
                    && !math_random_int_below(750))
                    *(int *)(state + 0x2f4) = snd_play_from_class_bank(14, 0, obj, 0xfbf);
            }
        }
        vec_clear_128(state + 0x280);
        vec_clear_128(state + 0x2c0);
        if (follower_get_state(obj) == 8) {
            *(float *)(state + 0x284) = math_fast_sin_or_cos_b(0.78539824f);
            *(float *)(state + 0x28c) = math_fast_sin_or_cos_a(0.78539824f);
            *(float *)(state + 0x2c4) = math_fast_sin_or_cos_b(0.78539824f);
            *(float *)(state + 0x2cc) = math_fast_sin_or_cos_a(0.78539824f);
            if (sub->f108)
                moby_spawn_effect_after_guards(obj);
        } else {
            *(float *)(state + 0x2cc) = *(float *)(state + 0x28c) = 1.0f;
            if (sub->f108 && sub->f104)
                moby_spawn_effect_after_guards(obj);
        }
        if (moby_can_take_next_step(obj)) {
            if (list_count_objects_matching_value(obj, 5) <= 0)
                moby_l05_set_state_value(obj, 5);
            else
                moby_l05_set_state_value(obj, 1);
            moby_start_movement_state(obj);
        }
        math_fast_float_d(state + 0x268);
        func_L05_003D1AB8(obj);
    }
    {
        char *sound2 = g_sound_state + *(int *)(state + 0x2f0) * 0x70;

        if (*(char **)(sound2 + 0x88) != obj || !*(unsigned char *)(sound2 + 0x74))
            *(int *)(state + 0x2f0) = snd_play_from_class_bank(1, 6, obj, 0x97c);
    }
}
