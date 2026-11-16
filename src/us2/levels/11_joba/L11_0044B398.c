#include "common.h"
#include "include_asm.h"

typedef int TI128 __attribute__((mode(TI)));

extern void arena_add_waiting_fighter(s32 a0, int a1);
extern void security_robot_destroy_held_item(char *self, TI128 *pos);
extern void security_robot_deactivate(char *a0);
extern void mem_clear(char *a0, int a1, int a2);
extern void AttachManipulator(char *a0, int a1, char *a2);
extern void vec_random_direction(void *a0, float f12, float f13);
extern void part_spawn_masked_debris(char *a0, int a1, void *a2, float f12, float f13, float f14,
                        float f15, int a3);
extern void moby_set_anim_type_three(char *a0, int a1, int a2);
extern void part_queue_moby_for_glow(char *a0, int a1, char *a2);

/* func_US2_L11_0044B398, the USA v2.00 copy of func_L11_00449970: the same C, and it also clears
   the 0x1000 flag of the halfword at 0x34. */
/* Kills the security robot, then either resets it right away or schedules the reset. (USA v2.00) */
void security_robot_kill_us2(char *object, int skip_fade, int reset_now)
{
    char *state = *(char **)(object + 0x68);
    char *rig;
    TI128 vec;
    float epsilon;

    *(s32 *)(state + 0x20) = 0;
    if (*(s16 *)(state + 0x366) == 1)
        arena_add_waiting_fighter(*(s32 *)(object + 0xB8), 0xD98);
    *(s16 *)(state + 0x366) = 0;
    *(s32 *)(state + 0x350) = 0;
    if (*(s32 *)(state + 0x354) != 0) {
        vec = *(TI128 *)((char *)(long)*(s32 *)(state + 0x354) + 0x10);
        security_robot_destroy_held_item(object, &vec);
    }
    if (*(u8 *)(state + 0x2B1) == 0) {
        rig = state + 0x2B0;
        mem_clear(rig, 0, 0x40);
        AttachManipulator(object, 3, rig);
        epsilon = 1.0e-4f;
        *(u8 *)(state + 0x2B2) = 1;
        *(f32 *)(state + 0x2D8) = epsilon;
        *(f32 *)(state + 0x2D4) = epsilon;
        *(f32 *)(state + 0x2D0) = epsilon;
        vec_random_direction((char *)&vec, 1.0f / 60.0f, 0.0500000045f);
        part_spawn_masked_debris(object, 0x20, (char *)&vec, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
    }
    *(s32 *)(object + 0x98) = 0;
    *(u16 *)(object + 0x34) &= 0xEFFF;
    if (skip_fade == 0)
        moby_set_anim_type_three(object, 0, -1);
    if (reset_now == 0)
        part_queue_moby_for_glow(object, 0, (char *)security_robot_deactivate);
    else
        security_robot_deactivate(object);
}
