#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
typedef struct { int action[4]; } ActionChoices;
extern int g_hero_tether_enabled;
extern ActionChoices g_creature_action_choices;
extern float g_creature_float_threshold __attribute__((sda));
extern float g_hero_position[4];
extern int flying_creature_update_state(unsigned char *);
extern void moby_set_state(unsigned char *, int, int);
extern unsigned long moby_dispatch_action_by_kind(void *, void *);
extern void group_destroy_attached_parts(char *, char *);
extern void SetDeathBits(void *, int, int);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern int PlayMobySound(int, int, char *);
extern void *SpawnExplosion(void *, int, int, int, int, int, int, int, int, int, int, void *, float, float);
extern void mat_get_euler_angles(float *, float *);
extern void vec_scale_to_length(void *, void *, float);
extern void part_spawn_masked_debris(char *, int, float *, float, float, float, float, unsigned char);
extern void moby_mark_spawned(void *);
extern int math_random_int_range(int, int);
extern int flag_set_first_pending(unsigned char *);
extern int math_random_int_below(int);
extern void anim_start_blended(void *, int, int, int);
extern int moby_check_target_point_from_offset(char *, void *);
extern int moby_aim_at_target_offset(char *, char *);
extern float coll_sample_height_at_position(unsigned char *, void *, void *);
extern float math_fabs(float);
extern float moby_get_anim_value(char *);
extern int coll_sweep_from_object(void *, void *, int, int, int, int, float, float, float);
extern void creature_tick_timers(void *);

/* Per-frame update for the moby of class 3214: a creature that picks between idle, walking and
   attack animations, and blows up in a burst of effects when it dies. */
void creature_update(unsigned char *object) {
    /* Mutually exclusive uses of the same 16-byte retail workspace. */
    union { ActionChoices choices; Vector position; } workspace;
    Vector seed;
    Vector velocity;
    char *private;
    unsigned long flags;
    float time;
    int next;
    int i;
    if (!g_hero_tether_enabled) return;
    private = *(char **)(object + 0x68);
    if (flying_creature_update_state(object)) { moby_mark_spawned(object); return; }
    switch (object[0x95]) {
    case 0:
        if (*(short *)(private + 0x224) == 1) {
            if (object[0x20] == 1) moby_set_state(object, 4, 2);
            else moby_set_state(object, 5, 2);
        } else if (*(short *)(private + 0x226)) {
            moby_set_state(object, 3, 1);
            *(short *)(private + 0x226) = 0;
            if (*(short *)(private + 0x220) < 300)
                *(short *)(private + 0x220) = math_random_int_range(480, 600);
        }
        break;
    case 1:
        if (*(short *)(private + 0x224) == 1)
            moby_set_state(object, 5, 2);
        else if (*(short *)(private + 0x220) == 0 && (object[0x60] & 2))
            moby_set_state(object, 2, 0);
        break;
    case 2:
        if (*(short *)(private + 0x224) != 1 && object[0x20] != 6) {
            moby_set_state(object, 3, 1);
            *(short *)(private + 0x220) = math_random_int_range(580, 600);
        }
        break;
    case 3:
        flags = moby_dispatch_action_by_kind(object, private + 0x50);
        if (((flags & 1UL) == 1UL) || *(float *)(private + 0x20) <= 0.0f) {
            group_destroy_attached_parts((char *)object, private + 0x270);
            SetDeathBits(object, 0, 3);
            seed.q = 0;
            seed.f[2] = 1.0f;
            matrix_mul_vec3(&workspace.position, &seed, object + 0xC0);
            FastVecAdd(&workspace.position, &workspace.position, object + 0x10);
            PlayMobySound(13, 0, (char *)object);
            SpawnExplosion(&workspace.position, 0, 25, 20, 20, 20, 45, 0, 0, 1, 0, 0, 0.8f, 20.0f);
            mat_get_euler_angles((float *)(object + 0xC0), (float *)(object + 0xF0));
            vec_scale_to_length(&velocity, private + 0xD0, 0.083333336f);
            part_spawn_masked_debris((char *)object, 0x3F8, velocity.f, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
            moby_mark_spawned(object);
            return;
        }
        if (((flags & 2UL) == 2UL) || (unsigned char)private[0x6A] > 1) {
            moby_set_state(object, 6, 2);
            *(short *)(private + 0x220) = math_random_int_range(580, 600);
        }
        break;
    }
    switch (object[0x20]) {
    case 2:
        if (flag_set_first_pending(object) && object[0x43] != 2)
            anim_start_blended(object, 2, 0, 20);
        break;
    case 3:
        workspace.choices = g_creature_action_choices;
        if (flag_set_first_pending(object) && object[0x43] != workspace.choices.action[math_random_int_below(4)])
            anim_start_blended(object, workspace.choices.action[math_random_int_below(4)], 0, 20);
        moby_check_target_point_from_offset((char *)object, g_hero_position);
        if (object[0x60] & 2) {
            next = workspace.choices.action[math_random_int_below(4)];
            if (next == object[0x43]) next = (next + math_random_int_below(3)) % 4;
            if (object[0x43] != next) anim_start_blended(object, next, 0, 20);
        }
        break;
    case 4:
        if (flag_set_first_pending(object) && object[0x43] != 4)
            anim_start_blended(object, 4, 0, 10);
        if (object[0x60] & 2) moby_set_state(object, 5, -1);
        break;
    case 5:
        if (flag_set_first_pending(object) && object[0x43] != 8)
            anim_start_blended(object, 8, 0, 20);
        moby_aim_at_target_offset((char *)object, private + 0x1F0);
        if ((*(float *)(private + 0x1CC) < g_creature_float_threshold) &&
            (math_fabs(coll_sample_height_at_position(object, private + 0x1F0, private + 0x230)) < 0.17453295f))
            moby_set_state(object, 6, -1);
        break;
    case 6:
        if (flag_set_first_pending(object) && object[0x43] != 9)
            anim_start_blended(object, 9, 8, 20);
        if (object[0x60] & 2) moby_set_state(object, 5, -1);
        time = moby_get_anim_value((char *)object);
        if (object[0x42] == object[0x43] && time >= 18.0f && time <= 24.0f) {
            for (i = 0; i < 2; i++)
                coll_sweep_from_object(object, *(char **)(private + 0x270 + i * 4) + 0x10,
                              0x4000001, 0, 1, 0, 0.333f, (float)(unsigned char)private[0x34], 1.0f);
        }
        break;
    }
    creature_tick_timers(object);
    return;
}
