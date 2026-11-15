#include "include_asm.h"


#include "common.h"
struct Sub_003D15E8 {
      char pad000[0x104];
      int f104;
      int f108;
      int pad10C;
      int mode;
      int pad114[2];
      int targetMode;
      char *target;
};
extern char *D_L05_001B251C MACRO_ADDR;
extern char g_sound_state[];
extern void *state_get_stored_pointer_value(char *);
extern struct Sub_003D15E8 *moby_get_motion_data(char *);
extern void func_PAL_L05_003D5628(char *);
extern void vec_clear_128(void *);
extern void level_append_object(char *, void *, int, int);
extern void moby_l00_update_empty_3(void);
extern void AttachManipulator(char *, int, void *);
extern void func_PAL_L05_0037E8E0(char *);
extern int moby_process_collision_hit(char *, int, int, int);
extern void moby_check_player_in_view_and_range(char *, int, float);
extern float fast_vec_dist(void *, void *);
extern int math_random_int_below(int);
extern int snd_play_from_class_bank(int, int, char *, int);
extern int follower_get_state(char *);
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_sin_or_cos_a(float);
extern void func_PAL_L05_003D5738(char *);
extern int moby_can_take_next_step(char *);
extern int list_count_objects_matching_value(char *, int);
extern void moby_l05_set_state_value(char *, int);
extern void func_PAL_L05_0037DE20(char *);
extern int math_fast_float_d(void *);
extern void func_PAL_L05_003D5800(char *);

/* The object's update: on its first frame it sets itself up; afterwards, while its record is
   active, it aims at the object its state names (with a chance of a sound when close), turns
   its two vectors, may take its next step, and keeps its looping sound playing. */
void func_PAL_L05_003D5330(char *obj)
{
    char *state = *(char **)(obj + 0x68);
    struct Sub_003D15E8 *sub;
    float tmp[4];
    int one, mode;

    if (!*(unsigned char *)(obj + 0x20)) {
        *(unsigned char *)(obj + 0x30) = 0xff;
        if (!state_get_stored_pointer_value(obj))
            return;
        func_PAL_L05_003D5628(obj);
        vec_clear_128(tmp);
        if (*(int *)(state + 0x264))
            level_append_object(obj, moby_l00_update_empty_3, 0, 0);
        AttachManipulator(obj, 2, state + 0x270);
        AttachManipulator(obj, 3, state + 0x2b0);
        return;
    }
    sub = moby_get_motion_data(obj);
    if (!sub->mode)
        return;
    one = 1;
    func_PAL_L05_0037E8E0(obj);
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
                func_PAL_L05_003D5738(obj);
        } else {
            *(float *)(state + 0x2cc) = *(float *)(state + 0x28c) = 1.0f;
            if (sub->f108 && sub->f104)
                func_PAL_L05_003D5738(obj);
        }
        if (moby_can_take_next_step(obj)) {
            if (list_count_objects_matching_value(obj, 5) <= 0)
                moby_l05_set_state_value(obj, 5);
            else
                moby_l05_set_state_value(obj, 1);
            func_PAL_L05_0037DE20(obj);
        }
        math_fast_float_d(state + 0x268);
        func_PAL_L05_003D5800(obj);
    }
    {
        char *sound2 = g_sound_state + *(int *)(state + 0x2f0) * 0x70;

        if (*(char **)(sound2 + 0x88) != obj || !*(unsigned char *)(sound2 + 0x74))
            *(int *)(state + 0x2f0) = snd_play_from_class_bank(1, 6, obj, 0x97c);
    }
}



extern char *func_379CA0(char *);
extern void func_379FA0(char *, int, int, int, float, float, float, float, int, int, int);
extern int func_332AB8(int);
extern void func_3719A8(int, int, char *, int);

/* Spawns the object's effect after three guards, then runs the timer. */
void func_PAL_L05_003D5738(char *object)
{
    char *s1 = *(char **)(object + 0x68);
    char *r;

    r = func_379CA0(object);
    if (r == 0)
        return;
    if (*(int *)(r + 0x120) == 0)
        return;
    if (*(int *)(s1 + 0x268) != 0)
        return;
    func_379FA0(object, 0x60000090, 1, 0, 0.6f, 2.0f, 1.0f, 1.3f, 0, -1, 0);
    if (func_332AB8(3) == 0)
        func_3719A8(0, 0, object, 0x97C);
    *(int *)(s1 + 0x268) = 0x32;
}

