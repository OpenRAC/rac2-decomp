#include "common.h"

extern u8 *CreateMoby(s32);
extern f32 math_random_angle(void);
extern void anim_start_blended(u8 *, s32, s32, s32);
extern f32 D_L01_001B0828 __attribute__((sda));

typedef int SpawnQuad __attribute__((mode(TI)));
/* Measured state prefix; total allocation extent is unspecified. */
struct SpawnState {
    SpawnQuad position;
    u8 *handle;
    u8 unknown14[4];
    f32 weight;
};

/* Creates the 0xB24 object, seeds its state block and copies the two vectors in. */
/* Creates a thrown object, sets up its state and copies the start position and target into it. */
u8 *moby_spawn_thrown_object(u8 *spawn_position, u8 *target_position, u8 *owner_handle, f32 weight)
{
    u8 *new_moby;
    struct SpawnState *state;

    new_moby = CreateMoby(0xB24 /* moby class 2852 */);
    if (new_moby != 0) {
        *(u8 *)(new_moby + 0x30) = 0xFF;
        *(u16 *)(new_moby + 0x32) = 0xFF;
        *(u8 *)(new_moby + 0x31) = 1;
        *(u8 *)(new_moby + 0x20) = 0;
        state = *(struct SpawnState **)(new_moby + 0x68);
        *(f32 *)(new_moby + 0xF8) = math_random_angle();
        *(f32 *)(new_moby + 0xF4) = math_random_angle();
        *(f32 *)(new_moby + 0xF0) = math_random_angle();
        *(f32 *)(new_moby + 0x2C) = *(f32 *)(*(u8 **)(new_moby + 0x24) + 0x24) * D_L01_001B0828;
        state->handle = owner_handle;
        state->weight = weight;
        qcopy(new_moby + 0x10, spawn_position);
        qcopy(&state->position, target_position);
        if (*(u8 *)(new_moby + 0x43) != 0)
            anim_start_blended(new_moby, 0, 0, 0xA);
    }
    return new_moby;
}
