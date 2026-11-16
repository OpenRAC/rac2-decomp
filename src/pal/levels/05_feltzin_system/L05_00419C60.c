#include "include_asm.h"
#include "names.h"


extern void vec_clear_128(char *block);
extern int math_random_int_below(int kind);
extern char *moby_get_motion_data(char *object);
extern void *state_get_stored_pointer_value(char *object);
extern void level_append_object(char *object, int a1, int a2, int a3);
extern void follower_l05_update_pal(char *object);
extern int moby_process_collision_hit(char *object, int a1, int a2, int a3);
extern void moby_check_player_in_view_and_range(char *object, int a1, float a2);
extern int moby_can_take_next_step(char *object);
extern void follower_start_wander_pal(char *object);
extern int math_fast_float_d(char *block);
extern char *g_feltzin_target_mobys __attribute__((sda));
extern char g_sound_state[];
extern int snd_play_from_class_bank(int, int, char *, int);
typedef struct {
    char pad0[0x104];
    int x104, x108, pad10C, mode, pad114, pad118;
    int has_target;
    char *target;
} Target05;
extern float fast_vec_dist(char *a, char *b);
extern void feltzin_enemy_init_position_pal(char *obj);
extern void feltzin_enemy_fire_burst_shot_pal(char *object);
extern void tail_trail_spawn_marks_a_pal(char *obj);

/* Per-frame update. On the first frame it initializes the object; afterwards it points the record
   at moby state+0x260, renews the D_00188660 slot in state+0x270 near that target at random and the
   one in state+0x26C when the object no longer owns it. */
void feltzin_enemy_a_update_pal(char *object)
{
    char *state = *(char **)(object + 0x68);
    Target05 *motion;
    char *sound_rec, *near_sound_rec;
    char buf[0x10];

    if (*(unsigned char *)(object + 0x20) == 0) {
        *(unsigned char *)(object + 0x30) = 0xFF;
        if (state_get_stored_pointer_value(object) == 0)
            return;
        feltzin_enemy_init_position_pal(object);
        vec_clear_128(buf);
        if (*(int *)(state + 0x264) != 0)
            level_append_object(object, 0, 0, 0);
        return;
    }
    motion = (Target05 *)moby_get_motion_data(object);
    if (motion->mode == 0)
        return;
    {
        int one = 1;

        follower_l05_update_pal(object);
        moby_process_collision_hit(object, 0, 0, 0);
        moby_check_player_in_view_and_range(object, one, 32.0f);
        if (motion->mode == one) {
            if (*(int *)(state + 0x260) != -1) {
                motion->has_target = 1;
                motion->target = g_feltzin_target_mobys + *(int *)(state + 0x260) * 256;
                if (fast_vec_dist(motion->target + 0x10, object + 0x10) < 10.0f) {
                    near_sound_rec = g_sound_state + *(int *)(state + 0x270) * 0x70;
                    if (*(char **)(near_sound_rec + 0x88) != object ||
                        *(unsigned char *)(near_sound_rec + 0x74) == 0) {
                        if (math_random_int_below(0x190) == 0)
                            *(int *)(state + 0x270) =
                                snd_play_from_class_bank(0xE, 0, object, 0xFBF);
                    }
                }
            }
            if (motion->x104 != 0)
                feltzin_enemy_fire_burst_shot_pal(object);
            if (moby_can_take_next_step(object) != 0)
                follower_start_wander_pal(object);
            math_fast_float_d(state + 0x268);
            tail_trail_spawn_marks_a_pal(object);
        }
    }
    sound_rec = g_sound_state + *(int *)(state + 0x26C) * 0x70;
    if (*(char **)(sound_rec + 0x88) != object || *(unsigned char *)(sound_rec + 0x74) == 0)
        *(int *)(state + 0x26C) = snd_play_from_class_bank(0, 6, object, 0xF73);
}


#include "common.h"
extern void func_306630(char *dst, char *src, char *src2);
extern float func_332B50(float a, float b);
extern float func_332C18(void);
extern void func_33B330(char *dst, float a, float b, float c);
extern char *func_379CA0(char *object);
extern void func_37AEC0(char *object, int flag);
extern int g_feltzin_challenge_state[];
extern char *g_feltzin_enemy_table __attribute__((sda));

/* Sets up a new enemy: starts it at a random spot around its spawn point and resets its timers. */
void feltzin_enemy_init_position_pal(char *obj)
{
    char *state = *(char **)(obj + 0x68);
    char *table;
    float radius, angle_a, angle_b;

    *(unsigned char *)(obj + 0x20) = 1;
    *(unsigned short *)(obj + 0x34) = *(unsigned short *)(obj + 0x34) | 0x100;
    *(int *)(func_379CA0(obj) + 0x148) = 0x14;
    func_37AEC0(obj, 1);
    table = g_feltzin_enemy_table + g_feltzin_challenge_state[0] * 128;
    *(int *)(state + 0x26C) = -1;
    *(int *)(state + 0x270) = -1;
    *(float *)(state + 0x180) = 20.0f;
    *(int *)(state + 0x268) = 0;
    *(float *)(obj + 0x2C) = 0.02f;
    radius = func_332B50(0.0f, *(float *)table);
    angle_a = func_332C18();
    angle_b = func_332C18();
    func_33B330(obj + 0x10, radius, angle_a, angle_b);
    func_306630(obj + 0x10, table + 0x30, obj + 0x10);
}

