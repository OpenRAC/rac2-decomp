#include "common.h"

extern u8 *func_0029EFD0(s32);
extern f32 func_002A7940(void);
extern void func_002A7470(u8 *, s32, s32, s32);
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
u8 *func_L01_003DA300(u8 *spawnPosition, u8 *targetPosition, u8 *ownerHandle, f32 weight)
{
    u8 *newMoby;
    struct SpawnState *state;

    newMoby = CreateMoby(0xB24 /* moby class 2852 */);
    if (newMoby != 0) {
        *(u8 *)(newMoby + 0x30) = 0xFF;
        *(u16 *)(newMoby + 0x32) = 0xFF;
        *(u8 *)(newMoby + 0x31) = 1;
        *(u8 *)(newMoby + 0x20) = 0;
        state = *(struct SpawnState **)(newMoby + 0x68);
        *(f32 *)(newMoby + 0xF8) = RandomAngle();
        *(f32 *)(newMoby + 0xF4) = RandomAngle();
        *(f32 *)(newMoby + 0xF0) = RandomAngle();
        *(f32 *)(newMoby + 0x2C) = *(f32 *)(*(u8 **)(newMoby + 0x24) + 0x24) * D_L01_001B0828;
        state->handle = ownerHandle;
        state->weight = weight;
        qcopy(newMoby + 0x10, spawnPosition);
        qcopy(&state->position, targetPosition);
        if (*(u8 *)(newMoby + 0x43) != 0)
            StartAnimationBlended(newMoby, 0, 0, 0xA);
    }
    return newMoby;
}
