#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
typedef float f32;
extern char *CreateMoby(s32 size);
extern f32 math_random_angle(void);
extern u8 *moby_create_effect_at_position(void *a0, s32 a1);
extern void STUB_printf(void *a0);
extern void moby_mark_spawned(void *a0);
extern u8 g_spinning_object_data[];
typedef int V4 __attribute__((mode(TI)));

/* Creates a new object (moby class 3704) at a position with a start velocity and a random spin; returns it, or 0 if its first setup step fails. */
s32 moby_spawn_spinning_object_pal(void *owner, void *start_pos, void *start_vel, f32 turn_speed, f32 move_speed)
{
    u8 *moby;
    u8 *position;
    u8 *state;
    f32 angle;
    s32 handle;

    moby = (u8 *)CreateMoby(0xE78);
    if (moby != 0) {
        state = *(u8 **)(moby + 0x68);
        position = moby + 0x10;
        *(u8 *)(moby + 0x30) = 0x40;
        *(u8 *)(moby + 0xBC) = 0;
        *(u8 *)(moby + 0x95) = 0;
        *(u8 *)(moby + 0x20) = 0;
        *(u32 *)(state + 0x18) = (u32)owner;
        *(V4 *)position = *(V4 *)start_pos;
        *(V4 *)state = *(V4 *)start_vel;
        *(f32 *)(state + 0x14) = turn_speed * 0.0003490659f;
        *(f32 *)(state + 0x10) = move_speed * 0.00040000002f;
        angle = math_random_angle();
        *(f32 *)(moby + 0xF0) = angle;
        angle = math_random_angle();
        *(f32 *)(moby + 0xF4) = angle;
        angle = math_random_angle();
        *(f32 *)(moby + 0xF8) = angle;
        handle = moby_create_effect_at_position(position, 0);
        *(u32 *)(state + 0x1C) = handle;
        if (handle == 0) {
            STUB_printf(g_spinning_object_data);
            moby_mark_spawned(moby);
            moby = 0;
        }
    }
    return (s32)moby;
}