extern void func_379FA0(char *object, int a1, int a2, int a3, float f0, float f1, float f2,
                        float f3, int a8, int a9, int a10);

/* Runs the object's pending effect when three guards clear, then marks the run. */
void feltzin_enemy_fire_burst_shot_pal(char *object)
{
    char *state = *(char **)(object + 0x68);
    char *effect_rec;

    effect_rec = func_379CA0(object);
    if (effect_rec == 0)
        return;
    if (*(int *)(effect_rec + 0x120) == 0)
        return;
    if (*(int *)(state + 0x268) != 0)
        return;
    if (*(unsigned char *)(object + 0x20) == 1)
        func_379FA0(object, 0x60800000, 1, 0, 0.75f, 5.0f, 1.0f, 1.0f, 0, -1, 0);
    *(int *)(state + 0x268) = 0x11;
}


extern char *feltzin_helper_create(char *a0, int a1);
extern void gfx_add_draw_callback_third(void *fn, char *object);
extern void beam_clear_record_owners(void);
extern void feltzin_enemy_init_with_helpers_pal(char *obj);
extern void feltzin_enemy_fire_shot_pal(char *object);
extern void tail_trail_spawn_marks_b_pal(char *object);
extern void beam_update_records_pal(char *obj);
extern void heavy_lancer_update(void);
extern char g_beam_records[];

/* func_L05_00415958 is defined in L05_00415958-qcopy.c. */

/* Per-frame update. On the first frame it initializes the object and, if state+0x264 is set,
   clears the owners of the 128 interpolation records; afterwards it creates the two
   func_L05_00416D68 children once, points the record at moby state+0x260, and renews the
   D_00188660 slot in state+0x274 when the object no longer owns it. */
void feltzin_enemy_b_update_pal(char *object)
{
    char *state = *(char **)(object + 0x68);
    Target05 *motion;
    char *sound_rec;
    char buf[0x10];

    if (*(unsigned char *)(object + 0x20) == 0) {
        *(unsigned char *)(object + 0x30) = 0xFF;
        if (state_get_stored_pointer_value(object) == 0)
            return;
        feltzin_enemy_init_with_helpers_pal(object);
        vec_clear_128(buf);
        if (*(int *)(state + 0x264) != 0) {
            char *base;
            int *p;
            int i;

            level_append_object(object, (int)beam_clear_record_owners, 0, 0);
            base = g_beam_records;
            p = (int *)(base + 0x27F0);
            i = 0x7F;
            do {
                *p = 0;
                p -= 0x14;
                i--;
            } while (i >= 0);
        }
        return;
    }
    motion = (Target05 *)moby_get_motion_data(object);
    if (motion->mode == 0)
        return;
    if (*(int *)(state + 0x26C) == 0 && *(int *)(state + 0x270) == 0) {
        *(int *)(state + 0x26C) = (int)feltzin_helper_create(object, 0);
        *(int *)(state + 0x270) = (int)feltzin_helper_create(object, 1);
        *(float *)(*(int *)(state + 0x26C) + 0x2C) = *(float *)(object + 0x2C);
        *(float *)(*(int *)(state + 0x270) + 0x2C) = *(float *)(object + 0x2C);
    }
    {
        int one = 1;

        follower_l05_update_pal(object);
        moby_process_collision_hit(object, 0, 0, 0);
        moby_check_player_in_view_and_range(object, one, 32.0f);
        if (motion->mode == one) {
            if (*(int *)(state + 0x260) != -1) {
                motion->has_target = 1;
                motion->target = g_feltzin_target_mobys + *(int *)(state + 0x260) * 256;
            }
            if (motion->x108 != 0 && motion->x104 != 0)
                feltzin_enemy_fire_shot_pal(object);
            if (moby_can_take_next_step(object) != 0)
                follower_start_wander_pal(object);
            math_fast_float_d(state + 0x268);
            tail_trail_spawn_marks_b_pal(object);
        }
    }
    sound_rec = g_sound_state + *(int *)(state + 0x274) * 0x70;
    if (*(char **)(sound_rec + 0x88) != object || *(unsigned char *)(sound_rec + 0x74) == 0)
        *(int *)(state + 0x274) = snd_play_from_class_bank(1, 6, object, 0xF76);
    beam_update_records_pal(object);
    gfx_add_draw_callback_third(heavy_lancer_update, object);
}
