#include "include_asm.h"
#include "names.h"

extern char *moby_get_motion_data(unsigned char *owner);
extern int coll_is_point_inside_unit_sphere(unsigned char *a, int b);
extern void moby_release_motion_slot(unsigned char *owner);
extern void follower_start_push_from_target(char *a0);
extern int g_moby_motion_state_words[];

/* Checks if the follower touches one of the listed hazard spots; if so, it dies and switches to state 13. */
void follower_check_hazard_contact_pal(unsigned char *owner)
{
    int i;
    unsigned int state;

    if (g_moby_motion_state_words[36] == 0)
        return;
    if (moby_get_motion_data(owner) == 0)
        return;
    state = follower_get_state(owner);
    if (state == 0xB)
        return;
    if (state == 0xD)
        follower_set_state(owner, 1);
    for (i = 0; i < g_moby_motion_state_words[36]; i++) {
        if (coll_is_point_inside_unit_sphere(owner + 0x10, g_moby_motion_state_words[39 + i])) {
            moby_release_motion_slot(owner);
            follower_set_state(owner, 0xD);
            follower_start_push_from_target((char *)owner);
            break;
        }
    }
}

typedef int V4_Fb6552688 __attribute__((mode(TI)));
extern void func_00282CC0_26(char *, V4_Fb6552688 *, char *);
extern void follower_clamp_push_vector(char *);
extern float math_random_angle(void);
extern float math_fast_sin_or_cos_a(float a0);
extern float math_fast_sin_or_cos_b(float a0);
extern float math_random_float_range(float a0, float a1);
extern char *g_follower_tuning_table __attribute__((sda));

/* Gives the follower a random starting push, clamps it, and sets its life timer to 250 (PAL). */
void follower_start_random_push_pal(unsigned char *owner)
{
    char *object;
    char *table;
    float push_x;
    float push_y;

    object = (char *)moby_get_motion_data(owner);
    if (object == 0)
        return;
    table = g_follower_tuning_table + g_moby_motion_state_words[0] * 128;
    push_x = math_fast_sin_or_cos_a(math_random_angle()) * math_random_float_range(0.0f, *(float *)table);
    *(float *)(object + 0x60) = push_x;
    push_y = math_fast_sin_or_cos_b(math_random_angle()) * math_random_float_range(0.0f, *(float *)table);
    *(float *)(object + 0x68) = 0.0f;
    *(float *)(object + 0x64) = push_y;
    func_00282CC0_26(object + 0x60, (V4_Fb6552688 *)(table + 0x30), object + 0x60);
    *(float *)(object + 0x68) = math_random_float_range(-64.0f, 64.0f) + *(float *)((char *)owner + 0x18);
    follower_clamp_push_vector((char *)owner);
    *(int *)(object + 0x130) = 250;
}

extern char *func_002ED688_1(char *);
extern void func_00282F20_10(V4_Fb6552688 *, char *, float);

/* Calls a callee with the object, returns when it fails, otherwise fills a 16-byte workspace from the object at +192 with 8.0f, hands it to a second callee through +96, calls a third, then stores 300 at +304. */
void follower_start_push_from_target_pal(char *follower)
{
    V4_Fb6552688 buf;
    char *motion;

    motion = func_002ED688_1(follower);
    if (motion == 0)
        return;
    func_00282F20_10(&buf, follower + 192, 8.0f);
    func_00282CC0_26(motion + 96, &buf, follower + 16);
    follower_clamp_push_vector(follower);
    *(int *)(motion + 304) = 250;
}

