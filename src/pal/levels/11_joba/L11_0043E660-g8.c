#include "include_asm.h"

#include "common.h"
extern float g_rotor_timer_step __attribute__((sda));

/* Bleeds the ten rotation timers the level keeps beside its state: each armed
   entry loses a sixtieth of the shared rate and clamps at zero, disarming. */
void rotor_tick_timers_pal(char *obj)
{
    char *state = *(char **)(obj + 0x68);
    int i;

    for (i = 0; i < 10; i++) {
        u8 *armed = (u8 *)(state + 0x380 + i);
        f32 *timer = (f32 *)(state + 0x2F0 + 4 * i);
        if (*armed == 1) {
            f32 left = *timer - g_rotor_timer_step * 0.020000001f;
            *timer = left;
            if (left < 0.0f) {
                *timer = 0.0f;
                *armed = 2;
            }
        }
    }
}

extern int math_random_int_below(int);
extern float g_rotor_aim_motion_speed __attribute__((sda));
extern int g_moby_l11_table;
extern void FastVecSub(void *dst, void *a, void *b);
extern void vec_scale_to_length(void *dst, void *src, float scale);
extern void vec_add_random_offset(float *p, float f);
extern int math_random_int_below(int n);
extern char *arena_get_center_point(char *object);
extern void arena_set_boss_owner(char *object, int value);
extern void InitializeRandomizedObjectMotion(void *a0, void *a1, float f0, float f1);

/* Aims the object at the entry its state names: crosses the entry with the record,
   jitters the result by a random sixtieth and hands it to the level's own helper.
   The table base is read afresh for each of the three groups, which is how retail
   keeps it in the caller-saved registers. */
void rotor_aim_at_entry_pal(char *obj, int index, int flag)
{
    char *state = *(char **)(obj + 0x68);
    char *base1;
    char *base2;
    char *base3;
    int offset = index * 4;
    char *entry;
    float direction[3];
    float strength;
    int random_value;
    int record;

    entry = arena_get_center_point(*(char **)(obj + 0xB8));

    base1 = g_moby_l11_table;
    FastVecSub(direction, entry, ((char *)(base1 + (*(int *)(*(char **)(obj + 0x68) + offset + 0x330) << 8))) + 0x10);
    random_value = math_random_int_below(10) + 15;
    vec_scale_to_length(direction, direction, (float)random_value * (0.020000001f));
    vec_add_random_offset(direction, 0.020000001f);
    random_value = math_random_int_below(5) + 5;
    direction[2] = (float)random_value * (0.020000001f);

    strength = 1.0f - ((float)*(short *)(state + 0x378) - 4.0f) * (1.0f / 6.0f);
    if (strength > 1.0f)
        strength = 1.0f;
    if (strength < 0.0f)
        strength = 0.0f;

    base2 = g_moby_l11_table;
    InitializeRandomizedObjectMotion(((char *)(base2 + (*(int *)(*(char **)(obj + 0x68) + offset + 0x330) << 8))), direction, g_rotor_aim_motion_speed * (0.00040000002f), strength);

    base3 = g_moby_l11_table;
    /* The record's field at 0xB8 takes the object's own handle. */
    *(int *)((char *)((*(int *)(*(char **)(obj + 0x68) + offset + 0x330) << 8) + (int)base3)
            + 0xB8) = *(int *)(obj + 0xB8);
    record = (int)((char *)(base3 + (*(int *)(*(char **)(obj + 0x68) + offset + 0x330) << 8)));
    *(int *)(state + 0x364) = record;
    if (flag != 0)
        arena_set_boss_owner(*(char **)(obj + 0xB8), record);
    else
        arena_set_boss_owner(*(char **)(obj + 0xB8), 0);

    *(unsigned char *)(state + index + 0x380) = 1;
}
