#include "include_asm.h"

#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void arena_add_waiting_fighter(s32 a0, int a1);
extern void mem_clear(char *a0, int a1, int a2);
extern void security_robot_destroy_held_item_pal(char *self, TI128 *pos);
extern void AttachManipulator(char *a0, int a1, char *a2);
extern void vec_random_direction(void *a0, float f12, float f13);
extern void part_spawn_masked_debris_pal(char *a0, int a1, void *a2, float f12, float f13, float f14,
                              float f15, int a3);
extern void moby_set_anim_type_three_pal(char *a0, int a1, int a2);
extern void part_queue_moby_for_glow(char *a0, int a1, char *a2);
void security_robot_deactivate(char *a0);

/* func_PAL_L11_0044F420, the PAL copy of func_L11_00449970: the same C, where 1/60 and 0.05 become
   0.02 and 0.06 and the object's flag bit 0x1000 (halfword +0x34) is also cleared.
   The moby's death path: clears the spawn flags, hands the last position to the scene
   manager, resets the 0x2B0 rig and leaves the object in its dead state. */
void security_robot_kill_pal(char *object, int skip_anim, int deactivate_now)
{
    char *state = *(char **)(object + 0x68);
    char *rig;
    TI128 vector;
    float rig_scale;

    *(s32 *)(state + 0x20) = 0;
    if (*(s16 *)(state + 0x366) == 1)
        arena_add_waiting_fighter(*(s32 *)(object + 0xB8), 0xD98);
    *(s16 *)(state + 0x366) = 0;
    *(s32 *)(state + 0x350) = 0;
    if (*(s32 *)(state + 0x354) != 0) {
        vector = *(TI128 *)((char *)(long)*(s32 *)(state + 0x354) + 0x10);
        security_robot_destroy_held_item_pal(object, &vector);
    }
    if (*(u8 *)(state + 0x2B1) == 0) {
        rig = state + 0x2B0;
        mem_clear(rig, 0, 0x40);
        AttachManipulator(object, 3, rig);
        rig_scale = 1.0e-4f;
        *(u8 *)(state + 0x2B2) = 1;
        *(f32 *)(state + 0x2D8) = rig_scale;
        *(f32 *)(state + 0x2D4) = rig_scale;
        *(f32 *)(state + 0x2D0) = rig_scale;
        vec_random_direction((char *)&vector, 0.020000001f, 0.060000002f);
        part_spawn_masked_debris_pal(object, 0x20, (char *)&vector, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
    }
    *(u16 *)(object + 0x34) &= ~0x1000;
    *(s32 *)(object + 0x98) = 0;
    if (skip_anim == 0)
        moby_set_anim_type_three_pal(object, 0, -1);
    if (deactivate_now == 0)
        part_queue_moby_for_glow(object, 0, (char *)security_robot_deactivate);
    else
        security_robot_deactivate(object);
}
